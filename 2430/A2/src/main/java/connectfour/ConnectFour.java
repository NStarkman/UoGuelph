package connectfour;

 /**
     * The ConnectFour Class runs the menu and the game itself with the help of the other classes
     * 
     * Author: Nathan Starkman
     */
public class ConnectFour{
    private Board gameBoard = new Board(); //Board Object
    private TextUI printer = new TextUI(); //TextUI object
    private int turn = 1;  //The current player turn if the board is empty
  
   
    /**
     *  Runs the pregame menu and asks if they would like to start new game, load, or exit
     *
     * @return done (false if load or new game, true when exit)
     */
    public boolean runMenu(){
        boolean done = false; 
        int response = -1; 
       
        while (response == -1) { 
            response = printer.printMenu(); 
            //Checks each choice for corrisponding answer
            switch (response) {
                case 1:
                    break;
                case 2:
                    while (gameBoard.loadBoard(printer.getFilename()) != 0) {
                        printer.failToLoad(); 
                    }
                    turn = gameBoard.calcTurn(); 
                    break;
                case 3:
                    done = true; 
                    break;
                default:
                    printer.invalidChoice();
                    response = -1;
            }
        }
        return done;
    }

    /**
     *  Runs the game with all of the methods from board, TextUI
     * 
     *  @return void
     */
    public void runGame() {
        boolean done = runMenu();
        int position;
        
        while (!done) { //Runs when not done
            //Checks the board for any winners
            int winner = gameBoard.getWinnerStatus(); 
            //Ends if board is full
            if (gameBoard.isBoardFull()&& winner ==0){
                printer.endedInTie();
                done = true;
                break;
            }    
            //Ends if a winner was found
            if (winner != 0) {
                printer.printWinner(winner, gameBoard.boardToString()); 
                done = true;
                break;
            }
            //Takes in the new piece position
            position = printer.scanTurn(turn, gameBoard.boardToString());
            if (position == -1) {
                while (gameBoard.saveBoard(printer.getFilename()) != 0) {
                    printer.failToSave(); 
                }
                return;
            }
            //Saves board on request
            if (gameBoard.placeSymbol(position, turn) == -1) {
                printer.invalidMove(); 
                continue;
            }
            //Switches the turn
            turn = gameBoard.switchTurn(turn);
        }
    }
}