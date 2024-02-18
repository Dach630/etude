        .ORIG x3000
	;gray vers binaire avec SCAN selon scan.asm
main:   JSR g2bS
exit:   TRAP x25

x:      .FILL 24

g2bS:   LD R0, x
	SCAN R0, R0, R0
        RET

        .END