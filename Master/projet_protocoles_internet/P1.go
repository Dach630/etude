package main

import (
	"bytes"
	"crypto/sha256"
	"crypto/tls"
	"encoding/binary"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net"
	"net/http"
	"os"
	"strconv"
	"strings"
	"time"
)

type datagramme struct {
	Id        uint32
	Type      uint8
	Length    uint16
	Body      []byte
	Signature []byte
}

type hellomsg struct {
	Id         uint32
	Type       uint8
	Length     uint16
	Extensions []byte
	Name       []byte
	Signature  []byte
}

const MAX_noeudMerkle_child = 16

const MAX_Big_Files_Chunk = 32

const MAX_Length_Of_File_Name = 32 // octets
// si plus de 32 fils  donc uniquement fils BigFiles
// soit bigfile, soit chunk pas les deus ensembles

// le ogdata est vide si on est un dossier ou un bigfile
// name est utilise pour les dossier, bigfiles et chunk unique (bigfile sans child)

type Node struct {
	Name      []byte
	isDir     bool
	isBigFile bool
	theHash   []byte
	ogData    []byte
	child     []Node
}

// place dans byte
const LEN_ID = 4
const LEN_TYPE = 1
const LEN_LENGTH = 2

const addrUrl = "https://jch.irif.fr:8443/peers/jch.irif.fr/addresses"
const peersUrl = "https://jch.irif.fr:8443/peers/"

const TYPE_NoOp uint8 = 0  // pas effets, à ignorer, length 0 à 1024 octets
const TYPE_Error uint8 = 1 // message erreur, corps peut être lu par un human codé UTF-8
const TYPE_Hello uint8 = 2
const TYPE_PublicKey uint8 = 3
const TYPE_Root uint8 = 4
const TYPE_GetDatum uint8 = 5
const TYPE_NatTraversalRequest uint8 = 6
const TYPE_NatTraversal uint8 = 7
const TYPE_ErrorReply uint8 = 128 // meme sytaxe que error
const TYPE_HelloReply uint8 = 129
const TYPE_PublicKeyReply uint8 = 130
const TYPE_RootReply uint8 = 131
const TYPE_Datum uint8 = 132
const TYPE_NoDatum uint8 = 132

const BLOCK_Length = 1024
const MAX_File_in_Dir = 16
const MAX_Big_File = 32

var id_actuel uint32 = 0
var connection []int
var connectedPair []string
var connectedPairsdst []*net.UDPAddr

const dossier = "mygame"

func test() {
	//liste de pairs
	allAddr := strings.Split(readmsg(addrUrl), "\n")
	fmt.Println(allAddr[0])

	msg := getallpairs()
	fmt.Println(msg)
	sp := strings.Split(msg, "\n")
	for i := 0; i < (len(sp) - 1); i++ {
		//adresses de pairs
		fmt.Println(sp[i])
		msg = getaddressespairs(sp[i])
		fmt.Println("adresses : " + string(msg))

		//recherche de clé publique
		//imprime [] si le pair est connu mais qu'on a pas de clé publique
		key := getkey(sp[i])
		fmt.Print("cle publique : ")
		fmt.Println(key)
		// a voir le port

		//recherches de racines
		root := getroot(sp[i])
		fmt.Print("root : ")
		fmt.Println(root)
		fmt.Print("\n")

	}

	conn, err := net.ListenPacket("udp", ":8087")
	if err != nil {
		log.Fatal("listen :", err)
	}

	defer conn.Close()
	dst, err := net.ResolveUDPAddr("udp", allAddr[0])
	if err != nil {
		conn.Close()
		log.Fatal("resolve :", err)
	}

	msg2 := makeHello("Gaspard")
	sendMsg(conn, dst, msg2)
	fmt.Println("Hello envoyé...")

	//todo
	msgReply := make([]byte, 1500)
	isHelloReply := false
	//boucle où on renvoit le hello tant qu'on n'a pas reçu de helloreply
	for !isHelloReply {
		_, _, err := conn.ReadFrom(msgReply)
		if err != nil {
			fmt.Println(err)
		}
		if msgReply[4] == 129 {
			isHelloReply = true
			fmt.Print("HelloReply reçu !\n\n")
		} else {
			fmt.Println("erreur, renvoi du Hello...")
			sendMsg(conn, dst, msg2)
		}
	}

	//on lit la requete Publickey du serveur
	_, _, err = conn.ReadFrom(msgReply)
	if err != nil {
		fmt.Println(err)
	}

	if msgReply[4] == 3 {
		fmt.Println("demande de clé recue")
		//on répond à la requête
		MessageReply(conn, dst, msgReply, TYPE_PublicKeyReply)
		fmt.Println("cle envoyée")
	}
}

