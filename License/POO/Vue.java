import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JPanel;


public class Vue extends JFrame{
    JPanel  info, game;
    Model model;
    JLabel score, pet;
    Font font = new Font("Arial", Font.PLAIN, 20);
    Block[][] level;
    JMenuBar menu;
    JButton retry;
    
    
    Vue(){
        setVisible(true);
        setSize(1200, 1200);
        setTitle("pet rescue");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        getContentPane().setLayout(new GridLayout(1,2));
        model = new Model();
        game = new JPanel();
        setMenu();
        
        stage();
    }
  
    void stage(){
        info = new JPanel();
        info.setLayout(new BoxLayout(info, BoxLayout.PAGE_AXIS));
        setMenu();
        info.setBackground(Color.green);
        score = new JLabel(model.score + "", JLabel.CENTER);
        score.setFont(font);
        pet = new JLabel("pet: " + model.save + "/" + model.pet, JLabel.CENTER);
        pet.setFont(font);
        info.add(score);
        info.add(pet);
        info.setLayout(new BoxLayout(info, BoxLayout.PAGE_AXIS));
        getContentPane().add(info);
        getContentPane().add(game);
        setGame();
        model.load(1);
        update();  
    }
    
    void setGame(){ // set level
        Block b;
        level = new Block[model.level.length - 2][model.level[0].length - 2];
        game.setLayout(new GridLayout(model.level[0].length - 2, model.level.length - 2));
        for(int i = 1; i < model.level.length - 1; i++){
            for(int j = 1; j < model.level[i].length - 1; j++){
                final int x = i;
                final int y = j;
                b = new Block(i, j, model.level[i][j]); 
                b.addActionListener((ActionEvent e) -> {
                    model.move(x, y);
                    update();
                });
                game.add(b);
                level[i - 1][j - 1] = b;
            }
        }
    }
    
    void setMenu(){
        JButton level1, level2, level3;
        menu= new JMenuBar();
        retry= new JButton("retry");
        retry.addActionListener((ActionEvent e) -> {
            model.score = 0;        
            model.save = 0;
            for(int i = 1; i < model.level.length - 1; i++){
                for(int j = 1; j < model.level[i].length - 1; j++){
                    model.level[i][j] = model.levelInit[i][j]; 
                }
            } 
            update();
            score.setFont(font);
        });
        menu.add(retry);
        level1 = new JButton("level " + 1);
        level1.addActionListener((ActionEvent e) -> {
            model.load(1);
            update();
        });
        menu.add(level1);
        level2 = new JButton("level " + 2);
        level2.addActionListener((ActionEvent e) -> {
            model.load(2);
            update();
        });
        menu.add(level2);
        level3 = new JButton("level " + 3);
        level3.addActionListener((ActionEvent e) -> {
            model.load(3);
            update();
        });
        menu.add(level3);
        setJMenuBar(menu);
    }
    
    void update(){// update level after action
        for(int i = 1; i < model.level.length - 1; i++){
            for(int j = 1; j < model.level[i].length - 1; j++){
                level[i - 1][j - 1].setColor(model.level[i][j]);
            }
        }
        updateScore();
        updatePet();
    }
    
    private void updateScore(){
        pet.setText("" + model.score);
    }
    
    private void updatePet(){
        pet.setText("pet: " + model.save + "/" + model.pet);
    }    
}

