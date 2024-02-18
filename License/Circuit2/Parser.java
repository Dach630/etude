import java.io.IOException;
import java.util.Scanner;
import java.io.File;

public class Parser {

    private int[][] pixels;

    //Creer un double tableau de pixel a partir d'un fichier ppm
    public Parser(String chemin) throws IOException {
        try {
            File file = new File(chemin);
            Scanner s = new Scanner(file);
            s.nextLine();
            s.nextLine();
            //Sert a prendre les dimensions du tableau de pixel
            int w = s.nextInt();
            int h = s.nextInt();
            pixels = new int[h][w];
            s.nextInt();
            int r , g , b;
            int i = 0 , j = 0;

            //Ne peut convertir que 4 couleurs
            while(s.hasNextInt()){
                r = s.nextInt();
                g = s.nextInt();
                b = s.nextInt();
                //Verifie si la colonne est pleine
                if(j >= pixels[i].length){
                    j=0;
                    i++;
                }
                //Cas 1: Noir / Chemin
                if(r > 128 && g>128 && b>128){
                    pixels[i][j] = 0;
                    j++;
                }
                //Cas 2: Blanc / Mur
                else if(r < 128 && g<128 && b<128){
                    pixels[i][j]= 1;
                    j++;
                }
                //Cas 3: Rouge / Point de depart
                else if(r > 128 && g<128 && b<128){
                    pixels[i][j]= 2;
                    j++;
                }
                //Cas 4: Bleu / Point d'arrivee
                else if(r < 128 && g < 128 && b > 128){
                    pixels[i][j]= 3;
                    j++;
                }
            }
            s.close();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public int[][] getPixels(){
        return pixels;
    }
}
