open Type;;
open Read;;
open Print;;
open Simpl;;
open Vars;;
open Progr;;
open Eval;;

(* aide pour les commandes *)
let usage () = 
  print_string "Polish : analyse statique d'un mini-langage\n";
  print_string "usage:\n"; 
  print_string "./run -reprint [fichier] | affiche le programme polish sans les commentaires et les lignes vide,\n";
  print_string "                           donner en argument\n";
  print_string "./run -eval [fichier]    | execute le fichier polish donner en argument\n";
  print_string "./run -simpl [fichier]   | affiche la simplification le programme polish donner en argument\n";
  print_string "./run -vars [fichier]    | affiche les variables du fichier polish donner en argument\n";
  print_string "                           1er ligne : les varibles initialisés avant leur utilisation\n";
  print_string "                           2nd ligne : les varibles a risque qui peuvent être utilisés avant initialisation\n";
  print_string "./run -prog [fichier]    | affiche la conversion du fichier polish donner selon le format du Type.ml\n";
;;

let main () = 
  match Sys.argv with
  | [|_;"-print";file|] -> print_polish(read_polish file) 
  | [|_;"-eval";file|] -> eval_polish(read_polish file) 
  | [|_;"-simpl";file|] -> print_polish(simpl_polish(read_polish file))
  | [|_;"-vars";file|] -> vars_polish(read_polish file) 
  | [|_;"-prog";file|] -> prog_polish(read_polish file)
  | _ -> usage () 
;; 
(* lancement de ce main *)
let () = main ()