open Graphics;;
open Types;;
open Entities;;
open Worldmap;;
open Movements;;
open Combat;;
open Draw;;

let move joueur direction =
	let x = (int_of_float (joueur.posX1 )) / 32 in
	let y = (int_of_float (joueur.posY1 )) / 32 in
	let nx = (int_of_float (joueur.posX1 +. 31.0)) / 32 in
	let ny = (int_of_float (joueur.posY1 +. 31.0)) / 32 in
	let items = getItems joueur in
	match direction with
	|8 ->
		(
			if((getCaseSet joueur).(10 - y - 1).(x) != 1 && (getCaseSet joueur).(10 - y - 1).(nx) != 1) then(
				(if (joueur.posY1 +. 8. > 310.) then(
					move_out_screen items;
					joueur.posY1 <- 32.;
					(if (joueur.plateau_actuelY < ((Array.length map.full_map)-1)) then(joueur.plateau_actuelY <- joueur.plateau_actuelY + 1)
					 else (joueur.plateau_actuelY <- 0));
					screen()
				)else (joueur.posY1 <- (joueur.posY1 +. 8.)));
				joueur.last_move <- "8";
				sprite_step joueur
			)else()
		)
	|6 ->
		(
			if((getCaseSet joueur).(10 - y).(x + 1) != 1 && (getCaseSet joueur).(10 - ny).(x + 1) != 1)then(
				(if (joueur.posX1 +. 8. > 470.) then(
					move_out_screen items;
					joueur.posX1 <- 32.;
					(if (joueur.plateau_actuelX < ((Array.length map.full_map) - 1)) then (joueur.plateau_actuelX <- joueur.plateau_actuelX + 1)
					 else (joueur.plateau_actuelX <- 0));
					screen()
				)else (joueur.posX1 <- (joueur.posX1 +. 8.)));
				joueur.last_move <- "6";
				sprite_step joueur
		)else ())
	|4 ->
		(
			if((getCaseSet joueur).(10 - y).(nx - 1) != 1 && (getCaseSet joueur).(10 - ny).(nx - 1) != 1)then(
				(if (joueur.posX1 -. 8. <= 1.) then(
					move_out_screen items;
					joueur.posX1 <- 448.;
					(if(joueur.plateau_actuelX > 0) then(joueur.plateau_actuelX <- joueur.plateau_actuelX - 1)
					 else (joueur.plateau_actuelX <- ((Array.length map.full_map) - 1)));
					screen()
				)else (joueur.posX1 <- (joueur.posX1 -. 8.)));
				joueur.last_move <- "4";
				sprite_step joueur
			)else ())
	|2 ->
		(
			if((getCaseSet joueur).(10 - ny + 1).(x) != 1 && (getCaseSet joueur).(10 - ny + 1).(nx) != 1)then(
				(if(joueur.posY1 -. 8. <= 1.) then(
					move_out_screen items;
					joueur.posY1 <- 288.;
					(if (joueur.plateau_actuelY > 0) then (joueur.plateau_actuelY <- joueur.plateau_actuelY - 1)
					 else (joueur.plateau_actuelY <- ((Array.length map.full_map.(0)) - 1)));
					screen()
				)else (joueur.posY1 <- (joueur.posY1 -. 8.)));
				joueur.last_move <- "2";
				sprite_step joueur
			)else ())
	|_ -> ()
;;

let use_obj_anim hand=
	player1.step <- "3";
	player1.use <- hand;
	Thread.delay 0.1;
	player1.step <- "0";
	player1.use <- 0
;;

