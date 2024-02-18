open Type;;

(*affiche le programme*)
let print_polish (p:program) : unit =
  (*expresion en string*)
  let rec expStr (ex: expr): string = 
    match ex with
    |Num(i)-> string_of_int(i);
    |Var(n)-> n
    |Op(op, ex1, ex2) ->
        match op with
        | Add ->"(" ^ "+ " ^ (expStr ex1) ^ " " ^(expStr ex2) ^")"
        | Sub ->"(" ^ "- " ^ (expStr ex1) ^ " " ^(expStr ex2) ^")"
        | Mul ->"(" ^ "* " ^ (expStr ex1) ^ " " ^(expStr ex2) ^")"
        | Div ->"(" ^ "/ " ^ (expStr ex1) ^ " " ^(expStr ex2) ^")"
        | Mod ->"(" ^ "% " ^ (expStr ex1) ^ " " ^(expStr ex2) ^")" 
  in 
  (*condition en string*)
  let condStr (condi: cond) : string =
    let (ex1,com,ex2) = condi in
    match com with
    | Eq ->"(" ^ (expStr ex1) ^ " = " ^ (expStr ex2) ^")"
    | Ne ->"(" ^ (expStr ex1) ^ " <> " ^ (expStr ex2) ^")"
    | Lt ->"(" ^ (expStr ex1) ^ " < " ^ (expStr ex2) ^")"
    | Le ->"(" ^ (expStr ex1) ^ " <= " ^ (expStr ex2) ^")"
    | Gt ->"(" ^ (expStr ex1) ^ " > " ^ (expStr ex2) ^")"
    | Ge ->"(" ^ (expStr ex1) ^ " >= " ^ (expStr ex2) ^")" 
  in 
  let rec print (p:program) (tab : string): unit = 
    match p with
    |[] -> ()
    |(pos, ins) :: t -> 
        print_string (tab); 
        match ins with
        |Set (n, ex) -> 
            print_string(n ^ " := "); print_string(expStr ex); print_string ("\n");
            print t tab
        |Read (n) -> 
            print_string("Read " ^ n); print_string ("\n");
            print t tab
        |Print (ex) -> 
            print_string("Print "); print_string(expStr ex); print_string ("\n");
            print t tab
        |If (condi, b1, b2)-> 
            print_string("If "); print_string(condStr condi); print_string ("\n");
            print b1 (tab ^ "  "); 
            if (b2 <> []) then(
              print_string("Else\n");
              print b2 (tab ^ "  ");
              print t tab)
            else print t tab
        |While (condi, b) ->
            print_string("While "); print_string(condStr condi); print_string ("\n");
            print b (tab ^ "  ");
            print t tab
              
  in
  print p "" 
;;
