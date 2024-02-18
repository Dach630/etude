open Type;;

(*simplifie l'expression*)
let rec simpl_expr (ex : expr) : expr = 
  match ex with 
  |Op(op, ex1, ex2) -> (
      let x1 = simpl_expr ex1 in
      let x2 = simpl_expr ex2 in
      match x1, x2 with
      |Num(n1), Num(n2) -> (
          match op with
          | Add -> Num(n1 + n2)
          | Sub -> Num(n1 - n2) 
          | Mul -> Num(n1 * n2)
          | Div -> 
              if (n2 = 0) then x1 
              else Num(n1 / n2)
          | Mod ->
              if (n2 = 0) then x1 
              else Num(n1 mod n2)
        )
      | _ , Num(n2) -> (
          match op with
          | Add -> 
              if (n2 = 0) then x1
              else Op (Add, x1, x2)
          | Sub -> 
              if (n2 = 0) then x1
              else Op (Sub, x1, x2) 
          | Mul -> 
              if (n2 = 0) then Num(0)
              else if (n2 = 1) then x1
              else Op (Mul, x1, x2)
          | Div -> 
              if (n2 = 0) then x1 
              else Op (Div, x1, x2)
          | Mod ->
              if (n2 = 0) then x1 
              else Op (Mod, x1, x2)
        )
      | Num(n1), _ -> (
          match op with
          | Add -> 
              if (n1 = 0) then x2
              else Op (Add, x1, x2)
          | Sub -> 
              if (n1 = 0) then x2
              else Op (Sub, x1, x2) 
          | Mul -> 
              if (n1 = 0) then Num(0)
              else if (n1 = 1) then x2
              else Op (Mul, x1, x2)
          | Div -> 
              if (n1 = 0) then Num(0)
              else Op (Div, x1, x2)
          | Mod ->
              if (n1 = 0) then Num(0)
              else Op (Mod, x1, x2)
        )
      | _ , _ ->
          match op with
          | Add -> Op (Add, x1, x2)
          | Sub -> Op (Sub, x1, x2) 
          | Mul -> Op (Mul, x1, x2)
          | Div -> Op (Div, x1, x2)
          | Mod -> Op (Mod, x1, x2)
    )
  | _ -> ex 
;;

(*simplifie une condition*)
let simpl_cond (condi : cond) : cond = 
  let (ex1, c, ex2) = condi in
  ((simpl_expr ex1), c, (simpl_expr ex2))
;;
(*teste une condition pour voir si il y a des block mort dans les If*)
let simpl_test_cond (condi : cond) : (bool option) =
  let (ex1, c, ex2) = condi in
  match ex1, ex2 with
  |Num(n1), Num (n2) -> (
      match c with
      |Eq -> Some(n1 = n2)
      |Ne -> Some(n1 <> n2)
      |Lt -> Some(n1 < n2)
      |Le -> Some(n1 <= n2)
      |Gt -> Some(n1 > n2)
      |Ge -> Some(n1 >= n2)
    )
  |_ -> None 
;;
(*simplifie le program, en simplifiant les expression, les conditions et en supprimant les blocks morts*)
let simpl_polish (p : program) :program = 
  let rec simpl (p : program) (acc : program) (posi : int) : (int * program)= 
    match p with
    |[] -> (posi, List.rev acc)
    |(pos, ins) :: t -> 
        match ins with
        |Set (n, ex) -> simpl t ((posi , Set(n, simpl_expr ex)) :: acc) (posi + 1) 
        |Read (n) -> simpl t ((posi , Read(n)) :: acc) (posi + 1) 
        |Print (ex) -> simpl t ((posi , Print(simpl_expr ex)) :: acc) (posi + 1) 
        |If (condi, b1, b2) -> (
            let c = simpl_cond condi in
            let test = simpl_test_cond c in
            match test with
            |Some (tf) ->
                if tf then 
                  let (position, block_vraie) = simpl b1 [] posi  in
                  simpl t (List.rev_append block_vraie acc) position 
                else
                  let (position, block_faux) = simpl b1 [] posi  in
                  simpl t (List.rev_append block_faux acc) position 
            |None ->
                let (position, block_vraie) = simpl b1 [] (posi + 1) in
                let (position2, block_faux) = simpl b2 [] position in
                simpl t ((posi, If(c, block_vraie, block_faux)) :: acc) position2 
          )
        |While (condi, b) ->
            let c = simpl_cond condi in
            let test = simpl_test_cond c in
            match test with
            |Some(false) -> 
                simpl t acc posi
            |_ ->
                let (position, block) = simpl b [] (posi + 1) in 
                simpl t ((posi, While(c, block)) :: acc) position 
  in
  let (_, res) = simpl p [] 1 in
  res
;;
