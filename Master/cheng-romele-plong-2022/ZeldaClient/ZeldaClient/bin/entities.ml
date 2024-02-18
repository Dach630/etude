open Types;;

let entity2 =
	{sprite = "monster/darknut_";
	attaque = 1;
	vitesse = 4.;
	};;

let entity3 =
	{sprite = "monster/octorock_";
	attaque = 1;
	vitesse = 4.;
	};;

let ennemi2 =
	{
	ennemi_specs = entity2;
	ennemi_last_move = "0";
	ennemi_step = "0";
	timeswalked = 0;
	possible_drops = ["sprite/object/sword_2.png";"sprite/object/sword_4.png"]
	};;

let ennemi3 =
	{
	ennemi_specs = entity3;
	ennemi_last_move = "2";
	ennemi_step = "0";
	timeswalked = 1;
	possible_drops = ["sprite/object/sword_2.png";"sprite/object/sword_4.png"]
	};;

let entity_joueur =
	{sprite = "/Link1/Link_";
	attaque = 3;
	vitesse = 8.;
	};;

let player1 =
	{id = 1;
  player_specs = entity_joueur;
	pv = 10;
	pv_max = 10;
	last_move = "2";
	step = "0";
  plateau_actuelX = 0;
  plateau_actuelY = 0;
  posX1 = 128.0;
  posY1 = 128.0;
	hand1 = "sword";
	hand2 = "none";
	hand3 = "none";
	use = 0;
	money = 0;
	can_attack = 0;
	delai_mouvement = 0;
	};;

let draw_entity filename posX posY =
  let img = Png.load_as_rgb24 filename [] in
  let g = Graphic_image.of_image img in
  Graphics.draw_image g (int_of_float posX) (int_of_float posY)
;;