//todo : envoyer la racine + faire une loop qui gère les demandes du client et les requêtes venant d'autres pairs

/*conn, err := net.Dial("udp", allAddr[0])
	if err != nil {
		log.Fatalln(err)
	}
	defer msg.Body.Close()
	body, err := io.ReadAll(msg.Body)
	if err != nil {
		log.Fatalln(err)
	}
	return (string(body))
}*/

func readmsg(url string) string {
	transport := http.DefaultTransport.(*http.Transport)
	transport.TLSClientConfig = &tls.Config{InsecureSkipVerify: true}
	client := &http.Client{
		Transport: transport,
		Timeout:   5 * time.Second,
	}
	msg, err := client.Get(url)
	if err != nil {
		log.Fatalln(err)
	}
	defer msg.Body.Close()
	body, err := io.ReadAll(msg.Body)
	if err != nil {
		log.Fatalln(err)
	}
	return (string(body))
}

func sendMsg(conn net.PacketConn, dst *net.UDPAddr, msg []byte) {
	_, err := conn.WriteTo(msg, dst)
	if err != nil {
		conn.Close()
		log.Fatal("write :", err)
	}
}

func MsgCommonPart(txt string, typeMsg uint8) []byte {
	if len([]byte(txt)) > 32767 {
		log.Fatal("message trop long")
	}

	var msg []byte

	idMsg := make([]byte, 4)
	binary.BigEndian.PutUint32(idMsg, id_actuel)
	id_actuel = id_actuel + 1

	msg = append(msg, idMsg...)

	msg = append(msg, typeMsg)

	lenMsg := make([]byte, 2)
	binary.BigEndian.PutUint16(lenMsg, uint16(len(txt)))

	msg = append(msg, lenMsg...)

	msg = append(msg, txt...)
	return msg
}

// le message Hello ayant un format particulier, on le fait ici (voir 5.1.3)
func makeHello(name string) []byte {
	var msg = MsgCommonPart(name, TYPE_Hello)
	txtMsg := []byte(name)
	length := uint16(len(txtMsg))
	ExtensionMsg := make([]byte, 4)
	signature := make([]byte, 0)

	for i := 0; i < 4; i++ {
		msg = append(msg, ExtensionMsg[i])
	}

	for i := 0; i < int(length); i++ {
		msg = append(msg, txtMsg[i])
	}
	//todo
	for i := 0; i < len(signature); i++ {
		msg = append(msg, signature[i])
	}

	return msg
}

// Protocole pair-à-pair
func msgP2P(txt string, typeMsg uint8) []byte {
	var msg = MsgCommonPart(txt, typeMsg)

	txtMsg := []byte(txt)
	signature := make([]byte, 0)

	for i := 0; i < len(txtMsg); i++ {
		msg = append(msg, txtMsg[i])
	}
	//todo
	for i := 0; i < len(signature); i++ {
		msg = append(msg, signature[i])
	}

	return msg
}

// Même chose que pour le makeHello
// je ferais plus tard un if, si on reçoit un Hello on utilisera cette fonction, sinon celle en dessous
func Helloreply(conn net.PacketConn, dst *net.UDPAddr, msg []byte) {
	var reply []byte
	txtMsg := []byte("Gaspard")
	message := hellomsg{
		//l'id d'une réponse est le même id que celui qui était dans le message reçu
		//référence : début de la partie 5
		Type:       TYPE_HelloReply,
		Length:     uint16(len(txtMsg)),
		Extensions: make([]byte, 4),
		Name:       txtMsg,
		Signature:  make([]byte, 0), //[]byte{},
	}

	for i := 0; i < 4; i++ {
		reply = append(reply, msg[i])
	}

	reply = append(reply, message.Type)

	lenMsg := make([]byte, 2)
	binary.BigEndian.PutUint16(lenMsg, message.Length)
	for i := 0; i < 2; i++ {
		reply = append(reply, lenMsg[i])
	}

	for i := 0; i < 4; i++ {
		reply = append(reply, message.Extensions[i])
	}

	for i := 0; i < int(message.Length); i++ {
		reply = append(reply, message.Name[i])
	}

	reply = append(reply, 0)
	sendMsg(conn, dst, reply)
}

