open Type;;

(* ligne en expresion ici j'utilise des stack pour stocker les operation, les var et l'expresion final
Ici les expresion sont fait de maniére prefix et il peut avoir une longue chaine d'operation
*)
                                                                     
let lineExpr (lines : string list) : expr = 
  let rec lineExpr2 (lines : string list) s1 s2 : expr = 
    match lines with
    |[] -> 
        if((Stack.is_empty s1) && ((Stack.length s2) = 1))
        then Stack.pop s2
        else failwith "erreur syntaxe expresion"
    |h :: t -> 
        match h with 
        |"+" | "-" | "*" | "/" | "%" -> (Stack.push h s1; lineExpr2 t s1 s2)
        | _ ->
            (match String.get h 0 with
             |'0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' -> Stack.push (Num (int_of_string h)) s2
             | _-> Stack.push (Var (h)) s2
            ); 
            if (((Stack.length s1) > 0) && ((Stack.length s2) > 1)) then
              let e1 = Stack.pop s2 in 
              let e2 = Stack.pop s2 in
              let op = Stack.pop s1 in 
              (match op with
               |"+" -> Stack.push (Op(Add,e1,e2)) s2
               |"-" -> Stack.push (Op(Sub,e1,e2)) s2
               |"*" -> Stack.push (Op(Mul,e1,e2)) s2
               |"/" -> Stack.push (Op(Div,e1,e2)) s2
               |"%" -> Stack.push (Op(Mod,e1,e2)) s2
               |_ ->failwith "erreur syntaxe expresion"
              ); 
              lineExpr2 t s1 s2
            else
              lineExpr2 t s1 s2
  in 
  lineExpr2 lines (Stack.create()) (Stack.create())
;;

(*ligne en condition*)
let rec lineCond (lines : string list) l1 : cond = 
  match lines with 
  |h :: t -> 
      (match h with
       |"=" -> ((lineExpr (List.rev l1)), Eq, (lineExpr t))
       |"<>"-> ((lineExpr (List.rev l1)), Ne, (lineExpr t))
       |"<" -> ((lineExpr (List.rev l1)), Lt, (lineExpr t))
       |"<="-> ((lineExpr (List.rev l1)), Le, (lineExpr t))
       |">" -> ((lineExpr (List.rev l1)), Gt, (lineExpr t))
       |">="-> ((lineExpr (List.rev l1)), Ge, (lineExpr t))
       | _ -> lineCond t (h :: l1)
      )
  |_-> failwith"error syntaxe cond"
;; 

(*regare si il y a seulement un element dans la list
utiliser pour le Read
*) 
let onlyhead (list : string list) =
  match list with
  |[h] -> h
  |_ -> failwith "error syntaxe onlyhead"
;;

(*retire le 1er element de la liste pour le Set*)
let noHd list =
  match list with
  | h :: t -> t
  | _ -> []
;; 
(*fonction pour créer le If avec sa conditon, emplacement du If, emplacement actuel, le nombre de tabulation, 
le 1er et le 2nd block,un bool pour savoir si on est dans le else et la lines de ce qui doit lire.
Il renvoie un (int * string list list * (position * instr)) le int et le string list list c'est pour envoyer la position 
ainsi que de ce qui reste a lire, et il renvoie une pair (position * instr) qui sera ensuit mis dans un block
*)



let rec linesIf 
    (condi : cond)
    (lines : (int * string list) list)
    (pos: int)
    (posIf: int) 
    (tab: int) 
    (b1: block)
    (b2: block)
    (inElse : bool)
  :(int * (int * string list) list * (position * instr)) = 
  match lines with
  |[] -> (pos, lines ,(posIf,(If(condi,(List.rev b1), (List.rev b2)))))
  |(nbt, h) :: t -> 
      if(nbt > tab) then failwith "error syntaxe if"
      else 
      if(nbt = tab)then 
        match h with
        |hh :: ht ->
            (match hh with 
             |"COMMENT"-> linesIf condi t pos posIf tab b1 b2 inElse 
             |"READ" -> 
                 if(inElse)
                 then linesIf condi t (pos + 1) posIf tab b1 ((pos, Read (onlyhead ht))::b2) inElse 
                 else linesIf condi t (pos + 1) posIf tab ((pos, Read (onlyhead ht))::b1) b2 inElse  
             |"PRINT" -> if(inElse)
                 then linesIf condi t (pos + 1) posIf tab b1 ((pos, Print (lineExpr ht))::b2) inElse 
                 else linesIf condi t (pos + 1) posIf tab ((pos, Print (lineExpr ht))::b1) b2 inElse
             |"IF" -> 
                 let (posi,reste, prog) = linesIf (lineCond ht []) t (pos + 1) pos (tab + 2) [] [] false in
                 if(inElse) then
                   linesIf condi reste posi posIf tab b1 (prog :: b2) inElse
                 else
                   linesIf condi reste posi posIf tab (prog :: b1) b2 inElse 
             |"WHILE" -> 
                 let (posi, reste, prog) = linesWhile (lineCond ht []) t (pos + 1) pos (tab + 2) [] in
                 if(inElse)
                 then linesIf condi reste posi posIf tab b1 (prog :: b2) inElse
                 else linesIf condi reste posi posIf tab (prog:: b1) b2 inElse
             |other -> 
                 if (List.hd ht = ":=") 
                 then 
                   if(inElse) 
                   then linesIf condi t (pos + 1) posIf tab 
                       b1 ((pos, Set(hh,(lineExpr(noHd ht)))) :: b2) inElse
                   else linesIf condi t (pos + 1) posIf tab 
                       ((pos, Set(hh,(lineExpr(noHd ht)))) :: b1) b2 inElse
                 else failwith "error syntaxe if " 
            )
        |_ -> failwith "error syntaxe if " 
      else 
      if(nbt = (tab - 2)) then 
        match h with
        |"ELSE" :: ht ->
            if(inElse) then failwith "error syntaxe if else 1"
            else 
            if (ht = []) then
              linesIf condi t (pos + 1) posIf tab b1 b2 true
            else failwith "error syntaxe if else 2"
        |_ -> (pos, lines,(posIf,(If(condi,(List.rev b1), (List.rev b2))))) 
      else (pos, lines,(posIf,(If(condi,(List.rev b1), (List.rev b2))))) 
  (*cette fonction et attacher car ils s'appelent mutuellement
il fait la partie While pour program 
il fait presque la même chose que le lineIf sans avoir de 2eme block a faire
*)

