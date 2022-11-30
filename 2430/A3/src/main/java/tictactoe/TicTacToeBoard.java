package tictactoe;

import boardgame.Grid;
/**
 * This file and class were created by Nathan Starkman
 */
public class TicTacToeBoard extends Grid{
    private String symbol = "";
    private int moveCounter = 0;
    
    // Calling the super class constructor.
    public TicTacToeBoard(int wide, int tall) {
        super(wide, tall);
    }
   /**
    * This function checks the value of the cell at the given coordinates
    * 
    * @param across The column number of the cell you want to check.
    * @param down the row number
    * @return The value of the cell at the given coordinates.
    */
    public String checkValue(int across, int down){
        return getValue(across, down);
    }
    /**
     * If there is a winner, return 1 if the winner is X, 2 if the winner is O, 0 if there is a tie,
     * and -1 if there is no winner
     * 
     * @return The winnerCheck method returns the winner of the game.
     */
    public int winnerCheck(){
        if (horzWinner()||vertWinner()||diagWinner()){
            if (symbol =="X"){
                return 1;
            }
            if (symbol =="O"){
                return 2;
            }
        }else if (moveCounter==9){
            return 0;
        }else{
            return -1;
        }
        return -1;
    }

    /**
     * If the symbol is equal to the value of the first row, second row, or third row, then return true
     * 
     * @return The method is returning a boolean value.
     */
    public boolean horzWinner(){
        if ((symbol == getValue(1, 1) && symbol == getValue(2, 1)&& symbol ==getValue(3, 1))
        ||(symbol == getValue(1, 2) && symbol ==  getValue(2, 2) &&symbol ==  getValue(3,2))
        ||(symbol == getValue(1, 3) && symbol == getValue(2, 3) && symbol == getValue(3,3))){
            return true;
        }

        return false;
                
    }
    /**
     * If the symbol is equal to the value of the first column, second column, or third column, then return true
     * 
     * @return The method is returning a boolean value.
     */
    public boolean vertWinner(){
        if ((symbol == getValue(1, 1) && symbol == getValue(1, 2)&& symbol ==getValue(1, 3))
        ||(symbol == getValue(2, 1) && symbol ==  getValue(2, 2) &&symbol ==  getValue(2,3))
        ||(symbol == getValue(3, 1) && symbol == getValue(3, 2) && symbol == getValue(3,3))){
            return true;
        }
        return false;
    }
    /**
     * If the center square is the same as the top left and bottom right squares, or the center square
     * is the same as the top right and bottom left squares, then return true
     * 
     * @return The method is returning a boolean value.
     */
    public boolean diagWinner(){

        if ((getValue(1,1)==symbol && getValue(2,2) == symbol && getValue(3,3) == symbol) 
        ||(getValue(1,3) == symbol && getValue(2,2) == symbol && getValue(3,1) == symbol)) {
            return true;
        }
        return false;
    }
    /**
     * If the moveCounter is even, set the symbol to X, otherwise set the symbol to O
     */
    public void setSymbol(){
        if (moveCounter%2==0){
            symbol = "X";
        }else{
            symbol = "O";
        }
    }
    /**
     * This function returns the symbol of the current player
     * 
     * @return The symbol of the card.
     */
    public String getSymbol(){
        return symbol;
    }

   /**
    * Changes the symbol manually when loading a file
    * 
    * @param emblem The symbol of the player.
    */
    public void updateSymbol(String emblem){
        symbol = emblem;
    }
    
   /**
    * This function increments the moveCounter variable by 1
    */
    public void incrementCounter(){
        moveCounter++;
    }
}