func MessageReply(conn net.PacketConn, dst *net.UDPAddr, msg []byte, Type uint8) {
	var reply []byte
	txtMsg := []byte("")
	message := datagramme{
		//l'id d'une réponse est le même id que celui qui était dans le message reçu
		Type:      Type,
		Length:    uint16(len(txtMsg)),
		Body:      txtMsg,
		Signature: make([]byte, 0), //[]byte{},
	}

	for i := 0; i < 4; i++ {
		reply = append(reply, msg[i])
	}
	reply = append(reply, message.Type)

	lenMsg := make([]byte, 2)
	binary.BigEndian.PutUint16(lenMsg, message.Length)
	for i := 0; i < 2; i++ {
		reply = append(reply, lenMsg[i])
	}

	reply = append(reply, 0)

	for i := 0; i < len(message.Signature); i++ {
		reply = append(reply, message.Signature[i])
	}
	sendMsg(conn, dst, reply)
}

// 4.1 addresses de tout les pairs
func getallpairs() string {
	return (readmsg(peersUrl))
}

// 4.2 addresses de pairs
func getaddressespairs(p string) string {
	return (readmsg(peersUrl + p + "/addresses"))
}

// 4.3 recherche de clés
func getkey(p string) []byte {
	transport := http.DefaultTransport.(*http.Transport)
	transport.TLSClientConfig = &tls.Config{InsecureSkipVerify: true}
	client := &http.Client{
		Transport: transport,
		Timeout:   5 * time.Second,
	}
	msg, err := client.Get(peersUrl + p + "/key")
	if err != nil {
		log.Fatalln(err)
	}
	defer msg.Body.Close()
	body, err := io.ReadAll(msg.Body)
	if err != nil {
		log.Fatalln(err)
	}
	return (body)
}

// 4.4 recherche de racines
func getroot(p string) []byte {
	transport := http.DefaultTransport.(*http.Transport)
	transport.TLSClientConfig = &tls.Config{InsecureSkipVerify: true}
	client := &http.Client{
		Transport: transport,
		Timeout:   5 * time.Second,
	}
	msg, err := client.Get(peersUrl + p + "/root")
	if err != nil {
		log.Fatalln(err)
	}
	defer msg.Body.Close()
	body, err := io.ReadAll(msg.Body)
	if err != nil {
		log.Fatalln(err)
	}
	return (body)
}

func pairSelect() int {
	fmt.Println("Choisissez un pair :")
	msg := readmsg(peersUrl)
	sp := strings.Split(msg, "\n")
	for i := 0; i < (len(sp) - 1); i++ {
		fmt.Printf("%d.%s\n", i, sp[i])
	}
	var pair string
	fmt.Scanln(&pair)
	number, err := strconv.Atoi(pair)
	if err != nil {
		return -1
	}
	return number
}

func repeatHello(conn net.PacketConn, dst *net.UDPAddr) {
	msgReply := make([]byte, 1500)
	t := time.NewTimer(30 * time.Second)
	for {
		<-t.C
		msg2 := makeHello("Gspard")
		sendMsg(conn, dst, msg2)
		t.Reset(30 * time.Second)
		for i := 0; i < len(connectedPairsdst); i++ {
			if connection[i] == 0 {
				connectedPair[i] = connectedPair[len(connectedPair)-1]
				connectedPair = connectedPair[:len(connectedPair)-1]
				/*connectedPairsconn[i] = connectedPairsconn[len(connectedPairsconn)-1]
				connectedPairsconn = connectedPairsconn[:len(connectedPairsconn)-1]*/
				connectedPairsdst[i] = connectedPairsdst[len(connectedPairsdst)-1]
				connectedPairsdst = connectedPairsdst[:len(connectedPairsdst)-1]
				connection[i] = connection[len(connection)-1]
				connection = connection[:len(connection)-1]
				i = 0
			} else {
				sendMsg(conn, connectedPairsdst[i], msg2)
				_, _, err := conn.ReadFrom(msgReply)
				if err != nil {
					conn.Close()
					log.Fatal(err)
				}
				if msgReply[4] == TYPE_HelloReply {
					connection[i] = 3
				} else {
					connection[i] -= 1
				}
			}
		}
	}
}

