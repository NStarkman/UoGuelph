package numberttt;

import boardgame.Grid;
/**
 * This file and class were created by Nathan Starkman
 */
public class NumTicTacToeBoard extends Grid{
    private int moveCounter=0;
    
    //private String playerName;
    private String moveName = "";
    private String symbol = "";
   // Calling the super class constructor.
    public NumTicTacToeBoard(int wide, int tall) {
        super(wide, tall);
    }

    

   /**
    * If there is a winner, return the winner's number. If there is a tie, return 0. If there is no
    * winner or tie, return -1
    * 
    * @return The winnerCheck method is returning the winner of the game.
    */
    public int winnerCheck(){
        if (horzWinner()||vertWinner()||diagWinner()){
            if (moveName =="Odd"){
                return 1;
            }
            if (moveName =="Even"){
                return 2;
            }
        }else if (moveCounter==9){
            return 0;
        }
        return -1;    
    }


  /**
   * If the moveCounter is even, the moveName is set to "Odd" and the symbol is set to "O". If the
   * moveCounter is odd, the moveName is set to "Even" and the symbol is set to "E"
   */
    public void setTurn(){
        if (moveCounter%2==0){
            moveName = "Odd";
            symbol = "O";
        }else{
            moveName = "Even";
            symbol = "E";
        }
    }
  
   /**
    * This function returns the name of the move that the player is currently on
    * 
    * @return The name of the move.
    */
    public String getTurnName(){
        return moveName;
    }

    /**
     * If the moveName is "Even" and the value is even, return true. If the moveName is "Odd" and the
     * value is odd, return true. Otherwise, return false
     * 
     * @param value The value that the user has entered.
     * @return The method is returning a boolean value.
     */
    public boolean checkInputValue(int value){
        if (moveName == "Even"&&value %2==0){
            return true;
        }else if (moveName == "Odd"&&value %2==1){
            return true;
        }
        return false;
    }

   /**
    * changes the string into an integer
    * 
    * @param x the row number
    * @param y The column of the cell
    * @return The value of the cell at the given coordinates.
    */
    public int changeStringToInt(int x, int y){
        int returnValue = 0;
        if (getValue(x, y) == " "||getValue(x, y) == ""){
            return 16;
        }
        returnValue = Integer.parseInt(getValue(x, y));
        return returnValue;
    }
    /**
     * If the sum of the first row, second row, or third row is 15, then return true. Otherwise, return
     * false
     * 
     * @return The method is returning a boolean value.
     */
    public boolean horzWinner(){
         if ((changeStringToInt(1, 1) + changeStringToInt(2, 1)+ changeStringToInt(3, 1)==15)
        ||(changeStringToInt(1, 2) + changeStringToInt(2, 2)+ changeStringToInt(3, 2)==15)
        ||(changeStringToInt(1, 2) + changeStringToInt(2, 3)+ changeStringToInt(3, 3)==15)) {
            return true;
        }
        return false;
                
    }

   /**
    * If the sum of the first column, second column, or third column is equal to 15, then return true
    * 
    * @return The method is returning a boolean value.
    */
    public boolean vertWinner(){
        if ((changeStringToInt(1, 1)+ changeStringToInt(1, 2)+ changeStringToInt(1, 3)==15)
        ||(changeStringToInt(2, 1)+ changeStringToInt(2, 2)+ changeStringToInt(2, 3)==15)
        ||(changeStringToInt(3, 1)+ changeStringToInt(3, 2)+ changeStringToInt(3, 3)==15)){
            return true;
        }
        return false;
    }
   /**
    * If the sum of the values in the first diagonal or the second diagonal is equal to 15, then return
    * true
    * 
    * @return The method is returning a boolean value.
    */
    public boolean diagWinner(){

        if ((changeStringToInt(1, 1)+ changeStringToInt(2, 2)+ changeStringToInt(3, 3)==15)
        ||(changeStringToInt(1, 3)+ changeStringToInt(2, 2)+ changeStringToInt(3, 1)==15)) {
            return true;
        }
        return false;
    }

   /**
    * It checks if the input is already in the grid
    * 
    * @param input the number that the user inputs
    * @return The method is returning a boolean value.
    */
    public boolean checkGridCells(int input){
        
        for (int i = 1; i<=3; i++){
            for (int j = 1; j<=3; j++){
                if(changeStringToInt(j, i)==input){
                    return false;
                }
            }
        }
        return true;
    }
    /**
     * This function returns the symbol of the stock
     * 
     * @return The symbol of the card.
     */
    public String getSymbol(){
        return symbol;
    }

    /**
     * This function takes a string as an argument and sets the value of the symbol variable to the
     * value of the string
     * 
     * @param emblem The symbol of the stock
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
