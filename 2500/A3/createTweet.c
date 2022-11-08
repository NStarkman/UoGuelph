#include "headerA3.h"
#include "helper.h"

/******
 createTweet: writes a tweet to add to the list
 In: tweetList
 Out: newTweet
 Post: Returns the tweet and adds it to linked list using addNodeToList
*******/
tweet * createTweet( tweet * tweetList){
    int sum=0;
    int flag = 0;
    tweet * newTweet = malloc(sizeof(tweet));
    tweet * current = tweetList; 
    char charBuffer[1000];
    char tweetBuffer[1000];
    char username[51];
    char tweet[141];

    //Enters Username
    do{

        printf("Enter Username: ");
        scanf("%s", charBuffer);
        //Removes trailing newline
        // charBuffer[strlen(charBuffer)-1] = '\0';
        //Enters tweet text
        getchar();
        printf("Enter the user's tweet: ");
        if(fgets(tweetBuffer, 1000, stdin)==NULL){
            printf("ERROR. NULL GIVEN\n");
            return NULL;
        }
        //Removes trailing newline
        tweetBuffer[strlen(tweetBuffer)-1] = '\0';


        // Checks if the tweet or username is either nothing or too long
        if (strlen(charBuffer)>50||strlen(charBuffer)==0){
            printf("USERNAME NOT VALID: Try Again\n");
            flag = 1;
        }
        else if (strlen(tweetBuffer)>140||strlen(tweetBuffer)==0){
            printf("TWEET NOT VALID: Try Again\n");
            flag = 1;
        }
        else{
            strcpy(username, charBuffer);
            strcpy(tweet, tweetBuffer);
            flag = 0;
        }
    }while(flag == 1);
    //Calculates the sum for the user ID
    int len = strlen(username);
    for (int i = 0; i < len; i++)
    {
        sum = sum + username[i];
    }
    //copies info into node
    strcpy(newTweet->user, username);
    strcpy(newTweet->text, tweet);
    sum = sum + strlen(tweet);
    // Checks if ID is the same somewhere else in the linked list and adds random value if not
    while (current != NULL)
    {
        if (sum == current->id){
            sum = sum + rand() % 999+1;
            break;
        }
        current = current->next;
    }
    //returns the created node
    printf("The Computer Generated Userid is %d\n", sum);
    newTweet->id = sum;
    newTweet->next = NULL;
    return newTweet;
}