#include "headerA3.h"
#include "helper.h"

/******
searchTweetsByKeyword: Finds tweets with specific inputted keyword
 In: tweetList
 Out: found
 Post: Prints the times the word was found, and returns 1. If it was not found, it returns 0. If there is no linked list, it returns 2
*******/

int searchTweetsByKeyword(tweet * tweetList){
    
    //found: flag if the data is found
    int found;
    //flag: flag if no words have any of the said keyword
    int flag = 0;
    //word: data for the word to search for
    char * word = malloc(sizeof(char)*51);
    //node: reference for the linked list head
    tweet * node;

    // scans for the word to search for
    printf("Enter any word to search: ");
    scanf("%s", word);
    found = 2;
    //Goes through the list and searches for words
    if (tweetList != NULL) {
        node = tweetList;

        while (node !=NULL){
            if(strcasestr(node->text, word)){
                found = 1;            
            }
            else{
                found = 0;
            }
            if(found == 1){
                printf("Match found for '%s': %s wrote: %s\n", word, node->user, node->text);
                flag = 1;
            }
            node = node->next;
        }
      
    }
    
    if (found ==0 && flag  != 1){
        printf("No word found\n");
    }
    else if (found ==2){
        printf("NO LINKED LIST TO SEARCH! Please try Again\n");
    }
    
    free(word);
    return found;
}
