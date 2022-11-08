#include "headerA3.h"
#include "helper.h"
/******
displayTweets: Prints tweets in linked list
 In: tweetList
 Out: NONE
 Post: Prints linked list tweets
*******/
void displayTweets(tweet * tweetList){
    if (tweetList != NULL) {
        printf ("%d: Created by %s: %s\n", tweetList->id, tweetList->user,tweetList->text);
        displayTweets (tweetList->next);
    
    }
 
}