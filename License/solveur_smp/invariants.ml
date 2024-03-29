open Printf

(* Définitions de terme, test et programme *)
type term = 
  | Const of int
  | Var of int
  | Add of term * term
  | Mult of term * term

type test = 
  | Equals of term * term
  | LessThan of term * term

let tt = Equals (Const 0, Const 0)
let ff = LessThan (Const 0, Const 0)
 
type program = {nvars : int; 
                inits : term list; 
                mods : term list; 
                loopcond : test; 
                assertion : test}

let x n = "x" ^ string_of_int n

(* Question 1. Écrire des fonctions `str_of_term` et `str_of_term` qui
   convertissent des termes et des tests en chaînes de caractères du
   format SMTLIB.

  Par exemple, str_of_term (Var 3) retourne "x3", str_of_term (Add
   (Var 1, Const 3)) retourne "(+ x1 3)" et str_of_test (Equals (Var
   2, Const 2)) retourne "(= x2 2)".  *)
let rec str_of_term t = 
  match t with
  |Const(i) -> string_of_int i;
  |Var(i) -> x i
  |Add(t1, t2)-> "(+ " ^ (str_of_term t1) ^ " " ^ (str_of_term t2) ^ ")"
  |Mult(t1, t2)-> "(* " ^ (str_of_term t1) ^ " " ^ (str_of_term t2) ^ ")"
;;

let str_of_test t = 
  match t with
  |Equals(t1, t2)-> "(= " ^ (str_of_term t1) ^ " " ^ (str_of_term t2) ^ ")"
  |LessThan(t1, t2)-> "(< " ^ (str_of_term t1) ^ " " ^ (str_of_term t2) ^ ")"
;;

let str_inverse t = 
  match t with
  |Equals( t1, t2) -> "!= " ^ (str_of_term t1) ^ " " ^ (str_of_term t2) ^ ")"
  |LessThan(t1, t2)-> "(>= " ^ (str_of_term t1) ^ " " ^ (str_of_term t2) ^ ")"

let string_repeat s n =
  Array.fold_left (^) "" (Array.make n s)
  
   (* Question 2. Écrire une fonction str_condition qui prend une liste
      de termes t1, ..., tk et retourne une chaîne de caractères qui
      exprime que le tuple (t1, ..., tk) est dans l'invariant.  Par
      exemple, str_condition [Var 1; Const 10] retourne "(Invar x1 10)".
*)
let init_var n =
  let rec repeat n acc ref =
      if ref <> n then repeat n (Var(ref+1) ::acc) (ref+1) else List.rev acc in
  repeat n [] 0

let str_condition l = 
  let rec repeat l r = 
    match l with 
    |[] -> r ^ ")"
    |h :: t -> repeat t (r ^ " " ^ (str_of_term h))
  in
  match l with 
  |h :: t -> repeat l "(Invar"
  |_ -> failwith("str_condition no term")

   (* Question 3. Écrire une fonction str_assert_for_all qui prend en
      argument un entier n et une chaîne de caractères s, et retourne
      l'expression SMTLIB qui correspond à la formule "forall x1 ... xk
                               (s)".
     Par exemple, str_assert_forall 2 "< x1 x2" retourne : 
      "(assert (forall ((x1 Int) (x2 Int)) (< x1 x2)))". 
 *)

 let str_assert s = "(assert " ^ s ^ ")" ;;
 let str_forall s = "(forall " ^ s ^ ")" ;;
 let str_strStr s1 s2 = "(" ^ s1 ^ ") (" ^ s2 ^ ")" ;; 
 let str_int s = "(" ^ s ^ " Int)" ;;
 
 let rec contains x list=
   match list with
   |[] -> false
   |h :: t -> if h = x then true else contains x t 
 ;;
 
 
 let rec str_inForAll n split res dejaVu= 
   match split with 
   |[] -> 
       if n < 1 then res 
       else failwith("n > nb of Var")
   |h :: t ->
       if  h <> "" then
         if((String.get h 0) = 'x') 
         then 
           if (contains h dejaVu) then str_inForAll n t res dejaVu
           else str_inForAll (n - 1) t (res ^ " " ^(str_int h)) (h :: dejaVu)
         else str_inForAll n t res dejaVu
       else str_inForAll n t res dejaVu
 ;;
 
 let str_assert_forall n s = 
   let r1 = String.split_on_char ' ' s in
   let rec r2 strL res = 
     match strL with
     |h :: t -> r2 t ((String.split_on_char ')' h) :: res)
     |[] -> List.flatten(List.rev res) 
   in 
   let r = str_inForAll n (r2 r1 []) "" []in
   let res =String.sub r 1 ((String.length r) - 1) in 
   str_assert (str_forall (str_strStr res s))
 ;;



(* Question 4. Nous donnons ci-dessous une définition possible de la
   fonction smt_lib_of_wa. Complétez-la en écrivant les définitions de
   loop_condition et assertion_condition. *)

let smtlib_of_wa p = 
  let declare_invariant n =
    "; synthèse d'invariant de programme\n"
    ^"; on déclare le symbole non interprété de relation Invar\n"
    ^"(declare-fun Invar (" ^ string_repeat "Int " n ^  ") Bool)" in
  let loop_condition p =
    "; la relation Invar est un invariant de boucle\n" 
    ^str_assert_forall p.nvars ("=>"^"(and" ^ str_condition(init_var p.nvars)^ (str_of_test p.loopcond) ^")"
    ^ str_condition p.mods) in
  let initial_condition p =
    "; la relation Invar est vraie initialement\n"
    ^str_assert (str_condition p.inits) in
  let assertion_condition p =
    "; l'assertion finale est vérifiée\n"
    ^ str_assert_forall p.nvars ("=>"^"(and" ^ str_condition(init_var p.nvars) ^ str_inverse p.loopcond ^")"
    ^ (str_of_test p.assertion)) in
  let call_solver =
    "; appel au solveur\n(check-sat-using (then qe smt))\n(get-model)\n(exit)\n" in
  String.concat "\n" [declare_invariant p.nvars;
                      loop_condition p;
                      initial_condition p;
                      assertion_condition p;
                      call_solver];;

let p1 = {nvars = 2;
          inits = [(Const 0) ; (Const 0)];
          mods = [Add ((Var 1), (Const 1)); Add ((Var 2), (Const 3))];
          loopcond = LessThan ((Var 1),(Const 3));
          assertion = Equals ((Var 2),(Const 9))};;

let() = print_string "////////////////////////P1////////////////////// \n"

let () = Printf.printf "%s" (smtlib_of_wa p1);;

let() = print_string "\n////////////////////////P2//////////////////////\n"

(* Question 5. Vérifiez que votre implémentation donne un fichier
   SMTLIB qui est équivalent au fichier que vous avez écrit à la main
   dans l'exercice 1. Ajoutez dans la variable p2 ci-dessous au moins
   un autre programme test, et vérifiez qu'il donne un fichier SMTLIB
   de la forme attendue. *)

let p2 = {nvars = 2;
          inits = [(Const 0) ; (Const 36)];
          mods = [Add ((Var 1), (Const 5)); Add ((Var 2), (Const 1))];
          loopcond = LessThan ((Var 2),(Const 45));
          assertion = Equals ((Var 1),(Var 2))};;

let () = Printf.printf "%s" (smtlib_of_wa p2)