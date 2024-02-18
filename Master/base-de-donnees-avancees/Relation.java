import java.util.*;

public class Relation {
    String title; // nom d'une table
    Set <String> titres; //nom des elements d'une table
    ArrayList <Tulpe> tab; //la liste des tulpes

    public Relation (String title,Set <String> titres,ArrayList <Tulpe> tab) {
        this.title = title;
        this.titres = titres;
        int index = 0;
        // On verifie que tous les tulpes ont le nombre d'elements qui correspond au nombre d'elements attendus dans la relation
        while (index < tab.size()){
            if (titres.size() != tab.get(index).elements.length){
                System.out.println("Erreur, un element de la relation "+title+" n'a pas le bon nombre d'elements");
                tab.remove(index);
            }
            index++;
        }
        this.tab = tab;
    }

    public int titrecorrespond (String c){
        int j = 0;
        for (Iterator <String> it = titres.iterator();it.hasNext();){
            String s = it.next();
            if (c.equals(s)){
                return j;
            }
            j++;
        }
        System.out.println(c + " ne correspond a aucun titre d'element dans la table "+ title);
        return -1;
    }

    public boolean addTulpe (Tulpe t) {
        if(titres.size() != t.elements.length){
            System.out.println("Erreur : un tulpe n'a pas pu etre ajoute.");
            return false;
        }else{
            tab.add(t);
            System.out.println ("ajout d'un tulpe dans la table.\n");
            return true;
        }
    }
}