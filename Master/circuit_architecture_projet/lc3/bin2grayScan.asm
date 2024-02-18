        .ORIG x3000
	; binaire vers gray avec SCAN selon scan.asm
main:   JSR b2gS
exit:   TRAP x25

x:      .FILL 20

b2gS:   LD R0, x
	SCAN R0, R0, R0
	SCAN R0, R0, R0
	SCAN R0, R0, R0
	RET

        .END
