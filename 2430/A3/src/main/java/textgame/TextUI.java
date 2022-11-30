package textgame;

import java.util.Scanner;

import boardgame.Grid;
/**
 * This file and class were created by Nathan Starkman
 */
public class TextUI {
    private Scanner scan = new Scanner(System.in);

   /**
    * This function prints the menu and returns the user's choice
    * 
    * @return The choice of the user.
    */
    public int printMenu(){
        System.out.println("***** Welcome to TicTacToe! *****");
        System.out.println("1. New game");
        System.out.println("2. Load game from file");
        System.out.println("3. Exit game");

        System.out.println("Please enter your option: ");
        int choice = scan.nextInt();
        scan.nextLine();

        return choice;

    }


    /**
     * Prints the board along with a vicotry statement for the player who won
     * 
     * @param player
     * @param board
     * @return void
     */
    public void printWinner(int player, Grid board) {

        
        System.out.println("Player " + player + " is the winner! Congratulations!");

    }

    /**
     * Takes in the player choice to drop onto the board, or takes in -1 to save the board
     * 
     * @param player
     * @param board
     * @return choice
     */
    
    public int scanTurn(String player){
        //Init variables
        int choice = -1;
        System.out.println("Turn: Player " + player);
        while(true){
            System.out.println("Choose a column value between 1-9 (0 to save the board)");
            choice = scan.nextInt();
            if ((choice >= 0) && (choice < 10)) {
                break;
            } else {
                invalidChoice();
            }      
        }
        return choice; 
    }
    
    /**
     * Prints a message that states a choice is invalid
     *     
     *  @return void
     */
    public void invalidChoice(){
        System.out.println("This choice is invalid. Please try again.");
    }
    /**
     * Prints a message that states a file saving error occured
     *     
     *  @return void
     */
    public void failToSave(){
        System.out.println("Sorry! THere was an Error saving this File.");
    }
    /**
     * Prints a message that states a file loading error occured     
     *  @return void
     */
    public void failToLoad(){
        System.out.println("Sorry! There was an Error loading that File. ");
    }

    
    /**
     * Checks the string if it includes a space in it 
     * 
     * @param str
     * @return boolean value
     */
    boolean containsWhitespace(String str){
        return str.matches(".*\\s.*");
    }

    /**
     * Asks the user to enter a filename and ensures it follows the correct size parameters
     * 
     * @return filename
     */
    public String getFilename() {
        String filename;
        
        while(true){
            System.out.println("Enter your file name:");
            filename = scan.next();
            if (filename.length()>3) {
                break;
            } else if(containsWhitespace(filename)){
                System.out.println("No spaces allowed in the file name");
            } else {
                System.out.println("File Name too Small.");
            }
        }
        return filename;
    }

}
