open Types;;
open Worldmap;;
open Entities;;
(*open Dijkstra;;*)

let getCaseSet joueur =
	(map.full_map.(joueur.plateau_actuelY).(joueur.plateau_actuelX))#caseSet;;

let getEnnemis joueur =
		(map.full_map.(joueur.plateau_actuelY).(joueur.plateau_actuelX))#ennemis;;

let getItems joueur =
		(map.full_map.(joueur.plateau_actuelY).(joueur.plateau_actuelX))#items;;

let can_go_right x y =
	if((getCaseSet player1).(10 - y).(x + 1) != 1 && x + 1 < 15 ) then true else false;;

let can_go_up x y=
	if((getCaseSet player1).(10 - y - 1).(x) != 1 && y + 1 < 10) then true else false;;

let can_go_down x y =
	let ny = (int_of_float (y +. 31.0)) / 32 in
	if((getCaseSet player1).(10 - ny + 1).(x) != 1 && y -. 32. >= 0.2)then true else false;;

let can_go_left x y =
	let nx = (int_of_float (x +. 31.0)) / 32 in
	if((getCaseSet player1).(10 - y).(nx - 1) != 1 && x -. 32. >= 0.2) then true else false;;

let mv1 posX posY =
	let x = (int_of_float (posX)) / 32 in
	let y = (int_of_float (posY)) / 32 in
	match (ennemi1.ennemi_last_move) with
	|"6" -> if (can_go_right x y) then "6" else
				if (can_go_up x y) then "8" else
				if (can_go_left posX y) then "4" else
				if (can_go_down x posY) then "2" else "0"
	|"8" -> if (can_go_up x y) then "8" else
				if (can_go_left posX y) then "4" else
				if (can_go_down x posY) then "2" else
				if (can_go_right x y) then "6" else "0"
	|"4" -> if (can_go_left posX y) then "4" else
				if (can_go_down x posY) then "2" else
				if (can_go_right x y) then "6" else
				if (can_go_up x y) then "8" else "0"
	|"2" -> if (can_go_down x posY) then "2" else
				if (can_go_right x y) then "6" else
				if (can_go_up x y) then "8" else
				if (can_go_left  posX y) then "4" else "0"
	|_-> "0"
;;

(* let mv2 px py ex ey =
	let poseX = ((int_of_float (ex)) / 32) in
	let poseY = ((int_of_float (ey)) / 32) in
	let pospX = ((int_of_float (px)) / 32) in
	let pospY = ((int_of_float (py)) / 32) in
	if ((pospY > 0 || pospY < (Array.length (getCaseSet player1))) && (pospX > 0 || pospX < (Array.length (getCaseSet player1).(pospY)))) then (
		let arr = Array.make 10 (Array.make 15 0) in
		let to_be_visited = Array.make 100 (0,999,0,0,0) in
		let to_visit = fill_visited (getCaseSet player1) arr 0 0 (pospX-1) (pospY-1) in
		to_be_visited.(0) <- (0,0,0,(poseY),(poseX));
		let path = dijkstra to_visit to_be_visited [] in
		if ((List.length path) == 1) then(
		)else if ((List.length path) > 1) then (
			let dir = List.nth path 1 in
			if ((dir == 2) && (can_go_down poseX ey)) then (
				"2"
			)else if ((dir == 6) && (can_go_right poseX poseY)) then (
				"6"
			)else if ((dir == 8) && (can_go_up poseX poseY)) then (
				"8"
			)else if ((dir == 4) && (can_go_left ex poseY)) then (
				"4"
			)else("0")
		)else("0")
	)else ("0")
;;
*)

