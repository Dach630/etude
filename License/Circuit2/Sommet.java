import java.util.ArrayList;

public class Sommet {

    private final int x,y;
    private int vx,vy;
    private final int type;     //0:Chemin ; 1:Mur ; 2:Point de depart ; 3: Point d'arrivee
    private Sommet predecesseur;
    private int nombreCoup;

    private final ArrayList<Sommet> successeurs = new ArrayList<>();

    //Constructeurs:
    Sommet(int x, int y, int type){
        this.x = x;
        this.y = y;
        vx = vy = 0;
        this.type = type;
    }

    Sommet(int x, int y, int vx, int vy, int type){
        this.x = x;
        this.y = y;
        this.vx = vx;
        this.vy = vy;
        this.type = type;
    }

    //Fonctions qui permet de trouver les successeurs d'un sommet a partir de ses coordonnees et de sa vitesse
    void setSuccesseurs(Circuit c){
        int xt = this.x + this.vx;
        int yt = this.y + this.vy;

        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if(c.estDansPlateau(xt + j, yt + i) && c.estChemin(xt + j, yt + i) && noTP(xt + j, yt + i, c)){
                    Sommet l = new Sommet(xt + j, yt + i, this.vx + j, this.vy + i, 0);
                    c.getSommet(xt + j,yt + i).setV(this.vx + j, this.vy + i);
                    successeurs.add(c.getSommet(xt+ j, yt + i));
                    c.setSommet(xt + j,yt + i, l);
                }
            }

        }
    }

    //Affiche Position: {x,y} Predecesseur: {x',y'} Nombre coup:nbC
    void affiche() {
        if(this.predecesseur == null) {
            System.out.print("Position: {" + this.x + "," + this.y + "} Vitesse {" + this.vx + "," + this.vy + "} Nombre coup:" + this.nombreCoup);
            if(type == 2) System.out.print("                            POINT DE DEPART");
            System.out.println();
        }
        else {
            System.out.print("Position {" + this.x + "," + this.y + "} Predecesseur: {" + this.predecesseur.x + "," + this.predecesseur.y + "} Vitesse {" + this.vx+"," + this.vy + "} Nombre coup:" + this.nombreCoup);
            if(type == 3) System.out.print("                    POINT D'ARRIVE");
            System.out.println();
        }
    }

    //Fonction qui compare deux sommets
    public boolean equals(Object n) {
        if (n instanceof Sommet)  {
            Sommet aux = (Sommet) n;
            return (x == aux.x) && (y == aux.y) && (vx == aux.vx) && (vy == aux.vy);
        }
        return false;
    }
    
    @Override
    public int hashCode() {
        return x + 100 * y + vx * 10000 + vy * 1000000;
    }

    boolean noTP(int fX, int fY, Circuit circuit){// verifie si il n'y a pas un mur en chemin
        if(!circuit.estDansPlateau(fX, fY)){ // suppose circuit rectangle
            return false;
        }
        // cheminement cas trivial
        if(fX == x){// horizontal
            int d = fY - y;
            if(d > 0){
                for(int i = y + 1; i <= fY; i++){// regarde jusqu'à fY
                    if(!circuit.estChemin(x, i)){
                        return false;
                    }
                }
            }else if(d < 0){
                for(int i  = y - 1; i >= fY; i--){// regarde jusqu'à fY
                    if(!circuit.estChemin(x, i)){
                        return false;
                    }
                }
            }
            return true;
        }
        if(fY == y){// vertical
            int d = fX - x;
            if(d > 0){
                for(int i = x + 1; i <= fX; i++){// regarde jusqu'à fX
                    if(!circuit.estChemin(i, y)){
                        return false;
                    }
                }
            }else if(d < 0){
                for(int i = x - 1; i >= fX; i--){// regarde jusqu'à fX
                    if(!circuit.estChemin(i, y)){
                        return false;
                    }
                }
            }
            return true;
        }
        //diagonal
        int dX = fX - x;
        int dY = fY - y;
        int absDY = Math.abs(dY);
        int absDX = Math.abs(dX);
        int iX, iY, reste, longueur;
        int tempX = x;
        int tempY = y;
        if(dX < 0){// incrementeur ou decrementeur
            iX = -1;
        }else{
            iX = 1;
        }
        if(dY < 0){
            iY = -1;
        }else{
            iY = 1;
        }
        if(absDY > absDX){//1, 4, 5, 8 octant
            reste = absDY % absDX;
            longueur = absDY / absDX;
            for(int i = 0; i < absDX; i++){
                for(int j = 0; j < longueur; j++){
                    tempY += iY;
                    if(!circuit.estChemin(tempX, tempY)){
                        return false;
                    }
                }
                tempX += iX;
                if(!circuit.estChemin(tempX, tempY)){
                    return false;
                }
            }
            for(int i = 0; i < reste; i++){
                tempY += iY;
                if(!circuit.estChemin(tempX, tempY)){
                    return false;
                }
            }
        }else{//2, 3, 6, 7 octant
            reste = absDX % absDY;
            longueur = absDX / absDY;
            for(int i = 0; i < absDY; i++){
                for(int j = 0; j < longueur; j++){
                    tempX += iX;
                    if(!circuit.estChemin(tempX, tempY)){
                        return false;
                    }
                }
                tempY += iY;
                if(!circuit.estChemin(tempX, tempY)){
                    return false;
                }
            }
            for(int i = 0; i < reste; i++){
                tempX += iX;
                if(!circuit.estChemin(tempX, tempY)){
                    return false;
                }
            }
        }
        return true;
    }

    //Setter et Getter:
    int getX(){
        return x;
    }
    
    int getY(){
        return y;
    }
    
    Sommet getPredecesseur(){
        return predecesseur;
    }
    
    int getNombreCoup(){
        return nombreCoup;
    }
    
    ArrayList<Sommet> getSuccesseurs(){
        return successeurs;
    }

    void setV(int vx, int vy){
        this.vx = vx;
        this.vy = vy;
    }
    
    void setPredecesseur(Sommet pred){
        predecesseur = pred;
    }
    
    void setNombreCoup(int distance){
        this.nombreCoup = distance;
    }

    public String toString(){
        return "Sommet"+this.x+";"+this.y;
    }
}
