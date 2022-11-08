#include "headerA3.h"
#include "helper.h"

int main(){
    int search, number;
    char choice1;
    tweet * tweetList = NULL;
      do {
        printf ("\n");
        printf ("1. Create a new Tweet\n");
        printf ("2. Display Tweets\n");
        printf ("3. Search a tweet (by keyword)\n");
        printf ("4. Find how many words are \"stop words\" \n");
        printf ("5. Delete nth tweet\n");
        printf ("6. Save tweets to a file\n");
        printf ("7. Load tweets from a file\n");
        printf ("8. Sort the given linked list on userid\n");
        printf ("9. Exit\n");
       
    
        printf ("\nEnter your choice: ");
        scanf("%s",&choice1);

         number =atoi(&choice1);
        if(number!=0){
            switch (number) {
            case 1:
                addNodeToList(&tweetList, createTweet(tweetList));
                break;
            case 2:
                displayTweets(tweetList);
                break;
            case 3:
                search = searchTweetsByKeyword(tweetList);
                if (search == 1){
                    break;
                }
                else{                
                    break;
                }
            case 4:
                countStopWords(tweetList);
                break;
            case 5:
                deleteTweet(&tweetList);
                break;
            case 6:
                saveTweetsToFile(tweetList);
                break;
            case 7:
                loadTweetsFromFile(&tweetList);
                break;
            case 8:
                sortID(&tweetList);
                break;
            case 9:
                clearList(tweetList);
                break;
            default:  
                printf ("\nThat is an invalid choice\n");      
        }
    
        }else{
             printf("INVALID INPUT. TRY AGAIN!\n");
        }
        
    } while (number != 9);
    return 0;
}