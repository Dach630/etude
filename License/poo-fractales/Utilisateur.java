import java.util.Scanner;
import java.util.InputMismatchException;

public class Utilisateur {

	//Permet à l'utilisateur de choisir les chiffres réels et imaginaires d'un nombre complexe.
    public Complexe buildComplexe() {
        try {
            Scanner myObj = new Scanner(System.in);
    	    System.out.println("Entrer deux doubles pour créer un nombre complexe :");
    	    System.out.println(" nombre réel :");
    	    double r1 = myObj.nextDouble();
    	    System.out.println(" nombre imaginaire :");
    	    double im1 = myObj.nextDouble();
    	    return new Complexe (r1,im1);
    	}catch (InputMismatchException e){
            System.out.println("valeur invalide. Veuiller recommencer.");
            return buildComplexe();
    	}
    }
	
  //Permet à l'utilisateur de choisir la valeur maximale avant que l'on considère que la fonction ne converge.
    public int buildMaxVal() {
        try {
            Scanner myObj = new Scanner(System.in);
            System.out.println("Entrer le nombre d'itérations maximale de l'algorithme :");
            int max = myObj.nextInt();
            return max;
        }catch (InputMismatchException e){
            System.out.println("valeur invalide. Veuiller recommencer.");
            return buildMaxVal();
    	}
    }
	
    //Permet à l'utilisateur de choisir la valeur du zoom sur l'image.
    public double buildZoom() {
        try {
            Scanner myObj = new Scanner(System.in);
            System.out.println("Entrer le zoom de l'image (150 donne un bon résultat):");
            double rad = myObj.nextInt();
            return rad;
        }catch (InputMismatchException e){
            System.out.println("valeur invalide. Veuiller recommencer.");
            return buildMaxVal();
    	}
    }
	
  //Permet à l'utilisateur de choisir la position de la vue sur l'axe des abscisses.
    public double buildMoveX() {
        try {
            Scanner myObj = new Scanner(System.in);
            System.out.println("Entrer le déplacement de l'image sur l'axe des abscisses (400 centre l'image):");
            double rad = myObj.nextInt();
            return rad;
        }catch (InputMismatchException e){
            System.out.println("valeur invalide. Veuiller recommencer.");
            return buildMaxVal();
    	}
    }
    
    //Permet à l'utilisateur de choisir la position de la vue sur l'axe des ordonnées.
    public double buildMoveY() {
        try {
            Scanner myObj = new Scanner(System.in);
            System.out.println("Entrer le déplacement de l'image sur l'axe des ordonnées (300 centre l'image):");
            double rad = myObj.nextInt();
            return rad;
        }catch (InputMismatchException e){
            System.out.println("valeur invalide. Veuiller recommencer.");
            return buildMaxVal();
    	}
    }
    
    //Quand l'utilisateur a fait une fractale, ce programme lui demande s'il veut en faire une nouvelle ou quitter le programme.
    public void buildNewImage() {
    	try {
	    	Scanner sc = new Scanner(System.in);
	    	System.out.println("Pour créer une nouvelle fractale, taper 1. Pour quitter le programme, taper 2.");
	    	int j = sc.nextInt();
	    	switch(j) {
	    	case 1 :
	    	{
	    		buildImage();
	    	}
	    	case 2:
	    	{
	    		break;
	    	}
	    	default : 
	    	System.out.println("erreur : nombre invalide");
	    	break;
	    	}
	    }catch (InputMismatchException e){
	    	System.out.println("valeur invalide. Veuiller recommencer.");
	    	buildImage();
	    }
	}
    
    //Permet de construire une fractale à partir de différents paramètres choisis par l'utilisateur.
    public void buildImage() {
    	try {
	        Scanner sc = new Scanner(System.in);
	        System.out.println("Pour un ensemble de Julia, entrez 1. Pour un ensemble Mandelbrot, entrez 2. ");
	        int i = sc.nextInt();
	        switch (i) {
	        	case 1:
	            {
	            	new Fenetre("Julia Set", this, 1);
	            	buildNewImage();
	                break;
	            }
	            case 2:
	            {
	            	new Fenetre("Mandelbrot Set", this, 2);
	            	buildNewImage();
	            	break;
	            }
	       default:
	       System.out.println("erreur : nombre invalide.");
	       buildImage();
	       break;
	       }
       }catch (InputMismatchException e){
    	   System.out.println("valeur invalide. Veuiller recommencer.");
    	   buildImage();
       }
    }
}
