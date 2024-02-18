import java.util.Scanner;

public class User {
    private Scanner s;
    private Parser p;
    private Circuit c;
    
    void choice(){
        try{
            s = new Scanner(System.in);
            String res;
            // si les instruction du scanner sont bon
            boolean bon = false;
            // finir le programme
            boolean end = false;
            // si le 2eme choix est un algorithme
            boolean algo = false;
            while(!end){
                bon = false;
                while(!bon){// choix du circuit
                    System.out.println("Quel circuit voulez vous?");
                    System.out.println("1.test1  2.test2  3.test3");
                    res = s.nextLine();
                    switch(res){
                        case "1":
                            p = new Parser("test1.ppm"); 
                            bon = true;
                            break;
                        case "2":
                            p = new Parser("test2.ppm");
                            bon = true;
                            break;
                        case "3":
                            p = new Parser("test3.ppm");
                            bon = true;
                            break;
                        default:
                            System.out.println("Je n'ai pas compris votre requete.");
                    }
                }
                c = new Circuit(p);
                c.printTableau();
                bon = false;
                while(!bon){// choix de l'algo
                    System.out.println("Quel algorithme voulez vous?");
                    System.out.println("1.parcours en largeur  2.dijkstra  3.a*  4.voiture");
                    res = s.nextLine();
                    switch(res){
                        case "1":
                            Algos.pL(c);
                            algo = true;
                            bon = true;
                            break;
                        case "2":
                            Algos.dijkstra(c);
                            algo = true;
                            bon = true;
                            break;
                        case "3":
                            Algos.aEtoile(c);
                            algo = true;
                            bon = true;
                            break;
                        case "4":
                            Voiture v = new Voiture(c);
                            v.play();
                            bon= true;
                            break;
                        default:
                            System.out.println("Je n'ai pas compris votre requete.");
                    }
                }
                if(algo){
                    Algos.trace_chemin(c.getArrivee(), c);
                    c.printTableau();
                    Algos.affiche_predecesseur(c.getArrivee());
                }
                bon = false;
                while(!bon){// choix de continuer
                    System.out.println("Voulez vous continuer?");
                    System.out.println("1.Oui  2.Non");
                    res = s.nextLine();
                    switch(res){
                        case "1":
                            algo = false;
                            bon = true;
                            break;
                        case "2":
                            end = true;
                            bon = true;
                            break;
                        default:
                            System.out.println("Je n'ai pas compris votre requete.");
                    }
                }    
            }
            s.close();
        }catch(Exception e){
            System.out.println(e);
        }
    }
}