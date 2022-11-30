package tictactoe;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import boardgame.ui.PositionAwareButton;
import game.GameUI;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.io.File;
import java.awt.Dimension;
import java.awt.Font;
import users.TTTPlayers;
/**
 * This file and class were created by Nathan Starkman
 */
public class TicTacToeUI extends JPanel{// implements ActionListener Class to this class
    private JLabel messageLabel;
    private TicTacToe game;

    private PositionAwareButton[][] buttons = new PositionAwareButton[3][3];
    private GameUI root;
    // This is the constructor for the class. It is setting up the size of the window, the layout, the
    // game controller, and the root. It is also adding the title message, the button grid, and the
    // bottom panel.
    public TicTacToeUI(int width, int height, GameUI gameFrame) {
        super();
        setUpSize();
        setLayout(new BorderLayout());
        setGameController(new TicTacToe(width, height));
        root = gameFrame;
        add(titleMessage(), BorderLayout.NORTH);
        
        add(makeButtonGrid(height, width));
        add(bottomPanel(),BorderLayout.SOUTH);
    }
    /**
     * This function returns the game object
     * 
     * @return The game object.
     */
    public TicTacToe getGame(){
        return game;
    }
    /**
     * Sets the game controller for the game
     * 
     * @param controller The controller object that will be used to control the game.
     */
    public void setGameController(TicTacToe controller){
        this.game = controller;
    }

    
   /**
    * This function sets the preferred size of the JFrame to 500 by 600 pixels
    */
    private void setUpSize(){
        setPreferredSize(new Dimension(500, 600));    
    }

    /**
     * This function creates a JLabel object with the text "Welcome to TicTacToe" to be
     * used as the title of the game
     * 
     * @return The messageLabel is being returned.
     */
    private JLabel titleMessage(){
        messageLabel = new JLabel("Welcome to TicTacToe");
        messageLabel.setFont(new Font("Monospaced", Font.BOLD, 20));
        messageLabel.setHorizontalAlignment(JLabel.CENTER);
        return messageLabel;
    }

    /**
     * It creates a grid of buttons, and adds them to a panel
     * 
     * @param tall the number of columns
     * @param wide the number of columns
     * @return A JPanel with a grid layout of buttons.
     */
    private JPanel makeButtonGrid(int tall, int wide){
        
        JPanel bPanel = new JPanel();
        bPanel.setLayout(new GridLayout(wide, tall));
        for (int y=0; y<wide; y++){
            for (int x=0; x<tall; x++){ 
                buttons[y][x] = new PositionAwareButton();
                doTurn(y, x);
                bPanel.add(buttons[y][x]);
            }
        }
        return bPanel;
    }

    /**
     * This function is called when a button is clicked. It changes the symbol, and then calls the
     * takeTurn function in the game class. If the takeTurn function returns true, then the button is
     * set to the current symbol
     * 
     * @param y the row of the button
     * @param x the x coordinate of the button
     */
    private void setTile(int y, int x){
        game.changeSymbol();
        if(game.takeTurn(x+1,y+1,game.getCurrSymbol())){
            buttons[y][x].setFont(new Font("Monospaced", Font.BOLD, 100));
            buttons[y][x].setText(game.getCurrSymbol());
        }
        
    }
    
    /**
     * Calls the set tile method if a button is clicked and checks if the game was won
     * 
     * @param y the y coordinate of the button
     * @param x The x coordinate of the tile
     */
    private void doTurn(int y, int x){
        buttons[y][x].addActionListener(e->{
            setTile(y,x);
            checkGameState();
            });
    }
    /**
     * It creates a panel with three buttons, one to return to the main menu, one to save the current
     * game, and one to load a previous game
     * 
     * @return A JPanel with three buttons.
     */
    private JPanel bottomPanel(){
        JPanel returnPanel = new JPanel();
        JButton game2Button = new JButton("Return to main menu");
        game2Button.addActionListener(e->mainMenu());
        returnPanel.add(game2Button);
        JButton saveButton = new JButton("Save Current Game");
        saveButton.addActionListener(e->saveGame());
        returnPanel.add(saveButton);
        JButton loadButton = new JButton("Load old game");
        loadButton.addActionListener(e->loadGameButton());
        returnPanel.add(loadButton);
        return returnPanel;
        
    }
    
    /**
     * This function checks if the game is over, and if it is,check if there is a user, if there is, 
     * save the user's data, then it asks the user if they want to go to
     * the main menu, start a new game, or close the program
     */
    private void checkGameState(){
        if(game.isDone()){
            try{
                TTTPlayers player = root.getPlayer();
                if (game.getWinner() == 1){
                    player.setWins();
                }else if(game.getWinner()==2){
                    player.setNewGames();
                }
                player.setNewGames();
                player.savePlayer(player.getName());
            }catch(Exception e){
                JOptionPane.showMessageDialog(null, "No User found. Data will not be saved.");
            }
            String[] options = {"Go to main menu","New Game", "Close Program"};
            var x = 
            JOptionPane.showOptionDialog(null,game.getGameStateMessage(),"Game is over!",0,3,null,options,options[0]);
            if (x ==0){
                mainMenu();
            }else if (x==1){
                removeAll();
                add(new TicTacToeUI(3,3, root));
                repaint();
                revalidate();
            }else{
                System.exit(0);
            }
        }
    }   

    /**
     * It sets the root's current scene to the main menu scene
     */
    protected void mainMenu(){
        root.reMenu();
    }
    /**
     * loads a saved game from a file and sets the tiles in the specific pattern
     */
    private void loadGameButton(){
        String filename = "";
        game.loadSavedString(getFileName(filename, 2));
        for (int i = 1; i<=3; i++){
            for (int j = 1; j<=3; j++){
                buttons[i-1][j-1].setFont(new Font("Monospaced", Font.BOLD, 100));
                buttons[i-1][j-1].setText(game.getBoard().getValue(i, j));
            }
        }
    }
   /**
    * If the user enters a filename that doesn't exist, the program will ask the user to enter a new
    * filename. Otherwise, the program closes
    * 
    */
    protected void saveGame(){
        String filename = "";
        filename = getFileName(filename, 1);
        if (game.saveBoard(filename)==1){
            JOptionPane.showMessageDialog(null,
            "Filename does not exist.");
        }else{
            JOptionPane.showMessageDialog(null,
            "Your file has been saved. Thanks for playing!");
            System.exit(0);
        }
    }

    
    /**
     * This function is used to get the file name from the user
     * 
     * @param filename the name of the file to be saved or opened
     * @param option 1 = save, 2 = open
     * @return The file name of the file that was selected.
     */
    private String getFileName(String filename, int option){
        int response = 0;
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(
            new File("C:\\Users\\nstar\\Documents\\cis2430\\coursework\\A3\\assets\\boards"));
        if (option ==1){
            response = fileChooser.showSaveDialog(null);
        }else if (option ==2){
            response = fileChooser.showOpenDialog(null);
        }
        switch (response) {
            case JFileChooser.APPROVE_OPTION:
                filename = (fileChooser.getSelectedFile().getPath());
                break;
            case JFileChooser.CANCEL_OPTION:
                break;
            case JFileChooser.ERROR_OPTION:
                break;
            default:
                break;
            }
        return filename;
    }
}