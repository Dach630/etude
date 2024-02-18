module Names = Map.Make(String)
open Type;;

(*récupere les variables non initialisé de l'expression*)
let rec vars_expr (ex :expr) res =
  match ex with
  |Num(n) -> res
  |Var(v) -> 
      if (Names.mem v res)
      then res
      else Names.add v "not_init" res
  |Op(op, ex1, ex2) -> 
      let res2 = vars_expr ex1 res in
      vars_expr ex2 res2
;;

(*récupere les variables non initialisé de la condition*)
let vars_cond (condi : cond) res = 
  let (ex1, com, ex2) = condi in
  let res2 = vars_expr ex1 res in
  vars_expr ex2 res2
;;

(*Les mp_1 et mp_2 n'ont aucun clés en commun avec res, res est le map qui contient toutes les variables 
  fusionne les 2 premier map pour touver les variables initialisées du If et Else 
  et ajoute la fusion au map final
*)
let vars_union mp_1 mp_2 res=
  let res2 = Names.union 
      (fun k info1 info2 ->
         if info1 = "init" && info2 = "init" 
         then Some("init")
         else Some("not_init")) 
      mp_1 mp_2 in
  Names.union 
    (fun k info1 info2 ->
       if info1 = "init" && info2 = "init" 
       then Some("init")
       else Some("not_init"))  
    res2 res
;;
let vars_print_init key pass = 
  if(pass = "init") then
    print_string(key ^ " ")
;;
let vars_print_nInit key pass = 
  if(pass = "not_init") then
    print_string(key ^ " ")
;;

(*affiche les variables initialiséses et les variables utilisées non initialisées*)
let vars_polish (p : program) : unit = 
  (*recherche des variable dans les boucles*)
  let rec vars_b (p : program) tmp res = 
    match p with
    |[] ->(tmp, res)
    |(pos, ins) :: t -> 
        match ins with
        |Set (n, ex) -> 
            if (Names.mem n res) || (Names.mem n tmp)
            then vars_b t tmp res
            else vars_b t (Names.add n "init" tmp) res
        |Read (n) ->
            if (Names.mem n res) || (Names.mem n tmp)
            then vars_b t tmp res
            else vars_b t (Names.add n "init" tmp) res
        |Print (ex) ->
            let res2 = vars_expr ex res in
            vars_b t tmp res2
        |If (condi, b1, b2) -> 
            let res2 = vars_cond condi res in
            let (tmp3, res3) = vars_b b1 Names.empty res2 in
            let (tmp4, res4) = vars_b b2 Names.empty res3 in 
            let res5 = vars_union tmp3 tmp4 res4 in
            vars_b t tmp res5
        |While (condi, b) -> 
            let res2 = vars_cond condi res in
            let (tmp3, res3) = vars_b b Names.empty res2 in
            let res4 = vars_union tmp3 Names.empty res3 in
            vars_b t tmp res4
  in
  (*recherche des variables hors boucle*)
  let rec vars (p : program) res = 
    match p with
    |[] -> res
    |(pos, ins) :: t -> 
        match ins with
        |Set (n, ex) -> 
            if (Names.mem n res)
            then vars t res
            else vars t (Names.add n "init" res)
        |Read (n) ->
            if (Names.mem n res)
            then vars t res
            else vars t (Names.add n "init" res)
        |Print (ex) ->
            let res2 = vars_expr ex res in
            vars t res2
        |If (condi, b1, b2) -> 
            let res2 = vars_cond condi res in
            let (tmp3, res3) = vars_b b1 Names.empty res2 in
            let (tmp4, res4) = vars_b b2 Names.empty res3 in 
            let res5 = vars_union tmp3 tmp4 res4 in
            vars t res5
        |While (condi, b) -> 
            let res2 = vars_cond condi res in
            let (tmp3, res3) = vars_b b Names.empty res2 in
            let res4 = vars_union tmp3 Names.empty res3 in
            vars t res4
  in
  let res = vars p Names.empty in 
  Names.iter vars_print_init res;
  print_string("\n");
  Names.iter vars_print_init res 
;;