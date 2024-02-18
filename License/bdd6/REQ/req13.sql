WITH RECURSIVE Trajet(port_depart,port_arrive) AS
  (
      SELECT * FROM Voyage
    UNION ALL
      SELECT v.port_depart,t.port_arrive
      FROM Voyage v, Trajet t
      WHERE v.port_arrive = t.port_depart
  )
  SELECT * FROM Trajet
  LIMIT 10;