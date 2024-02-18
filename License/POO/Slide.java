public class Slide {

    int[][] plateau;

    public Slide(int[][] tab){
        plateau = tab;
    }

    //Range le plateau
    public void rangeTableau(){
        SlideBas sb= new SlideBas();
        SlideCote sc= new SlideCote();
        sb.slideBas();
        sc.slideCote();
    }

    //True si la colonne est remplie de 0
    private boolean verifCol0(int i ,int j){
        //Vérifie si la colonne est remplie de 0
        if(plateau[i][j]== -1) return true;
        else if(plateau[i][j]==0) return verifCol0(i-1,j);
        else return false;
    }

    private class SlideCote{

        //Glisse toute les colonnes vers la gauche
        void slideCote(){
            int i= plateau.length-2;
            //Vérifie si il y a toujours des colonnes à ranger
            while(!verifPC()){
                for(int j=1;j<plateau[i].length-2;j++){
                    //Si c'est le cas, stack les colonnes sur la gauche
                    if(verifCol0(i,j)){
                        //System.out.println("i = " + i + "   j = " + j);
                        fillColumn(i,j);
                    }
                }
            }
        }

        //Remplit la colonne actuelle avec la colonne de droite
        void fillColumn(int i, int j){
            if(plateau[i][j+1]!=-1) {
                //System.out.println("a");
                plateau[i][j]=plateau[i][j+1];
                plateau[i][j+1]=0;
                fillColumn(i-1,j);
            }
        }

        //True si le tableau est rangé
        boolean verifPC(){
            int i= plateau.length-2, a=0;
            //Si verifCol0 est vérifié une fois...
            for(int j=1; j<plateau[i].length-2;j++){
                if(verifCol0(i,j)){
                    a=j;
                    break;
                }
            }
            //Vérifie si le reste du tableau est rempli de 0
            if(a>0){
                while(a<plateau[i].length){
                    if(!verifCol0(i,a)) return false;
                    a++;
                }
            }
            return true;
        }

    }

    private class SlideBas{

        //Fait descendre les blocks vers le bas
        void slideBas(){
            int i=plateau.length-2;
            for(int j=1;j<plateau[i].length;j++){
                if(verifCol0(i,j) || whereis0Col(j)!=-1){
                    arrColTer(j);
                }
            }
        }

        //Retourne la position du premier 0 trouvé
        int whereis0Col(int j){
            for(int i=plateau.length-2;i>1;i--){
                if(plateau[i][j]==0) return i;
            }
            return -1;
        }

        //True si la colonne est rangée
        boolean verif0Haut(int j){
            int a=0;
            //Si la colonne à un 0...
            for(int i= plateau.length-2; i>1;i--){
                if(plateau[i][j]==0){
                    a=i;
                    break;
                }
            }
            //Vérifie si le reste de la colonne est rempli de 0 de a à 1
            if(a>0){
                while(a>1){
                    if(plateau[a][j]!=0) return false;
                    a--;
                }
            }
            return true;
        }

        //TriPartiel sur la colonne
        void arrColumn(int i,int j){
            int a=i;
            while(a>1 && plateau[a][j]==0 && plateau[a-1][j]!=-1){
                int tmp=plateau[a-1][j];
                plateau[a-1][j]=plateau[a][j];
                plateau[a][j]=tmp;
                a--;
            }
        }

        //TriParInsertion sur le plateau
        void arrColTer(int j){
            while(!verif0Haut(j)){
                int a=whereis0Col(j);
                arrColumn(a,j);
            }
        }

    }

}
