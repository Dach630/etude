import java.util.Scanner;

public class Voiture {
    // x axe des ordonnées
    // y axe des abscisses
    //position
    int x;
    int y;
    // vitesse
    int vectX;
    int vectY;
    // circuit
    int[][] piste;
    // nombre de coup
    int coup;
    // condition de fin
    boolean win;
    boolean lose;
    
    Voiture(Circuit c){
        // le point de depart
        this.x = c.getDepart().getX();
        this.y = c.getDepart().getY();
        vectX = 0;
        vectY = 0;
        piste = c.pixels;
        win = false;
        lose = false;
    }
    
    //joue une partie et verifie la condition de victoire et de defaite
    void play(){
        while(!win && !lose){
            playConsole();
            if(win){
                affCircuit();
                System.out.println("Vous avez fait "+ coup +" coups pour finir ce circuit");
            }
            else if(lose){
                affCircuit();
                System.out.println("Vous avez abandonné");
            }
        }
    }
    
    //demande le choix de la vitesse et la change selon le choix
    //ensuite il essaye de bouger la voiture
    private void playConsole(){
        affCircuitChoix();
        Scanner res = new Scanner(System.in);
        boolean bon = false; // bonne commande;
        System.out.println("7 | 8 | 9");
        System.out.println("4 | 5 | 6");
        System.out.println("1 | 2 | 3");
        System.out.println("0 pour abandonner");
        String s; // pour la reponce du joueur
        while(!bon){
            System.out.println("Vers où?");
            s = res.nextLine();
            switch(s){ // modifie vecteur
                case "7":
                    vectX--;
                    vectY--;
                    bon = true;
                    break;
                case "4":
                    vectY--;
                    bon = true;
                    break;
                case "1":
                    vectX++;
                    vectY--;
                    bon = true;
                    break;
                case "8":
                    vectX--;
                    bon = true;
                    break;
                case "5":
                    bon = true;
                    break;
                case "2":
                    vectX++;
                    bon = true;
                    break;
                case "9":
                    vectX--;
                    vectY++;
                    bon = true;
                    break;
                case "6":
                    vectY++;
                    bon = true;
                    break;
                case "3":
                    vectX++;
                    vectY++;
                    bon = true;
                    break;
                case "0":
                    lose = true;
                    return;
                default:
                    System.out.println("Mouvement impossible.");
            }
        }
        move(x + vectX, y + vectY);
        coup++;
    }
    // verifie si la voiture ne sort pas du circuit ou percute un mur,il change sa position et verifie la condition de victoire
    private void move(int fX, int fY){// bouge la voiture verifie si il percute un mur
        if(fX > piste.length - 1 || fX < 0 || fY < 0 || fY > piste[0].length - 1){ // suppose circuit rectangle
            System.out.println("hors du circuit");
            respawn();
            return;
        }
        // cheminement cas trivial
        if(fX == x){// horizontal
            int d = fY - y;
            if(d > 0){
                for(int i = y + 1; i <= fY; i++){// regarde jusqu'à fY 
                    if(wall(x, i)){
                        System.out.println("mur toucher");
                        respawn();
                        return;
                    }
                }
            }else if(d < 0){
                for(int i = y - 1; i >= fY; i--){// regarde jusqu'à fY 
                    if(wall(x, i)){
                        System.out.println("mur toucher");
                        respawn();
                        return;
                    }
                }
            }
            y = fY;
            win(x, y);
            return;
        }      
        if(fY == y){// vertical
            int d = fX - x;
            if(d > 0){
                for(int i = x + 1; i <= fX; i++){// regarde jusqu'à fX 
                    if(wall(i, y)){
                        System.out.println("mur toucher");
                        respawn();
                        return;
                    }
                }
            }else if(d < 0){
                for(int i = x - 1; i >= fX; i--){// regarde jusqu'à fX 
                    if(wall(i, y)){
                        System.out.println("mur toucher");
                        respawn();
                        return;
                    }
                }
            }
            x = fX;
            win(x, y);
            return;
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
                    if(wall(tempX, tempY)){
                        System.out.println("mur toucher");
                        respawn();
                        return;
                    }
                }
                tempX += iX;
                if(wall(tempX, tempY)){
                    System.out.println("mur toucher");
                    respawn();
                    return;
                }
            }
            for(int i = 0; i < reste; i++){
                tempY += iY;
                if(wall(tempX, tempY)){
                    System.out.println("mur toucher");
                    respawn();
                    return;
                }
            }          
        }else{//2, 3, 6, 7 octant
            reste = absDX % absDY;
            longueur = absDX / absDY;
            for(int i = 0; i < absDY; i++){
                for(int j = 0; j < longueur; j++){
                    tempX += iX;
                    if(wall(tempX, tempY)){
                        System.out.println("mur toucher");
                        respawn();
                        return;
                    }
                }
                tempY += iY;
                if(wall(tempX, tempY)){
                    System.out.println("mur toucher");
                    respawn();
                    return;
                }
            }
            for(int i = 0; i < reste; i++){
                tempX += iX;
                if(wall(tempX, tempY)){
                    System.out.println("mur toucher");
                    respawn();
                    return;
                }
            }
        }
        x = fX;
        y = fY;
        win(x, y);
    }
    
    // remet la vitesse de la voiture a 0
    private void respawn(){
        // garde la position avant le choix du mouvement avec sa vitesse a 0 
        vectX = 0;
        vectY = 0;
    }
     
    //verifie si la position est un mur
    private boolean wall(int x, int y){ // regarde si la position est un mur
        return piste[x][y] == 1;
    }
    
    //verifie si la position est le point d'arrivee
    private void win(int x, int y){// regarde si c'est le point d'arrivee
        if(piste[x][y] == 3) win = true;
    }
    
    // affiche le circuit avec la voiture ainsi que les choix de deplacement possible de la voiture
    private void affCircuitChoix(){
        for(int i = 0; i < piste.length; i++){
            for(int j = 0; j< piste[0].length; j++){
                if(i == x && j == y){// voiture
                    System.out.print("V");   
                }else if(i >= x + vectX - 1 && i <= x + vectX + 1 && j >= y + vectY - 1 && j <= y + vectY + 1){// choix
                    if(wall(i,j)){// choix dans un mur
                        System.out.print("x");
                    }
                    else{// choix dans le chemin
                        System.out.print("+");
                    }
                }else{//circuit
                    switch(piste[i][j]){
                        case 0:// chemin
                            System.out.print(" ");
                            break;
                        case 1:// mur
                            System.out.print("#");
                            break;
                        case 2:// depart
                            System.out.print("D");
                            break;
                        case 3:// arrivee
                            System.out.print("A");
                            break;
                    }
                }
            }
            System.out.println();
        }
    }
    
    //affiche le circuit avec la voiture
    private void affCircuit(){
        for(int i = 0; i < piste.length; i++){
            for(int j = 0; j< piste[0].length; j++){
                if(i == x && j == y){// voiture
                    System.out.print("V");
                }else{//circuit
                    switch(piste[i][j]){
                        case 0:
                            System.out.print(" ");
                            break;
                        case 1:
                            System.out.print("#");
                            break;
                        case 2:
                            System.out.print("D");
                            break;
                        case 3:
                            System.out.print("A");
                            break;
                    }
                }
            }
            System.out.println();
        }
    }
} 