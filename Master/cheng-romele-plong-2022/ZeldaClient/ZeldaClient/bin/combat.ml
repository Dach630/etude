open Types;;
open Worldmap;;
open Movements;;
open Draw;;

let rec move_out_screen plateau_items =
	match plateau_items with
	|[] -> ()
	|(_,w,x,y,z) :: plateau_items->
		if (!z == 0) then (
			z := 1;
			w := "";
			x := 0.;
			y := 0.;
		 	move_out_screen plateau_items
		)else(move_out_screen plateau_items)
;;


let player_damage joueur ennemi =
	let x = (int_of_float (joueur.posX1 )) / 32 in
	let y = (int_of_float (joueur.posY1 )) / 32 in
	let nx = (int_of_float (joueur.posX1 +. 31.0)) / 32 in
	let ny = (int_of_float (joueur.posY1 +. 31.0)) / 32 in
	let items = getItems joueur in
	joueur.pv <- joueur.pv - ennemi.ennemi_specs.attaque;
	match ennemi.ennemi_last_move with
	|"8" ->
	if((getCaseSet joueur).(10 - y - 1).(x) != 1 && (getCaseSet joueur).(10 - y - 1).(nx) != 1) then(
		if (joueur.posY1 +. 32. > 310.) then (
			move_out_screen items;
			joueur.posY1 <- 32.;
			(if (joueur.plateau_actuelY < ((Array.length map.full_map)-1)) then (joueur.plateau_actuelY <- joueur.plateau_actuelY + 1)
			 else (joueur.plateau_actuelY <- 0));
			screen()
		)else (joueur.posY1 <- joueur.posY1 +. 32.)
	)else ()
	|"4" ->
	(if((getCaseSet joueur).(10 - y).(nx - 1) != 1 && (getCaseSet joueur).(10 - ny).(nx - 1) != 1)then(
		if (joueur.posX1 -. 32. <= 1.) then (
			move_out_screen items;
			joueur.posX1 <- 448.;
			(if(joueur.plateau_actuelX > 0) then (joueur.plateau_actuelX <- joueur.plateau_actuelX - 1)
			else (joueur.plateau_actuelX <- ((Array.length map.full_map.(0))-1)));
			screen()
			)else (joueur.posX1 <- joueur.posX1 -. 32.))
	else ())
	|"2" ->
	(if((getCaseSet joueur).(10 - ny + 1).(x) != 1 && (getCaseSet joueur).(10 - ny + 1).(nx) != 1)then(
		if(joueur.posY1 -. 32. <= 1.) then (
		 	move_out_screen items;
			joueur.posY1 <- 288.;
			(if (joueur.plateau_actuelY > 0) then (joueur.plateau_actuelY <- joueur.plateau_actuelY - 1)
			else (joueur.plateau_actuelY <- ((Array.length map.full_map)-1)));
			screen()
		)else (joueur.posY1 <- joueur.posY1 -. 32.)
	)else ())
	|"6" ->
	(if((getCaseSet joueur).(10 - y).(x + 1) != 1 && (getCaseSet joueur).(10 - ny).(x + 1) != 1)then(
		if (joueur.posX1 +. 32. > 470.) then (
			move_out_screen items;
			joueur.posX1 <- 32.;
			(if (joueur.plateau_actuelX < ((Array.length map.full_map)-1)) then (joueur.plateau_actuelX <- joueur.plateau_actuelX + 1)
			 else (joueur.plateau_actuelX <- 0));
			screen())
		else (joueur.posX1 <- joueur.posX1 +. 32.))
	else ())
	|_ -> ()
;;

let money_pickup player =
	if (player.money < 999) then (player.money <- player.money+1)
	else ()
;;

let heart_pickup player =
	if(player.pv == player.pv_max-1) then(
		player.pv <- player.pv_max;
	)else(
		player.pv <- player.pv + 2;
	);;

let select_item length=
	if (length > 0) then (
		Random.self_init();
		Random.int length
	)else length
;;

let rec item_drop list_items ennemi nb x y=
 	match list_items with
	|[] -> ()
	|(a,b,c,d,e) :: list_items ->
		if (a == nb) then (
			b := (List.nth ennemi.possible_drops (select_item (List.length (list_items))));
			c := !x;
			d := !y;
			e := 0
		)else(item_drop list_items ennemi nb x y)
;;

let ennemi_damage joueur ennemi ennemi_id ennemi_pv posX posY =
	let x = (int_of_float (!posX)) / 32 in
	let y = (int_of_float (!posY)) / 32 in
	let nx = (int_of_float (!posX +. 31.0)) / 32 in
	let ny = (int_of_float (!posY +. 31.0)) / 32 in
	ennemi_pv := !ennemi_pv - joueur.player_specs.attaque;
	let _ = if (!ennemi_pv <= 0) then
		item_drop (getItems joueur) ennemi ennemi_id posX posY
 	in
	match joueur.last_move with
	|"8" ->
	(if((getCaseSet joueur).(10 - y - 1).(x) != 1 && (getCaseSet joueur).(10 - y - 1).(nx) != 1) then(
		if (!posY +. 32. > 310.) then ()
		else (posY := !posY +. 32.))
	else ())
	|"4" ->
	(if((getCaseSet joueur).(10 - y).(nx - 1) != 1 && (getCaseSet joueur).(10 - ny).(nx - 1) != 1)then(
		if (!posX -. 32. <= 1.) then ()
		else (posX := !posX -. 32.))
	else ())
	|"2" ->
	(if((getCaseSet joueur).(10 - ny + 1).(x) != 1 && (getCaseSet joueur).(10 - ny + 1).(nx) != 1)then(
		if(!posY -. 32. <= 1.) then ()
		else (posY := !posY -. 32.))
	else ())
	|"6" ->
	(if((getCaseSet joueur).(10 - y).(x + 1) != 1 && (getCaseSet joueur).(10 - ny).(x + 1) != 1)then(
		if (!posX +. 32. > 470.) then ()
		else (posX := !posX +. 32.))
	else ())
	|_ -> ()
;;

let player_attack joueur ennemi ennemi_id ennemi_pv posX posY =
	let x = (int_of_float !posX)/32 in
	let y = (int_of_float !posY)/32 in
	let px = (int_of_float (joueur.posX1))/32 in
	let py = (int_of_float (joueur.posY1))/32 in
	match joueur.last_move with
	|"4"->
		if ((((int_of_float joueur.posX1)/32)-1 == x) && y == py) then (ennemi_damage joueur ennemi ennemi_id ennemi_pv posX posY) else ()
	|"2"->
		if ((((int_of_float joueur.posY1)/32)-1 == y)&& x == px) then (ennemi_damage joueur ennemi ennemi_id ennemi_pv posX posY) else ()
	|"6"->
		if ((((int_of_float joueur.posX1)/32)+1 == x) && y == py) then (ennemi_damage joueur ennemi ennemi_id ennemi_pv posX posY) else ()
	|"8"->
		if ((((int_of_float joueur.posY1)/32)+1 == y) && x == px) then (ennemi_damage joueur ennemi ennemi_id ennemi_pv posX posY) else ()
	|_ -> ()
;;
