import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class Mandelbrot extends JPanel {
    private BufferedImage bImg;
    private final int max_iter;
    private final double zoom,move_x,move_y;
    private static boolean save;
	 
    public Mandelbrot(int max,double z,double move_x, double move_y) {
        this.max_iter = max;
        this.zoom = z;
        save = false;
        this.move_x = move_x;
        this.move_y = move_y;
        setPreferredSize(new Dimension(800,600));
        setBackground(Color.white);
    }
	 
  //Cette fonction est responsable du calcul de la fractal et de sa représentation graphique.
    void drawMandelbrot(Graphics2D g) {
    	int w = getWidth();
        int h = getHeight();
        bImg = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
        //pour chaque point (x,y) de la fenêtre on calcule la fractale
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                double zx = 0;
                double zy = 0;
                double cX = (x-move_x)/zoom;
                double cY = (y-move_y)/zoom;
                float i = this.max_iter;
                //On fait une boucle qui tourne jusqu'à ce que la fonction diverge ou converge.
                while (Math.sqrt(zx*zx + zy*zy) < 2  && i > 0) {
                	//La formule calculant cx et cy est une formule commune aux fractales.
                    double tmp = zx * zx - zy * zy + cX;
                    zy = 2 * zx * zy + cY;
                    zx = tmp;
                    i--;
                }
                int c;
                if (i > 0){
                	//définit la couleur si la fonction diverge
                    c = Color.HSBtoRGB((this.max_iter / i) % 1, 1, 1);
                }else{
                	//définit la couleur si la fonction converge
                    c = Color.HSBtoRGB((this.max_iter / i) % 1, 1, 0);
                }
                bImg.setRGB(x,y,c);
            }
        }
      //sauvegarde automatique de l'image
        g.drawImage(bImg, 0, 0, null);
        if(!save){
            save();
            save = true;
        }
    }
	 
    @Override
    public void paintComponent(Graphics gg) {
	Graphics2D g = (Graphics2D) gg;
        drawMandelbrot(g);
    }
     
  //Cette fonction permet de sauvegarder la fractale créée.
    public void save(){
        try {
            System.out.println("- saving ... mandelbrot.png-");
            ImageIO.write(bImg, "PNG", new File("mandelbrot.png"));
            System.out.println("- saved -");
        }catch (IOException e) {
            System.out.println("error!");
        }
    }          
}
