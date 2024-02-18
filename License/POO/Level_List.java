import java.util.ArrayList;

public class Level_List {

    //-1=mur 0=vide 1=pet 2=violet 3=rouge 4=bleu 5=vert 6=jaune

    ArrayList<Niveaux> level;

    Level_List(){
        level=new ArrayList<>();
        createNiveau1();
        createNiveau2();
        createNiveau3();
    }

    void LevelList(){
        System.out.print("Niveaux : ");
        for(Niveaux n : this.level){
            System.out.print(n.num + " ");
        }
        System.out.println();
    }

    void createNiveau1(){
        Niveaux n= new Niveaux(7,7,1,2000);
        //int[] c={1,1}, c2={1,3} , c3={1,7};//Zone vide
        int[] c4={1,2}, c5={1,6};//Zone animalière
        int[] c6={2,1}, c7={2,6}, c8={4,1}, c9={2,3}, c10={6,1}, c11={6,2}, c12={6,5}, c13={4,6};//Zone colorée
        /*
        n.fillzone(c,1,1,-1);
        n.fillzone(c2,1,3,-1);
        n.fillzone(c3,1,1,-1);
        */
        n.fillzone(c4,1,1,1);
        n.fillzone(c5,1,1,1);

        n.fillzone(c6,2,2,2);
        n.fillzone(c7,2,2,3);
        n.fillzone(c8,4,7,4);
        n.fillzone(c9,3,3,5);
        n.fillzone(c10,2,1,2);
        n.fillzone(c11,2,2,3);
        n.fillzone(c12,2,2,2);
        n.fillzone(c13,2,2,6);
        level.add(n);
    }

    //-1=mur 0=vide 1=pet 2=violet 3=rouge 4=bleu 5=vert 6=jaune
    void createNiveau2(){
        Niveaux n2= new Niveaux(8,5,2,1000);
        int[] c1= {3,1},c2={3,2},c3= {3,4};
        int[] c4={1,2} , c5={1,4};
        int[] c6={5,1}, c7={5,2},c8={5,4},c9={5,5};
        int[] c13={7,1}, c10={7,2},c11={7,4},c12={7,5};
        int[] cp1={2,1}, cp2={1,3}, cp3={2,5};
        n2.fillzone(c1,6,5,4);
        n2.fillzone(c2,2,1,5);
        n2.fillzone(c3,2,1,5);
        n2.fillzone(c4,2,1,3);
        n2.fillzone(c5,2,1,3);
        n2.fillzone(c6,2,1,5);
        n2.fillzone(c7,2,1,3);
        n2.fillzone(c8,2,1,3);
        n2.fillzone(c9,2,1,5);
        n2.fillzone(c13,2,1,3);
        n2.fillzone(c10,2,1,5);
        n2.fillzone(c11,2,1,5);
        n2.fillzone(c12,2,1,3);
        n2.fillzone(cp1,1,1,1);
        n2.fillzone(cp3,1,1,1);
        n2.fillzone(cp2,3,1,1);
        level.add(n2);
    }

    void createNiveau3(){
        Niveaux n3=new Niveaux(7,8,3,1000);
        int[] c1={1,4};
        int[] c2={2,1},c3={5,1},c4={2,5},c5={5,5};
        n3.fillzone(c1,1,4,1);
        n3.fillzone(c2,3,4,6);
        n3.fillzone(c3,4,4,4);
        n3.fillzone(c4,3,4,4);
        n3.fillzone(c5,4,4,6);
        level.add(n3);
    }
}