.ORIG x3000

;LEA R6, stbot

main :    ADD R6,R6,-3
          LEA R1,string  	;pointeur de la chaîne
          STR R1,R6,0     ;arg0 <- R1
          LD  R2,char     ;code ASCII du caractère
          NOT R2,R2
          ADD R2,R2,1    	;R2 = -R2
          STR R2,R6,1     ;arg1 <- R2
          JSR index       ;index(arg0,arg1)
          JSR rindex      ;rindex(arg0,arg1)
          LEA R2,char     ;pointeur de la chaîne
          STR R2,R6,1     ;arg1 <- R2
          JSR strcmp
          JSR strcpy      ;strcpy(arg0,arg1);
          AND R0,R0,0
          ADD R0,R0,4
          STR R0,R6,2     ;arg2 <- R0
          JSR strncpy     ;strncpy(arg0,arg1,arg2)
          ADD R6,R6,3
          AND R0,R0,0
          AND R1,R1,0
          AND R2,R2,0
          TRAP x25

rindex :  ADD R6,R6,-6    ;prologue
          STR R0,R6,0
          STR R1,R6,1
          STR R2,R6,2
          STR R3,R6,3
          STR R4,R6,4
          STR R7,R6,5

          AND R0,R0,0
          AND R4,R4,0    	;compteur

looprind: LDR R3,R1,0  	  ;code ASCII du caractère dans R1
          BRz finrind     ;test de fin de la chaîne
          ADD R3,R3,R2 	  ;comparaison
          BRz saverind    ;si le résultat est 0 alors R2 == R3

loop0rind:ADD R4,R4,1
          ADD R1,R1,1  	  ;incrémentations
          BR looprind

saverind :ADD R0,R4,0 	  ;R0 <- R4
          BR loop0rind

finrind : LD R4,char0
          ADD R0,R0,R4    ;R0 <- R0 + '0'
          TRAP x21
          LD R0, charNL   ;R0 <-'\n'
          TRAP x21

          LDR R7,R6,5     ;épilogue
          LDR R4,R6,4
          LDR R3,R6,3
          LDR R2,R6,2
          LDR R1,R6,1
          LDR R0,R6,0
          ADD R6,R6,6
          RET

index :   ADD R6,R6,-5    ;prologue
          STR R0,R6,0
          STR R1,R6,1
          STR R2,R6,2
          STR R3,R6,3
          STR R7,R6,4

          AND R0,R0,0     ;compteur

loopind : LDR R3,R1,0
          BRz finind      ;test de fin de la chaîne
          ADD R3,R3,R2    ;comparaison
          BRz returnind   ;si le résultat est 0 alors les deux caractères sont égaux
          ADD R0,R0,1
          ADD R1,R1,1     ;incrémentations
          BR loopind

finind :  AND R0,R0,0   ;on remet R0 à 0 si on a pas trouvé le caractère dans la chaîne

returnind:LD R3,char0
          ADD R0,R0,R3    ;R0 <- R0+'0'
          TRAP x21
          LD R0, charNL   ;R0 <- '\n'
          TRAP x21

          LDR R7,R6,4     ;épilogue
          LDR R3,R6,3
          LDR R2,R6,2
          LDR R1,R6,1
          LDR R0,R6,0
          ADD R6,R6,5
          RET

strcmp :  ADD R6,R6,-5
          STR R0,R6,0
          STR R1,R6,1
          STR R2,R6,2
          STR R3,R6,3
          STR R7,R6,4

lpcmp :   LDR R0,R1,0
          LDR R3,R2,0
          NOT R3,R3
          ADD R3,R3,1
          ADD R0,R0,R3
          LD R0,char0
          ADD R3,R3,R0
          TRAP x21
          BRnp endcmp
          ADD R1,R1,1
          ADD R2,R2,1
          BR lpcmp

endcmp :  LDR R7,R6,4
          LDR R3,R6,3
          LDR R2,R6,2
          LDR R1,R6,1
          LDR R0,R6,0
          ADD R6,R6,5
          RET

strcpy :  ADD R6,R6,-4    ;prologue
          STR R1,R6,0
          STR R2,R6,1
          STR R3,R6,2
          STR R7,R6,3

          LDR R3,R1,0     ;src
          BRz fincpy	    ;test chaîne vide

loopcpy:  STR R3,R2,0     ;dest
          ADD R1,R1,1
          ADD R2,R2,1
          LDR R3,R1,0
          BRnp loopcpy

fincpy :  LDR R7,R6,3      ;épilogue
          LDR R3,R6,2
          LDR R2,R6,1
          LDR R1,R6,0
          ADD R6,R6,4
          RET

strncpy : ADD R6,R6,-5
          STR R0,R6,0
          STR R1,R6,1
          STR R2,R6,2
          STR R3,R6,3
          STR R7,R6,4

          LDR R3,R1,0      ;src
          BRz finncpy	   ;test chaîne vide

loopncpy: STR R3, R2, 0 ; dest
          ADD R0,R0,-1
          BRnz finncpy
          ADD R1,R1,1
          ADD R2,R2,1
          LDR R3,R1,0
          BR loopncpy

finncpy:  LDR R7,R6,4
          LDR R3,R6,3
          LDR R2,R6,2
          LDR R1,R6,1
          LDR R0,R6,0
          ADD R6,R6,5
          RET

string :	.STRINGZ "Hello_world"

char :  	.STRINGZ "l"

char0 :   .FILL 48     ; code de '0'

charNL :  .FILL 10     ; code de '\n'

sttop:    .BLKW 100
stbot:

.END
