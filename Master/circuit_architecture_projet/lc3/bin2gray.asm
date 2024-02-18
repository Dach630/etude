        .ORIG x3000
main:   JSR b2g
	PUTC
        TRAP x25

x:      .FILL 20
compt:  .FILL 16

b2g:    ; save R1 - R3
        AND R0, R0, 0
        LD R1, compt
        AND R2, R2, 0 ; dernier bit de R3 vue
        LD R3, x
        BRz end
	;décale jusqu'à voir le 1er bit 1
initb2g:AND R3, R3, R3
        BRn nb2g
        ADD R3, R3, R3
        ADD R1, R1, -1
        BRp initb2g
	
lpb2g:  ADD R0, R0, R0
        ADD R3, R3, R3
        BRn nb2g
        AND R2, R2, R2
        BRz lpnext
        ADD R0, R0, 1
        AND R2, R2, 0
        BRnzp lpnext
nb2g:   AND R2, R2, R2
        BRp lpnext
        ADD R0 ,R0, 1
        ADD R2, R2, 1
lpnext: ADD R1, R1, -1
        BRp lpb2g
end:    
        ; restore R1 - R3
        RET

        .END