let rec refresh ()=
	(*
	(match ic with
	| _ -> close_graph ();
		Unix.shutdown_connection ic
	);
	*)
	let playX = (int_of_float (player1.posX1))/32 in
	let playY = (int_of_float (player1.posY1))/32 in
	auto_synchronize false;
	Graphics.draw_image !background 0 0;
	let _ = if (player1.pv > 0) then
		(
		draw_obj ();
		draw_entity (spritename player1.player_specs.sprite player1.last_move player1.step) player1.posX1 player1.posY1
		)
		else (print_endline "GAME OVER!"; close_graph ())
	in
	(let rec match_monsterlist z =
		match z with
		|[] -> Thread.delay 0.1
		|(1,a,x,y,w) :: z ->
			if (!w > 0) then (
				(let direction = mv1 !x !y in
					monster_behavior a direction x y;
					draw_entity (spritename a.ennemi_specs.sprite a.ennemi_last_move a.ennemi_step) !x !y;
					let _ = if ((int_of_float (!x)/32) == playX && (int_of_float(!y)/32) == playY) then
						(player_damage player1 a) in match_monsterlist z)
			)else(match_monsterlist z)
		|(2,a,x,y,w) :: z ->
			if (!w > 0) then (
			(let direction = (mv2 player1.posX1 player1.posY1 !x !y) in
				monster_behavior a direction x y;
			  draw_entity (spritename a.ennemi_specs.sprite a.ennemi_last_move a.ennemi_step) !x !y;
				let _ = if ((int_of_float (!x)/32) == playX && (int_of_float(!y)/32) == playY) then
					(player_damage player1 a) in match_monsterlist z)
				)else (match_monsterlist z)
		|(3,a,x,y,w) :: z ->
			if (!w > 0) then (
				mv3 a x y;
				draw_entity (spritename a.ennemi_specs.sprite a.ennemi_last_move a.ennemi_step) !x !y;
				let _ = if ((int_of_float (!x)/32) == playX && (int_of_float(!y)/32) == playY) then
					(player_damage player1 a) in match_monsterlist z
			)else (match_monsterlist z)
		|_-> Thread.delay 0.;
	in match_monsterlist (getEnnemis player1));
	(let rec match_items plateau_items =
		match plateau_items with
		|[] -> ()
		|(_,w,x,y,z) :: plateau_items->
			if (!z == 0) then (
				draw_entity !w !x !y;
				if ((int_of_float (!x)/32) == playX && (int_of_float (!y)/32) == playY) then(
					(if (!w = "sprite/object/sword_2.png") then (
						heart_pickup player1
					)else(
						money_pickup player1
					));
					z := 1;
					match_items plateau_items
				)else(match_items plateau_items)
			)else(match_items plateau_items)
	in match_items (getItems player1));
	auto_synchronize true;
	(if (player1.can_attack > 0) then (
		player1.can_attack <- player1.can_attack -1
	)else ());
	(if (player1.delai_mouvement > 0) then (
		player1.delai_mouvement <- 0
	)else ());
	refresh ()
;;

let rec input () =
	(if key_pressed () then (
		match read_key () with
		| 'z' ->if (player1.delai_mouvement == 0) then(
				move player1 8;
				player1.delai_mouvement <- 1
			)else()
	    	| 's' ->if (player1.delai_mouvement == 0) then(
				move player1 2;
				player1.delai_mouvement <- 1
			)else()
	    	| 'q' ->if (player1.delai_mouvement == 0) then(
				move player1 4;
				player1.delai_mouvement <- 1
			)else()
	    	| 'd' ->if (player1.delai_mouvement == 0) then(
				move player1 6;
				player1.delai_mouvement <- 1
			)else()
 	   	| 'j' ->if (player1.can_attack == 0) then (
				let rec is_monster_attacked z=
				 	match z with
					|(ennemi_id,ennemi,x,y,ennemi_pv) :: z ->(
						player_attack player1 ennemi ennemi_id ennemi_pv x y;
						is_monster_attacked z)
					|_ -> ()
				in 
				is_monster_attacked (getEnnemis player1);
				use_obj_anim 1;
				player1.can_attack <- 3;
			)else()
	    	| 'k' -> move player1 0
		| 'l' -> move player1 0
    		| _   -> ()
  		)
  	else()
	);
	input ()
;;

(*main*)
let _ =
	(* 16(taille original du pixel art)x2 x16(nombre de bloc par colonne ou ligne) = 512 *)
	set_window_title "Zelda NES";
	(*draw_sreen ((map.full_map.(player1.plateau_actuelY).(player1.plateau_actuelX)).caseSet) 0 0;*)
	screen ();
	let _ = Thread.create refresh () in
    	input ()
;;