func listenForHellos(conn net.PacketConn, sp []string) {
	msg := make([]byte, 1500)
	_, _, err := conn.ReadFrom(msg)
	if err != nil {
		conn.Close()
		log.Fatal(err)
	}
	if msg[4] == TYPE_Hello {
		name := string(msg[8 : msg[7]+8])
		var newdst *net.UDPAddr
		for i := 0; i < len(sp); i++ {
			if name == sp[i] {
				adr := getaddressespairs(name)
				adrlist := strings.Split(adr, "\n")
				newdst, err = net.ResolveUDPAddr("udp", adrlist[0])
				if err != nil {
					conn.Close()
					log.Fatal("resolve :", err)
				}
				Helloreply(conn, newdst, msg)
				break
			}
		}
		b := false
		for i := 0; i < len(connectedPairsdst); i++ {
			if connectedPairsdst[i] == newdst {
				b = true
				connection[i] = 3
				break
			}
		}
		if !b {
			connectedPairsdst = append(connectedPairsdst, newdst)
			connection = append(connection, 3)
			go requestreplier(conn, newdst)
		}
	}
}

func mainloop(sp []string, conn net.PacketConn, dst *net.UDPAddr) {
	msgReply := make([]byte, 1500)
	for {

		fmt.Println("Quel opération voulez-vous effectuez ?")
		fmt.Println("Client-serveur :")
		fmt.Println("	0.Rafraichir la liste de pairs")
		fmt.Println("	1.Adresses de pairs")
		fmt.Println("	2.Recherche de clés")
		fmt.Println("	3.Recherche de racines")
		fmt.Println("Pair-à-pair :")
		fmt.Println("	4.Requête vide")
		fmt.Println("	5.Envoi d'un Hello")
		fmt.Println("	6.Transfert de clés")
		fmt.Println("	7.Transfert de racines")
		fmt.Println("	8.Transfert de données")
		fmt.Println("9.Sortir")
		fmt.Print("Votre réponse : ")

		var request string
		fmt.Scanln(&request)
		switch request {

		case "0":
			msg := readmsg(peersUrl)
			fmt.Println("Liste des pairs actuels : ")
			sp = strings.Split(msg, "\n")
			fmt.Println(msg)

		case "1":
			pair := pairSelect()
			if pair == -1 {
				fmt.Println("Format incorrect, veuillez réessayer")
			} else {
				msg := readmsg(peersUrl)
				sp = strings.Split(msg, "\n")
				if pair >= 0 && pair < len(sp) {
					addresse := getaddressespairs(sp[pair])
					fmt.Println("adresse : " + addresse)
				} else {
					fmt.Println("Pair inexistant, opération annullée")
				}
			}

		case "2":
			pair := pairSelect()
			if pair == -1 {
				fmt.Println("Format incorrect, veuillez réessayer")
			} else {
				msg := readmsg(peersUrl)
				sp = strings.Split(msg, "\n")
				if pair >= 0 && pair < len(sp) {
					publicKey := getkey(sp[pair])
					fmt.Print("clé : ")
					fmt.Println(publicKey)
				} else {
					fmt.Println("Pair inexistant, opération annullée")
				}
			}

		case "3":
			pair := pairSelect()
			if pair == -1 {
				fmt.Println("Format incorrect, veuillez réessayer")
			} else {
				msg := readmsg(peersUrl)
				sp = strings.Split(msg, "\n")
				if pair >= 0 && pair < len(sp) {
					root := getroot(sp[pair])
					fmt.Print("root : ")
					fmt.Println(root)
				} else {
					fmt.Println("Pair inexistant, opération annullée")
				}
			}

		case "4":
			//requête NoOp
			msgrequest := MsgCommonPart("ignore request", TYPE_NoOp)
			var pair = pairSelect()
			if pair == -1 {
				fmt.Println("Format incorrect, veuillez réessayer")
			} else {
				msg := readmsg(peersUrl)
				sp = strings.Split(msg, "\n")
				if pair >= 0 && pair < len(sp) {
					adr := getaddressespairs(sp[pair])
					adrlist := strings.Split(adr, "\n")
					newdst, err := net.ResolveUDPAddr("udp", adrlist[0])
					if err != nil {
						conn.Close()
						log.Fatal("resolve :", err)
					}
					sendMsg(conn, newdst, msgrequest)
				} else {
					fmt.Println("pair inexistant, veuillez réessayer")
				}
			}

		case "5": //envoi d'un hello à un pair
			msgrequest := makeHello("Gspard")
			var pair = pairSelect()
			if pair == -1 {
				fmt.Println("Format incorrect, veuillez réessayer")
			} else {
				msg := readmsg(peersUrl)
				sp = strings.Split(msg, "\n")
				if pair >= 0 && pair < len(sp) {
					adr := getaddressespairs(sp[pair])
					adrlist := strings.Split(adr, "\n")
					newdst, err := net.ResolveUDPAddr("udp", adrlist[0])
					if err != nil {
						conn.Close()
						log.Fatal("resolve :", err)
					}
					sendMsg(conn, newdst, msgrequest)
					_, _, err = conn.ReadFrom(msgReply)
					fmt.Println(msgReply)
					if err != nil {
						conn.Close()
						log.Fatal(err)
					}
					for msgReply[4] != TYPE_HelloReply {
						if msgReply[4] == TYPE_Error {
							fmt.Println("Une erreur s'est produite,opération annulée")
							break
						}
						fmt.Println("Erreur, renvoi du hello")
						sendMsg(conn, newdst, msgrequest)
						_, _, err = conn.ReadFrom(msgReply)
						if err != nil {
							conn.Close()
							log.Fatal(err)
						}
					}
					b := false
					for i := 0; i < len(connectedPair); i++ {
						if connectedPair[i] == sp[pair] {
							b = true
							fmt.Println("vous êtes déjà connecté à ce pair")
							connection[i] = 3
							break
						}
					}
					if !b {
						fmt.Println("Connexion établie !")
						connectedPair = append(connectedPair, sp[pair])
						//connectedPairsconn = append(connectedPairsconn, conn)
						connectedPairsdst = append(connectedPairsdst, newdst)
						connection = append(connection, 3)
						fmt.Println(connectedPair)
						go requestreplier(conn, newdst)
					}

					//fmt.Println("La connexion avec ce pair n'a pas pu être établie")
				} else {
					fmt.Println("pair inexistant, veuillez réessayer")
				}
			}

		case "6":
			//requête PublicKey à un pair
			msgrequest := MsgCommonPart("", TYPE_PublicKey)
			var pair = pairSelect()
			if pair == -1 {
				fmt.Println("Format incorrect, veuillez réessayer")
			} else {
				msg := readmsg(peersUrl)
				sp = strings.Split(msg, "\n")
				if pair >= 0 && pair < len(sp) {
					//adr := getaddressespairs(sp[pair])
					/*adrlist := strings.Split(adr, "\n")
					newdst, err := net.ResolveUDPAddr("udp", adrlist[0])
					if err != nil {
						conn.Close()
						fmt.Println("ERREUR")
						log.Fatal("resolve :", err)
					}*/
					b := false
					var p int
					for i := 0; i < len(connectedPair); i++ {
						fmt.Println(connectedPair[i])
						if connectedPair[i] == sp[pair] {
							b = true
							p = i
							break
						}
					}
					if !b {
						fmt.Println("Vous n'êtes pas connecté à ce pair, veuillez d'abord lui envoyez un hello")
					} else {
						for msgReply[4] != TYPE_PublicKeyReply {
							fmt.Println("envoi de la demande de clés...")
							fmt.Println(msgrequest)
							sendMsg(conn, connectedPairsdst[p], msgrequest)
							_, _, err := conn.ReadFrom(msgReply)
							fmt.Println(msgReply)
							if err != nil {
								conn.Close()
								log.Fatal(err)
							}
						}
						if msgReply[6] == 64 {
							fmt.Println(msgReply)
						} else {
							fmt.Println("pas de clé")
						}
					}
				} else {
					fmt.Println("pair inexistant, veuillez réessayer")
				}
			}

		case "7":
			msgrequest := MsgCommonPart("", TYPE_Root)
			var pair = pairSelect()
			if pair == -1 {
				fmt.Println("Format incorrect, veuillez réessayer")
			}
			msg := readmsg(peersUrl)
			sp = strings.Split(msg, "\n")
			if pair >= 0 && pair < len(sp) {
				adr := getaddressespairs(sp[pair])
				adrlist := strings.Split(adr, "\n")
				newdst, err := net.ResolveUDPAddr("udp", adrlist[0])
				if err != nil {
					conn.Close()
					log.Fatal("resolve :", err)
				}
				b := false
				for i := 0; i < len(connectedPair); i++ {
					if connectedPair[i] == sp[pair] {
						b = true
						break
					}
				}
				if !b {
					fmt.Println("Vous n'êtes pas connecté à ce pair, veuillez d'abord lui envoyez un hello")
				} else {
					sendMsg(conn, newdst, msgrequest)
					_, _, err = conn.ReadFrom(msgReply)
					if err != nil {
						conn.Close()
						log.Fatal(err)
					}
					if msgReply[4] == TYPE_RootReply {
						fmt.Println("valeur du hash racine reçue")
					}
				}
			} else {
				fmt.Println("pair inexistant, veuillez réessayer")
			}
		case "8":
			fmt.Println("Fin de l'exécution")
			return

		default:
			fmt.Println("Requête inconnue, veuillez réessayer ")
		}
	}
}

