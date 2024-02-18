SELECT DISTINCT v.*
  FROM Voyage v, Port p1, Port p2, Navire n
    WHERE v.port_depart = p1.nom
    AND v.port_arrive = p2.nom
    AND v.id_navire = n.id_navire
    AND p1.nationalite = p2.nationalite
    AND p1.nationalite = n.nationalite
;
