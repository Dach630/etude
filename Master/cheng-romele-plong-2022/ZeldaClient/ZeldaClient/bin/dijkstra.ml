let rec fill_visited cases tab i j pX pY =
	if (i < 9) then (
		if (j < 14) then (
			if (pY == i && pX == j ) then (
				tab.(i).(j) <- 2;
				fill_visited cases tab i (j+1) pX pY
			)else if (cases.(i).(j) == 1) then (
				tab.(i).(j) <- 1;
				fill_visited cases tab i (j+1) pX pY
			)else(
				tab.(i).(j) <- 0;
				fill_visited cases tab i (j+1) pX pY
			)
		)else(fill_visited cases tab (i+1) 0 pX pY)
	)else tab
;;

let change_min case v min dir =
	match case with
	|(_,a,_,y,x) ->
		if (min <= a) then (v,min,dir,y,x)
		else (case)
;;

let rec new_case arr pos y x =
	if (pos+1 < Array.length arr) then (
		match arr.(pos) with
		|(0,0,999,0,0) -> (arr.(pos) <- (0,0,999,y,x); pos)
		|(_,_,_,_,_) -> new_case arr (pos+1) y x
	)else(
		match arr.(pos) with
		|(0,0,999,0,0) -> (arr.(pos) <- (0,0,999,y,x); pos)
		|(_,_,_,_,_) -> 0
	)
;;

let rec find_case arr pos y x =
	if (pos+1 < Array.length arr) then (
		match arr.(pos) with
		|(_,_,_,i,j) ->
			(if (i==y && j==x) then (pos)
			else(find_case arr (pos+1) y x))
	)else (
		match arr.(pos) with
		|(_,_,_,i,j) ->
			(if (i==y && j==x) then (pos)
			else(new_case arr 0 y x))
	)
;;

let add_element tab arr y x a dir =
	let point = find_case arr 0 y x in
	let v = tab.(y).(x) in
	arr.(point) <- change_min arr.(point) v (a+1) dir
;;

let rec find_min arr pos n min dir posY posX=
	if (pos < (Array.length arr)) then (
		match arr.(pos) with
			|(0,a,b,c,d) ->
				if (a < min) then (find_min arr (pos+1) pos a b c d)
				else (find_min arr (pos+1) n min dir posY posX)
			|(2,a,b,c,d) ->
				if (a < min) then (find_min arr (pos+1) pos a b c d)
				else (find_min arr (pos+1) n min dir posY posX)
			|(_,_,_,_,_) -> find_min arr (pos+1) n min dir posY posX
	)else (
		[|n;min;dir;posY;posX|]
	)
;;

let rec dijkstra tab to_be_visited path =
	let coords = find_min to_be_visited 0 0 999 0 0 0 in
	let posX = coords.(4) in
	let posY = coords.(3) in
	let dir = coords.(2) in
	let min = coords.(1) in
	let pos = coords.(0) in
	let newpath =  path @ [dir] in
	match tab.(posY).(posX) with
	|2 -> newpath
	|0 ->
		(
			to_be_visited.(pos) <- (1,9999,dir,posY,posX);
			(if (tab.(posY).(posX+1) != 1) then (
				add_element tab to_be_visited posY (posX+1) (min+1) 6
			)else());
			(if (tab.(posY+1).(posX) != 1) then (
				add_element tab to_be_visited (posY+1) posX (min+1) 8
			)else());
			(if (tab.(posY).(posX-1) != 1 ) then (
				add_element tab to_be_visited posY (posX-1) (min+1) 4
			)else());
			(if (tab.(posY-1).(posX) != 1 ) then (
				add_element tab to_be_visited (posY-1) posX (min+1) 2
			)else());
			dijkstra tab to_be_visited newpath
		)
	|_ -> newpath
;;
