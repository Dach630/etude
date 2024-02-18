open Type;;

let rec maj liste (str, i) acc= 
  match liste with
  |[] -> (str,i) :: acc
  |(nom,var):: t -> 
      if nom = str then List.rev_append ((str, i)::acc) t
      else maj t (str,i) ((nom,var) :: acc)

(*acc est vide au debut*)
let rec maj_env liste (str,v) acc= 
  match liste with 
  |[]                         -> if (acc =[]) then (*si l'acc est vide: donc le if (chaine=str) du 2eme match ne c'est jamais exécuté*)
                                 [(str,v)] 
                                 else 
                                 []
  |(chaine, entier)::queue    -> if (chaine=str) then 
                                 [(str,v)]@(maj_env queue (str,v) acc)@acc (*Si on trouve le chaîne cette partie d'instruction ne va plus s'exécuter, autrement dit il s'exécute une seul fois.*)
                                 else 
                                 [(chaine, entier)]@(maj_env queue (str, v) acc) 


let rec eval_expr (expression: expr) (l :environnement)=  
  match expression with 
  |Num(n)                   -> n 
  |Var(s)            -> List.assoc s l(*récuperer l'entier associer à s*)
  |Op(operation, e1, e2)    -> match operation with
                                    |Add -> (eval_expr e1 l)  +  (eval_expr e2 l) 
                                    |Sub -> (eval_expr e1 l) - (eval_expr e2 l) (*(eval_expr e2 l)  -  (eval_expr e1 l)*) (*Le stockage des données d'une expression à été stocker à l'envers*)
                                    |Mul -> (eval_expr e1 l)  *  (eval_expr e2 l) 
                                    |Div -> (eval_expr e1 l)  /  (eval_expr e2 l) 
                                    |Mod -> (eval_expr e1 l) mod (eval_expr e2 l)

(*let eval_condition condition l =  
  match condition with 
  |(e1,Eq,e2)  -> (eval_expr e1 l)=(eval_expr e2 l)
  |(e1,Ne,e2)  -> (eval_expr e1 l)<>(eval_expr e2 l)
  |(e1,Lt,e2)  -> (eval_expr e1 l)<(eval_expr e2 l)
  |(e1,Le,e2)  -> (eval_expr e1 l)<=(eval_expr e2 l)
  |(e1,Gt,e2)  -> (eval_expr e1 l)>(eval_expr e2 l)
  |(e1,Ge,e2)  -> (eval_expr e1 l)>=(eval_expr e2 l)*)

(*let eval_condition e1 e2 c l =  
  match c with 
  |Eq   -> (eval_expr e1 l)=(eval_expr e2 l)
  |Ne   -> (eval_expr e1 l)<>(eval_expr e2 l)
  |Lt   -> (eval_expr e1 l)<(eval_expr e2 l)
  |Le   -> (eval_expr e1 l)<=(eval_expr e2 l)
  |Gt   -> (eval_expr e1 l)>(eval_expr e2 l)
  |Ge   -> (eval_expr e1 l)>=(eval_expr e2 l)*)


let eval_condition con env : bool =
  match con with 
  | (e1,comp,e2) -> 
      match comp with
      | Eq -> (eval_expr e1 env) =  (eval_expr e2 env)
      | Ne -> (eval_expr e1 env) <> (eval_expr e2 env)
      | Lt -> (eval_expr e1 env) <  (eval_expr e2 env)
      | Le -> (eval_expr e1 env) <=  (eval_expr e2 env)
      | Gt -> (eval_expr e1 env) >  (eval_expr e2 env)
      | Ge -> (eval_expr e1 env) >=  (eval_expr e2 env)



(*fonction d'evaluation d'une block*) 
let rec eval_block (bloc: block) (liste: environnement) = 
  match bloc with 
  |[]                     ->  liste 
  (*(eval_instr (i) (l))*)
  |(n,i)::bloc_suivant           ->  let l2 = (match i with
                                        |Read(s)                                 -> Printf.printf "%s?" s;    (*Lecture*)(*Afficher le contenue de la variable s sur la sortie strandard*)
                                                                                    let b=read_int() in maj liste (s,b) [] 

                                        |Set(s,e)                                -> let r=(eval_expr (e) (liste)) in maj liste (s,r) []

                                        |Print(e)                                -> let r=(eval_expr (e) (liste)) in 
                                                                                    print_int r;
                                                                                    print_newline();
                                                                                    liste

                                        |If(con, bloc1, bloc2)          ->if (eval_condition con liste) then 
                                                                                        eval_block bloc1 liste 
                                                                                      else eval_block bloc2 liste
                                        | While(con, b) -> match con with 
                      (e1,c,e2) -> if (eval_condition (e1,c,e2) liste) then eval_block b liste 
                      else liste) in eval_block bloc_suivant l2
                                        
                                                            (*match con with 
                                                            (e1,c,e2) -> let rec loop eval_condition liste =
                                                                match (eval_condition (e1,c,e2) liste) with 
                                                                |true   -> loop (eval_condition (e1,c,e2)) liste
                                                                |false  -> liste*)



let eval_polish (p:program) : unit = 
  let resultat = eval_block p [] in 
  if resultat <> [] then ()
  else ()
;;

