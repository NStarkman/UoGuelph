#include "headerA3.h"
#include "helper.h"

/******
deleteTweet: Removes tweet from specific coordinate in linked list
 In: tweetList
 Out: NONE
 Post: Removes desired node and readjusts the linked list accordingly
*******/
void deleteTweet(tweet ** tweetList){
    
    tweet *ptr = *tweetList;
    tweet * del= *tweetList;
    tweet *tweetNext;
    int count = getCount(ptr);
    int nodeDelete=0;
    printf("currently there are %d tweets\n", count);
    if(count == 0){
        printf("There are no tweets. Please populate the list and try again.\n");
        return;
    }
    printf("Which tweet do you wish to delete? enter a value between 1 and %d:\n", count);
    scanf("%d", &nodeDelete);

    if (nodeDelete < 1){
        printf("Node is less then zero\n");
        return;
    }
    else if (nodeDelete==1 && ptr !=NULL){
        *tweetList = del->next;
        printf("Tweet %d deleted. There are %d tweets left\n", del->id, count-1);
        free(del);
        return;
    }
    else{
        nodeDelete--;
        for (int i = 0; i<nodeDelete-1; i++){
            del=del->next;
            
        }
        if (ptr != NULL){
            tweetNext = del->next->next;
            printf("Tweet %d deleted. There are %d tweets left\n", del->next->id, count-1);
            free(del->next);
            del->next = tweetNext;
            return;
        }
        else{
            printf("Node is already Null!\n");
        }
    }
}