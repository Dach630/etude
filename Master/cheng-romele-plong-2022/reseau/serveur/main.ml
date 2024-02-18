(*deroulement du jeu*)


let input ic = 
    (*prend les paquet du joueur et les applique au jeu*)
    failwith("todo")
;;

let output oc =
    (*le programme doit envoyer des paquets sans arret pour mettre a jour l'interface graphique du joueur*)
    failwith("todo")
;;

let game_service ic oc =
	while true do
		let s = input_line ic in
		print_endline s;
		if(s = "QUIT\n") then
			exit 0
		else(
			output_string oc ("TEST\n");
			flush oc
		)
	done
;;

let establish_server server_fun sockaddr =
	let domain = Unix.domain_of_sockaddr sockaddr in
	let sock = Unix.socket domain Unix.SOCK_STREAM 0 in
	Unix.bind sock sockaddr ;
	Unix.listen sock 3;
	print_endline "START\n";
	while true do
		let (s, _) = Unix.accept sock in
		match Unix.fork() with
		|0 -> if Unix.fork() <> 0 then
			exit 0 ;
			let inchan = Unix.in_channel_of_descr s
			and outchan = Unix.out_channel_of_descr s in
			server_fun inchan outchan ;
		       	close_in inchan ;
                       	close_out outchan ;
                       	exit 0
		|id -> Unix.close s; ignore(Unix.waitpid [] id)
      done
;;
let get_my_addr () = (Unix.gethostbyname(Unix.gethostname())).Unix.h_addr_list.(0) ;;

let _ =
	let port =  1400 in
        let mon_adresse = get_my_addr ()in
	print_endline (Unix.string_of_inet_addr mon_adresse);
	establish_server game_service  (Unix.ADDR_INET(mon_adresse, port))
;;