import java.awt.Color;
import java.awt.Image;
import javax.swing.JButton;

public class Block extends JButton{
    Image image;
    Color color;
    final int x, y;
    int object;
    
    Block(int x, int y, int o){
        this.x = x;
        this.y = y;
        object = o;
        setColor(o);
    }
    
    void setColor(int o){
        switch(o){
            case 1:
                color = new Color(255, 255, 255);
                break;
            case 2:
                color = new Color(255, 0, 0);
                break;
            case 3:
                color = new Color(0, 255, 0);
                break;
            case 4:
                color = new Color(0, 0, 255);
                break;
            case 5:
                color = new Color(155, 155, 155);
                break;
            case 6 :
                color = new Color(155,155,0);
                break;
            default:
                this.setVisible(false);
                break;
        }
        this.setBackground(color);
    }
 
}