func main() {
	n := MakeMerkel()
	printNode(n, "")
	//liste de pairs
	msg := readmsg(peersUrl)
	//fmt.Println(msg)
	sp := strings.Split(msg, "\n")
	/*var addresses string
	for i := 0; i < (len(sp) - 1); i++ {
		//recherches de racines
		/*root := getroot(sp[i])
		fmt.Print("root : ")
		fmt.Println(root)
		fmt.Print("\n")
	}*/
	conn, err := net.ListenPacket("udp", ":8087")
	if err != nil {
		log.Fatal("listen :", err)
	}

	defer conn.Close()
	serveradr := getaddressespairs("jch.irif.fr")
	serveradrlist := strings.Split(serveradr, "\n")
	dst, err := net.ResolveUDPAddr("udp", serveradrlist[0])
	if err != nil {
		conn.Close()
		log.Fatal("resolve :", err)
	}

	msg2 := makeHello("Gspard")
	sendMsg(conn, dst, msg2)
	fmt.Println("Hello envoyé...")

	msgReply := make([]byte, 1500)
	isHelloReply := false
	//boucle où on renvoit le hello tant qu'on n'a pas reçu de helloreply
	for !isHelloReply {
		_, _, err := conn.ReadFrom(msgReply)
		if err != nil {
			conn.Close()
			log.Fatal(err)
		}
		if msgReply[4] == TYPE_HelloReply {
			isHelloReply = true
			fmt.Print("HelloReply reçu !\n\n")
		} else {
			fmt.Println("erreur, renvoi du Hello...")
			sendMsg(conn, dst, msg2)
		}
	}

	//on lit la requete Publickey du serveur
	for msgReply[4] != TYPE_PublicKey {
		_, _, err = conn.ReadFrom(msgReply)
		if err != nil {
			conn.Close()
			log.Fatal(err)
		}
	}
	fmt.Println("demande de clé recue")
	//on répond à la requête
	MessageReply(conn, dst, msgReply, TYPE_PublicKeyReply)
	fmt.Println("clé envoyée")

	for msgReply[4] != TYPE_Root {
		_, _, err = conn.ReadFrom(msgReply)
		if err != nil {
			conn.Close()
			log.Fatal(err)
		}
	}
	fmt.Println("demande de root reçue")
	MessageReply(conn, dst, msgReply, TYPE_RootReply)
	fmt.Println("root envoyée")

	go repeatHello(conn, dst)
	go listenForHellos(conn, sp)
	mainloop(sp, conn, dst)
	//todo : envoyer la racine + faire une loop qui gère les demandes du client et les requêtes venant d'autres pairs
	//timer := time.NewTimer(30 * time.Second)
	//todo : un thread pour gérer la réception de requêtes

}

