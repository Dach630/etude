  SELECT c.id_cargaison,SUM(p.volume * c.quantite)
  FROM Produit p, Cargaison c
  WHERE p.id_produit = c.id_produit
  GROUP BY c.id_cargaison
  ;