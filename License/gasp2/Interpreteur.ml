open String
open Tree

let rec inter mot pointer pile state (tr : tree) =
  if ((pointer <= (length mot)) && (not (equal pile ""))) then
    match tr with
    |[] ->  failwith "il n'y a aucune transition possible\n"
    |Node (a,b) :: tr ->
        if (a = state) then
          let rec nodescan b acc  =
            match b with
            |[] -> failwith "il n'y a aucune transition possible\n"
            |Leaf (Some l,m,n,o)  :: b->
                if ((Char.equal (get mot pointer) l) && (Char.equal (get pile ((length pile)-1)) m)) then
                  inter mot (pointer+1) ((sub pile 0 ((length pile)-1)) ^ o) n (Node(a,(acc @ b))::tr)
                else nodescan b ((Leaf (Some l,m,n,o)) :: acc)
            |Leaf (None,m,n,o) :: b ->
                if (Char.equal (get pile ((length pile)-1)) m) then
                inter mot pointer ((sub pile 0 ((length pile)-1)) ^ o) n (Node(a,(acc @ b))::tr)
                else nodescan b ((Leaf (None,m,n,o)) :: acc)
          in nodescan b []
        else inter mot pointer pile state tr
  else if ((pointer = (length mot)) && (equal pile "")) then
    print_string ("Le mot "^mot^" appartient a la grammaire donnee\n")
  else if ((pointer = (length mot)) && (not(equal pile ""))) then
    failwith "l'entree est epuisee sans que la pile soit vide \n"
  else
    failwith "la pile est vide sans que l'entree soit epuisee \n"
;;

(** let test1 = inter "a" 0 "Z" 1 [];;

let test2 = inter "a" 0 "Z" 1 [Node (2,[Leaf (Some 'a','Z',2,"")])];;

let test3 = inter "bac" 0 "Z" 3 [Node (1,[Leaf (Some 'a','Z',1,"ZA");Leaf (Some 'b','Z',1,"ZB");Leaf (Some 'c','Z',2,"Z")])];;*)

let test5 = inter "abcba" 0 "Z" 1 [Node (1,[Leaf (Some 'a','Z',1,"ZA");Leaf (Some 'b','Z',1,"ZB");Leaf (Some 'c','Z',2,"Z"); Leaf (Some 'a','A',1,"AA");Leaf (Some 'b','A',1,"AB");Leaf (Some 'c','A',2,"A");Leaf (Some 'a','B',1,"BA");Leaf (Some 'b','B',1,"BB");Leaf (Some 'c','B',2,"B")]);Node (2,[Leaf (Some 'a','A',2,"");Leaf (Some 'b','B',2,"");Leaf(None,'Z',2,"")])];;

let test6= inter "ab" 0 "Z" 1 [Node (1,[Leaf (Some 'a','Z',2,"Z")]);Node (2,[Leaf (Some 'b','Z',1,"")])];;
