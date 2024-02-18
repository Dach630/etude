import java.util.*;

public class Database {
    ArrayList <Relation> tables; // ensemble des relations
    ArrayList <String []> contraintes; // Un element d'une contrainte est note sous la forme Relation.titre

    public Database (ArrayList <Relation> tables,ArrayList <String []> contraintes){

        for (int i = 0; i < tables.size()-1; i++){
            for (int j = i + 1 ; j < tables.size(); j++ ){
                if (tables.get(i).title.equals(tables.get(j).title)){
                    tables.remove(j);
                }
            }
        }
        this.tables = tables;

        int i = 0;
        while (i < contraintes.size()){
            int j = 0;
            boolean correspond = true;
            while (j < contraintes.get(i).length && correspond){
                String [] full_title = contraintes.get(i)[j].split("\\.");
                if (full_title.length != 2){
                    System.out.println ("La contrainte "+i+" a un format incorrect. Abandon de la contrainte.");
                    contraintes.remove(i);
                    correspond = false;
                }else{
                    for (Relation r : tables){
                        if (r.title.equals(full_title[0])){
                            //La fonction titrecorrespond parcoure le set de titres dans la relation, on n'a besoin de l'appeler qu'une fois
                            if(r.titrecorrespond(full_title[1]) == -1){
                                System.out.println ("L'element "+full_title[1]+" n'existe pas dans la table "+full_title[0]+". Abandon d'une contrainte.");
                                correspond = false;
                                contraintes.remove(i);
                            }
                        }
                    }
                }
                j++;
            }
            if(correspond){
                i++;
            }
        }
        this.contraintes = contraintes;
    }


    public boolean addContrainte (String [] c){
        for (int i = 0; i < c.length; i++){
            String [] full_title = c[i].split("\\.");
            if (full_title.length != 2){
                System.out.println ("La contrainte "+i+" a un format incorrect. Abandon de la contrainte.");
                return false;
            }else{
                int j = 0;
                boolean correspond = false;
                while (j < tables.size() && !correspond){
                    if (tables.get(j).title.equals(full_title[0])){
                        if(tables.get(j).titrecorrespond(full_title[1]) == -1){
                            System.out.println ("L'element "+full_title[1]+" n'existe pas dans la table "+full_title[0]+". Abandon de l'ajout de la contrainte.");
                            return false;
                        }else{
                            correspond = true;
                        }
                    }else{
                        j++;
                    }
                }
            }
        }
        contraintes.add(c);
        System.out.println("Une nouvelle contrainte a ete ajoutee");
        return true;
    }

    public boolean StandardChaseEGD (Relation rel,String [] contrainte){
        boolean b = true;
        for (int i = 0; i < rel.tab.size()-1; i++){
            Tulpe t1 = rel.tab.get(i);
            int j = i;
            while (j < rel.tab.size()){
                Tulpe t2 = rel.tab.get(j);
                int k = 0;
                String a = "";
                int corr = 0;
                boolean same_element = true;
                while (k < contrainte.length -1){
                    a = contrainte[k];
                    corr = rel.titrecorrespond(a);
                    if (corr == -1){
                        System.out.println("Un element d'une des contraintes n'existe pas dans la relation "+rel.title);
                        return false;
                    }
                    if(t1.elements[corr].equals(t2.elements[corr])){
                        same_element = false;
                        k = contrainte.length;
                    }else{
                        k++;
                    }
                }
                if(same_element){
                    a = contrainte[contrainte.length-1];
                    corr = rel.titrecorrespond(a);
                    if (!t1.elements[corr].equals(t2.elements[corr])){
                        if (t1.elements[corr].equals("NULL")){
                            t1.elements[corr] = t2.elements[corr];
                        }else{
                            t2.elements[corr] = t1.elements[corr];
                        }
                    }
                }
                j++;
            }
        }
        return true;
    }

    public int findtwo (String [] array){
        for (int i = 0; i < array.length-1;i++){
            if (array[i].equals(array[array.length-1])){
                return i;
            }
        }
        return -1;
    }

    boolean newElements (int index,String [] elems,Relation r, int nbTours){
        if (nbTours < 5){
            Scanner values = new Scanner(System.in);
            String [] backup = elems;
            int l = 0;
            for (Iterator <String> it = r.titres.iterator();it.hasNext();){
                String titr = it.next();
                if (l != index){
                    System.out.print (titr+": ");
                    String newValue = values.nextLine();
                    elems[l] = newValue;
                    System.out.println("");
                }
                l++;
            }
            Tulpe t = new Tulpe(elems);
            if (!r.addTulpe(t)){
                System.out.println("Echec de l'ajout, veuillez reesayer");
                newElements (index,backup,r,nbTours++);
            }else{
                return true;
            }
        }
        System.out.println("Trop de tentatives echoues, abandon de l'operation");
        return false;
    }

    public int StandardChaseTGD (Relation r1, Relation r2, String [] contrainte){
        int pos = 0;
        while (pos < contrainte.length -1){
            String a = contrainte[pos];
            int corr = r1.titrecorrespond(a);
            if (corr == -1){
                System.out.println("Erreur1 :un element de " + r1.title +" dans une contrainte TGD la liant avec "+r2.title+ " n'existe pas");
                return -1;
            }
            pos++;
        }
        pos = r2.titrecorrespond(contrainte[contrainte.length-1]);
        if (pos == -1){
            System.out.println("Erreur2 :l'element de" + r2.title +" dans une contrainte TGD la liant avec "+r1.title+ " n'existe pas");
            return -1;
        }
        int cleEtrangere = findtwo (contrainte);
        if (cleEtrangere == -1){
            System.out.println("Erreur :"+r2.title+" n'a pas de cle etrangere la liant avec "+r1.title);
            return -1;
        }
        for (int i = 0; i < r1.tab.size(); i++){
            Tulpe t1 = r1.tab.get(i);
            boolean foundtulpe = false;
            int j = 0;
            while (j < r2.tab.size() && !foundtulpe){
                Tulpe t2 = r2.tab.get(j);
                if(t1.elements[cleEtrangere].equals(t2.elements[pos])){
                    foundtulpe = true;
                }
                j++;
            }
            if (!foundtulpe){
                int l = r2.titres.size();
                String [] elems = new String [l];
                l = 0;
                int index = 0;
                for (Iterator <String> it = r2.titres.iterator();it.hasNext();){
                    String r = it.next();
                    if(r.equals(contrainte[contrainte.length-1])){
                        elems[l] = t1.elements[cleEtrangere];
                        index = l;
                    }
                    l++;
                }
                System.out.println ("Erreur : la relation "+r2.title+" ne respecte pas une contrainte TGD avec la relation "+r1.title);
                System.out.println ("Veuillez inserer les valeurs du nouveau tulpe :");
                if (!newElements(index,elems,r2,0)){
                    return -1;
                }
                return 1;
            }
        }
        return 0;
    }
}