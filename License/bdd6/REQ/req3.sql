SELECT DISTINCT * FROM (
    SELECT r.pays1
    FROM relation AS r
    WHERE r.nature = 4
) newTable GROUP BY r.pays1
HAVING count(r.pays1) >= 2
;