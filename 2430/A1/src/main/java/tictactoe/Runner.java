package tictactoe;

import java.util.Scanner;
public class Runner {
    
    public static void main(String[] args) {
        
        Scanner scanner = new Scanner(System.in);
        Board playBoard = new Board();
        Game gameBoard = new Game();        
        //Runs the game
        gameBoard.runGame(playBoard, playBoard.getBoard(), scanner);
        
    }     
}