SELECT DISTINCT v1.date_arrive,v1.port_arrrive
  FROM Voyage v1
    LEFT OUTER JOIN Voyage v2 ON v2.date_depart = v1.date_arrive
      WHERE v1.port_arrive = v2.port_depart
;