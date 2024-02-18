{
open Token
}

let inputs = ['a'-'z']
let stack = ['A'-'Z']
let states = ['0'-'9']+

rule main = parse
	| ' '			{ main lexbuf }
	| '\n'			{JUMP}
 	| inputs			{ LETINP }
	| stack 			{ LETSTK }
	| states			{ LETSTA }
	| ','			{ VIR }
	| '\n'			{JUMP}
	| ')'			{ RPAREN }
	| '('			{ LPAREN }
	| ';'			{ POIVIR }
	| "input symbols :"		{ ALINP }
	| "stack symbols :"		{ ALSTK }
	| "states :" 		{ ALSTA }
	| "initial state :"		{ STATE }
	| "initial stack :"		{ STACK }
	| "transitions :"		{ TRANS }
	| eof			{ EOF }
	| _			{ failwith "unexpected character in lexeur" }
