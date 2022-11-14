# Assignemnt 1: Tic Tac Toe

    This is a Tic Tac Toe Terminal game, made for two users to play in the terminal, using the X and O markers as representatives for each player.

## Description

    This code base was made from scratch using reference from the provided ticTacToeP file along with my own personal skills. The code creates a board from a 2D array, and then requests input for each player at each specific index of the Tic Tac Toe board. To determine the turn of each player, a variable entitled depth counts a successfully inputted move. Since the X player starts, and the counter begins at 0, if you modulus depth, the X player will always have a remainder of 0 and the O player will always have a remaider of one. By checking the depth after each round, the code switches each turn by checking modulus 2. Then, after each round, if the gameboard sees a win, it will call it. Otherwise, if it is a tie and the board is full, the game ends. Entering a number outside of the range of positions in the board (less than 1, greater than 9) it will repromt the user for another attempt. With all of those functions, the program can execute and run, providing a fun game for all who play!

## Getting Started

### Dependencies

*   Java.Util.Scanner - Important for use to read imputs from the user
*   Scioer shell/Gradle - Important to use for running the program, includes Checkstyle review

### Executing program

* How to build and run the program
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
    cd A1
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
    java -cp build/classes/java/main tictactoe.Runner
```
* Then, copy that last line and past it into your terminal. hit enter, and with that, the program should run!

## Limitations

    To my knowledge, everthing is completed

## Author Information

    Nathan Starkman
    1127811
    nstarkma@uoguelph.ca

## Development History

* Sunday
    * Added comments and did the final commit and push.
* Thursday
    * Completed the three classes and fixed all bugs to completion.

## Acknowledgments

* ticTacToeP.java - Given by the professors



