package connectfour;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
 /**
     * The Board Class manages and changes the board during the game
     * 
     * Author: Nathan Starkman
     */
public class Board{
    //The Board itself where the pieces are held
    private int[][] board= new int[6][7];


   
    /**
     * Checks if the position is filled, and if not, puts the player number there. 
     * 
     * @param position
     * @param playerNumber
     * @return 0,-1 (0 for pass, -1 for fail)
     */
    public int placeSymbol(int position, int playerNumber) {
        for (int i = 5; i >= 0; i--) {
            if (board[i][position] == 0) { 
                board[i][position] = playerNumber; 
                return 0; 
            }
        }
        return -1; 
    }

    /**
     * Goes through the board and checks if it is full - if it is empty, false, otherwise, true
     * 
     * @return  boolean value
     */
    public boolean isBoardFull(){ 
        for (int i = 0; i<6; i++){
            for (int j = 0; j<7; j++){
                if (board[i][j]==0){
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Turns the board into a string for printing and file writing
     * 
     * @return  BoardString (Board as a string)
     */
    public String boardToString() {

        String boardString = "";

        for (int i = 0; i < 6; i++) { //Loops through rows
            for (int j = 0; j < 7; j++){ //Loops through columns
                //Adds values to string with a comma
                boardString = boardString +Integer.toString(board[i][j]) + ","; 
            }
            //Removes final comma and adds a newline for each row
            boardString = boardString.substring(0, boardString.length() - 1);
            boardString = boardString + "\n";
        }
        return boardString;
    }



    /**
     * Saves current game board as a string and then sends it to be written to desired file
     * 
     * @param filename
     * @return 1/0 (1 for fail, 0 for pass)
     */
    public int saveBoard(String filename) {

        String boardString = boardToString();
        // Removes the final newline from the string
        boardString = boardString.substring(0, boardString.length() - 1);

        File file = new File("assets/"+filename);

        FileWriter fw = null; 

        //Attempts to write string to desired file
        try {
            fw = new FileWriter(file, false);
            fw.write(boardString);
        } catch (IOException e) { 
            e.printStackTrace();
            return 1; 
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
        return 0;
    }

    /**
     * Takes a file with a premade board and loads it into the board to continue playing
     * 
     * @param filename
     * @return  end = -1/0, -1 (-1 for a fail, 0 for a pass)
     */
    public int loadBoard(String filename) {
        int end = 0;
        File file = new File("assets/"+filename);
        try {
            try (Scanner scan = new Scanner(file)) {
                String line;
                String[] splitLine;
                //Loop through the file and check if it has all the lines needed
                for (int i = 0; i < 6; i++){ 
                    if (!scan.hasNextLine()){
                        return -1; 
                    }
                    //add each number to the array and split by the commas
                    line = scan.nextLine();
                    splitLine = line.split(",");
                    if (splitLine.length != 7) {
                        return -1; 
                    }
                    //Ensure that the file only has 1s and 2s
                    for(int j = 0; j < 7; j++){ 
                        board[i][j] = Integer.parseInt(splitLine[j]); 
                        if ((board[i][j] < 0) || (board[i][j] > 2)) {
                            return -1;      
                        }
                    }
                }
            }
        } catch (FileNotFoundException e) {
            end = -1;
            
        }catch(Exception e){
            end = -1;
        }
        return end; 
    }

    /**
     * Checks for diagonal wins on the board
     * 
     * @return  match (0,1,2 (0 for none, 1/2 for the piece that won))
     */
    public int getDiagonalWinnerStatus(){
        int match = 0;
        //Loops from left to middle 
        for(int i = 5; i >=3; i--) { 
            winnerLoop: 
            for (int j = 0; j < 4; j++){
                match = board[i][j];
                if (match == 0) { 
                    continue winnerLoop;
                }
                //check if they all match
                for (int l = 1; l < 4; l++){
                    if (match != board[i-l][j+l]) { 
                        continue winnerLoop;
                    }
                }
                return match; 
            }
        }
        //Loops from middle to right
        for(int i = 5; i >=3; i--) { 
            winnerLoop:
            for (int j = 3; j < 7; j++){
                match = board[i][j];
                if (match == 0) { 
                    continue winnerLoop;
                }
                //check if they all match
                for (int l = 1; l < 4; l++){ 
                    if (match != board[i-l][j-l]) {
                        continue winnerLoop;
                    }
                }
                return match; 
            }
        }
        return 0;
    }

    /**
     * Checks for a horizontal or vertical win on the board
     * 
     * @return match (0,1,2 (0 for none, 1/2 for the piece that won))
     */
    public int getHorzVertWinner(){
        int match = 0;
        //Horizontal Check
        for (int i = 5; i >= 3; i--){ 
            winnerLoop:
            for (int j = 0; j < 7; j++){
                match = board[i][j];
                if (match == 0) { 
                    continue winnerLoop;
                }
                for (int l = 1; l < 4; l++){
                    if (match != board[i-l][j]) { 
                        continue winnerLoop;
                    }
                }
                return match; 
            }
        }
        //Vertical Check
        for (int i = 5; i >=0; i--){ 
            winnerLoop:
            for (int j = 0; j < 4; j++){
                match = board[i][j];
                if (match == 0) { 
                    continue winnerLoop;
                }
                for (int l = 1; l < 4; l++){ 
                    if (match != board[i][j+l]) { 
                        continue winnerLoop;
                    }
                }
                return match; 
            }
        }
        return 0;
    }

    /**
     * Confirms the two types of possible wins for the board against each other
     * 
     * @return 0,1,2 (0 for none, 1/2 for the piece that won)
     */
    public int getWinnerStatus(){
        int lineWinner = getHorzVertWinner();
        int slantWinner = getDiagonalWinnerStatus();
        if (lineWinner != 0) {
            return lineWinner;
        }
        return slantWinner;
    }
  

    /**
     * Checks which player has more pieces on the board. 
     * 
     * @return 1/2 (1 if 2 has more, 2 if 1 has more)
     */
    public int calcTurn() {
        int moveP1 = 0;
        int moveP2 = 0;
        //Counts the amounts of 1s and 2s
        for (int i = 0; i < 6; i++){ 
            for (int j = 0; j < 7; j++){ 
                if (board[i][j] == 1){
                    moveP1++; 
                } else if (board[i][j] == 2) {
                    moveP2++; 
                }
            }
        }
        if (moveP2 >= moveP1) {
            return 1; 
        } else {
            return 2; 
        }
    }

    /**
     * Switches turn from 1 to 2 or 2 to 1
     * 
     * @param turn
     * @return turn
     */
    public int switchTurn(int turn){
        if (turn == 1) {
            turn = 2; 
        } else {
            turn = 1; 
        }
        return turn;
   }
}