let ch = open_in (Sys.argv.(1)) ;;
let lexbuf = Lexing.from_channel ch ;;

let rec input_symb (t:Token.token) n =
  match t with
  | LETINP ->
      if n = 0
      then input_symb (Lexeur.main lexbuf) 1
      else failwith "missing , in input symbols"
  | VIR ->
      if n = 1
      then input_symb (Lexeur.main lexbuf) 0
      else failwith "missing [a-z] in input symbols"
  |JUMP ->
      if n = 1
      then t
      else failwith "missing [a-z] in input symbols"
  |_ -> failwith "unknown in input symbols"
;;

let rec stack_symb (t:Token.token) n =
  match t with
  | LETSTK ->
      if n = 0
      then stack_symb (Lexeur.main lexbuf) 1
      else failwith "missing , in stack symbols"
  | VIR ->
      if n = 1
      then stack_symb (Lexeur.main lexbuf) 0
      else failwith "missing [A-Z] in stack symbols"
  |JUMP ->
      if n = 1
      then t
      else failwith "missing [A-Z] in stack symbols"
  |_ -> failwith "unknown in stack symbols"
;;

let rec state_symb (t:Token.token) n =
  match t with
  | LETSTA ->
      if n = 0
      then state_symb (Lexeur.main lexbuf) 1
      else failwith "missing , in state symbols"
  | VIR ->
      if n = 1
      then state_symb (Lexeur.main lexbuf) 0
      else failwith "missing [0-9]+ in state symbols"
  | JUMP ->
      if n = 1
      then t
      else failwith "missing [0-9]+ in state symbols"
  |_ -> failwith "unknown in stack symbols"
;;

let rec init_state (t:Token.token) n =
  match t with
  | LETSTA ->
      if n = 0
      then init_state (Lexeur.main lexbuf) 1
      else failwith "too much state symbol in initial state"
  |JUMP ->
      if n = 1
      then t
      else failwith "missing state symbol in initial state"
  | _ -> failwith "unknown in initial state"
;;

let rec init_stack (t:Token.token) n =
  match t with
  | LETSTK ->
      if n = 0
      then init_stack (Lexeur.main lexbuf) (1)
      else failwith "too much stack symbol in initial stack"
  | JUMP ->
      if n = 1
      then t
      else failwith "missing stack symbol in initial stack"
  |_-> failwith "unknown in initial stack"
;;

let error_transition n =
  match n with
  | 0 -> "missing ( in transition"
  | 1 -> "missing state symbol in transition"
  | 2 -> "missing , in transition"
  | 3 -> "missing input symbol in transition"
  | 4 -> "missing , in transition"
  | 5 -> "missing stack symbol in transition"
  | 6 -> "missing , in transition"
  | 7 -> "missing state symbol in transition"
  | 8 -> "missing , in transition"
  | 9 -> "missing stack symbol in transition"
  | 10 -> "missing stack symbol or a ; or a ) in transition"
  | 11 -> "missing ) in transition"
  | 12-> "missing jump line in transition"
  | _ -> "unknown error"
;;

let mot n =
  match n with
  | 3 -> 4
  | _ -> failwith (error_transition n)
;;

let stack n =
  match n with
  | 5 -> 6
  | 9 -> 10
  |11 -> 10
  | _ -> failwith (error_transition n)
;;

let state n =
  match n with
  | 1 -> 2
  | 7 -> 8
  | _ -> failwith (error_transition n)
;;

let virgule n =
  match n with
  | 2 -> 3
  | 3 -> 5
  | 4 -> 5
  | 6 -> 7
  | 8 -> 11
  | _ -> failwith (error_transition n)
;;

let rec transition (t:Token.token) n =
  match t with
  | LETINP -> transition (Lexeur.main lexbuf) (mot n)
  | LETSTK -> transition (Lexeur.main lexbuf) (stack n)
  | LETSTA -> transition (Lexeur.main lexbuf) (state n)
  | VIR -> transition (Lexeur.main lexbuf) (virgule n)
  | LPAREN ->
      if n = 0
      then transition (Lexeur.main lexbuf) 1
      else failwith " ( in wrong place in transition"
  | RPAREN ->
      if (n = 10 || n =11)
      then transition (Lexeur.main lexbuf) 12
      else failwith " ) in wrong place in transition"
  | POIVIR ->
      if n = 10
      then transition (Lexeur.main lexbuf) 9
      else failwith (error_transition n)
  |JUMP ->
      if (n = 0 || n = 12)
      then transition (Lexeur.main lexbuf) 0
      else failwith " jump line in wrong place in transition"
  |_ ->
      if (n = 0 || n = 12)
      then t
      else failwith "unknown statement in transition"
;;

let error_missing_part n =
  match n with
  | 0 -> failwith "missing input symbols"
  | 1 -> failwith "missing stack symbols"
  | 2 -> failwith "missing state symbols"
  | 3 -> failwith "missing initial state"
  | 4 -> failwith "missing initial stack"
  | 5 -> failwith "missing transition"
  | _ -> failwith "too much part"
;;

let rec f (t:Token.token ) n =
  match t with
  | ALINP ->
      if n = 0
      then f (input_symb (Lexeur.main lexbuf) 0) 1
      else failwith (error_missing_part n)
  | ALSTK ->
      if n = 1
      then f (stack_symb (Lexeur.main lexbuf) 0) 2
      else failwith (error_missing_part n)
  | ALSTA ->
      if n = 2
      then f (state_symb (Lexeur.main lexbuf) 0) 3
      else failwith (error_missing_part n)
  | STATE ->
      if n = 3
      then  f (init_state (Lexeur.main lexbuf) 0) 4
      else failwith (error_missing_part n)
  | STACK ->
      if n = 4
      then  f (init_stack (Lexeur.main lexbuf) 0) 5
      else failwith (error_missing_part n)
  | TRANS ->
      if n = 5
      then f (transition (Lexeur.main lexbuf) 0) 6
      else failwith (error_missing_part n)
  | EOF ->
      if n = 6
      then true
      else failwith (error_missing_part n)
  | JUMP -> f (Lexeur.main lexbuf) n
  | _ -> failwith (error_missing_part n)
;;

let test () =
    if (f (Lexeur.main lexbuf) 0)
    then print_string "OK\n"
    else failwith "HOW\n"
;;
test ()
