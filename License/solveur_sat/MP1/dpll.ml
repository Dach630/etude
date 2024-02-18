open List

(* fonctions utilitaires *********************************************)
(* filter_map : ('a -> 'b option) -> 'a list -> 'b list
    disponible depuis la version 4.08.0 de OCaml dans le module List :
    pour chaque élément de `list', appliquer `filter' :
    - si le résultat est `Some e', ajouter `e' au résultat ;
    - si le résultat est `None', ne rien ajouter au résultat.
    Attention, cette implémentation inverse l'ordre de la liste *)
let filter_map filter list =
    let rec aux list ret =
        match list with
        | []   -> ret
        | h::t ->
            match (filter h) with
            | None   -> aux t ret
            | Some e -> aux t (e::ret)
    in 
    aux list []
;;

(* print_modele : int list option -> unit
   affichage du résultat *)
let print_modele: int list option -> unit = function
    | None   -> print_string "UNSAT\n"
    | Some modele -> print_string "SAT\n";
    let modele2 = sort (fun i j -> (abs i) - (abs j)) modele in
    List.iter (fun i -> print_int i; print_string " ") modele2;
    print_string "0\n"
;;

(* ensembles de clauses de test *)
let exemple_3_12 = [[1;2;-3];[2;3];[-1;-2;3];[-1;-3];[1;-2]]
let exemple_7_2 = [[1;-1;-3];[-2;3];[-2]]
let exemple_7_4 = [[1;2;3];[-1;2;3];[3];[1;-2;-3];[-1;-2;-3];[-3]]
let exemple_7_8 = [[1;-2;3];[1;-3];[2;3];[1;-2]]
let systeme = [[-1;2];[1;-2];[1;-3];[1;2;3];[-1;-2]]
let coloriage = [[1;2;3];[4;5;6];[7;8;9];[10;11;12];[13;14;15];[16;17;18];[19;20;21];[-1;-2];[-1;-3];[-2;-3];[-4;-5];[-4;-6];[-5;-6];[-7;-8];[-7;-9];[-8;-9];[-10;-11];[-10;-12];[-11;-12];[-13;-14];[-13;-15];[-14;-15];[-16;-17];[-16;-18];[-17;-18];[-19;-20];[-19;-21];[-20;-21];[-1;-4];[-2;-5];[-3;-6];[-1;-7];[-2;-8];[-3;-9];[-4;-7];[-5;-8];[-6;-9];[-4;-10];[-5;-11];[-6;-12];[-7;-10];[-8;-11];[-9;-12];[-7;-13];[-8;-14];[-9;-15];[-7;-16];[-8;-17];[-9;-18];[-10;-13];[-11;-14];[-12;-15];[-13;-16];[-14;-17];[-15;-18]]

(********************************************************************)


(* fonction filtre utilisée dans simplifie int -> int list -> int list option *)
let filtre i clause =
    let rec filtre_aux i clause acc = 
    match clause with 
    | [] -> Some(acc)
    |l :: suite -> if i = l then None else if l = (-i) then (filtre_aux i suite acc) else (filtre_aux i suite ( l :: acc))
    in filtre_aux i clause []
;;


(* simplifie : int -> int list list -> int list list 
    applique la simplification de l'ensemble des clauses en mettant
    le littéral i à vrai *)
let simplifie i clauses =
    filter_map (filtre i) clauses
;;


(* solveur_split : int list list -> int list -> int list option
    exemple d'utilisation de `simplifie' *)
(* cette fonction ne doit pas être modifiée, sauf si vous changez 
    le type de la fonction simplifie *)
let rec solveur_split clauses interpretation =
    (* l'ensemble vide de clauses est satisfiable *)
    if clauses = [] then Some interpretation else
    (* une clause vide est insatisfiable *)
    if mem [] clauses then None else
    (* branchement *) 
    let l = hd (hd clauses) in
    let branche = solveur_split (simplifie l clauses) (l::interpretation) in
    match branche with
    | None -> solveur_split (simplifie (-l) clauses) ((-l)::interpretation)
    | _    -> branche
;;

(* tests *)
 let () = print_modele (solveur_split systeme []) 
 let () = print_modele (solveur_split coloriage []) 

(* solveur dpll récursif *)
    
(* unitaire : int list list -> int
    - si `clauses' contient au moins une clause unitaire, retourne
        le littéral de cette clause unitaire ;
    - sinon, lève une exception `Not_found' *)
let rec unitaire clauses =
    match clauses with
    |[] -> 0 (*failwith "Not_Found"*)
    |[a] :: t -> a
    |h :: t -> unitaire t
;;
      
(* pur : int list list -> int
    - si `clauses' contient au moins un littéral pur, retourne
        ce littéral ;
    - sinon, lève une exception `Failure "pas de littéral pur"' *)
let pur clauses =
    (* int list list -> int list -> int list
    transforma une list list en list avec tout les elements *)
    let rec flat ll r =
        match ll with 
        |[] -> r
        |h :: t -> flat (t)(List.rev_append h r) 
    in
      
    (*int -> int list -> int list -> int list
    ajoute x dans la list dans l'ordre croissant sans doublon *)
    let rec insert x l r =
        match l with 
        |[] -> List.rev (x :: r) 
        |h :: t -> 
            if x = h 
            then List.rev_append r l
            else if (h > x)
            then List.rev_append (x :: r) l
            else insert x t (h :: r) 
    in
      
    (*int list -> int list -> int list
    renvoie une liste croissant sans doublon *)
    let rec sort l r = 
        match l with
        |[] -> r
        |h :: t -> sort t (insert h r [])
    in 
      
    (*int -> int list-> boolean 
    teste si element x est dans liste croissant l *)
    let rec contains x l =
        match l with 
        |[] -> false;
        |h :: t -> 
            if h = x then true 
            else if h > x then false 
            else contains x t 
    in
      
    (*int list -> int -> int
    cherche littéral pur avec une liste de litéraux trié sans doublon *)
    let rec pure l n =
        if n <= 0 then 0 (*failwith "pas de littéral pur"*)
        else
            match l with
            |[] -> 0 (*failwith "pas de littéral pur"*)
            |h :: t ->
                if not(contains (-h) t) then h 
                else pure (List.rev_append(List.rev t) [h]) (n - 1)
    in
    
    let l = sort(flat clauses []) [] in
  
    pure l (List.length l)
;;
  
  
(* int list list -> boolean
    cherche une clause vide*)
let rec vide clausses =
    match clausses with
    |[]-> true
    |[_] -> false 
    |h :: t -> 
        if h = [] then true 
        else vide t
;;
  
(*int list list -> int
    prend la 1ere proposition*)
let prop clausses =
    match clausses with 
    |[hl::tl] -> hl
    |_ -> 0 (* failwith "pas de proposition"*)
;;
  
(* solveur_dpll_rec : int list list -> int list -> int list option *)
let rec solveur_dpll_rec clausses inter =
    if clausses = [] 
    then Some inter 
    else if vide clausses 
    then None
    else 
    let x = unitaire clausses in 
        if x <> 0 
        then solveur_dpll_rec (simplifie x clausses) (x :: inter)
        else 
        let x = pur clausses in
            if x <> 0 
            then solveur_dpll_rec (simplifie x clausses) (x :: inter)
            else 
                let x = prop clausses in
                    if x = 0 
                    then None
                    else 
                    let y = solveur_dpll_rec (simplifie x clausses) (x :: inter) in
                    if y <> None 
                    then y 
                    else solveur_dpll_rec (simplifie (-x) clausses) ((-x) :: inter)
;;
  
(* tests *)
let () = print_modele (solveur_dpll_rec systeme []) 
let () = print_modele (solveur_dpll_rec coloriage []) 
  
let () =
    let clauses = Dimacs.parse Sys.argv.(1) in
    print_modele (solveur_dpll_rec clauses [])
  