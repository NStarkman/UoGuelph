#include "../include/starkmanNathanA2.h"


/******
 readFile: Opens the file and preps it for reading
 In: fileName
 Out: word
 Post: A char is created with the exact characters from the file
*******/
char * readFile (char * filename){
    FILE *fp;
    
    int size = -1;
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Failed to find file with that name.\n");
    }
    //goes to the end of the file to find the size
    fseek(fp, 0, SEEK_END);
    size = ftell(fp); 
    rewind(fp);
    char * word = malloc(sizeof(char)*size);

    fread(word, strlen(word)+1, size, fp);

    return word;
}

/******
 stretchMe: Expands a string by multiplying each letter by a number of the users choice
 In: aStringToStretch
 Out: newString
 Post: Creates a NEW string that has expanded the word by the specific amounts
*******/
char * stretchMe (char * aStringToStretch){
    int n;
    n = strlen(aStringToStretch);

    int letAmount[n];
    int newSize = 0;
    for(int i = 0; i<n; i++){
        //scans the numbers to expand each char
        do{
            scanf("%d", &letAmount[i]);
        }while(letAmount[i]<0);
        newSize += letAmount[i];
    }
    
    char * newString = calloc(newSize, sizeof(char));

    int j = 0;
    // creates the new string
    for(int i = 0; i<n; i++){
        while(letAmount[i]--)
            newString[j++] = aStringToStretch[i];
    }

    return newString;
}

/******
 splitMe: counts the amount of words in a string and puts them into an array
 In: aStringToSplit, static2D
 Out: wCount
 Post: an array is populated with the words from the string, and creates a variable with the amount of words
*******/
int splitMe (char * aStringToSplit, char static2D [MAX_WORDS][MAX_LENGTH]){
    int wCount = 0;
    char * string;
    int index = 0;
    int length = strlen(aStringToSplit);
    string =(char*)malloc(sizeof(char)*length);
    strcpy(string, aStringToSplit);
    char * value;
    // checks each word based on their breaks
    char delimiters [] = " \n";
        value = strtok(string, delimiters);
        while(value != NULL){
            //copies into it into array
            strcpy(static2D[index], value);
            wCount ++; 
            index++;
            value = strtok(NULL, delimiters);
        }
    return wCount;
}

/******
 shrinkMe: Shrinks a string by removing puncuation
 In: aStringToShrink
 Out: count
 Post: changes the string to be the shrunken version, and returns the count of puncuations that were in the string
*******/
int shrinkMe (char * aStringToShrink){
    char puncArr[] = {'.',':',';','?','!'};
    char * newStr;
    char * finalStr = (char*)malloc(sizeof(char)*strlen(aStringToShrink));
    int count = 0;
    newStr = strtok(aStringToShrink, puncArr);
    while(newStr != NULL){
        //copies each new string into a temp string
        if (count == 0){
            strcpy(finalStr, newStr);
        }
        else{
            strcat(finalStr, newStr);
        }
        count++;
        newStr = strtok(NULL, puncArr);
    }
    //copies the final, shrunken word into the original string
    strcpy(aStringToShrink, finalStr);
    return count;
}

/******
 checkPalindrome: Checks individual words if they are palindromes
 In: pString
 Out: true or false
 Post: returns a boolean variable based on the status of a word being a palindrome
*******/
bool checkPalindrome(char *pString)
{
    int l = 0;
    int h = strlen(pString) - 1;
 
    while (h > l){
        if (pString[l] != pString[h]){
            return false;
        }
        l++;
        h--;
    }
    return true;
}

/******
 isItAPalindrome: Checks if an entire sentance is a palindrome
 In: aString
 Out: true or false
 Post: Returns the status of an entire string sentance being a palindrome
*******/
bool isItAPalindrome(char *aString)
{      
    //removes the punctuation from the words
    char puncArr[] = {'.',':',';','?','!',','};
    char * newStr;
    char * finalStr = (char*)malloc(sizeof(char)*strlen(aString)+10);
    int count = 0;
    newStr = strtok(aString, puncArr);
    while(newStr != NULL){
        if (count == 0){
            strcpy(finalStr, newStr);
        }
        else{
            strcat(finalStr, newStr);
        }
        count++;
        newStr = strtok(NULL, puncArr);
    }
    strcpy(aString, finalStr);

    //Checks every word by calling back from checkPalindrome
    char * pch;
    char delimiters[]= {' ', '\n'};
    for (int i = 0; i<strlen(finalStr);i++){
        finalStr[i]=tolower(finalStr[i]);
    }
    pch = strtok (finalStr, delimiters);
    while (pch != NULL)
    {
        if(!checkPalindrome(pch)) {
            return false;
        }

    pch = strtok (NULL, delimiters);
    }    
    return true;
    
}

/******
 printSuffixes: Takes a given word from a string and gives each letter a suffix
 In: aString, whichWord, desiredSuffix
 Out: VOID
 Post: prints the new words
*******/
void printSuffixes (char * aString, int whichWord, char * desiredSuffix){
    char wordArray [MAX_WORDS][MAX_LENGTH];
    int a  = splitMe(aString, wordArray);
    char * word = wordArray[whichWord-1];

    //Checks if the number is zero or the string is invalid
    if (whichWord ==0){
        return;
    }
    else if (aString == NULL || strcmp(aString, "")==0){
        return;
    }
    
    for (int i =0; i< strlen(word); i++){
        printf("%c%s\n", word[i], desiredSuffix);
    }
    if (a != -1){
    }
}

