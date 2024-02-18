        .ORIG x3000
main:   JSR g2b
        TRAP x25

x:      .FILL 24 ;code de gray
compt:  .FILL 16

g2b:    ; save R1 - R3
        AND R0, R0, 0
        LD R1, compt
        AND R2, R2, 0 ;dernier bit ajouter a R0
        LD R3, x
        BRz end
	;décale jusqu'à voir le 1er bit 1
initg2b:AND R3, R3, R3
        BRn ng2b
        ADD R3, R3, R3
        ADD R1, R1, -1
        BRp initg2b

lpg2b:  ADD R0, R0, R0
        ADD R3, R3, R3
        BRn ng2b
        AND R2, R2, R2
        BRz lpnext
        ADD R0, R0, 1
        ADD R2, R2, 1 
        BRnzp lpnext
ng2b:   AND R2, R2, R2
        BRp g2bz
        ADD R0 ,R0, 1
        ADD R2, R2, 1
        BRnzp lpnext
g2bz:   AND R2, R2, 0
lpnext: ADD R1, R1, -1
        BRp lpg2b
end:    
        ; restore R1 - R3
        RET

        .END