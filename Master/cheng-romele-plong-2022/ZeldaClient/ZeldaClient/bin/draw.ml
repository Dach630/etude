open Graphics;;
open Types;;
open Entities;;
open Worldmap;;
open Movements;;
let _ = open_graph " 512x352";;

let block = Graphic_image.of_image (Png.load_as_rgb24 "sprite/dungeon/block_5_0.png" []);;
let ground = Graphic_image.of_image (Png.load_as_rgb24 "sprite/overworld/sol_0_0.png" []);;
let background = ref(Graphic_image.of_image (Png.load_as_rgb24 "sprite/Empty.png" []));;

let rec draw_sreen set x y =
	(if ((set.(y)).(x) = 0) then
		Graphics.draw_image ground (xgraph.(x)) (ygraph.(y))
	else
		Graphics.draw_image block (xgraph.(x)) (ygraph.(y))
	);
	(if(x != 15 || y != 10) then
		(if(x == 15) then
			(if(y != 10) then
				draw_sreen set 0 (y+1)
			else ()
			)
		else draw_sreen set (x + 1) y
		)
	else ()
	)
;;

let spritename name move step = "./sprite/" ^ name ^ move ^"_"^ step ^".png";;

let screen () =
	draw_sreen (getCaseSet player1) 0 0;
	background := get_image 0 0 512 352
;;

let draw_obj () =
	let playX = (player1.posX1) in
	let playY = (player1.posY1) in
	match player1.use with
	|1 -> ((*toujours une epee*)
		match player1.last_move with
		|"2" ->draw_entity ("sprite/object/sword_2.png") playX (playY -. 24.)
		|"4" ->draw_entity ("sprite/object/sword_4.png") (playX -. 24.) playY
		|"6" ->draw_entity ("sprite/object/sword_6.png") (playX +. 24.) playY
		|"8" ->draw_entity ("sprite/object/sword_8.png") playX (playY +. 24.)
		| _ -> ()
		)
	|2 -> ()
	|3 -> ()
	| _ -> ()
;;
