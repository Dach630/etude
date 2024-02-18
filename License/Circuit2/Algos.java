import java.util.*;

public class Algos {

    //Parcours en largeur a la volee
    //Initialise les successeurs de tous les sommets jusqu'a l'arrivee
    static void pL(Circuit circuit){
        Sommet s = circuit.getDepart();
        s.setNombreCoup(0);
        s.setPredecesseur(null);

        Queue<Sommet> f = new LinkedList();                     //f est une structure FIFO
        ArrayList<Sommet> dejaVu = new ArrayList();              //dejaVu est l'ensemble de Sommet deja visite
        dejaVu.add(s);
        f.add(s);

        while(!f.isEmpty()) {
            //Sort x de la file et cherche ses successeurs
            Sommet x = f.poll();
            x.setSuccesseurs(circuit);

            for (Sommet y : x.getSuccesseurs()) {   //Pour chaque sommets jusqu'a l'arrive verifie si le sommet a deja ete parcourru et si c'est l'arrivee
                if (!estPresent(dejaVu, y)) {
                    dejaVu.add(y);
                    y.setNombreCoup(x.getNombreCoup() + 1);
                    y.setPredecesseur(x);
                    f.add(y);
                }
                if(y.equals(circuit.getArrivee())) return ;
            }
        }
        return ;
    }

    //Comme le parcourt en largeur, sauf qu'il utilise des files de prioritees, il est plus rapide
    static void dijkstra(Circuit circuit){
        Sommet s = circuit.getDepart();
        s.setNombreCoup(0);
        s.setPredecesseur(null);

        Sommet arrive = circuit.getArrivee();
        FdPg<Sommet> file = new FdPg<>();
        file.Ajouter(s, 0);
        HashSet<Sommet> dejavu = new HashSet<>();   //ici on a un hashset a la place de l'arraylist, ca facilite la comparaison
        while(!file.EstVide()){
            Sommet u = file.ExtraireMin();
            if (u.equals(arrive)) return;
            u.setSuccesseurs(circuit);
            for(Sommet v : u.getSuccesseurs()){
                int indice = file.IndiceDsF(v);     //indice est la position du sommet dans le hashmap de file
                if(indice != -1){       //-1 signifie que le sommet n'est pas dans la file
                    Sommet w = file.T.get(indice).val;      //w est le sommet avec les meme coordonnees et vitesse que v
                    if(w.getNombreCoup() > u.getNombreCoup() + 1) {     //comapre la distance des deux sommets w et v
                        w.setNombreCoup(u.getNombreCoup() + 1);
                        w.setPredecesseur(u);
                        file.MaJ(w, u.getNombreCoup() + 1);      //met a jour la valeur de w dans la file de priorite
                    }
                }else{
                    if(!dejavu.contains(v)){
                        dejavu.add(v);
                        if(!v.equals(circuit.getDepart())){     //verification pour evite que le depart ne devienne son propre predecesseur
                            v.setNombreCoup(u.getNombreCoup() + 1);
                            v.setPredecesseur(u);
                        }
                        file.Ajouter(v, v.getNombreCoup());
                    }
                }
            }
        }
        return;
    }
    
    static void aEtoile(Circuit circuit) { // Meme principe que dijkstra, mais renvoie un resultat plus rapidement.
	    Sommet s = circuit.getDepart();
        s.setNombreCoup(0);
        s.setPredecesseur(null);
  
        Sommet arrive=circuit.getArrivee();
        FdPg<Sommet> file = new FdPg<>();
        file.Ajouter(s, 0);
        HashMap<Sommet, Integer> dejavu = new HashMap<>(); // prend les points qu'on a deja observe
        while(!file.EstVide()){ // parcourt le tableau jusqu'a ce qu'on arrive au point d'arrivee
            Sommet u = file.ExtraireMin();
        	dejavu.put(u, u.getNombreCoup());
        	if(u.equals(arrive)) {
                return;
        	}
        	u.setSuccesseurs(circuit);
        	for(Sommet v : u.getSuccesseurs()){
        	    int indice = file.IndiceDsF(v);
        		if(indice != -1){ // Si l'indice est dans la file, on prend le sommet qui s'y trouve 
        		    Sommet w = file.T.get(indice).val;
                    if(w.getNombreCoup() > u.getNombreCoup() + 1) { // Si le sommet qu'on a pris peut etre atteint en moins de coups, on le remplace
                    	w.setNombreCoup(u.getNombreCoup() + 1);
                        w.setPredecesseur(u);
                        file.MaJ(w,u.getNombreCoup() + 1);
                    }
        		}else if(dejavu.get(v) != null) { //S'il n'est pas dans la file, on regarde dans dejavu
        			if(dejavu.get(v) > u.getNombreCoup() + 1) {// Si le sommet dans dejavu peut etre atteint en moins de coups, on le remplace
                        dejavu.remove(v);
                        file.Ajouter(v, v.getNombreCoup()); // On ajoute le sommet a la file
        		    }
        		}else{ // S'il n'est dans aucun des deux on le rajoute
            		v.setNombreCoup(u.getNombreCoup() + 1);
                    if(!v.equals(circuit.getDepart())){
                        v.setPredecesseur(u);
                    }
                    file.Ajouter(v, v.getNombreCoup());
        	    }
            }	
        }
    	return;
    }

    //Retourne true si un Sommet s est present dans une liste de Sommet v
    static boolean estPresent(ArrayList<Sommet> v, Sommet s){
        return v.contains(s);
    }

    static void trace_chemin(Sommet s,Circuit c) { //affiche le chemin parcouru par le véhicule
        while(s.getPredecesseur() != null){
            c.pixels[s.getPredecesseur().getX()][s.getPredecesseur().getY()] = 9;
            s = s.getPredecesseur();
        }
    }

    static void affiche_predecesseur(Sommet s) {  // affiche la liste des predecesseurs d'un sommet 
        if(s.getPredecesseur() != null){
            affiche_predecesseur(s.getPredecesseur());
        }
        s.affiche();
    }

}