let casesetA =
	[|
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;1;0;1;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;1;0;1;1;1;1;1;1;1;1|];
	[|0;0;1;1;1;1;1;0;1;1;1;1;1;1;0;0|];
	[|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
	[|0;0;1;1;1;1;1;0;1;1;1;1;1;1;0;0|];
	[|1;1;1;1;1;1;1;0;1;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;1;0;1;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
	|]
;;

let casesetB =
	[|
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;0;0;0;0;1;1;0;1;1;1;1;1;1;1;1|];
	[|1;0;0;0;0;1;1;0;0;0;0;0;0;0;0;1|];
	[|0;0;0;0;0;1;1;1;1;0;0;0;0;0;0;0|];
	[|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
	[|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
	[|1;1;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
	[|1;1;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
	[|1;1;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
	|]
;;

let casesetC =
	[|
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;1;1;0;1;1;0;0;1;1;1|];
	[|1;1;1;1;1;1;1;1;0;1;0;0;0;0;1;1|];
	[|0;0;1;1;1;1;1;1;0;1;0;0;0;0;0;0|];
	[|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
	[|0;0;1;1;1;1;1;1;0;1;0;0;0;0;0;0|];
	[|1;1;1;1;1;1;1;1;0;1;0;0;0;0;0;1|];
	[|1;1;1;1;1;1;1;1;0;1;0;0;0;0;0;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
	|]
;;

let casesetD =
	[|
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;0;0;1;1;1;1;1;0;1;1;1;1;1;1;1|];
	[|1;0;0;0;1;1;1;1;0;1;1;1;1;1;1;1|];
	[|0;0;0;0;0;1;1;1;0;1;1;1;1;1;0;0|];
	[|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
	[|0;0;0;0;0;1;1;1;0;1;1;1;1;1;0;0|];
	[|1;0;0;0;1;1;1;1;0;1;1;1;1;1;1;1|];
	[|1;0;0;1;1;1;1;1;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
	|]
;;

let casesetE =
	[|
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;0;1;1;1;1;1;1|];
	[|1;1;1;0;0;0;0;0;0;0;0;0;0;0;0;1|];
	[|1;1;0;0;1;0;0;0;0;0;0;0;0;0;0;1|];
	[|0;0;0;0;0;0;1;0;0;0;0;0;0;0;0;0|];
	[|0;0;0;0;1;0;0;0;1;0;0;0;0;0;0;0|];
	[|0;0;0;0;0;0;1;0;0;0;0;0;0;0;0;0|];
	[|1;1;0;0;1;0;0;0;0;0;0;0;0;0;0;1|];
	[|1;1;1;0;0;0;0;0;0;0;0;0;0;0;0;1|];
	[|1;1;1;1;1;1;0;0;0;0;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
	|]
;;

let casesetF =
	[|
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
	[|1;0;0;0;0;0;0;0;0;0;0;0;1;0;0;1|];
	[|0;0;0;0;0;0;0;0;0;0;1;0;0;0;0;0|];
	[|0;0;0;0;0;0;0;0;1;0;0;0;1;0;0;0|];
	[|0;0;0;0;0;0;0;0;0;0;1;0;0;0;0;0|];
	[|1;0;0;0;0;0;0;0;0;0;0;0;1;0;0;1|];
	[|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
	[|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
	|]
;;

let casesetG =
  [|
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
  [|1;1;1;1;1;1;0;0;0;1;1;0;0;0;0;1|];
  [|1;1;1;1;1;1;0;0;0;0;0;0;0;0;0;1|];
  [|0;0;1;1;1;0;0;0;0;0;0;0;0;0;0;0|];
  [|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
  [|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
  |]
;;

let casesetH =
  [|
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
  [|1;1;1;1;1;1;0;0;0;0;0;1;1;1;1;1|];
  [|1;0;0;1;1;1;1;1;1;1;0;1;1;1;1;1|];
  [|1;0;0;0;1;1;1;1;1;1;0;1;1;1;0;1|];
  [|0;0;0;0;0;1;1;1;1;1;0;1;1;0;0;0|];
  [|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
  [|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
  |]
;;

let casesetI =
  [|
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;1;0;1;0;0;0;0;0;0;1|];
  [|0;0;0;0;0;0;1;1;1;0;0;0;0;0;0;0|];
  [|0;0;0;0;0;0;1;0;1;0;0;0;0;0;0;0|];
  [|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
  |]
;;

let casesetJ =
  [|
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;1;1;1;0;0;0;0;0;0;1|];
  [|0;0;0;0;0;0;1;0;1;0;0;0;0;0;0;0|];
  [|0;0;0;0;0;0;1;1;1;0;0;0;0;0;0;0|];
  [|0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
  |]
;;

let casesetK =
  [|
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|0;0;0;0;0;0;1;1;1;0;0;0;0;0;0;0|];
  [|0;0;0;0;0;0;1;1;1;0;0;0;0;0;0;0|];
  [|0;0;0;0;0;0;1;1;1;0;0;0;0;0;0;0|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;1|];
  [|1;1;1;1;1;1;0;0;0;1;1;1;1;1;1;1|]
  |]
;;
