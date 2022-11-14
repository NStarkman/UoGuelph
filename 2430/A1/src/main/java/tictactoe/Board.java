package tictactoe;
import java.util.Scanner;
public class Board{

    private char symbol = ' ';
    private int gameMove; 

    public char[][] getBoard(){
        char[][] board = {{'1', '2', '3'},{'4', '5', '6'}, {'7', '8', '9'}};
        return board;
    }

    /**
     * Gives the numbers from the board and adds it to a nicely designed format and prints it
     * 
     * @param board     Takes in the list of positions to print
     */
    public void printBoard(char[][] board){
        System.out.println(board[0][0] + "|" +  board[0][1] + "|" +  board[0][2]);
        System.out.println("-+-+-");
        System.out.println(board[1][0] + "|" +  board[1][1] + "|" +  board[1][2]);
        System.out.println("-+-+-");
        System.out.println(board[2][0] + "|" +  board[2][1] + "|" +  board[2][2]);

    }
    /**
     * Prompts the user for their desired position to change into their symbol
     * 
     * @param gameStatus    The game status to ensure it is running
     * @param scanner       The scanner function to take in user input
     * @param board         the current status of the board to update
     */
    public void getMove(boolean gameStatus, Scanner scanner, char[][] board) {
        String userInput = "";
        while(gameStatus){
            System.out.println("Where would you like to play? (1-9)");
            userInput = scanner.nextLine();
            break;
        }
        setMove(board, userInput, symbol);
        
    }

    /**
     * Checks if the specific address on the board already has a symbol on it
     * 
     * @param c             The specific char at the index specified on the board
     * @param symbolCheck   The symbol that is going to be changed
     */
    public char checkMove(char c, char symbolCheck){
        if (!(c == 'X')||(c == 'O')){
                c = symbolCheck;
                gameMove++;
        } else{
            System.out.println("Already has a symbol. Try again");
        }
        return c;
        
    }

    /**
     * Takes in a position, checks if the position is one that is accepted, changes if it is, 
     * and then adds a new counter to gameMove to continue game until the board is full or the game is won.
     * 
     * @param board         Takes in the board to change the status
     * @param position      Takes the desired position to move it to
     * @param symbolCheck   The symbol that is going to be changed
     */
    public void setMove(char[][] board, String position, char symbolCheck){
        char c = ' ';
        switch(position) {
            case "1":
                c = checkMove(board[0][0], symbolCheck);
                board[0][0] = c;
                break;
                
            case "2":
                c = checkMove(board[0][1], symbolCheck);
                board[0][1] = c;
                break;
            
            case "3":
                c = checkMove(board[0][2], symbolCheck);
                board[0][2] = c;
                break;
            case "4":
                c = checkMove(board[1][0], symbolCheck);
                board[1][0] = c;
                break;
            
            case "5":
                c = checkMove(board[1][1], symbolCheck);
                board[1][1] = c;
                break;
            case "6":
                c = checkMove(board[1][2], symbolCheck);
                board[1][2] = c;
                break;
                
            case "7":
                c = checkMove(board[2][0], symbolCheck);
                board[2][0] = c;
                break;
            case "8":
                c = checkMove(board[2][1], symbolCheck);
                board[2][1] = c;
                break;
            case "9":
                c = checkMove(board[2][2], symbolCheck);
                board[2][2] = c;
                break;
            default:
                System.out.println("Not in range. Try again");
        }
    }
    
    /**
     * Takes in the depth and uses that to find the current turn
     * 
     * @param moveNum   Takes in the depth/moveNum to check the current symbol to use
     * @return      symbol (X or O)
     */
    public char setSymbol(int moveNum){
        if (moveNum % 2 ==0) {
            symbol = 'X';
        } else {
            symbol = 'O';
        }
        return symbol;

    }
   /**
    * returns the current depth/numMoves/ successful moves that have occured
    * 
    * @return gameMove
    */
    public int getDepth(){
        return gameMove;
    }
}
