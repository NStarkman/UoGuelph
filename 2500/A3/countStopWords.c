#include "headerA3.h"
#include "helper.h"

/******
countStopWords: Counts specific words from a list of stop words from throughout the linked list
 In: tweetList
 Out: NONE
 Post: prints the amount of stop words throughout the entire linked list
*******/
void countStopWords(tweet * tweetList){


    char wordsArray[25][10] = {"a","an","and","are","as","at","be","by","for","from","has","he","in","is","it","its","of","on","that","the","to","was","were","will","with"};
    tweet * node =tweetList;
    char array[1000];
    int count = 0;
    int amnt =0;

    while (node != NULL) {
        amnt+=1;
        //Copies text to array and turns it all lower case
        strcpy(array,node->text);
        for(int i=0;i<strlen(array);i++){
            array[i] = tolower(array[i]);
        }
        //strtoks at newlines or spaces
        char *token = strtok(array," \r\t\n");
        //goes through the linked list and counts when the words match an element of the wordsArray
        while(token!=NULL){
            for(int i=0;i<25;i++){
                if(strcmp(token,wordsArray[i])==0){
                    count+=1;
                }
            }
            token = strtok(NULL," \r\t\n");
        }
      node = node->next;
    }
    //Prints amount
    printf("Across %d tweets, %d stop words were found\n", amnt, count);
   
}