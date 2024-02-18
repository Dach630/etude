public class Main {
    
    public static void main(String[] args) {
        
        if(args.length == 1){
            Utilisateur u = new Utilisateur();
            u.buildImage();
        }else{
            if(args.length == 2 && args[1].equals("-i")){
                Fenetre fenetre = new Fenetre();
            }else{
                help();
            }
        }
        
    }  
    
    //aide pour l'utilisataur 
    public static void help(){
        System.out.println(
                "arguments :\n" +
                "          : sans arguments lance le programme sur la console\n" +
                "    -i    : lance l'interface graphique du programme"
        );    
    }
}