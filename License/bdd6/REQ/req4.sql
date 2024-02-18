SELECT DISTINCT nom
FROM produit
WHERE nom NOT IN (
    SELECT p.nom
    FROM produit AS p, cargaison AS c
    WHERE c.id_produit = p.id_produit
  );