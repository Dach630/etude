SELECT DISTINCT v.id_navire 
FROM voyage AS v, cargaison AS c, produit AS p
WHERE v.id_cargaison = c.id_cargaison
AND c.id_produit = p.id_produit
AND p.nom = 'PS5'
;