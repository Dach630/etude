SELECT r.pays1, ((COUNT(r.pays2) * 100)/ COUNT(r.pays1)) 
FROM relation as r 
WHERE r.nature = 1
GROUP BY r.pays1
HAVING ((COUNT(r.pays2) * 100)/ COUNT(r.pays1)) >= 75
;