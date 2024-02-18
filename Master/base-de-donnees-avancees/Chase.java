import java.util.*;
public class Chase {

    Database base;

    public Chase (Database base) {
        this.base = base;
    }

    public boolean StandardChase (int times_checked, ArrayList <String []> ctrs){

        if (times_checked <= 10){
            int i = 0;
            while (i < ctrs.size()){

                String [] s = new String [ctrs.get(i).length];
                String s1 = (ctrs.get(i)[0].split("\\."))[0];
                String s2 = (ctrs.get(i)[ctrs.get(i).length -1].split("\\."))[0];
                for (int j = 0; j < ctrs.get(i).length; j++){
                    s[j] = (ctrs.get(i)[j].split("\\."))[1];
                }
                int parc = 0;
                if (s1.equals(s2)){
                    boolean result = false;
                    while (parc < base.tables.size() && !result) {
                        Relation r = base.tables.get(parc);
                        if (r.title.equals(s1)){
                            result = true;
                            if (base.StandardChaseEGD(r,s)){
                                i++;
                            }else{
                                return false;
                            }
                        }
                        parc++;
                    }
                }else{
                    Relation r1 = base.tables.get(0);
                    Relation r2 = base.tables.get(0);
                    boolean result1 = false;
                    boolean result2 = false;
                    while (parc < base.tables.size() && (!result1 || !result2)){
                        Relation r = base.tables.get(parc);
                        if (r.title.equals(s1)){
                            r1 = r;
                            result1 = true;
                        }else if (r.title.equals(s2)){
                            r2 = r;
                            result2 = true;
                        }
                        parc++;
                    }
                    //Une contrainte TGD rajoute un tulpe, on doit donc reverifier toutes les contraintes vues precedemment
                    int recheck = base.StandardChaseTGD(r1,r2,s);
                    if (recheck > 0){
                        ArrayList <String []> newctrs = new ArrayList <String []> ();
                        for (int k = 0; k < i; k++){
                            newctrs.add(ctrs.get(i));
                        }
                        StandardChase(times_checked+1,newctrs);
                    }else if (recheck == -1){
                        return false;
                    }
                    i++;

                }
            }
            return true;
        }else{
            return false;
        }
    }

    //pas completement fini
    public boolean obliviousChase(int times_checked, List <String []> ctrs){
        if (times_checked <= 10){
            int i = 0;
            while (i < ctrs.size()){

                String [] s = new String [ctrs.get(i).length];
                String s1 = (ctrs.get(i)[0].split("\\."))[0];
                String s2 = (ctrs.get(i)[ctrs.get(i).length -1].split("\\."))[0];
                for (int j = 0; j < ctrs.get(i).length; j++){
                    s[j] = (ctrs.get(i)[j].split("\\."))[1];
                }
                int parc = 0;
                if (!s1.equals(s2)) {
                    Relation r1 = base.tables.get(0);
                    Relation r2 = base.tables.get(0);
                    boolean result1 = false;
                    boolean result2 = false;
                    while (parc < base.tables.size() && (!result1 || !result2)) {
                        Relation r = base.tables.get(parc);
                        if (r.title.equals(s1)) {
                            r1 = r;
                            result1 = true;
                        } else if (r.title.equals(s2)) {
                            r2 = r;
                            result2 = true;
                        }
                        parc++;
                    }
                    int recheck = base.StandardChaseTGD(r1, r2, s);
                    if (recheck == -1) {
                        return false;
                    }

                }
                i++;
            }
            return true;
        }else{
            return false;
        }
    }

}