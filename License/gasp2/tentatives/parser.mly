%{
open Ast
%}

%token LETINP LETSTK LETSTA VIR JUMP LPAREN RPAREN POIVIR ALINP ALSTK ALSTA STATE STACK TRANS EOF

%start<Ast.nice> input

%%

input: automate 			{OK}

automate:
declarations; transitions		{OK}

declarations:
inputs; stack; states; initStates; initStack	{OK}

inputs:
ALINP; LETINP; input_symbols 	{OK}

input_symbols:
VIR; LETINP; input_symbols		{OK}
| JUMP 				{OK}

stack:
ALSTK; LETSTK; stack_symbols	{OK}

stack_symbols:
 VIR; LETSTK; stack_symbols	 	{OK}
| JUMP 				{OK}

states:
ALSTA; LETSTA; states_symbols 	{OK}

states_symbols:
VIR; LETSTA; states_symbols		{OK}
| JUMP 				{OK}

initStates:
STATE; LETSTA; JUMP 		{OK}

initStack:
STACK; LETSTK; JUMP		{OK}

transitions:
TRANS; JUMP; allTransi 		{OK}

Transi:
LPAREN; LETSTA; VIR; LETINP; VIR; LETSTK; VIR; LETSTA; VIR; LETSTK; POIVIR; LETSTK; RPAREN 	{OK}
|LPAREN; LETSTA; VIR; LETINP; VIR; LETSTK; VIR; LETSTA; VIR; LETSTK; RPAREN 			{OK}
|LPAREN; LETSTA; VIR; LETINP; VIR; LETSTK; VIR; LETSTA; RPAREN 				{OK}
|LPAREN; LETSTA; VIR; VIR; LETSTK; VIR LETSTA; RPAREN 					{OK}

allTransi:
 Transi; JUMP; allTransi  		{OK}
| Transi;  EOF			{OK}