let mv2 x y posX posY =
	let px = (int_of_float x) / 32 in
	let py = (int_of_float y) / 32 in
	let ex = (int_of_float posX) / 32 in
	let ey = (int_of_float posY) / 32 in
	if (px-ex > 0) then
		if (can_go_right ex ey) then "6" else
		if (can_go_up ex ey) then "8" else
		if (can_go_down ex posY) then "2" else
		if (can_go_left posX ey) then "4" else "0"
	else if (px-ex < 0) then
		if (can_go_left posX ey) then "4" else
		if (can_go_down ex posY) then "2" else
		if (can_go_up ex ey) then "8" else
		if (can_go_right ex ey) then "6" else "0"
	else if (py-ey > 0) then
		if (can_go_up ex ey) then "8" else
		if (can_go_left posX ey) then "4" else
		if (can_go_right ex ey) then "6" else
		if (can_go_down ex posY) then "2" else "0"
	else if (py-ey < 0) then
		if (can_go_down ex posY) then "2" else
		if (can_go_right ex ey) then "6" else
		if (can_go_left posX ey) then "4" else
		if (can_go_up ex ey) then "8" else "0"
	else "0"
;;

let ennemi_sprite_step monster =
	if(monster.ennemi_step == "0") then
  	monster.ennemi_step <- "1"
	else
		monster.ennemi_step <- "0"
;;

let sprite_step joueur =
	if(joueur.step == "0") then
  	joueur.step <- "1"
	else
		joueur.step <- "0"
;;

let monster_behavior monster direction posX posY=
	match direction with
	|"8" ->
		posY := !posY +. monster.ennemi_specs.vitesse;
		monster.ennemi_last_move <- "8";
		ennemi_sprite_step monster
	|"4" ->
		posX := !posX -. monster.ennemi_specs.vitesse;
		monster.ennemi_last_move <- "4";
		ennemi_sprite_step monster
	|"6" ->
		posX := !posX +. monster.ennemi_specs.vitesse;
		monster.ennemi_last_move <- "6";
		ennemi_sprite_step monster
	|"2" ->
		posY := !posY -. monster.ennemi_specs.vitesse;
		monster.ennemi_last_move <- "2";
		ennemi_sprite_step monster
	|_ -> ()
;;

let mv3 monster posX posY =
	let x = (int_of_float !posX) / 32 in
	let y = (int_of_float !posY) / 32 in
	if (monster.timeswalked mod 5 <> 0) then (
    match monster.ennemi_last_move with
    |"8" -> if (can_go_up x y) then (
 		  monster_behavior monster (monster.ennemi_last_move) posX posY;
			monster.timeswalked <- monster.timeswalked+1
      ) else (monster.timeswalked <- monster.timeswalked+1)
    |"4" -> if (can_go_left !posX y) then (
      monster_behavior monster (monster.ennemi_last_move) posX posY;
			monster.timeswalked <- monster.timeswalked+1
      ) else (monster.timeswalked <- monster.timeswalked+1)
    |"6" -> if (can_go_right x y) then (
      monster_behavior monster (monster.ennemi_last_move) posX posY;
			monster.timeswalked <- monster.timeswalked+1
      ) else (monster.timeswalked <- monster.timeswalked+1)
    |"2" -> if (can_go_down x !posY) then (
      monster_behavior monster (monster.ennemi_last_move) posX posY;
			monster.timeswalked <- monster.timeswalked+1
      ) else (monster.timeswalked <- monster.timeswalked+1)
    |_ -> ()
	) else (
		let direction = Random.int 4 in
		match direction with
		|0 ->
			if (can_go_up x y) then (
				monster_behavior monster "8" posX posY;
				monster.ennemi_last_move <- "8";
				monster.timeswalked <- monster.timeswalked+1
			) else ()
		|1 ->
			if (can_go_left !posX y) then (
				monster_behavior monster "4" posX posY;
				monster.ennemi_last_move <- "4";
				monster.timeswalked <- monster.timeswalked+1
			) else()
		|2 ->
			if (can_go_right x y) then (
				monster_behavior monster "6" posX posY;
				monster.ennemi_last_move <- "6";
				monster.timeswalked <- monster.timeswalked+1
			)else()
		|3 ->
			if (can_go_down x !posY) then (
				monster_behavior monster "2" posX posY;
				monster.ennemi_last_move <- "2";
				monster.timeswalked <- monster.timeswalked+1
			)else()
		|_ -> ()
	);;
