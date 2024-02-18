import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;

public class Fenetre extends JFrame{
    
    // des constantes pour la partie graphique (slider)
    private static final int MOVE_MIN = -100;
    private static final int MOVE_MAX = 100;
    private static final int ZOOM_MIN = 0;
    private static final int ZOOM_MAX = 100;
    
    // La fenetre pour la partie console
    public Fenetre(String frac, Utilisateur u, int choix){
        this.setTitle(frac);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        // demande de valeur a l'utilisateur
        double x = u.buildMoveX();
        double y = u.buildMoveY();
        int max = u.buildMaxVal();
        double z = u.buildZoom();  
        
        switch(choix){
            case 1:
               Complexe c = u.buildComplexe();
               this.add(new Julia(max,z,c,x,y), BorderLayout.CENTER);
               break;
            case 2:
                this.add(new Mandelbrot(max,z,x,y), BorderLayout.CENTER);
                break;
            default:
                System.out.println("Erreur");
        }

        this.pack();
        this.setVisible(true);
    } 
    
    // La fenetre pour la partie graphique
    public Fenetre(){
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(500, 700);
        this.setResizable(false);
        
        JLabel box = new JLabel("Quel emsemble ?");
        String[] options = {"Julia", "Mandelbrot"};
        JComboBox<String> jBox = new JComboBox<>(options);

        JLabel mvX = new JLabel("Déplacement horizontal");
        JSlider moveX = new JSlider(JSlider.HORIZONTAL, MOVE_MIN, MOVE_MAX, 0);
        moveX.setMajorTickSpacing(20);
        moveX.setMinorTickSpacing(5);
        moveX.setPaintTicks(true);
        moveX.setPaintLabels(true);
        
        JLabel mvY = new JLabel("Déplacement vertical");
        JSlider moveY = new JSlider(JSlider.HORIZONTAL, MOVE_MIN, MOVE_MAX, 0);
        moveY.setMajorTickSpacing(20);
        moveY.setMinorTickSpacing(5);
        moveY.setPaintTicks(true);
        moveY.setPaintLabels(true);
        
        JLabel z = new JLabel("Zoom");
        JSlider zoom = new JSlider(JSlider.HORIZONTAL, ZOOM_MIN, ZOOM_MAX, 0);
        zoom.setMajorTickSpacing(20);
        zoom.setMinorTickSpacing(5);
        zoom.setPaintTicks(true);
        zoom.setPaintLabels(true);
        
        JLabel r = new JLabel("contante réel");
        JTextField CR = new JTextField(20);
        
        JLabel ima = new JLabel("constante imaginaire");
        JTextField CI = new JTextField(20);
        
        JLabel i = new JLabel("nombre d'itération");
        JTextField ite = new JTextField(20);
        
        jBox.addActionListener((ActionEvent e) -> {
            String set = jBox.getItemAt(jBox.getSelectedIndex());
            if(set.equals("Julia")){
                r.setVisible(true);
                ima.setVisible(true);
                CR.setVisible(true);
                CI.setVisible(true);
            }else{
                r.setVisible(false);
                ima.setVisible(false);
                CR.setVisible(false);
                CI.setVisible(false);
            }
        }); 
        
        JButton done = new JButton("Appliquer");
        done.addActionListener((ActionEvent e) -> {
            String set = jBox.getItemAt(jBox.getSelectedIndex());
            int max = 0;
            try{
                max = Integer.parseInt(ite.getText());
            }catch(NumberFormatException ex){
                ite.setText("ERREUR");
                return;
            }
            switch(set){
                case"Julia":
                    double cr = 0;
                    double ci = 0;
                    try{
                        cr = Double.parseDouble(CR.getText());
                    }catch(NumberFormatException ex){
                        CR.setText("ERREUR");
                        return;
                    }
                    try{
                        ci = Double.parseDouble(CI.getText());
                    }catch(NumberFormatException ex){
                        CI.setText("ERREUR");
                        return;
                    }
                    Complexe c = new Complexe(cr, ci);
                        new Fenetre("emsemble de Julia", 
                                new Julia(max, (zoom.getValue() * 20)+ 250, c,
                                        (moveX.getValue() * 20) + 400, (moveY.getValue() * 20) + 300));
                    break;
                case"Mandelbrot":
                        new Fenetre("emsemble de mandelbrot",
                                new Mandelbrot(max, (zoom.getValue() * 20)+ 250,
                                        (moveX.getValue() * 20) +400, (moveY.getValue() * 20) + 300));
                    break;
                default:
                    ite.setText("ERREUR");
                    CR.setVisible(true);
                    CR.setText("ERREUR");
                    CI.setVisible(true);
                    CI.setText("ERREUR");
            }
        });
        
        this.setLayout(new GridLayout( 15, 1, 5, 5));
        
        this.add(box);
        this.add(jBox);
        
        this.add(mvX);
        this.add(moveX);
        this.add(mvY);
        this.add(moveY);
        this.add(z);
        this.add(zoom);
        
        this.add(i);
        this.add(ite);
        this.add(r);
        this.add(CR);
        this.add(ima);
        this.add(CI);
        
        this.add(done);

        
        this.setVisible(true);
    }
    
    // utiliser dans la partie graphique pour ouvrir plusieurs fenetres des ensembles donner
    private Fenetre(String frac, JPanel ens){
        this.setTitle(frac);
        this.setLocationRelativeTo(null);
        this.setSize(1000, 1000);
        this.add(ens);
        this.pack();
        this.setVisible(true);
    }
    
}