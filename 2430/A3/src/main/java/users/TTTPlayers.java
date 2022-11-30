package users;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

import boardgame.Saveable;

/**
 * This file and class were created by Nathan Starkman
 */
public class TTTPlayers implements Saveable {
    private String name = "";
    private int wins;
    private int losses;
    private int totalGames;

   // A constructor that takes a string as a parameter. It sets the name to the parameter and then
   // calls the fileCheck method.
    public TTTPlayers(String playerName){
        this.name = playerName;
        fileCheck(name);
    }

   /**
    * It takes the name, wins, losses, and total games of a player and returns a string that is
    * formatted to be saved in a file
    * 
    * @return The name, wins, losses, and total games of the player.
    */
    @Override
    public String getStringToSave() {
        String toSave = "";
        toSave = getName() +","+getWins()+","+getLosses()+","+getTotalGames();
        return toSave;
    }

    /**
     * It takes a string, finds a file with that string as the name, and then reads the file and sets
     * the variables of the class to the values in the file
     * 
     * @param toLoad The name of the file to load
     */
    @Override
    public void loadSavedString(String toLoad) {

        File file = new File("assets/users/"+toLoad+".csv");
        
        Scanner scan;
        try {
            scan = new Scanner(file);
            String line;
            String[] splitLine;
            while (scan.hasNextLine()){
                line = scan.nextLine();
                splitLine = line.split(",");
                this.name = splitLine[0];
                this.wins = Integer.parseInt(splitLine[1]);
                this.losses = Integer.parseInt(splitLine[2]);
                this.totalGames = Integer.parseInt(splitLine[3]);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }      
    }
    

   /**
    * If the file exists, load the saved string. If it doesn't exist, save the player
    * 
    * @param playerName The name of the player
    */
    public void fileCheck(String playerName){
        File tempFile = new File("assets/users/"+playerName+".csv");

        boolean exists = tempFile.exists();
        if (exists){
            loadSavedString(playerName);
        }else if (!exists){
            savePlayer(playerName);
        }

    }

   /**
    * Saves the player name and stats to the user files
    * 
    * @param playerName The name of the player
    */
    public void savePlayer(String playerName){
        File file = new File("assets/users/"+playerName+".csv");
        FileWriter fw = null; 

        //Attempts to write string to desired file
        try {
            fw = new FileWriter(file, false);
            fw.write(getStringToSave());
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
    * This function increments the wins variable by 1
    */
    public void setWins(){
            this.wins += 1;
        
    }
    
    /**
     * Gets the total amount of wins of the user
     * @return The number of wins.
     */
    public int getWins(){
        return wins;
    }
    
    /**
     * This function increments the losses variable by 1
     */
    public void setLosses(){
            this.losses += 1;
        
    }

    /**
     * This function returns the number of losses
     * 
     * @return The losses variable is being returned.
     */
    public int getLosses(){
        return losses;
    } 

    /**
     * This function adds the value of newGame to the totalGames variable
     */
    public void setNewGames(){
        // Adding the value of newGame to the totalGames variable.
        this.totalGames +=1;
    }

   /**
    * Returns the total games a user played
    * 
    * @return The total number of games played.
    */
    public int getTotalGames(){
        return totalGames;
    }

   /**
    * This function sets the name of the player to the name that is passed in as a parameter
    * 
    * @param playerName The name of the player.
    */
    public void setName(String playerName){
        this.name = playerName;
    }

    /**
     * This function returns the name of the player
     * 
     * @return The name of the person
     */
    public String getName(){
        return name;
    }
}
