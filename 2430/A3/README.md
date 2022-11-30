# Project Title

This is my GUI and Console TicTacToe Game Suite!

## Description

There are 6 packages in the code. boardgame holds the provided classes (BoardGame, Saveable, PositionAwareButton, Grid). These will be extended and implemented by my files. the game class are the runners for the two codes.GameUI runs the first GUI and and creates buttons to the rest of the games. Runner runs the console version of ticTacToe. There, a simple version of TicTacToe is played. The game rules and Text that is printed is held in the textgame package. Game, which runs the game logic, holds an object of TicTacToe, which holds the logic for both the console and GUI ticTacToe games. the tictactoe package, which holds the TicTacToe files that has the game specific rules, also includes TicTacToeBoard and TicTacToeUI. The TicTacToeBoard runs the board, checks it for winners, and manages the current player symbol. The UI runs the game visually, calling the TicTacToe class, which has the rules of the game. This file relies on the previously mentioned TicTacToe board class. Similarly to the tictactoe package, the numberttt package runs the numeric TicTacToe game in a similarly set up fasion. NumTicTacToeBoard holds the board itself and manages the turns. An instance of it is in NumTicTacToe, which manages the rules of the game. That is called in NumTicTacToeUI, which visually outputs the game. In both Numeric Tic Tac Toe and regular, the user packages' TTTPlayer class is called. This takes in the users name, amount of wins, losses, and total games played. This can be loaded from an old file or saved to a new one. 

## Getting Started

### Dependencies
*   boardgame package (Grid,BoardGame,Saveable, PositionAwareButton) - used for extend and impleme
*   Java.Util.Scanner,file - Important for use to read imputs from the user and from files
*   Java Swing/awt - Used to create the visual GUI aspects of the code.
*   Scioer shell/Gradle - Important to use for running the program, includes Checkstyle review, testing, and more

### Executing program

 How to build and run the program
* NOTE: THIS IS IF YOU NEED TO RUN IT IN THE SCHOOL SERVERS. IF NOT, START BELOW
* First, ensure you are in the Scioer shell enviroment  - in Terminal, type scioer start
* Then, open a shell in the scioer enviroment - In Terminal, type scioer shell
``` 
    scioer start
    scioer shell

```
* START HERE WITHOUT SCHOOL SERVERS
* After that, make sure that you are in the A1 folder. Find the path of the A1 folder. cd into it, either directly, if you are in the same master file, or go into one file into another.
```
    cd outerFile
    cd A3
```
* Next, build the gradle and compile. To do that, type gradle build
* after gradle build, to recieve the command to run, type gradle run
```
    gradle build
    gradle run
```
* This will provide you with a command to run. It will usually look like this:
```
    > Task :run        
    To run the program:
    java -jar build/libs/A3.jar
```
* Note that I have had to run my code through PowerShell, and not through the scioer shell. What I ususally do is cd into the folder that the code is in from PowerShell, and run the line given above. 
* This will run the GUI code. if you want to run the version in the console, type this into the terminal
```
    java -cp build/classes/java/main game.Runner

```
## Limitations

    To my knowledge, everthing is completed

## Author Information

    Nathan Starkman
    1127811
    nstarkma@uoguelph.ca


## Development History


* 0.1
    * First version
* 0.2
    * Second Version

## Acknowledgments




