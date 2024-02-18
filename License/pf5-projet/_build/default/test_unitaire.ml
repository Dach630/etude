(*let rec maj_env liste (str,v) acc= 
  match liste with 
  |[]                         -> if (acc =[]) then (*si l'acc est vide: donc le if (chaine=str) du 2eme match ne c'est jamais exécuté*)
                                 (str,v) 
                                 else 
                                 () 
  |(chaine, entier)::queue    -> if (chaine=str) then 
                                 [(str,v)]@(maj_env queue (str,v) acc)@acc (*Si on trouve le chaîne cette partie d'instruction ne va plus s'exécuter, autrement dit il s'exécute une seul fois.*)
                                 else
                                 [(chaine, entier)]@(maj_env queue (str, v) acc) 

;;*)





(*let rec maj_env liste (str,v)=  
  match liste with 
  |[]                         ->[(str,v)]  

  |(chaine, entier)::queue    -> if (chaine=str) then 
                                 [(str,v)]@(maj_env queue (str,v)) (*Si on trouve le chaîne cette partie d'instruction ne va plus s'exécuter, autrement dit il s'exécute une seul fois.*)
                                 else
                                 [(chaine, entier)]@(maj_env queue (str, v))

;;





let l=[("s1", 2); ("s2", 7); ("s3", 19)];; 

maj_env l ("s5", 8);;*)



let rec maj liste (str, i) acc= 
  match liste with
  |[] -> (str,i) :: acc
  |(nom,var):: t -> 
      if nom = str then List.rev_append ((str, i)::acc) t
      else maj t (str,i) ((nom,var) :: acc)
;;


let l=[("s1", 2); ("s2", 7); ("s3", 19)];; 

maj l ("s1", 2) [] ;;



