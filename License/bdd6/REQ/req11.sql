SELECT v.port_depart , p.nom 
FROM voyage AS v, cargaison AS c, produit AS p 
WHERE v.id_cargaison = c.id_cargaison 
AND c.id_produit = p.id_produit;