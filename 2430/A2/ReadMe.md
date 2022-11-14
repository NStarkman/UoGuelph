# Project Title

This is a terminal Connect four Game. Using four classes, I was able to create a fully functional game, with the ability to save the game progress and load old games that are stored 
in the assets folder.
## Description

In the Board class, all methods are made to change and support the board. adding peices, changing turns, checking who won, and other methods like that all are included there
The TextUI class is all of the IO of the project, and is called upon each time the class needs to message the user.
The ConnectFour Class does all of the syncronizing of the Board and TextUI methods to create a game to be run, and has a menu to select to load, exit, or start a new game
Runner runs the game as created in ConnectFour.
    When the game begins, the menu prompts for three things: 1 fr new game, 2 for load old game, 3 for exit.
    If you select a new board, the program will ask for a number between 0 and 6. From there, it places a piece in that row, if possible. If you want to save your game, enter -1
    If you selected load from old game, you will give the name of the file it saved to and it will start from where it left off. You can save it again.
    if you select exit, the game will end


## Getting Started

### Dependencies

*   Java.Util.Scanner - Important for use to read imputs from the user
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
    cd A2
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
    java -cp build/classes/java/main connectfour.Runner
```
* Then, copy that last line and past it into your terminal. hit enter, and with that, the program should run!

## Limitations

    To my knowledge, everthing is completed

## Author Information

    Nathan Starkman
    1127811
    nstarkma@uoguelph.ca


## Development History


* 0.1
    * Finished game

## Acknowledgments




