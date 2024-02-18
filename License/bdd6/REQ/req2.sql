SELECT DISTINCT p1.nationalite 
FROM port as p1, port as p2 
WHERE p1.nationalite = p2.nationalite 
AND p1.categorie <> p2.categorie;