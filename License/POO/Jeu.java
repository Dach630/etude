public class Jeu {

    Niveaux n;
    ScAns sc;

    Jeu(Niveaux n, ScAns sc){
        this.n=n;
        this.sc=sc;
    }

    public void jouer(){
        boolean fin=false;
        System.out.println("Sauvez les animaux!");
        n.afficheCourant();
        n.barre();
        while(fin==false){
            if(n.win()) {
                fin=true;
                break;
            }
            int[] c= sc.demanderCoordonnes();
            n.action(c[0],c[1]);
            n.afficheCourant();
            n.barre();
        }
    }

}
