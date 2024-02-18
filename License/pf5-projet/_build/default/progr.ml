open Type;;

(*affiche l'expresion (expr)*)
let rec exr_p ex =
  match ex with
  | Num(n) -> 
      print_string("Num("); 
      print_int(n) ;
      print_string(")") 
  | Var(n) -> print_string("Var(\"" ^ n ^ "\")") 
  | Op(op, exp1, exp2) ->(
      match op with
      | Add -> print_string("Op(Add, ")
      | Sub -> print_string("Op(Sub, ")
      | Mul -> print_string("Op(Mul, ")
      | Div -> print_string("Op(Div, ")
      | Mod -> print_string("Op(Mod, ")
    );
      exr_p exp1;
      print_string(", ");
      exr_p exp2;
      print_string(")")
;;
(*affiche la condition (cond)*)
let con_p con = 
  let (ex1, c, ex2) = con in
  print_string("(");
  exr_p ex1 ;
  (match c with
   | Eq -> print_string(", Eq,")
   | Ne -> print_string(", Ne,")
   | Lt -> print_string(", Lt,")
   | Le -> print_string(", Le,")
   | Gt -> print_string(", Gt,")
   | Ge -> print_string(", Ge,")
  ); 
  exr_p ex2 ;
  print_string(")");
;; 

(*affiche la conversion du fichier polish lu en program*)
let prog_polish (p :program) : unit = 
  let rec print p =
    print_string ("(");
    match p with 
    |[] -> print_string("[]")
    |(pos,ist) :: t -> 
        print_int (pos); 
        match ist with
        | Set (n, ex) -> 
            print_string (", Set(\"" ^ n ^ "\", ");
            exr_p ex ;
            print_string ("))::");
            print t
        | Read (n) -> 
            print_string (", Read(\"" ^ n ^ "\")::"); 
            print t
        | Print (ex) ->  
            print_string (", Print(");
            exr_p ex ;
            print_string ("))::");
            print t
        | If ( con, blo1, blo2 )->
            print_string (", If(");
            con_p con ;
            print_string (",");
            print blo1;
            print_string (",");
            print blo2;
            print_string ("))::");
            print t
        | While ( con , blo) ->
            print_string (", While(");
            con_p con ;
            print_string (",");
            print blo; 
            print_string ("))::");
            print t 
  in
  print p
;; 
