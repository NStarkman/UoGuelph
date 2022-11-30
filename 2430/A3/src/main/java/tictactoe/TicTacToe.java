package tictactoe;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import boardgame.BoardGame;
import boardgame.Saveable;
//import users.TTTPlayers;

public class TicTacToe extends BoardGame implements Saveable {
    private TicTacToeBoard board;
    public TicTacToe(int width, int height){
        super(width, height);
        board = new TicTacToeBoard(width, height);
        setGrid(board);
    }


    /**
     * This function takes in the coordinates of the cell the user wants to place their marker in, and
     * the marker itself, and checks if the cell is empty. If it is, it places the marker in the cell
     * and increments the counter
     * 
     * @param across the column number
     * @param down the row number
     * @param input the player's input (X or O)
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
    * If the input is valid, the value is set and the counter is incremented.
    * 
    * @param across the row number
    * @param down the row number
    * @param input the value the user wants to place on the board
    * @return The method is returning a boolean value.
    */
    @Override
    public boolean takeTurn(int across, int down, int input) {
        if ((across>0 && across <=3)&&(down>0 && down <=3)){
            if (getCell(across, down)==" "){
                if(input>0&&input<10){
                    setValue(across, down, input);
                    board.incrementCounter();
                    return true;
                }
            }   
        }
        return false;
    }
// The above code is a TicTacToe game.

    @Override
    public boolean isDone() {
        if (getWinner()>=0){
            return true;
        }
        return false;
    }

    /**
     * If there is a winner, return 1 if the winner is X, 2 if the winner is O, otherwise return 0 if
     * there is a tie, otherwise return -1 if the game is not over
     * 
     * @return The winner of the game.
     */
    @Override
    public int getWinner() {
        return board.winnerCheck();    
    }

    /**
     * This function checks if the player has won horizontally
     * 
     * @return The method is returning a boolean value.
     */
    @Override
    public String getStringToSave() {
        String gridString = "";
        for (int i=1; i<=3; i++){
            for (int j=1; j<=3; j++){
                if (getCell(j, i) ==" "){
                    gridString = gridString+"" + ",";
                }else{
                    gridString = gridString+getCell(j, i) + ",";
                }
            } 
            gridString = gridString.substring(0, gridString.length() - 1);
            gridString = gridString+"\n";
        }
        return gridString;
    }


  /**
   * It takes a string, which is the file path, and loads the file into the game board
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
                            if (result.matches("[a-zA-Z]+")){                           
                                takeTurn(j+1, i, result);
                            }
                        }
                    } 
                }        
            } 
        }catch(Exception e){
        }  
    }
/**
 * // Java
 * 
 * @Override
 * public String getGameStateMessage() {
 *     String message = "The game has not finished";
 *     if (getWinner()==0){
 *        message = "The game is tied. GAME OVER"; 
 *     }else if (getWinner()==1){
 *         message = "Player X has won. GAME OVER";
 *     }else if (getWinner()==2){
 *         message = "player O has won. GAME OVER";
 *     }
 * 
 *     return message;
 * }
 * 
 * @return The message is being returned.
 */

   /**
    * The function returns a message that tells the user the game state
    * 
    * @return The message is being returned.
    */
    @Override
    // Returning a message.
    public String getGameStateMessage() {
        String message = "The game has not finished";
        if (getWinner()==0){
           message = "The game is tied. GAME OVER"; 
        }else if (getWinner()==1){
            message = "Player X has won. GAME OVER";
        }else if (getWinner()==2){
            message = "player O has won. GAME OVER";
        }

        return message;
    }
    
    /**
     * If the player is O, then update the symbol to X. If the player is X, then update the symbol to O
     * 
     * @param player the player who just played
     */
    public void switchTurn(String player){
        if (player == "O"){
           board.updateSymbol("X");
        }
        if (player == "X"){
            board.updateSymbol("O");
        }
    }
    
   /**
    * The function changeSymbol() is a public function that takes no parameters and returns nothing. It
    * calls the setSymbol() function from the board class
    */
    public void changeSymbol(){
        board.setSymbol();
    }
    /**
     * This function returns the symbol of the current player
     * 
     * @return The symbol of the current player.
     */
    public String getCurrSymbol(){
        return board.getSymbol();
    }

    /**
     * This function takes a filename as a parameter and writes the current board to the file
     * 
     * @param filename the name of the file to save the board to
     * @return The method is returning an integer.
     */
    public int saveBoard(String filename) {
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
            return 1; 
        } finally { 
            try {
                if (fw != null) {
                    fw.flush();
                    fw.close();
                }
            } catch (IOException e) {
                return 1;
            }
        }
        return 0;
    }
    /**
     * This function returns the board
     * 
     * @return The board object.
     */
    public TicTacToeBoard getBoard(){
        return board;
    }
    /**
     * For each row, get the value of each cell in the row, add it to the string, and add a pipe
     * character after each cell. Then, remove the last pipe character and add a new line character. If
     * it's not the last row, add a line of dashes and a new line character
     * 
     * @return The gridString is being returned.
     */
    public String getStringToPrint(){
        String gridString = "";
        for (int i=1; i<=3; i++){
            for (int j=1; j<=3; j++){
                gridString = gridString+getCell(j, i) + "|";
            } 
            gridString = gridString.substring(0, gridString.length() - 1);
            if (i<3){
                gridString = gridString+"\n------\n";
            }
        }
        return gridString;
    }

    /**
     * This function checks the value of a cell in the board
     * 
     * @param across the column number of the cell
     * @param down the row of the cell
     * @return The value of the cell at the given coordinates.
     */
    public String checkCell(int across, int down){
        return board.checkValue(across, down);
    }

   /**
    * It checks if a file exists, if it does, it loads the file and returns true, if it doesn't, it
    * returns false
    * 
    * @param toLoad The name of the file to load.
    * @return A boolean value.
    */
    public boolean checkFile(String toLoad){
        File file = new File("assets/boards/"+toLoad);
        if (file.exists()){
            loadSavedString("assets/boards/"+toLoad);
            return true;
        }
        return false;
    }
    /**
     * It saves the board to a file
     * 
     * @param toLoad The name of the file to load.
     * @return The method is returning an integer.
     */
    public int checkSaveFile(String toLoad){
        saveBoard("assets/boards/"+toLoad);
        return 0;
        
    }
}
