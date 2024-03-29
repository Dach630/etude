; synthèse d'invariant de programme
; on déclare le symbole non interprété de relation Invar
(declare-fun Invar (Int Int ) Bool)
; la relation Invar est un invariant de boucle
(assert (forall ((x1 Int) (x2 Int)) (=>(and(Invar x1 x2)(< x1 3))(Invar (+ x1 1) (+ x2 3)))))
; la relation Invar est vraie initialement
(assert (Invar 0 0))
; l'assertion finale est vérifiée
(assert (forall ((x1 Int) (x2 Int)) (=>(and(Invar x1 x2)(>= x1 3))(= x2 9))))
; appel au solveur
(check-sat-using (then qe smt))
(get-model)
(exit)