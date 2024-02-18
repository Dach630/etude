SELECT SUM(e.passagers_descendus) , p.nom 
FROM escale AS e, port AS p WHERE
e.nom_port = p.nom
GROUP BY (e.nom_port)
;