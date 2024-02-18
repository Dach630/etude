CREATE ASSERTION PAUSE_ENTRE_VOYAGES
CHECK (NOT EXISTS (
  SELECT v1.date_depart,v2.date_arrivee
  FROM Voyage v1,Voyage v2
  WHERE v1.date_depart > v2.date_arrivee
  AND v2.date_arrive - v1.date_depart <= 14
  GROUP BY id_navire
));

CREATE ASSERTION CAPACITE_MAX
  CHECK (NOT EXISTS(
    SELECT n.passagers,v.id_cargaison
    FROM Navire n,Voyage v
    WHERE v.id_navire = n.id_navire
    AND n.vol_marchandises_max >(SELECT SUM(volume * quantité)
                                 FROM Cargaison,Produit
                                 WHERE v.id_cargaison = Cargaison.id_cargaison
                                 AND Produit.id_produit = Cargaison.id_produit
                                 GROUP BY Cargaison.id_cargaison
                                )
    AND n.nb_passagers_max > v.passagers
  ));

  CREATE ASSERTION CATEGORIE_NAVIRE
    CHECK (NOT EXISTS (
      SELECT v.classe
      FROM Voyage v, Navire n
      WHERE n.categorie < 5
      AND v.classe = 'Intercontinental'
    ));

  CREATE ASSERTION VOYAGE_INTERCONTINENT
    CHECK (NOT EXISTS(
      SELECT v.classe
      FROM Voyage v,Nation nat1,Nation nat2,Port p1, Port p2
      WHERE nat1.nom = p1.nationalite
      AND p1.nom = v.port_arrive
      AND nat2.nom = p2.nationalite
      AND p2.nom = v.port_depart
      AND nat1.continent = nat2.continent
      AND v.classe = 'Intercontinental'
    ));

  CREATE ASSERTION VOYAGE_CONTINENT
    CHECK (NOT EXISTS(
      SELECT v.classe
      FROM Voyage v,Nation nat1,Nation nat2,Port p1, Port p2
      WHERE nat1.nom = p1.nationalite
      AND p1.nom = v.port_arrive
      AND nat2.nom = p2.nationalite
      AND p2.nom = v.port_depart
      AND nat1.continent <> nat2.continent
      AND v.classe <> 'Intercontinental'
    ));

  CREATE ASSERTION NB_ETAPES
    CHECK ( NOT EXISTS (
      SELECT v.nb_etapes
      FROM Voyage v
      WHERE v.nb <> (SELECT COUNT(*)
                     FROM Escale
                     WHERE Escale.nation_depart = v.nation_depart
                     AND Escale.id_navire = v.id_navire
                     AND Escale.port_arrive = v.port_arrive
                     AND Escale.date_depart = v.date_depart
                   )
    ));

  CREATE ASSERTION PRODUITS_FRAIS
    CHECK ( NOT EXISTS (
      SELECT c.id_produit
      FROM Voyage v, Cargaison c, Produit p
      WHERE (v.type = "long" OR v.type = "moyen")
      AND c.id_cargaison = v.id_cargaison
      AND c.id_produit = p.id_produit
      AND p.attribut = true
    ));

  CREATE ASSERTION CAN_DOCK
    CHECK ( NOT EXISTS (
      SELECT n.id_navire
      FROM Voyage v, Navire n, Port p, Escale e
      WHERE
      (n.id_navire = v.id_navire AND v.port_arrive = p.nom)
      OR
      (n.id_navire = e.id_navire AND e.nom_port = p.nom)
      AND n.categorie < p.categorie
    ));

  CREATE ASSERTION MEME_RELATION
    CHECK ( NOT EXISTS (
      SELECT r1.pays1,r2.pays1
      FROM Relation r1, Relation r2
      WHERE r1.pays1 = r2.pays2
      AND r1.pays2 = r2.pays1
      AND r1.nature <> r2.nature
    ));

  CREATE ASSERTION PAS_EN_GUERRE
    CHECK ( NOT EXISTS (
      SELECT v.port_depart
      FROM Port p1, Port p2, Nation n1, Nation n2, Relation r, Voyage v
      WHERE v.port_depart = p1.nom
      AND p1.nationalite = n1.nom
      AND v.port_arrive = p2.nom
      AND p2.nationalite = n2.nom
      AND r.pays1 = n1.nom
      AND r.pays2 = n2.nom
      AND r.nature = 4
    ));

  CREATE ASSERTION VOYAGES_COMMERCIAUX
    CHECK ( NOT EXISTS (
      SELECT r.nature
      FROM  Port p1, Port p2, Nation n1, Nation n2, Relation r
      WHERE p1.nationalite = n1.nom
      AND p2.nationalite = n2.nom
      AND r.pays1 = n1.nom
      AND r.pays2 = n2.nom
      AND r.nature = 1
      AND NOT EXISTS (
        SELECT v.port_depart,v.port_arrive
        FROM Voyage v
          WHERE v.port_depart = p1.nom
          AND v.port_arrive = p2.nom
      ));
