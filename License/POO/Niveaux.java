public class Niveaux {

    int[][] plateau;
    static int niveau;
    Action a;
    Slide s;
    int compt=0;
    int pet=0;
    int save=0;

    //-1=mur 0=vide 1=pet 2=violet 3=rouge 4=bleu 5=vert 6=jaune
    Niveaux(int height, int length){
        plateau= new int[height+2][length+2];
        a=new Action(plateau, pet);
        s=new Slide(plateau);
        for(int i=0;i< plateau.length;i++) {
            for (int j = 0; j < plateau[i].length; j++) {
                if (i == 0 || j == 0 || i == plateau.length - 1 || j == plateau[i].length - 1) plateau[i][j] = -1;
                else plateau[i][j] = 0;
            }
        }
        compt++;
        niveau=compt;
    }

    void fillzone(int[] c, int height, int lenght, int val) {
        for(int i=c[0];i<c[0]+height;i++){
            for(int j=c[1];j<c[1]+lenght;j++){
                plateau[i][j]=val;
                if(val==1) pet++;
            }
        }
    }

    void action(int x, int y){
        slidePlateau();
        suppr(x,y);
        slidePlateau();
    }

    private void slidePlateau(){
        s.rangeTableau();
        this.plateau=s.plateau;
    }

    private void suppr(int x,int y){
        a.suppr(x,y);
        a.save();
        save=a.save;
        this.plateau=a.tab;
    }

    boolean win(){
        return save == pet;
    }

    public void afficheCourant(){
        for(int i=0;i<plateau.length;i++){
            for(int j=0;j<plateau[i].length;j++){
                if(plateau[i][j]!=-1) System.out.print(plateau[i][j] + "  ");
                else System.out.print("   ");
            }
            System.out.println(" ");
        }
    }

    public void barre(){
        for(int i=0;i<plateau.length*3;i++)System.out.print("-");
        System.out.println("");
    }

    void fillzoneSc() {

    }

}
