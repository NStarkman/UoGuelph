package numberttt;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import boardgame.BoardGame;
import boardgame.Saveable;

/**
 * This file and class were created by Nathan Starkman
 */

/**
 * The NumTicTacToe class extends the BoardGame class and implements the Saveable interface.
 */
/**
 * This class extends the BoardGame class and implements the Saveable interface
 */
public class NumTicTacToe extends BoardGame implements Saveable {
    private NumTicTacToeBoard board;
    public NumTicTacToe(int width, int height){
        super(width, height);
        board = new NumTicTacToeBoard(width, height);
        setGrid(board);
    }

   /**
    * This function takes in the coordinates of the cell the user wants to place their marker in, and
    * the marker itself. It checks to see if the coordinates are valid, and if the cell is empty. If
    * both of these conditions are met, it places the marker in the cell and increments the counter
    * 
    * @param across the column number of the cell to be changed
    * @param down the row number
    * @param input the player's input, either "X" or "O"
    * @return The method is returning a boolean value.
    */
    @Override
    public boolean takeTurn(int across, int down, String input) {   
        if ((across>0 && across <=3)&&(down>0 && down <=3)){
            if (getCell(across, down)==" "){
                setValue(across, down, input);
                board.incrementCounter();
                return true;
            }   
        }
        return false;
    }

    /**
     * It takes in the coordinates of the cell and the value to be placed in the cell. It checks if the
     * coordinates are valid and if the cell is empty. It then checks if the value is valid and if it
     * is, it places the value in the cell and increments the counter
     * 
     * @param across the row number
     * @param down the row number
     * @param input the number the user wants to place on the board
     * @return The method is returning a boolean value.
     */
    @Override
    public boolean takeTurn(int across, int down, int input) {
        if ((across>0 && across <=3)&&(down>0 && down <=3)){
            if (getCell(across, down)==" "){
                if(input>0&&input<10){
                    if (board.checkGridCells(input)){
                        setValue(across, down, input);
                        board.incrementCounter();
                        return true;
                    }
                }
            }   
        }
        return false;
    }

    /**
     * checks if the win/tie conditions are met, and returns the responding boolean value
     * 
     * @return boolean value if the game was won
     */
    @Override
    public boolean isDone() {
        if (getWinner()>=0){
            
            return true;
        }
        return false;
    }

  /**
   * If the board has a winner, return the winner, otherwise return -1.
   * 
   * @return The winnerCheck method is being returned.
   */
    @Override
    public int getWinner() {
        return board.winnerCheck();  
    }
   
  /**
   * This function returns a string that represents the current state of the game
   * 
   * @return The gridString is being returned.
   */
    @Override
    public String getStringToSave() {
        String gridString = "";
        for (int i=1; i<=3; i++){
            for (int j=1; j<=3; j++){
                if (getCell(i, j) ==" "){
                    gridString = gridString+"" + ",";
                }else{
                    gridString = gridString+getCell(i, j) + ",";
                }
            } 
            gridString = gridString.substring(0, gridString.length() - 1);
            gridString = gridString+"\n";
        }
        return gridString;
    }

   /**
    * This function takes a string as a parameter and loads the game state from the file with the string
    * of the last played symbol
    * 
    * @param toLoad The file path of the file to load.
    */
    @Override
    public void loadSavedString(String toLoad) {
        File file = new File(toLoad);
        try {
            try (Scanner scan = new Scanner(file)) {
                String line;
                String[] splitLine;
                board.updateSymbol(scan.nextLine());
                for (int i =1; i <= 3; i++){ 
                    if (!scan.hasNextLine()){
                        break;
                    }
                    line = scan.nextLine();
                    splitLine = line.split(",");
                    for (int j = 0; j < splitLine.length; j++) {    
                        String result = splitLine[j];
                        if (!result.isEmpty()){
                            try{
                                int s = Integer.parseInt(result);
                                takeTurn(i,j+1, s);
                            } catch(NumberFormatException e){
                            }
                        }
                    } 
                }   
            }
        }catch(Exception e){
        }
    }

   /**
    * Returns message bassed on who was win/if there was a tie
    * 
    * @return The message that is being returned is the message that is being displayed to the user.
    */
    @Override
    public String getGameStateMessage() {
        String message = "The game has not finished";
        if (getWinner()==0){
           message = "The game is tied. GAME OVER"; 
        }else if (getWinner()==1){
            message = "Odd Player has won. GAME OVER";
        }else if (getWinner()==2){
            message = "Even player has won. GAME OVER";
        }

        return message;
    }
    
   /**
    * This function takes a filename as a parameter and writes the current board to the file to said file
    * 
    * @param filename The name of the file to save the board to.
    */
    public void saveBoard(String filename) {
        String boardString = getStringToSave();
        // Removes the final newline from the string
        boardString = boardString.substring(0, boardString.length() - 1);
        File file = new File(filename);
        FileWriter fw = null; 

        //Attempts to write string to desired file
        try {
            fw = new FileWriter(file, false);
            fw.write(board.getSymbol()+'\n');
            fw.write(boardString);
        } catch (IOException e) { 
            e.printStackTrace();
        } finally { 
            try {
                if (fw != null) {
                    fw.flush();
                    fw.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    /**
     * This function updates the turn of the board
     */
    public void updateTurn(){
        board.setTurn();
    }
    /**
     * This function returns the board
     * 
     * @return The board.
     */
    public NumTicTacToeBoard getBoard(){
        return board;
    }
    /**
     * This function checks if the input value is valid or not
     * 
     * @param num The number of the input you want to check.
     * @return The value of the input.
     */
    public boolean getInputValue(int num){
        return board.checkInputValue(num);
    }
    /**
     * It returns the name of the player whose turn it is
     * 
     * @return The name of the player whose turn it is.
     */
    public String checkTurnName(){
        return board.getTurnName();
    }
}
