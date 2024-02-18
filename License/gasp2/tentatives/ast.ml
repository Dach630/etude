type nice =
	| OK
	| LETINP
	| LETSTK
	| LETSTA
	| VIR
	| LPAREN
	| RPAREN
	| POIVIR
	| ALINP
	| ALSTK
	| ALSTA
	| STATE
	| STACK
	| TRANS
	| EOF


let good = function
	| OK -> true
        |_ -> false
