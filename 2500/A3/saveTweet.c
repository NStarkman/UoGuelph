#include "headerA3.h"
#include "helper.h"

/******
saveTweetsToFile: Saves tweets in linked list to file
 In: tweetList
 Out: NONE
 Post: Writes tweets from tweet List to created file
*******/
void saveTweetsToFile(tweet * tweetList){
    //filename: name of the file to create
    char filename[1000];
    //fptr: THe filepointer for the new file
    FILE * fptr;

    //If there are no tweets, it fails
    if(tweetList==NULL){
        printf("There are no tweets in the list. Please populate the list and try again.\n");
        return;
    }

    //scans for the file and creates the name if it is not NULL

    printf("Enter the filename where you would like to store your tweets: ");
    scanf("%s", filename);
    fptr = fopen(filename, "w");
    
    if (fptr==NULL){
        printf("Error, unable to create file\n");
    }
    else{
        //Populates the file
        tweet * node = tweetList;
        while(node !=NULL){
            fprintf(fptr, "%d,%s,%s\n", node->id, node->user, node->text);
            node = node->next;
        }
    }
    fclose(fptr);
}