func requestreplier(conn net.PacketConn, dst *net.UDPAddr) {
	msg := make([]byte, 1500)
	for {
		_, _, err := conn.ReadFrom(msg)
		if err != nil {
			conn.Close()
			log.Fatal(err)
		}

		switch string(msg[4]) {
		case "0":
		case "1":
			MessageReply(conn, dst, msg, TYPE_ErrorReply)
		case "2": //HelloReply
			Helloreply(conn, dst, msg)
		case "3": //PublicKeyReply
			MessageReply(conn, dst, msg, TYPE_PublicKeyReply)
		case "4":
			MessageReply(conn, dst, msg, TYPE_RootReply)
			//TODO case "5" et "6"
		default:
			response := MsgCommonPart("request unknown", TYPE_Error)
			sendMsg(conn, dst, response)
		}
	}
}

/*
type Node struct {
	Name 		string
	isDir 		bool
	isBigFile 	bool
	theHash 	[]byte
	ogData		[]byte
	child 		[]*Node
}
*/

func hashIt(data []byte) []byte {
	hasher := sha256.New()
	hasher.Write(data)
	data = hasher.Sum(nil)
	return data
}

func hashAll(child []Node) []byte {
	var data []byte
	for _, n := range child {
		data = append(data, n.theHash...)
	}
	return hashIt(data)
}

