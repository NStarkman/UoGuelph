#include "headerA3.h"
#include "helper.h"

/******
loadTweet: takes tweets from file and populates a link list with them
 In: tweetList
 Out: NONE
 Post: Adds the tweets from the file to linked list, if it exists
*******/
void loadTweetsFromFile(tweet ** tweetList){
    
    //Filename: Name of the file to load
    char filename[1000];
    //Buf: text buffer variable
    char buf[1024];
    //token:
    char * token;
    //index: char index number
    long index = 0;
    //fptr: file pointer
    FILE * fptr;

    //Scans the fllename to read
    printf("Enter the filename to load from: ");
    scanf("%s", filename);
    fptr = fopen(filename, "r");


    //Checks for it existing
    if (fptr==NULL){
        printf("Error, no file with that name\n");
        return;
    }
    //Scans the line and seperates the dta by the comma
    while(fgets(buf,1024,fptr)!=NULL){
        tweet * node = malloc(sizeof(tweet));
        
        node->next = NULL;
        token = strtok(buf,",");
        node->id = atoi(token);
        token = strtok(NULL,",");
        strcpy(node->user,token);
        token = strtok(NULL,"\0");
        strcpy(node->text, token);
        //Deletes trailing space or comma if there
        index = strlen(node->text);
        for(int i=index-1;i>0;i--){
            if(node -> text [i] == ',' || isspace (node -> text [i])){
                node->text[i] = '\0';
            }
            else{
                break;
            }
        }

        
        addNodeToList(tweetList, node);
      
}
    printf("Tweets Imported!\n");
    fclose(fptr);

}