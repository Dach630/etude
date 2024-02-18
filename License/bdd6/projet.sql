DROP TABLE IF EXISTS Produit cascade;
DROP TABLE IF EXISTS Cargaison cascade;
DROP TABLE IF EXISTS Voyage cascade;
DROP TABLE IF EXISTS Navire cascade;
DROP TABLE IF EXISTS Port cascade;
DROP TABLE IF EXISTS Nation cascade;
DROP TABLE IF EXISTS Relation cascade;
DROP TABLE IF EXISTS Escale cascade;

CREATE TABLE Produit(
 id_produit SERIAL PRIMARY KEY,
 nom TEXT,
 attribut BOOLEAN,
 volume INTEGER,
 UNIQUE (nom,attribut)
);

CREATE TABLE Cargaison(
 id_cargaison SERIAL,
 id_produit INTEGER,
 quantite INTEGER,
 PRIMARY KEY (id_cargaison),
 FOREIGN KEY (id_produit) REFERENCES Produit(id_produit)
 ON DELETE CASCADE
 ON UPDATE CASCADE
);

CREATE TABLE Nation (
 nom TEXT PRIMARY KEY,
 continent TEXT NOT NULL
);

CREATE TABLE Relation (
  pays1 TEXT,
  pays2 TEXT,
  nature INTEGER CHECK (nature BETWEEN 1 AND 4) NOT NULL,
  PRIMARY KEY (pays1,pays2),
  FOREIGN KEY (pays1) REFERENCES Nation(nom)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  FOREIGN KEY (pays2) REFERENCES Nation(nom)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  CHECK (pays1 <> pays2)
);

CREATE TABLE Navire (
 id_navire INTEGER PRIMARY KEY,
 type TEXT NOT NULL,
 categorie INTEGER CHECK (categorie BETWEEN 1 AND 5) NOT NULL,
 nationalite TEXT NOT NULL,
 vol_marchandises_max INTEGER NOT NULL,
 nb_passagers_max INTEGER NOT NULL,
 FOREIGN KEY (nationalite) REFERENCES Nation(nom)
 ON DELETE CASCADE
 ON UPDATE CASCADE
);

CREATE TABLE Port(
 nom TEXT PRIMARY KEY,
 localisation TEXT NOT NULL,
 nationalite TEXT,
 categorie INTEGER CHECK (categorie BETWEEN 1 AND 5) NOT NULL,
 FOREIGN KEY (nationalite) REFERENCES Nation(nom)
 ON DELETE CASCADE
 ON UPDATE CASCADE
);



CREATE TABLE Voyage(
  port_depart TEXT,
  port_arrive TEXT,
  date_depart DATE,
  date_arrive DATE,
  id_navire INTEGER,
  passagers INTEGER,
  id_cargaison INTEGER,
  type VARCHAR(5) NOT NULL,
  classe TEXT NOT NULL,
  nb_etapes INTEGER,

  PRIMARY KEY (port_depart, port_arrive,date_depart,id_navire),
  FOREIGN KEY (port_depart) REFERENCES Port(nom)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  FOREIGN KEY (port_arrive) REFERENCES Port(nom)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  FOREIGN KEY (id_navire) REFERENCES Navire(id_navire)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  FOREIGN KEY (id_cargaison) REFERENCES Cargaison (id_cargaison)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  CHECK (date_depart <= date_arrive),
  CHECK ((type = 'court' AND classe <> 'Intercontinental')
          OR (type = 'moyen')
          OR (type = 'long' AND nb_etapes > 0))

);

CREATE TABLE Escale (
 id_escale INTEGER,
 port_depart TEXT NOT NULL,
 port_arrive TEXT NOT NULL,
 date_depart DATE NOT NULL,
 id_navire INTEGER,
 nom_port TEXT,
 passagers_descendus INTEGER,
 passagers_montes INTEGER,
 produits_vendus INTEGER,
 produits_achetes INTEGER,

 PRIMARY KEY (id_escale,date_depart,id_navire,nom_port),
 FOREIGN KEY (nom_port) REFERENCES Port(nom)
 ON DELETE CASCADE
 ON UPDATE CASCADE,
 FOREIGN KEY (port_depart,port_arrive,date_depart,id_navire)
 REFERENCES Voyage (port_depart,port_arrive,date_depart,id_navire)
 ON DELETE CASCADE
 ON UPDATE CASCADE
);
