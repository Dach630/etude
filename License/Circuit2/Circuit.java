public class Circuit {

	private final Sommet[][] circuit;
	public int[][] pixels;
	private Sommet depart;
	private Sommet arrivee;

	//Crée un double tableau de Sommet
	Circuit(Parser p){
		this.pixels = p.getPixels();
		circuit = new Sommet[pixels.length][pixels[0].length];

		for(int i = 0; i < circuit.length; i++){
			for(int j = 0; j < circuit[i].length; j++){
				if(pixels[i][j] == 2){
				    //Definit le point de départ
					depart = new Sommet(i, j, 0, 0, 2);
					circuit[i][j] = depart;
				}
				else if(pixels[i][j] == 3){
				    //Definit le point d'arrivée
					arrivee = new Sommet(i, j, 3);
					circuit[i][j] = arrivee;
				}
				else circuit[i][j] = new Sommet(i, j, pixels[i][j]);
			}
		}
	}

    void printTableau(){
        //Renvoie un tableau un tableau de signes représentant le circuit
        for (int[] pixel : pixels) {
            for (int i : pixel) {
                if (i == 0) System.out.print(" ");// chemin
                else if (i == 1) System.out.print("#");// mur
                else if (i == 2) System.out.print("D");// depart
                else if(i == 3)System.out.print("A");// arrivee
                else System.out.print("X");// chemin tracé par l'algorithme
            }
            System.out.println();
        }
    }

	Sommet getDepart(){
	    return depart;
	}
	Sommet getArrivee(){
	    return arrivee;
	}
	Sommet getSommet(int x, int y){
		return circuit[x][y];
	}
	void setSommet(int x, int y, Sommet l){
	    circuit[x][y] = l;
	}

	boolean estDansPlateau(int x, int y){ //Vérifie qu'un point donné est dans le tableau
		return !(x < 0) && !(y < 0) && !(x > pixels.length - 1) && !(y > pixels[0].length - 1);
	}

	boolean estChemin(int x, int y){ //Vérifie que la case n'est pas un mur
		return pixels[x][y] != 1;
	}
}