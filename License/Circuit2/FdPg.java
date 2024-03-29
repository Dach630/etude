import java.util.HashMap;
import java.util.ArrayList;

// version ArrayList : non bornee...

// suppose que les Elements que l'on stocke, aient
// une fct equals redefinie et une fct hashcode compatible
// (pour que deux objets Elements considere's comme egaux soient geres
// de maniere identique... Important pour IndiceDansF)


public class FdPg <Element> {

    class Paire {
        Element val;
        int cle;
        public Paire () {
            val=null;
            cle=-1;
        }
        public Paire(Element v,int c) {
            val=v;
            cle=c;}
    }

    ArrayList<Paire> T;
    HashMap<Element,Integer> hmap;
    int nb;

    public FdPg() {
        T = new ArrayList<Paire>();
        hmap = new HashMap<Element,Integer>();
        nb=0;
        T.add(new Paire()); //on place une paire "bidon" a la position 0
    }

    //Ajoute un element dans la file de priorite
    void Ajouter(Element n,int c) {
        Paire P=new Paire(n,c);
        T.add(P);
        nb=nb+1;
        int i=nb;
        while (i/2 >= 1 && T.get(i/2).cle > c) {
            T.set(i,T.get(i/2));
            hmap.replace(T.get(i).val,i);
            i=i/2;
        }
        T.set(i,P);
        hmap.put(n,i);
    }

    //Extrait le plus petit element
    Element ExtraireMin() {
        assert(nb>0);
        Element res = T.get(1).val;
        T.set(1,T.get(nb));
        T.set(nb,null);
        hmap.remove(res);
        nb=nb-1;
        if (nb>0) {
            hmap.replace(T.get(1).val,1);
            RemiseEnTas(1);
        }
        return res;
    }

    //Permet de reoraganise la file
    void RemiseEnTas(int i) {
        int g=2*i, d=2*i+1, win=i;
        if (g <= nb && T.get(g).cle<T.get(win).cle)
            win=g;
        if (d <= nb && T.get(d).cle<T.get(win).cle)
            win=d;
        if (win != i) {
            Paire p=T.get(win);
            T.set(win,T.get(i));
            T.set(i,p);
            hmap.replace(T.get(win).val,win);
            hmap.replace(T.get(i).val,i);
            RemiseEnTas(win);
        }
    }

    boolean EstVide() {
        return (nb==0);
    }

    //Retourne l'indice dans le hashmap de l'element n
    int IndiceDsF(Element n) {
        if (hmap.containsKey(n))
            return hmap.get(n);
        else
            return -1;
    }

    //change la valeur associe a l'element n
    void MaJ(Element n,int c) {
        int pos = this.IndiceDsF(n);
        assert(pos != -1);
        int excle = T.get(pos).cle;
        assert(excle >= c);
        T.get(pos).cle=c;
        Paire P = T.get(pos);
        int i=pos;
        while (i/2 >= 1 && T.get(i/2).cle > c) {
            T.set(i,T.get(i/2));
            hmap.replace(T.get(i).val,i);
            i=i/2;
        }
        T.set(i,P);
        hmap.put(n,i);

    }

    public String toString() {
        System.out.print(hmap);
        String res="";
        for (int i=1;i<=nb;i++) {
            res+=String.valueOf(T.get(i).cle)+" ";
        }
        return res;
    }

}
