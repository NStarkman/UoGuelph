package textgame;

import tictactoe.TicTacToe;
/**
 * This file and class were created by Nathan Starkman
 */
public class Game {
    private TicTacToe game = new TicTacToe(3, 3);
    private TextUI text = new TextUI();
  
    /**
     * This function is used to check if the user has selected a valid position on the board. If the
     * user has selected a valid position, the function will return true, otherwise it will return
     * false
     * 
     * @param pos the position of the button that was clicked
     * @param symbol the symbol of the player who's turn it is
     * @return A boolean value.
     */
    public boolean topRowPlace(int pos, String symbol){
        switch (pos){
            case 0:
                while (game.checkSaveFile(text.getFilename()) != 0) {
                    text.failToSave(); 
                }
                System.exit(0);
                return false;
            case 1:
                game.takeTurn(1,1,symbol);
                return true;
            case 2: 
                game.takeTurn(2,1,symbol);
                return true;
            case 3:
                game.takeTurn(3,1,symbol);
                return true;
            default:
                return false;
        }
    }

    /**
     * This function is used to check if the user has selected a valid position on the board. If the
     * user has selected a valid position, the function will return true, otherwise it will return
     * false
     * 
     * @param pos the position of the button that was clicked
     * @param symbol the symbol of the player who's turn it is
     * @return A boolean value.
     */
    public boolean midRowPlace(int pos, String symbol){
        switch (pos){
            case 4:
                game.takeTurn(1,2,symbol);
                return true;
            case 5: 
                game.takeTurn(2,2,symbol);
                return true;
            case 6:
                game.takeTurn(3,2,symbol);
                return true;
            default:
                return false;
        }
    }
    /**
     * This function is used to check if the user has selected a valid position on the board. If the
     * user has selected a valid position, the function will return true, otherwise it will return
     * false
     * 
     * @param pos the position of the button that was clicked
     * @param symbol the symbol of the player who's turn it is
     * @return A boolean value.
     */
    public boolean bottomRowPlace(int pos, String symbol){
        switch (pos){
            case 7:
                game.takeTurn(1,3,symbol);
                return true;
            case 8: 
                game.takeTurn(2,3,symbol);
                return true;
            case 9:
                game.takeTurn(3,3,symbol);
                return true;
            default:
                return false;
        }
    }

  /**
   * If the position is in the top row, place the piece in the top row. If the position is in the
   * middle row, place the piece in the middle row. If the position is in the bottom row, place the
   * piece in the bottom row
   * 
   * @param pos the position of the board that the user wants to place the piece
   * @param symbol the symbol of the player
   * @return The method is returning a boolean value.
   */
    public boolean placePiece(int pos, String symbol){
        if (topRowPlace(pos, symbol)||midRowPlace(pos, symbol)||bottomRowPlace(pos, symbol)){
            return true;
        }
        return false;
    }

    /**
     * This function is a menu that allows the user to choose between three options: 1) Print the
     * current game, 2) Load a new game, or 3) Quit the game.
     * 
     * @return The boolean done is being returned.
     */
    public boolean runMenu(){
        boolean done = false; 
        int response = -1; 
        while (response == -1) { 
            response = text.printMenu(); 
            //Checks each choice for corrisponding answer
            switch (response) {
                case 1:
                    System.out.println(game.getStringToPrint());
                    break;
                case 2:
                    while(!game.checkFile(text.getFilename())){
                        text.failToLoad();
                    }
                    System.out.println(game.getStringToPrint());
                    break;
                    
                case 3:
                    done = true;
                    break;
                default:
                    text.invalidChoice();
                    response = -1;
            }
        }
        return done;
    }

    /**
     * The function runs the game by calling the runMenu function, which returns a boolean value.
     */
    public void runGame(){
        boolean done = runMenu();
        //checks if the games done
        while (!done) {
            done = game.isDone();
            game.changeSymbol();           
            //places the piece and checks for a win
            if(placePiece(text.scanTurn(game.getCurrSymbol()), game.getCurrSymbol())){
                System.out.println(game.getStringToPrint());
                done = game.isDone();
                if (done){
                    System.out.println(game.getGameStateMessage());
                }
            //prints if a choice was invalid  
            }else{
                text.invalidChoice();
            }
        }
    }
}
