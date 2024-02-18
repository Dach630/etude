open Types;;
open Entities;;
open Casesets;;

let xgraph = [|0;32;64;96;128;160;192;224;256;288;320;352;384;416;448;480|];;
let ygraph =[|320;288;256;224;192;160;128;96;64;32;0|];;

let tabA = new plateau casesetA [] [] 0;;

let get_surroundings_y i j xlength arr piece =
	if (j == xlength-1) then (
		if ((arr.(i).(0)#id == piece) || (arr.(i).(j-1)#id == piece)) then 1 else 0
	)else if (j==0) then (
		if ((arr.(i).(j+1)#id == piece) || (arr.(i).(xlength-1)#id == piece)) then 1 else 0
	)else(
		if ((arr.(i).(j+1)#id == piece) || (arr.(i).(j-1)#id == piece)) then 1 else 0
	)
;;

let get_surroundings i j ylength xlength arr piece=
	if (i == ylength-1) then (
		if ((arr.(0).(j)#id  == piece) || (arr.(i-1).(j)#id == piece)) then 1 else (
			get_surroundings_y i j xlength arr piece
		)
	)else if (i > 0) then (
		if ((arr.(i+1).(j)#id  == piece) || (arr.(i-1).(j)#id == piece)) then 1 else (
			get_surroundings_y i j xlength arr piece
		)
	)else(
		if ((arr.(i+1).(j)#id  == piece) || (arr.(ylength-1).(j)#id == piece)) then 1 else (
			get_surroundings_y i j xlength arr piece
		)
	)
;;

let rec choose i j ylength xlength arr =
	let piece = (Random.self_init();Random.int 11) in
	if ((get_surroundings i j ylength xlength arr piece) == 1)
		then (choose i j ylength xlength arr) else piece
;;

let rec map_generate i j ylength xlength arr =
	let selected_case = choose i j ylength xlength arr in
	let generate_plateau selected_case =
		match selected_case with
		|0 -> casesetA
		|1 -> casesetB
		|2 -> casesetC
		|3 -> casesetD
		|4 -> casesetE
		|5 -> casesetF
		|6 -> casesetG
		|7 -> casesetH
		|8 -> casesetI
		|9 -> casesetJ
		|10 -> casesetK
		|_ -> casesetA
	in
	let generate_ennemis selected_case =
		match selected_case with
		|5 -> [(1,ennemi1,ref 64.0,ref 64.0,ref 5);(2,ennemi2,ref 352.0,ref 224.0,ref 5);(3,ennemi3,ref 100.,ref 100.,ref 5)]
		|0 -> []
		|2 -> []
		|3 -> []
		|_ -> [(1,ennemi1,ref 160.,ref 64.,ref 5)]
	in
	let generate_items selected_case =
		match selected_case with
		|5 -> [(1,ref "",ref 0.,ref 0.,ref 1);(2,ref "",ref 0.,ref 0.,ref 1);(3,ref "",ref 0.,ref 0.,ref 1)]
		|0 -> []
		|2 -> []
		|3 -> []
		|_ -> [(1,ref "",ref 0.,ref 0.,ref 1)]
	in
	let plat = new plateau (generate_plateau selected_case) (generate_ennemis selected_case) (generate_items selected_case) selected_case in
	if (i < ylength-1) then(
		if (j < xlength-1) then(
			if (i == 0 && j == 0) then (
				arr.(i).(j) <- new plateau casesetF [(1,ennemi1,ref 64.0,ref 64.0,ref 5);(2,ennemi2,ref 352.0,ref 224.0,ref 5);(3,ennemi3,ref 100.,ref 100.,ref 5)] [(1,ref "",ref 0.,ref 0.,ref 1);(2,ref "",ref 0.,ref 0.,ref 1);(3,ref "",ref 0.,ref 0.,ref 1)] (5);
				map_generate i (j+1) ylength xlength arr
			)else(
				arr.(i).(j) <- plat;
				map_generate i (j+1) ylength xlength arr
			)
		)else(
			arr.(i).(j) <- plat;
			map_generate (i+1) 0 ylength xlength arr
		)
	)else(
		if (j < xlength-1) then (
			arr.(i).(j) <- plat;
			map_generate i (j+1) ylength xlength arr
		)else (arr)
	)
;;


let base_map = [|[|tabA;tabA;tabA;tabA|];[|tabA;tabA;tabA;tabA|];[|tabA;tabA;tabA;tabA|];[|tabA;tabA;tabA;tabA|]|];;

let map = {
	full_map = map_generate 0 0 4 4 base_map
};;
