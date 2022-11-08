#include "headerA3.h"
#include "helper.h"

/******
addNodeToList: adds node to the end of the linked list
 In: tweetList, node
 Out: NONE
 Post: Adds the created node to the linked List.
*******/
void addNodeToList(tweet**tweetList, tweet * node){
    tweet * newPtr;
    
    //Checks if first node is null and populates if not
    if (*tweetList ==NULL){
        *tweetList = node;
        

    }
 
    //Goes through the linked list and adds node to the last position
    else if(*tweetList !=NULL){
        
        newPtr = *tweetList;
        
        while (newPtr->next !=NULL){
            
            newPtr = newPtr->next;
        }

        newPtr->next = node;
    }
   
}
