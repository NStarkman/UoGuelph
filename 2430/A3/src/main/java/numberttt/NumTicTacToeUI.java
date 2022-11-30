package numberttt;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import boardgame.ui.PositionAwareButton;
import game.GameUI;
import users.TTTPlayers;

import javax.swing.JLabel;
import javax.swing.JOptionPane;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.io.File;
import java.awt.Dimension;
import java.awt.Font;
/**
 * This file and class were created by Nathan Starkman
 */
public class NumTicTacToeUI extends JPanel {
    private JLabel messageLabel;
    private NumTicTacToe game;
    private PositionAwareButton[][]  buttons = new PositionAwareButton[3][3];
    private GameUI root;
    // This is the constructor for the class. It is setting up the size of the panel, the layout, the
    // game controller, the root, the title message, the button grid, and the bottom panel.
    public NumTicTacToeUI(int width, int height, GameUI gameFrame) {
        super();
        setUpSize();
        setLayout(new BorderLayout());
        setGameController(new NumTicTacToe(width, height));
        root = gameFrame;
        add(titleMessage(), BorderLayout.NORTH);
        add(makeButtonGrid(height, width));
        add(bottomPanel(),BorderLayout.SOUTH);
    }
    
   /**
    * This function sets the game controller to the controller passed in as a parameter
    * 
    * @param controller The controller object that will be used to control the game.
    */
    public void setGameController(NumTicTacToe controller){
        this.game = controller;
        }

   /**
    * This sets the size of the game window
    */
    private void setUpSize(){
        setPreferredSize(new Dimension(500, 600));    
    }

    /**
     * This function creates a JLabel object with the text "Welcome to Numeric TicTacToe" and sets the
     * font to Monospaced, bold, and size 20. It then sets the horizontal alignment to center and
     * returns the JLabel object
     * 
     * @return The titleMessage method returns a JLabel object.
     */
    private JLabel titleMessage(){
        messageLabel = new JLabel("Welcome to Numeric TicTacToe");
        messageLabel.setFont(new Font("Monospaced", Font.BOLD, 20));
        messageLabel.setHorizontalAlignment(JLabel.CENTER);
        return messageLabel;
    }

   /**
    * It creates a grid of buttons, and adds them to a panel
    * 
    * @param tall the number of rows
    * @param wide the number of columns
    * @return A JPanel with a grid layout of buttons.
    */
    private JPanel makeButtonGrid(int tall, int wide){
        JPanel panel = new JPanel();
       
        panel.setLayout(new GridLayout(wide, tall));
        for (int y=0; y<wide; y++){
            for (int x=0; x<tall; x++){ 
                buttons[y][x] = new PositionAwareButton();
                doTurn(y, x);
                panel.add(buttons[y][x]);
            }
        }
        return panel;
    }

   /**
    * The function takes in the y and x coordinates of the button that was clicked, and then asks the
    * user for a value to place in the button. If the value is valid, the function will then call the
    * takeTurn function in the game class, which will then update the board
    * 
    * @param y the row of the button
    * @param x the x coordinate of the button
    */
    private void setTile(int y, int x){
        game.updateTurn();
        String value = JOptionPane.showInputDialog(null, "Enter value 1-9 (Turn = "+game.checkTurnName()+")");
        try { 
            int inputValue = Integer.parseInt(value);
            if (game.getInputValue(inputValue)){
               if(game.takeTurn(y+1,x+1,inputValue)){
                    buttons[y][x].setFont(new Font("Monospaced", Font.BOLD, 100));
                    buttons[y][x].setText(value);
                }
            }
            checkGameState();    
         } catch(NumberFormatException e) { 
           JOptionPane.showMessageDialog(null, "Value does not match requirements. Please Try again!");
         }
    }

    /**
     * Calls the set tile method if a button is clicked
     * 
     * @param y the y coordinate of the button
     * @param x The x coordinate of the tile
     */
    private void doTurn(int y, int x){
        buttons[y][x].addActionListener(e->setTile(y,x));
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
     * If the game is over, check if there is a user, if there is, save the user's data, then display a
     * message to the user and give them the option to go to the main menu, start a new game, or close
     * the program
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
                add(new NumTicTacToeUI(3,3, root));
                repaint();
                revalidate();
            }else{
                System.exit(0);
            }
        }
    }   

   /**
    * It takes the current scene and replaces it with the main menu scene.
    */
    protected void mainMenu(){
        root.reMenu();
    }
    /**
     * It loads a saved game from a file and sets the buttons on the grid
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
     * This function saves the game by calling the saveBoard function in the game class.
     */
    protected void saveGame(){
        String filename = "";
        removeAll();
        filename = getFileName(filename,1);
        game.saveBoard(filename);
        JOptionPane.showMessageDialog(null,
            "Your file has been saved. Thanks for playing!");
            System.exit(0);
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