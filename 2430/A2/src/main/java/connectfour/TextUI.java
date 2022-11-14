package connectfour;

import java.util.Scanner;
 /**
     * The TextUI Class prints and scans all IO messages from and to the user
     * 
     * Author: Nathan Starkman
     */
public class TextUI{
    
    private Scanner scan = new Scanner(System.in); //Scanner 

    /**
     * Prints the menu options and takes in the option chosen
     * 
     * @return choice (1,2,3)
     */
    public int printMenu(){
        System.out.println("***** Welcome to Connect Four! *****");
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
    public void printWinner(int player, String board) {

        System.out.println(board);
        System.out.println("Player " + player + " is the winner! Congratulations!");

    }

    /**
     * Takes in the player choice to drop onto the board, or takes in -1 to save the board
     * 
     * @param player
     * @param board
     * @return choice
     */
    public int scanTurn(int player, String board){
        //Init variables
        int choice = -2;
        System.out.println(board);
        System.out.println("Turn: Player " + player);

        while(true){
            System.out.println("Enter a number between 0 and 6 to place your piece (-1 to save): ");
            choice = scan.nextInt();
            if ((choice > -1) && (choice < 6)) {
                break;
            } else {
                invalidChoice();
            }      
        }
        return choice; 
    }

    /**
     * Prints a message that states a move is invalid
     *     
     *  @return void
     */
    public void invalidMove(){
        System.out.println("This move is not possible. Please try again.");
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
     * Prints a message that states the game ended in a tie   
     *  @return void
     */
    public void endedInTie(){
        System.out.println("The Game has Ended in a tie!");
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
            filename = scan.nextLine();
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