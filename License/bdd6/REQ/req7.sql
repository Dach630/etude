SELECT p.nom, (SUM(c.quantite)/COUNT(c.id_produit)) 
FROM produit AS p, cargaison AS c 
WHERE p.id_produit = c.id_produit
GROUP BY c.id_produit
;