func MerkleFile(data []byte, name []byte) Node {
	piece := len(data) / BLOCK_Length
	if len(data)%BLOCK_Length != 0 {
		piece = piece + 1
	}
	if piece > MAX_Big_Files_Chunk {
		piece := len(data) / MAX_Big_Files_Chunk
		if len(data)%MAX_Big_Files_Chunk != 0 {
			piece = piece + 1
		}
		var allnode []Node
		for i := 0; i < MAX_Big_Files_Chunk; i++ {
			if (i+1)*piece > len(data) {
				n := MerkleFile(data[i*piece:], name)
				allnode = append(allnode, n)
			} else {
				n := MerkleFile(data[i*piece:(i+1)*piece], name)
				allnode = append(allnode, n)
			}
		}

		bigf := Node{
			Name:      name,
			isDir:     false,
			isBigFile: true,
			theHash:   hashAll(allnode),
			ogData:    nil,
			child:     allnode,
		}
		//bigfile
		return bigf
	} else if piece != 1 {
		var chs []Node
		for i := 0; i < piece; i++ {
			if (i+1)*BLOCK_Length > len(data) {
				chunk := Node{
					Name:      name,
					isDir:     false,
					isBigFile: false,
					theHash:   hashIt(data[i*BLOCK_Length:]),
					ogData:    data[i*BLOCK_Length:],
					child:     nil,
				}
				chs = append(chs, chunk)
			} else {
				chunk := Node{
					Name:      name,
					isDir:     false,
					isBigFile: false,
					theHash:   hashIt(data[i*BLOCK_Length : (i+1)*BLOCK_Length]),
					ogData:    data[i*BLOCK_Length : (i+1)*BLOCK_Length],
					child:     nil,
				}
				chs = append(chs, chunk)
			}
		}

		bigf := Node{
			Name:      name,
			isDir:     false,
			isBigFile: true,
			theHash:   hashAll(chs),
			ogData:    nil,
			child:     chs,
		}

		//bigfile
		return bigf
	} else {
		chunk := Node{
			Name:      name,
			isDir:     false,
			isBigFile: false,
			theHash:   hashIt(data),
			ogData:    data,
			child:     nil,
		}

		//chunk
		return chunk
	}
}

func extendPath(path string, dir string) string {
	return path + "/" + dir
}

func MerkleDir(dir string, name []byte) Node {
	allcontents, err := os.ReadDir(dir)
	if err != nil {
		log.Fatal("erreur dir " + dir)
	}
	if len(allcontents) > MAX_File_in_Dir {
		log.Fatal("erreur trop elements " + dir)
	}
	var allChild []Node
	for _, element := range allcontents {
		theName := []byte(element.Name())
		if len(theName) > MAX_Length_Of_File_Name {
			log.Fatal("nom trop long " + element.Name())
		}
		if element.IsDir() {
			node := MerkleDir(extendPath(dir, element.Name()), theName)
			allChild = append(allChild, node)
		} else {
			filecontent, err := ioutil.ReadFile(extendPath(dir, element.Name()))
			if err != nil {
				log.Fatal("erreur lecture " + extendPath(dir, element.Name()))
			}
			node := MerkleFile(filecontent, theName)
			allChild = append(allChild, node)
		}
	}

	res := Node{
		Name:      name,
		isDir:     true,
		isBigFile: false,
		theHash:   hashAll(allChild),
		ogData:    nil,
		child:     allChild,
	}
	return res
}

