public class Model{
    
    int[][] level;
    int[][] levelInit;
    int save;
    int pet;
    int score;
    int scoreObjectif; 
    int win = 0;
    LevelList game;

    Model(){
        game = new LevelList();
        score = 0; 
    }
    
    void load(int l){
        save = 0;
        score = 0;
        levelInit= game.get(l-1);
        
        level = new int[levelInit.length][levelInit[0].length];
        
        level = new int[levelInit.length][levelInit[0].length];
        for(int i = 0;i< levelInit.length;i++) {
            for (int j = 0; j < levelInit[i].length; j++) {
                level[i][j] = levelInit[i][j];
            }
        }
        
    }
    
    public void move(int x, int y){
        if(check(x, y)){
            score(suppr(x, y));
            fall();
            if(win == 0){
                save();
                fall();
            }
            left();
        }
    }
    private void score(int n){
        score += n * n * 10;
    }
    
    private boolean check(int x, int y){
        if(x > 0 && y > 0 && x < level.length - 1 && y < level[0].length - 1){
            int c = level[x][y];
            if(c < 2) return false;
            return c == level[x-1][y] || c == level[x+1][y] || c == level[x][y-1] ||c == level[x][y+1];
        }
        return false;
    }
    
    private int suppr(int x, int y){// call first for remove 
        return suppr(x, y, level[x][y], 0);
    }
    private int suppr(int x, int y, int c, int n){
        n++;
        level[x][y]=0;
        if(level[x-1][y] == c) n += suppr(x - 1, y, c, n);
        if(level[x+1][y] == c) n += suppr(x + 1, y, c, n);
        if(level[x][y-1] == c) n += suppr(x, y - 1, c, n);
        if(level[x][y+1] == c) n += suppr(x, y + 1, c, n);
        return n;
    }
    
    private void save(){
        for(int i = 0 ; i< level[0].length; i++){
            if(level[level.length - 2][i] == 1){
                level[level.length - 2][i]=0;
                save++;
            }
        }
    }
    
    public boolean win(){// objectif
        switch(win){
            case 0:
                return winPet();
            case 1 :
                return winScore();
            case 2 :
                return winPuzzle();
            default:
                return false;
        }
    }
    
    private boolean winPet(){
        return save == pet;
    }
    private boolean winScore(){
        return score >= scoreObjectif;
    }
    private boolean winPuzzle(){
        for(int i = 1; i < level.length - 1; i++ ){
            for(int j = 1; j < level[i].length - 1; j++ ){
                if(level[i][j] != 0){
                    return false;
                }
            }
        }
        return true;
    }
    
    public boolean lose(){// can't do a move
        for(int i = 1; i < level.length - 1; i++ ){
            for(int j = 1; j < level[i].length - 1; j++ ){
                if(check(i, j)){
                    return false;
                }
            }
        }
        return true;
    }
    
    void fall(){
        int i = level.length - 2;
        for(int j = 1; j < level[i].length ; j++){
            if(verifCol0(i, j) || whereis0Col(j) != -1){
                arrColTer(j);
            }
        }
    }

    //Retourne la position du premier 0 trouvé
    int whereis0Col(int j){
        for(int i = level.length-2; i > 1; i--){
            if(level[i][j] == 0) return i;
        }
        return -1;
    }

    //True si la colonne est rangée
    boolean verif0Haut(int j){
        int a = 0;
        //Si la colonne à un 0...
        for(int i = level.length - 2; i > 1; i--){
            if(level[i][j] == 0){
                a = i;
                break;
            }
        }
    //Vérifie si le reste de la colonne est rempli de 0 de a à 1
        if(a > 0){
            while(a > 1){
                if(level[a][j] != 0) return false;
                a--;
            }
        }
        return true;
    }
    //TriPartiel sur la colonne
    void arrColumn(int i,int j){
        int a = i;
        while(a > 1 && level[a][j] == 0 && level[a-1][j] != -1){
            int tmp = level[a-1][j];
            level[a-1][j] = level[a][j];
            level[a][j] = tmp;
            a--;
        }
    }

    //TriParInsertion sur le plateau
    void arrColTer(int j){
        while(!verif0Haut(j)){
            int a = whereis0Col(j);
            arrColumn(a, j);
        }
    }
    
    //True si la colonne est remplie de 0
    boolean verifCol0(int i ,int j){
        //Vérifie si la colonne est remplie de 0
        if(level[i][j] == -1) return true;
        else if(level[i][j] == 0) return verifCol0(i-1,j);
        else return false;
    }

    //Glisse toute les colonnes vers la gauche
    void left(){
        int i = level.length - 2;
        //Vérifie si il y a toujours des colonnes à ranger
        while(!verifPC()){
            for(int j = 1; j < level[i].length - 2; j++){
                //Si c'est le cas, stack les colonnes sur la gauche
                if(verifCol0(i, j)){
                    //System.out.println("i = " + i + "   j = " + j);
                    fillColumn(i, j);
                }
            }
        }
    }

    //Remplit la colonne actuelle avec la colonne de droite
    void fillColumn(int i, int j){
        if(level[i][j+1] != -1) {
            //System.out.println("a");
            level[i][j] = level[i][j+1];
            level[i][j+1] = 0;
            fillColumn(i-1, j);
        }
    }

    //True si le tableau est rangé
    boolean verifPC(){
        int i = level.length - 2, a = 0;
        //Si verifCol0 est vérifié une fois...
        for(int j = 1; j < level[i].length - 2; j++){
            if(verifCol0(i, j)){
                a = j;
                break;
            }
        }
        //Vérifie si le reste du tableau est rempli de 0
        if(a > 0){
            while(a < level[i].length){
                if(!verifCol0(i, a)) return false;
                a++;
            }
        }
        return true;
    }
}  