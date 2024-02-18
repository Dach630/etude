type entity = {
  mutable sprite : string;
  mutable attaque : int;
  mutable vitesse : float;
}

type  ennemi = {
  ennemi_specs : entity;
  mutable ennemi_last_move : string;
  mutable ennemi_step : string;
  (*ObjetsLaches : objet list;*)
  mutable timeswalked : int;
  possible_drops : string list;
}


let entity1 = {
  sprite = "monster/Moblin_";
	attaque = 1;
	vitesse = 4.;
};;

let ennemi1 = {
	ennemi_specs = entity1;
	ennemi_last_move = "2";
	ennemi_step = "0";
	timeswalked = 0;
	possible_drops = ["sprite/object/sword_2.png";"sprite/object/sword_4.png"]
};;

class plateau j k l m = object (this)
  val mutable id = 0
  val mutable zone = 0
  val mutable caseSet = j
  val mutable ennemis =[(0,ennemi1,ref 0.,ref 0.,ref 0)]
  val mutable items = [(0,ref "",ref 0., ref 0., ref 0)]
  method modify_caseSet x y z = caseSet.(x).(y) <- z
  method modify_ennemis n = ennemis <- n
  method modify_items n = items <- n
  method modify_id n = id <- n
  method open_wall x y = this#modify_caseSet x y 0
  method zone = zone
  method caseSet = caseSet
  method ennemis = ennemis
  method items = items
  method id = id
  initializer this#modify_ennemis k
  initializer this#modify_items l
  initializer this#modify_id m
end;;

type carte = {
  full_map : (plateau array) array;
}

type joueur = {
  id : int;
  player_specs : entity;
  mutable pv : int;
  mutable pv_max : int;
  mutable last_move : string;
  mutable step : string;
  (*affichage : objet;*)
  mutable plateau_actuelX : int;
  mutable plateau_actuelY : int;
  mutable posX1 :  float;
  mutable posY1 :  float;
  (*mutable ObjetsPossedes : objet list;*)
  mutable hand1 : string;
  mutable hand2 : string;
  mutable hand3 : string;
  mutable use : int;
  mutable money : int;
  mutable can_attack : int;
  mutable delai_mouvement : int;
}
