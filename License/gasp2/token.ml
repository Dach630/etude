type token =
  LETINP| LETSTK| LETSTA| VIR| LPAREN| RPAREN| JUMP| POIVIR|  ALINP| ALSTK| ALSTA| STATE| STACK| TRANS| EOF


let to_string = function
    	LETINP -> "LETINP"
	| LETSTK -> "LETSTK"
	| LETSTA -> "LETSTA"
	| VIR -> "VIR"
	|JUMP -> "JUMP"
	| LPAREN -> "LPAREN"
	| RPAREN -> "RPAREN"
	| POIVIR -> "POIVIR"
	| ALINP -> "ALINP"
	| ALSTK -> "ALSTK"
	| ALSTA -> "ALSTA "
	| STATE -> "STATE"
	| STACK -> "STACK"
	| TRANS -> "TRANS"
  	| EOF -> "EOF"
