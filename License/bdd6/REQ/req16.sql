 SELECT AVG(e1.passagers_descendus)
 FROM Escale e1
 GROUP BY e1.id_escale
 HAVING AVG(e1.passagers_descendus) <
    MIN (
      SELECT AVG (e2.passagers_descendus)
      FROM Escale e2
      WHERE e1.id_escale <> e2.id_escale
    );