/*L'identifiant des navires ayant transportés des PS5.*/
SELECT DISTINCT v.id_navire
FROM voyage AS v, cargaison AS c, produit AS p
WHERE v.id_cargaison = c.id_cargaison
AND c.id_produit = p.id_produit
AND p.nom = 'PS5'
;

/*Les nations qui possédent plusieurs catégories de port*/
SELECT DISTINCT p1.nationalite
FROM port as p1, port as p2
WHERE p1.nationalite = p2.nationalite
AND p1.categorie <> p2.categorie;

/*Les nations en guerre contre au minimum 2 pays*/
SELECT DISTINCT * FROM (
    SELECT r.pays1
    FROM relation AS r
    WHERE r.nature = 4
) newTable GROUP BY pays1
HAVING count(pays1) >= 2
;

/*Les noms de produits dans aucune cargaison*/
SELECT DISTINCT nom
FROM produit
WHERE nom NOT IN (
    SELECT p.nom
    FROM produit AS p, cargaison AS c
    WHERE c.id_produit = p.id_produit
  );

/*Les noms de produits dont la quantité dans les cargaison sont supérieur a 10000*/
SELECT DISTINCT p.nom FROM produit as p WHERE
p.id_produit IN (
    SELECT c.id_produit
    FROM Cargaison AS c
    GROUP BY c.id_cargaison
    HAVING SUM(c.quantite) > 10000
);

/*Les nations et le pourcentage de nation avec qui ils sont en paix au minimum 75%*/
SELECT r.pays1, ((COUNT(r.pays2) * 100)/ COUNT(r.pays1)) AS pourcentage
FROM relation as r
WHERE r.nature = 1
GROUP BY r.pays1
HAVING ((COUNT(r.pays2) * 100)/ COUNT(r.pays1)) >= 75
;

/*Le nom et la moyenne des quantités de produit dans leur cargaison*/
SELECT p.nom, (SUM(c.quantite)/COUNT(c.id_produit)) AS moyenne
FROM produit AS p, cargaison AS c
WHERE p.id_produit = c.id_produit
GROUP BY p.nom
;

/*Nombre des différents noms de produits avec null */
SELECT COUNT(nom) AS nb_produit FROM produit;

/*Nombre des différents noms de produits sans null */
SELECT COUNT(*) AS nb_produit FROM produit;

/*Quelle cargaison transporte quel produit*/
SELECT id_cargaison, nom
FROM cargaison
FULL OUTER JOIN produit ON cargaison.id_produit = produit.id_produit
;

/*Quel produit part de quel pays*/
SELECT v.port_depart , p.nom
FROM voyage AS v, cargaison AS c, produit AS p
WHERE v.id_cargaison = c.id_cargaison
AND c.id_produit = p.id_produit;

/*Le nombre de passagers qui descendent dans un pays*/
SELECT SUM(e.passagers_descendus) , p.nom 
FROM escale AS e, port AS p 
WHERE e.nom_port = p.nom
GROUP BY p.nom
;

/*Les 10 premiers ports qu'un navire peut atteindre à partir d'un port*/
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

/*Les jours et ports ayant un bateau arrivant dans le port et un bateau quittant le port le même jour*/
SELECT DISTINCT v1.date_arrive,v1.port_arrive
  FROM Voyage v1
    LEFT OUTER JOIN Voyage v2 ON v2.date_depart = v1.date_arrive
      WHERE v1.port_arrive = v2.port_depart
;

/*Les voyages internes d'une nation*/
SELECT DISTINCT v.*
  FROM Voyage v, Port p1, Port p2, Navire n
    WHERE v.port_depart = p1.nom
    AND v.port_arrive = p2.nom
    AND v.id_navire = n.id_navire
    AND p1.nationalite = p2.nationalite
    AND p1.nationalite = n.nationalite
;

/*La moyenne minimum de passagers descendus aux escales au cours d'un voyage*/
 SELECT AVG(e1.passagers_descendus)
 FROM Escale e1
 GROUP BY e1.id_escale
 HAVING AVG(e1.passagers_descendus) <
    ALL (
      SELECT AVG (e2.passagers_descendus)
      FROM Escale e2
      WHERE e1.id_escale <> e2.id_escale
    );

/*Le nombre de ports de catégorie 5 par pays*/
  SELECT COUNT(categorie),nationalite
  FROM Port
  WHERE categorie = 5
  GROUP BY nationalite
  ;

/*Les voyages intercontinentaux qui ne sont jamais arrivés à destination*/
  SELECT *
  FROM Voyage
  WHERE date_arrive IS NULL
  AND type = 'intercontinental'
  ;

/*Le volume total pour chaque cargaison*/
  SELECT c.id_cargaison,SUM(p.volume * c.quantite)
  FROM Produit p, Cargaison c
  WHERE p.id_produit = c.id_produit
  GROUP BY c.id_cargaison
  ;

/*Le nombre de pays dans un continent*/
  SELECT COUNT (nom),
  FROM Nation
  GROUP BY continent
  ;
