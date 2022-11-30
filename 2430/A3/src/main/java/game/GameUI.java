package game;

import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JPanel;

import numberttt.NumTicTacToeUI;

import tictactoe.TicTacToeUI;
import users.TTTPlayers;

import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;

import java.awt.BorderLayout;
import java.awt.Container;

import java.awt.Font;

/**
 * This file and class were created by Nathan Starkman
 */
public class GameUI extends JFrame{
    private TTTPlayers player1;
    private JMenuBar mb;
    private JMenu loadMenu;
    private JMenu createMenu;
    private JMenuItem create;
    private JMenuItem load;
    private Container contentPane;
    
    public static final int WIDTH = 600;
    public static final int HEIGHT= 500;

    // This is the constructor for the GameUI class. It is calling the super constructor, setting up
    // the size of the window, setting the title, and setting the main container.
    public GameUI(){
        super();
        setUpSize();
        setTitle("Nathan's Games");
        setMainContainer();
 
    }
    /**
     * This function sets the main container of the GUI.
     */
    private void setMainContainer(){
        contentPane = getContentPane();
        contentPane.setLayout(new BorderLayout());
        contentPane.add(startupMessage(), BorderLayout.CENTER);
        contentPane.add(makeButtonPanel(), BorderLayout.SOUTH);
        contentPane.add(makePlayerMenu(), BorderLayout.NORTH);
        
    }
   /**
    * Sets the size of the gameUI, along with the title
    */
    private void setUpSize(){
        setSize(WIDTH, HEIGHT);
        setTitle("A Game GUI");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    
    }
    /**
     * It creates a menu bar with two options, one to load an existing player and one to create a new
     * player.
     * 
     * 
     * @return The JMenuBar is being returned.
     */
    private JMenuBar makePlayerMenu(){
        mb = new JMenuBar();
        loadMenu = new JMenu("Load");
        createMenu = new JMenu("Create");
        load = new JMenuItem("Load Existing Player");
        create = new JMenuItem("Create New Player");
        load.addActionListener(e->getUser());
        create.addActionListener(e->getUser());
        loadMenu.add(load);
        createMenu.add(create);
        mb.add(load);
        mb.add(create);
        return mb;
    }

    /**
     * Makes the panel at the bottom of the page for game selection
     * 
     * @return The buttonPanel is being returned.
     */
    private JPanel makeButtonPanel(){
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(makeTicTacToeButton());
        buttonPanel.add(makeSecondGameButton());
        return buttonPanel;
    }


    /**
     * Creates a start up message for the front page
     * 
     * @return A JPanel with a JLabel on it.
     */
    private JPanel startupMessage(){
        JPanel temp = new JPanel();
        JLabel label = new JLabel("Lets Play a Game!");
        label.setFont(new Font("Monospaced", Font.BOLD, 40));
        temp.add(label);

        return temp;
    }
    
   /**
    * This function gets the user's name and creates a new TTTPlayers object with the name.
    */
    private void getUser(){
        String playerName = JOptionPane.showInputDialog(this, "Enter Player 1 name: ");
        player1 = new TTTPlayers(playerName);
    }
    /**
     * This function returns the player1 variable
     * 
     * @return The player1 object.
     */
    public TTTPlayers getPlayer(){
        return player1;
    }

   /**
    * "This function creates a new button that, when clicked, will create a new Tic Tac Toe game."
    * 
    * @return A button with the text "Play new Tic Tac Toe"
    */
    private JButton makeTicTacToeButton(){
        JButton button = new JButton("Play new Tic Tac Toe");
        TicTacToeUI newGame = new TicTacToeUI(3,3, this);
        button.addActionListener(e->ticTacToe(newGame));
        return button;
    }

    /**
     * This function creates a button that, when clicked, will start a new game of Numeric Tic Tac Toe.
     * 
     * @return A button with the text "Play new Numeric Tic Tac Toe"
     */
    private JButton makeSecondGameButton(){
        JButton button = new JButton("Play new Numeric Tic Tac Toe");
        button.addActionListener(e->secondGame());
        return button;
    }
    

    /**
     * Removes all the components from the contentPane, adds the new game to the contentPane,
     * repaints the contentPane, revalidates the contentPane, and packs the contentPane
     * 
     * @param newGame The new game that is being displayed.
     */
    protected void ticTacToe(TicTacToeUI newGame){
        contentPane.removeAll();
        contentPane.add(newGame);
        getContentPane().repaint();
        getContentPane().revalidate();
        pack();
    }

    /**
     * It removes all the components from the contentPane, adds a new NumTicTacToeUI object to the
     * contentPane, repaints the contentPane, revalidates the contentPane, and then packs the
     * contentPane.
     */
    protected void secondGame(){
        contentPane.removeAll();
        contentPane.add(new NumTicTacToeUI(3, 3, this));
        getContentPane().repaint();
        getContentPane().revalidate();
        pack();
     
    }
   
    
    /**
     * It removes all the components from the JFrame, disposes of the current JFrame, creates a new
     * JFrame, makes it visible, repaints the content pane, revalidates the content pane, and packs the
     * JFrame.
     * 
     */
    public void reMenu(){
        contentPane.removeAll();
        this.dispose();
        GameUI newMenu = new GameUI();
        newMenu.setVisible(true);
        getContentPane().repaint();
        getContentPane().revalidate();
        pack();
    }
    
   /**
    * This function is the main function of the program. It creates a new instance of the GameUI class
    * and sets it to visible.
    */
    public static void main(String[] args){
        GameUI example = new GameUI();
        example.setVisible(true);
    }
} 

