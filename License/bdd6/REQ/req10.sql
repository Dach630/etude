SELECT id_cargaison, nom FROM cargaison
FULL OUTER JOIN produit ON cargaison.id_produit = produit.id_produit
;