and linesWhile 
    (condi : cond)
    (lines : (int * string list) list)
    (pos: int)
    (posWh: int) 
    (tab: int) 
    (b: block)
  :(int * (int * string list) list * (position * instr)) =
  match lines with
  |[] -> (pos, lines,(posWh,(While(condi,(List.rev b)))))
  |(nbt, h) :: t -> 
      if(nbt > tab) then failwith "error syntaxe while" 
      else
      if (nbt < tab) then (pos, lines,(posWh,(While(condi,(List.rev b)))))
      else
        match h with 
        |hh :: ht -> 
            (match hh with 
             |"COMMENT"-> linesWhile condi t pos posWh tab b
             |"READ" -> linesWhile condi t (pos + 1) posWh tab ((pos, Read (onlyhead ht)) :: b)
             |"PRINT" -> linesWhile condi t (pos + 1) posWh tab ((pos, Print (lineExpr ht)) :: b)
             |"IF" -> 
                 let (posi,reste, prog) = linesIf (lineCond ht []) t (pos + 1) pos (tab + 2) [] [] false in 
                 linesWhile condi reste posi posWh tab (prog :: b)
             |"WHILE" -> 
                 let (posi, reste, prog) = linesWhile (lineCond ht []) t (pos + 1) pos (tab + 2) []in 
                 linesWhile condi reste posi posWh tab (prog :: b) 
             |other -> 
                 if (List.hd ht = ":=") then
                   linesWhile condi t (pos + 1) posWh tab 
                     ((pos, Set(hh,(lineExpr(noHd ht)))) :: b)
                 else failwith "error syntaxe while" 
            )    
        |_ -> failwith "error syntaxe while" 
;;


(*crée un program avec sa position*)
let rec linesBlock (lines : (int * string list) list) (p: int) (r : program) :program = 
  match lines with
  |[] -> List.rev r
  |(tb, h) :: t -> 
      match h with
      |[] -> List.rev r
      |hh :: ht -> 
          match hh with
          |"COMMENT" -> linesBlock t p r 
          |"READ" -> linesBlock t (p + 1) ((p, Read (onlyhead ht)) :: r)
          |"PRINT" -> linesBlock t (p + 1) ((p, Print(lineExpr ht)) :: r) 
          |"IF" -> 
              let (posi,reste, prog) = linesIf (lineCond ht []) t (p + 1) p 2 [] [] false in 
              linesBlock reste posi (prog :: r) 
          |"WHILE" -> 
              let (posi, reste, prog) = linesWhile (lineCond ht []) t (p + 1) p 2 [] in
              linesBlock reste posi (prog :: r) 
          |_ ->
              if (List.hd ht = ":=") 
              then linesBlock t (p + 1) ((p, Set(hh,(lineExpr(noHd ht)))) :: r)
              else failwith "error syntaxe linesBlock" 
;; 



(*lit le fichier ligne par ligne et stock ces lignes dans une list
split chaque ligne par ' ' pour l'analyser dans linesBlock*) 
let read_polish (filename:string) : program = 
  try 
    let lines = ref [] in
    let file = open_in filename in 
    try
      while true; do 
        lines := input_line file :: !lines
      done; []
    with 
    |End_of_file -> 
        close_in file; 
        let rec nbTab list res n =
          match list with
          |[] ->
              if (res = []) then (-1,[])
              else (n, List.rev res)
          |h :: t -> 
              if (h = "") then nbTab t res (n + 1)
              else nbTab t (h :: res) n 
        in
        let rec sll list res =
          match list with
          |[]-> res
          |h :: t -> let (tab,prog) = (nbTab (String.split_on_char ' ' h) [] 0) in
              if tab = -1 
              then sll t res
              else sll t ((tab,prog) :: res)
        in
        linesBlock (sll !lines  []) 1 [] 
    |_ -> failwith "read file" 
  with _ -> failwith "open file"
;;