func MakeMerkel() Node {
	return MerkleDir(dossier, []byte(dossier))
}

func printNode(n Node, decalage string) {
	fmt.Print(decalage)
	fmt.Println(n.Name)
	fmt.Print(decalage)
	fmt.Println(n.isDir)
	fmt.Print(decalage)
	fmt.Println(n.isBigFile)
	fmt.Print(decalage)
	fmt.Println(n.theHash)
	fmt.Println()
	for _, c := range n.child {
		printNode(c, "\t")
	}
}

func makeMsgFromNode(n Node) []byte {
	var msg []byte
	if n.isDir {
		msg = append(msg, byte(2))
		for i := 0; i < len(n.child); i++ {
			msg = append(msg, n.child[i].Name...)
			if len(n.child[i].Name) < MAX_Length_Of_File_Name {
				empty := make([]byte, MAX_Length_Of_File_Name-len(n.child[i].Name))
				msg = append(msg, empty...)
			}
			msg = append(msg, n.child[i].theHash...)
		}
	} else if n.isBigFile {
		msg = append(msg, byte(1))
		for i := 0; i < len(n.child); i++ {
			msg = append(msg, n.child[i].theHash...)
		}
	} else {
		msg = append(msg, byte(0))
		msg = append(msg, n.ogData...)
	}
	return msg
}

func partage(conn net.PacketConn, dst *net.UDPAddr, n Node) {
	// todo formater les messages
	msg := makeMsgFromNode(n)
	sendMsg(conn, dst, msg)
	for _, child := range n.child {
		partage(conn, dst, child)
	}
}

func getRoot() []byte {
	//todo obetenir racine
	var rootHash []byte

	return rootHash
}

func getAll(conn net.PacketConn, dst *net.UDPAddr, path string) {
	rootHash := getRoot()
	getDataDir(conn, dst, path, rootHash, "root")
}

func getDataDir(conn net.PacketConn, dst *net.UDPAddr, path string, hash []byte, name string) {
	msg := msgP2P(string(hash), TYPE_GetDatum)
	sendMsg(conn, dst, msg)
	msgReply := make([]byte, 2000)

	isReply := false
	for !isReply {
		_, _, err := conn.ReadFrom(msgReply)
		if err != nil {
			fmt.Println(err)
		}
		if msgReply[4] == TYPE_Datum {
			isReply = true
		} else if msgReply[4] == TYPE_NoDatum {
			return
		}
	}
	length := binary.BigEndian.Uint16(msg[5:7]) - 32
	data := msg[40 : 40+length]
	if msgReply[39] == 0 { // chunk
		myhash := hashIt(data)
		res := bytes.Equal(myhash, msg[7:39]) // compare les hash
		if !res {
			// todo
			return
		}
		writeInFile(extendPath(path, name), data)
	} else if msgReply[39] == 1 { // tree
		for i := 0; (i * 32) < len(data); i++ {
			getDataDir(conn, dst, path, data[i*32:(i+1)*32], name)
		}
	} else if msgReply[39] == 2 { // directory
		createDirectory(extendPath(path, name))
		for i := 0; (i * 64) < len(data); i++ {
			tmp := data[i*64 : (i+1)*64]
			getDataDir(conn, dst, extendPath(path, name), tmp[32:], string(tmp[0:32]))
		}
	} else {
		//todo
		return
	}
}

func writeInFile(path string, data []byte) {

	_, err := os.Stat(path)
	if os.IsNotExist(err) {
		fichier, err := os.Create(path)
		if err != nil {
			fmt.Println("erreur create "+path, err)
		}
		defer fichier.Close()
	} else if err != nil {
		fmt.Println("erreur stat "+path, err)
	}

	fichier, err := os.OpenFile(path, os.O_WRONLY|os.O_APPEND|os.O_CREATE, 0644)
	if err != nil {
		fmt.Println("erreur ouverture "+path, err)
	}

	n, err := fichier.Write(data)
	if err != nil {
		fmt.Println("erreur ecriture "+path, err)
	}
	if n != len(data) {
		fmt.Println("erreur nombre octet ecriture " + path)
	}
}

func createDirectory(path string) {
	err := os.MkdirAll(path, 0755)
	if err != nil {
		fmt.Println("erreur creation de dossier "+path, err)
	}
}
