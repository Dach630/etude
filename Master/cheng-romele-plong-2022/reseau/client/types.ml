open Graphics;;
type entity = {
	sprite : string;
	x: int;
	y: int;
}

type screen = {
	mutable tileset: image array;
	mutable plateau: (int array) array;
	mutable imgPlat: image;
	mutable listJou: entity list;
	mutable listEnn: entity list;
	mutable listObj: entity list;
	mutable chargement: bool;
	mutable move: bool;
}
