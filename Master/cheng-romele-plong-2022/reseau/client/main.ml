open Graphics;;
open String;;
open Types;;


let _ = open_graph " 512x448";;


let ecran ={
	tileset = [||];
	plateau = [||];
	imgPlat = Graphic_image.of_image (Png.load_as_rgb24 "sprite/Empty.png" []);
	listJou = [];
	listEnn = [];
	listObj = [];
	chargement  = false;
	move = true;
};;

let xgraph = [|0;32;64;96;128;160;192;224;256;288;320;352;384;416;448;480|];;
let ygraph =[|320;288;256;224;192;160;128;96;64;32;0|];;

let rec draw_sreen set x y =
	Graphics.draw_image (ecran.tileset.((set.(y)).(x))) (xgraph.(x)) (ygraph.(y));
	
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

let rec draw_entity list=
	match list with
	|[] -> ()
	|h :: t -> 
		let img = Graphic_image.of_image (Png.load_as_rgb24 (h.sprite) []) in
		Graphics.draw_image (img) (h.x) (h.y);
		draw_entity t
;;


let screen () =
	draw_sreen (ecran.plateau) 0 0;
	ecran.imgPlat <- get_image 0 0 512 448
;;

let rec refresh_screen () = 
	auto_synchronize false;
	Graphics.draw_image ecran.imgPlat 0 0;
	(if (not ecran.chargement) 
		then(
		draw_entity ecran.listObj;
		draw_entity ecran.listEnn;
		draw_entity ecran.listJou;
		)
	);
	auto_synchronize true;
	refresh_screen ()
;;

(*
close_graph ();		
Unix.shutdown_connection ic
*)
(*name of sprite| name of sprite ...*)

let change_tileset str = 
	let list_name = split_on_char '|' str in
	let rec list_img list res=
		match list with
		|[] -> List.rev res
		|h :: t -> 
		list_img t ((Graphic_image.of_image (Png.load_as_rgb24 (h) [])) :: res) 
	in
	ecran.tileset <- Array.of_list (list_img list_name [])
;;

let listEntity str = 
	let list = split_on_char '|' str in
	let rec list_of_entity list res =
		match list with
		|[] -> res
		|h :: t ->
			let tmp = split_on_char ';' h in
			let arr = Array.of_list tmp in
			let enti = {
				sprite = arr.(1);
				x= int_of_string arr.(2);
				y= int_of_string arr.(3);
			}in
			list_of_entity t (enti :: res)
	in
	list_of_entity list []
;;

let change_pla str =
	let list = split_on_char '|' str in
	let rec list_of_int list res =
		match list with
		|[] -> Array.of_list(List.rev res)
		|h :: t -> list_of_int t ((int_of_string h) :: res)
	in
	let rec list_array_int listStr res =
		match listStr with
		|[] -> Array.of_list(List.rev res)
		|h :: t -> list_array_int t ( (list_of_int (split_on_char ';' h) []):: res)
	in
	ecran.plateau <- list_array_int list []
;;

let list_empty list =
	match list with
	|[] -> true
	| _ -> false
;;

(*type:information*)
let rec refresh_info ic =
	let split = split_on_char ':' (input_line ic) in 
	(match split with
	|"JOU" :: t -> 
		let list = listEntity (List.hd t) in
		ecran.listJou <- list
	|"ENN" :: t-> 
		let list = listEntity (List.hd t) in
		ecran.listEnn <- list
	|"OBJ" :: t-> 
		let list = listEntity (List.hd t) in
		ecran.listObj <- list;
		if ecran.chargement then (*changement complete fin du tableau de jeu*)
			(ecran.move <- true;		
			ecran.chargement <- false;
		)else ()
	|"GO" :: t ->
		if(list_empty t) then(
			ecran.move <- true
		)else()
	|"PLA" :: t-> (*changement complete debut du tableau de jeu*)
		ecran.chargement <- true;
		ecran.move <- false;
		change_pla (List.hd t) ;
		screen ();
	|"TIL" :: t ->
		change_tileset (List.hd t);
		screen ()
	|"QUIT" :: t->
		if(list_empty t) then(
			close_graph ();		
			Unix.shutdown_connection ic;
			failwith ("end")
		)else()
	| _ -> () 	
	);
	refresh_info ic
;;

let rec input oc =
  	(if (key_pressed ()) && (ecran.move) then (
	   	match read_key () with
    		| 'z' -> output_string oc ("Z") ;
       	   		flush oc
	    	| 's' -> output_string oc ("S") ;
       	  		flush oc
	    	| 'q' -> output_string oc ("Q") ;
       	   		flush oc
	    	| 'd' -> output_string oc ("D") ;
       	   		flush oc
 	   	| 'j' -> output_string oc ("J") ;
       			flush oc;
			ecran.move <- false
	    	| 'k' -> output_string oc ("K") ;
       		   	flush oc;
			ecran.move <- false
		| 'l' -> output_string oc ("L") ;
       		   	flush oc;
			ecran.move <- false
		| '!' -> output_string oc ("QUIT") ;
       		   	flush oc;
			ecran.move <- false
    		| _   -> ()	
  		)
  	else()
	);
	input oc
;;



let get_my_addr () = (Unix.gethostbyname(Unix.gethostname())).Unix.h_addr_list.(0) ;;

(*main*)
let _ =
	let serveur_adr = get_my_addr () in
	let port = 1400 in
	let sockadr = Unix.ADDR_INET(serveur_adr, port) in
	let ic, oc = Unix.open_connection sockadr in
	(* 16(taille original du pixel art)x2 x16(nombre de bloc par colonne ou ligne) = 512 *)
	set_window_title "Zelda NES multi";
	
	let _ = Thread.create refresh_info ic in
	(while not (equal (input_line ic) "GO") do
		print_endline "chargement...";
	done);	
	let _ = Thread.create refresh_screen () in
    	input oc
;;
