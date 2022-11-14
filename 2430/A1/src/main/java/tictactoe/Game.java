package tictactoe;

import java.util.Scanner;

public class Game {

    private boolean gameStatus;

    /**
     * Checks the number of moves and changes the game status accordingly
     * 
     * @param moveNumber    The amount of successful moves that have been made so far
     */
    public void setGameStatus(int moveNumber){
        if (moveNumber !=9){
            gameStatus = true;
        }else{
            gameStatus = false;
        }
    }

    /**
     * Returns the status of the game, whether it is over or not
     * 
     * @return  gameStatus
     */
    public boolean getGameStatus(){
        return gameStatus;
    }
    
    /**
     * Takes in board, along with the symbol that the turn it is, and checks for a win on the board going horizontally
     * 
     * @param board     the current state of the board with the symbols in each position to check for a three in a row
     * @param symbol    the symbol that is being checked for the three in a row
     * @return boolean value
     */
    public boolean horizontalWin(char[][] board, char symbol){
        if ((board[0][0] == symbol && board[0][1] == symbol && board[0][2] == symbol) 
        ||(board[1][0] == symbol && board[1][1] == symbol && board[1][2] == symbol) 
        ||(board[2][0] == symbol && board[2][1] == symbol && board[2][2] == symbol)) {
            return true;
        }
        return false;
    }

    /**
     * Takes in the board, along with the symbol that the turn it is, and checks for a win on the board going vertically
     * 
     * @param board     the current state of the board with the symbols in each position to check for a three in a row
     * @param symbol    the symbol that is being checked for the three in a row
     * @return boolean value
     */
    public boolean verticalWin(char[][] board, char symbol){
        if ((board[0][0] == symbol && board[1][0] == symbol && board[2][0] == symbol) 
        ||(board[0][1] == symbol && board[1][1] == symbol && board[2][1] == symbol) 
        ||(board[0][2] == symbol && board[1][2] == symbol && board[2][2] == symbol)) {
            return true;
        }
        return false;
    }

    /**
     * Takes in the board, along with the symbol that the turn it is, and checks for a win on the board going diagonally
     * 
     * @param board     the current state of the board with the symbols in each position to check for a three in a row
     * @param symbol    the symbol that is being checked for the three in a row
     * @return boolean value
     */
    public boolean diagonalWin(char[][] board, char symbol){
        if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) 
        ||(board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {
            return true;
        }
        return false;
    }

    /**
     * Checks the three possible win types against each other
     * 
     * @param board     the current state of the board with the symbols in each position to check for a three in a row
     * @param symbol    the symbol that is being checked for the three in a row
     * @return boolean value
     */
    public boolean getWinStatus(char[][] board, char symbol) {
        if ((horizontalWin(board, symbol)) || (verticalWin(board, symbol))||(diagonalWin(board, symbol))) {
            return true;
        }
        return false;
    }

    /**
     * Prints out the statment of success for the winning player
     * 
     * @param board     sends in the information of the board to check for winners
     */

    public void getFinishedStatus(char[][] board){
        if (getWinStatus(board, 'X')){
            System.out.println("X Player wins!");
        }else if (getWinStatus(board, 'O')) {
            System.out.println("O Player wins!");
        }else{
            System.out.println("The game ended in a tie!");
        }
    }

    /**
     * Takes in the board, the board class, and a scanner, to run the game for player use
     * 
     * @param board      the current state of the board with the symbols in each position to check for a three in a row
     * @param scanner    the symbol that is being checked for the three in a row
     * @param playBoard  The board class that has access to all of the board functions needed
     * @return NONE
     */
    public void runGame(Board playBoard, char[][] board, Scanner scanner){
        char turnSymbol = ' ';
        playBoard.printBoard(playBoard.getBoard());
        setGameStatus(playBoard.getDepth());
        //Runs the game while the game status is still true
        while(getGameStatus()){
            //sets the current player symbol
            turnSymbol = playBoard.setSymbol(playBoard.getDepth());
            System.out.println("Turn = " + turnSymbol);

            //Prompts the player for a move and checks if it is allowed
            playBoard.getMove(getGameStatus(), scanner, board);
            if (getWinStatus(board, turnSymbol)){
                playBoard.printBoard(board);
                getFinishedStatus(board);
                break;
            //Checks or a tie/Full board
            }else if (!(getWinStatus(board, turnSymbol))&&(playBoard.getDepth()==9)){
                playBoard.printBoard(board);
                getFinishedStatus(board);
                break;
            }
            //Print the board again and changes the status agains
            playBoard.printBoard(board);
            
            setGameStatus(playBoard.getDepth());

        }
    }
} 
