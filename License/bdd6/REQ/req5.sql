SELECT DISTINCT p.nom 
FROM produit as p 
WHERE p.id_produit IN (
    SELECT c.id_produit 
    FROM Cargaison AS c
    GROUP BY c.id_cargaison
    HAVING SUM(c.quantite) > 10000
);
