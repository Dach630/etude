open Tree
let rec err_init_state allState init =
	match allState with
	| [] -> failwith "initial state is not in state symbols"
	| h :: t ->
		if h = init
		then true
		else err_init_state t init
;;

let rec err_init_stack allStack init =
	match allStack with
	| [] -> failwith "initial stack is not in stack symbols"
	| h :: t ->
		if h = init
		then true
		else err_init_stack t init
;;

let rec transi_ok transList transi =
	match transList with
	| [] -> true
	| (inputL, stackL,_ , _) :: t ->
	    let (input, stack , _, _) = transi in
	    if(inputL = None)
	    then false
	    else if (inputL = input && stackL = stack)
		then false
		else transi_ok t transi

let rec test_deter transiList =
	match transiList with
	|[] -> true
	|transi :: t ->
	    let (input, stack, _ , _) = transi in
	    if(input = None)
	    then false
	    else if (transi_ok transiList transi)
		then test_deter t
		else false

let rec err_deter arbre =
	match arbre with
	| [] -> true
	| (n , list) :: t ->
		if (test_deter list)
		then err_deter t
		else failwith "automate non deterministe"
;;
