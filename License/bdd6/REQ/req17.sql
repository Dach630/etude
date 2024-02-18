SELECT COUNT(categorie),nationalite
  FROM Port
  GROUP BY nationalite
    HAVING categorie = 5
  ;