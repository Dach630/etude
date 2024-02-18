open String 
open Tree
open Value

let rec noEmptyLine tab acc =
  match tab with 
  |[] -> List.rev acc
  |h :: t -> 
      if h = ""
      then noEmptyLine t acc
      else noEmptyLine t (h :: acc)
;;
          
let rec removeSpace tab acc = 
  match tab with 
  |[] -> List.rev acc
  |h :: t -> 
      if h = ' '
      then removeSpace t acc
      else removeSpace t (h :: acc)
;;
          
let rec removeDot tab acc = 
  match tab with 
  |[] -> List.rev acc
  |h :: t -> 
      if h = ','
      then removeDot t acc
      else removeDot t (h :: acc)
;;

let rec removeDot tab acc = 
  match tab with 
  |[] -> List.rev acc
  |h :: t -> 
      if h = ','
      then removeDot t acc
      else removeDot t (h :: acc)
;;
let rec removePare tab acc=
  match tab with 
  |[] -> List.rev acc
  |h :: t -> 
      if (h = '(' || h = ')')
      then removeDot t acc
      else removeDot t (h :: acc)
;;
  
let explode s = 
  let rec exp s i n acc =
    if n = i 
    then List.rev acc
    else exp s (i + 1) n ((get s i) :: acc )
  in
  exp s 0 (length s) [] 
;;
          
let strList str =
  let ex = explode str in
  let ex1 = removeSpace ex [] in
  removeDot ex1 []
;;

let rec allSymbol str =
  let ex = strList str in
  let ex1 = removeSpace ex [] in
  removeDot ex1 []
;;
let rec reforStr list acc =
  match list with
  |[] -> acc
  |h :: t -> reforStr t (acc ^ (make 1 h))
;;

  
let inp_sym s =
  let subStr = sub s 0 15 in
  if (subStr = "input symbols :")
  then 
    let rest = sub s 15 ((length s)-15) in 
    allSymbol rest 
  else failwith "Not input symbols"
;;

let stack_sym s =
  let subStr = sub s 0 15  in
  if (subStr = "stack symbols :")
  then 
    let rest = sub s 15 ((length s)-15) in 
    allSymbol rest 
  else failwith "Not stack symbols"
;;

let state_sym s =
  let subStr = sub s 0 15  in
  if (subStr = "state symbols :")
  then 
    let rest = sub s 15 ((length s)-15) in 
    allSymbol rest 
  else failwith "Not state symbols"
;;

let ini_state s =
  let subStr = sub s 0 15  in
  if (subStr = "initial state :")
  then 
    let rest = sub s 15 ((length s)-15) in 
    match (allSymbol rest) with
    |[] -> failwith "no init state"
    |h :: t -> h 
  else failwith "Not initial state"
;;

let ini_stack s =
  let subStr = sub s 0 15  in
  if (subStr = "initial stack :")
  then 
    let rest = sub s 15 ((length s)-15) in 
    match (allSymbol rest) with
    |[] -> failwith "no init state"
    |h :: t -> h 
  else failwith "Not initial stack"
;;

let rec allTrans list acc =
  match list with
  |[] -> List.rev_append acc ["end"]
  |h :: t -> allTrans t (h :: acc) 
;;
    

let link s tab =
  let subStr = sub s 0 13 in
  if (subStr = "transition :")
  then allTrans tab []
  else failwith "Not transition"
;;

let read_file filename = 
  let lines = ref [] in
  let chan = open_in filename in
  try
    while true; do
      lines := input_line chan :: !lines
    done; !lines
  with End_of_file ->
    close_in chan;
    List.rev (noEmptyLine !lines [])
;;

let init_global file_name =
  let lines = read_file file_name in
  let rec allPart lines n =
    match lines with
    |[] -> 
        if n <> 6
        then failwith ""
        else ()
    |h :: t ->
        match n with
        |0 -> (ipt_sym := inp_sym h; allPart t 1)
        |1 -> (stk_sym := stack_sym h; allPart t 2)
        |2 -> (ste_sym := state_sym h; allPart t 3)
        |3 -> (it_state := ini_state h; allPart t 4)
        |4 -> (it_stack := ini_stack h; allPart t 5)
        |5 -> (lien := link h t; ())
        |_ -> failwith "too much part for the automate" 
  in
  allPart lines 0
;;

let rec mot spl acc =
  match spl with
  |[] -> failwith "la parenthèse d'une transition n'est pas fermée"
  |";" :: spl -> mot spl acc
  |")" :: spl-> acc
  |x :: spl-> mot spl (acc ^ x) ;;

let rec make_leaf tr spl =
  match spl  with
  |[] -> tr
  |a :: "," :: b :: "," :: c :: "," :: d :: "," :: spl ->
      let rec parcours_arbre tr a b c d  =
        match tr with
        |[] ->
            if (equal b "") then
              tr @ [Node ((int_of_string a),[Leaf (None,c.[0],(int_of_string d),(mot spl ""))])]
            else
              tr @ [Node ((int_of_string a),[Leaf ((Some b.[0]),c.[0],(int_of_string d),(mot spl ""))])]
        |Node (x,y) :: tr ->
            if ((int_of_string a) = x) then
              if (equal b "") then
                [Node (x,y @ [Leaf (None ,c.[0],(int_of_string d),(mot spl ""))])] @ tr
              else
                [Node (x,y @ [Leaf ((Some b.[0]) ,c.[0],(int_of_string d),(mot spl ""))])] @ tr
            else parcours_arbre tr a b c d
      in parcours_arbre tr a b c d
  |_ :: spl -> failwith "structure d'une transition incorrecte" ;;

let rec interpreteur (tr : tree) s i =
  try
    let spl =(split_on_char ' ' (List.nth s i)) in
    match spl with
    |[] -> interpreteur tr s (i + 1)
    |"(" ::spl-> make_leaf tr spl
    |"end" ::spl -> tr
    |_ :: spl-> interpreteur tr s (i+1)
  with e -> raise e
;;


let create () =
  init_global Sys.argv.(2); 
  interpreteur [] !lien 0
;;
  