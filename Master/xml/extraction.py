import csv

# extraction des informations dans le fichier csv 
def extract_couple(filename, header1="", header2="", header3="", header_offset=1):
    fd = open(filename, "r")

    csvreader = csv.reader(fd)
    # On avance de header_offset ligne(s) pour dépasser le header
    for i in range(header_offset):
        header = next(csvreader)
    #print(header)

    #src_id = header.index("source_node_id")
    #target_id = header.index("target_node_id")

    src_id = header.index(header1)
    target_id = header.index(header2)
    other_id = 0

    if header3 != "":
        other_id = header.index(header3)

    couples = []

    for line in csvreader:
        if line[src_id] != "" and header3 == "":
            # récupération des liens
            couples.append([line[src_id], line[target_id]])
        elif header3 != "":
            # récupération des id, noms et nb enfants
            couples.append([line[src_id], line[target_id], line[other_id]])

    fd.close()

    return couples

def write_xml(links, nodes, filename="treeoflife.xml"):
    g = "\""
    n = "\n"
    tab = "\t"
    
    # ouverture en overwriting pour reset le XML et laisser un fichier vide prêt pour réécriture
    reset = open(filename, "w")
    reset.write("")
    reset.close()
    
    output = open(filename, "a")
    output.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>" + n)
    output.write("<root>" + n)
    prof = 1
    
    # Writes data (nodes informations)
    output.write(addtab(prof, tab) + "<data>" + n)
    prof = prof + 1
    
    for noeud in nodes:
        output.write(addtab(prof, tab) + "<node id=" + g + noeud[0] + g + " name=" + g + noeud[1] + g + " children=" + g + noeud[2] + g + "/>" + n)
        """prof = prof + 1
        output.write(addtab(prof, tab) + "<name>" + noeud[1] + "</name>" + n)
        prof = prof - 1
        output.write(addtab(prof, tab) + "</node>" + n)"""
        
    prof = prof - 1
    output.write(addtab(prof, tab) + "</data>" + n)
    
    # Writes tree information
    output.write(addtab(prof, tab) + "<tree>" + n)
    prof = prof + 1
    
    # écriture de l'arbre selon les infos extraites
    write_node_start(output, links)

    output.write(addtab(prof, tab) + "<treeinfo leaves=" + g + str(nbleaf) + g + " depthMax=" + g + str(depthmax) + g + "/>" + n)
    
    prof = prof - 1
    output.write(addtab(prof, tab) + "</tree>" + n)
    
    output.write("</root>" + n)
    
    output.close()
    

# returns the amount of tabulation we want
def addtab(n, tab):
    tmp = ""
    for i in range(n):
        tmp = tmp + tab
    
    return tmp

# fd fichier a ecrire
#index de lecture dans list links
# depth profondeur actuelle (debut : 1)
#actualnode 
#return 0 = fin fichier
#return 1 = fichier en cours de lecture
nbleaf = 0
depthmax = 0
def write_node_start(fd, links):
    if(len(links) == 0):
        return
    write_node(fd, 0, links, 1, int(links[0][0]))
    

def write_node(fd, index, links, depth, node):
    if index > len(links):   
        return index
    global depthmax
    global nbleaf
    depthmax = max(depth, depthmax)
    fd.write(addtab(depth + 1, "\t") + "<node idref=\"" + str(node) + "\"" + " nbLeavesPassed=\"" + str(nbleaf) + "\"")
    child = False
    while (index < len(links)):
        if(node != int(links[index][0])):
            if(not child):
                nbleaf = nbleaf + 1
                fd.write("/>\n")
            else:
                fd.write(addtab(depth + 1, "\t")+"</node>\n")
            return index
        else: #(node == int(links[index][0]))
            if(not child):
                child = True
                fd.write(">\n")
            index = write_node(fd, index+1, links, depth+1, int(links[index][1]))
    if(not child):
        nbleaf = nbleaf + 1
        fd.write("/>\n")
    else:
        fd.write(addtab(depth + 1, "\t")+"</node>\n")
    return index
    
    
def main():
    #links_csv = input("Entrez le nom du fichier csv des liens : ")
    #nodes_csv = input("Entrez le nom du fichier csv des noeuds : ")
    output_name = input("Entrez le nom du fichier de sortie voulu (taper la touche 'entrer' pour le nom par défaut) : ")
    
    links_csv = "treeoflife_links.csv"
    nodes_csv = "treeoflife_nodes.csv"

    links = extract_couple(links_csv, "source_node_id", "target_node_id")
    #print(len(links))
    nodes = extract_couple(nodes_csv, "node_id", "node_name", "child_nodes")
    
    #print(links)
    #print(nodes)

    if output_name.rstrip() != "":
        write_xml(links, nodes, output_name.rstrip() + ".xml")
    else:
        write_xml(links, nodes)
    
    #write_xml(links, nodes)
    #write_xml(links, nodes, "test.xml")
    
    print("nbleaf : " + str(nbleaf))
    print("depthmax:" + str(depthmax))


if __name__ == "__main__":
    main()
