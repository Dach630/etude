import java.util.Scanner;

public class ScAns {
    String nom;
    int h,l;
    Scanner scanReponse;

    ScAns(){
        nom="Nouveau Joueur";
        scanReponse=new Scanner(System.in);
    }

    //Eteind le scanner
    public void finish() {
        scanReponse.close();
    }

    //Retourne les coordonnees sous forme de tableau avec t[0]=x et t[1]=y
    public int[] demanderCoordonnes() {
        int[] res=new int[2];
        boolean sort = true;
        String sX="", sY="";
        int x=demanderInt("Quelle sont les coordonnees de X");
        int y=demanderInt("Quelle sont les coordonnees de Y");
        res[0]=x;
        res[1]=y;
        return res;
    }

    //x="nbr"
    public int demanderInt(String q){
        String s="";
        boolean sort=true;
        int res=-1;
        do {
            s=demanderStr(q);
            try{
                res=Integer.parseInt(s);
                sort=true;
            }
            catch(Exception e){
                System.out.println("Veuillez taper un nombre");
                sort=false;
            }
        }while (sort==false);
        return res;
    }

    private String demanderStr(String q) {
        System.out.println(q);
        String s=scanReponse.next();
        return s;
    }

    public int demanderNiveau(){
        return 0;
    }

}
