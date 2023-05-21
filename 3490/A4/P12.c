
/*
    Nathan Starkman
    1127811
    nstarkma@uoguelph.ca
    Assignment 4
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct node node;

 struct node{
	char * string;
    float total;	
	float count;
	node * left;
	node * right;
};


void greedyTree (FILE * fp, char * string); 
node *createNode(char *string, float total, float count);
node *insertNode(char * string, node * root);
void freeTree(node * node);
void travelTree(int totalString, node *root);
int stringComp(const void *a, const void *b);
int hasChild(node* node);
node * readTree(node * root, char * string);
int getHeight(node* node);
node * createTree(int i, int j);
int probabilityFind(int i, int j);

char * words[2000];
float probability[2000];
int currIndex = 1;
/**
 * This function reads the text file and creates a tree with the words in the text file. Then it
 * creates a new tree with the words in the text file in a random order. Then it prints the words in
 * the new tree in order
 * 
 * @param fp the file pointer to the text file
 * @param string the string that will be returned
 */

void greedyTree (FILE * fp, char * string){
    string[strlen(string)] = '\0';
    node *root = NULL;
    node *randomRoot = NULL;
    char wordBuffer[520];
    int buffeerLen = 0;
    int i = 0;
    int letterCount = 0;
    char currWord[50];
    int wordCount = 0;
    //obtain each sentence from the text file and put the words into tree
    while(!feof(fp)){
        while (fgets(wordBuffer, 520, fp) != NULL && wordBuffer[0] != '\n'){
            wordBuffer[strlen(wordBuffer)] = '\0';
            buffeerLen = strlen(wordBuffer);
            for(i = 0; i < buffeerLen; i++){
                if(wordBuffer[i] != ' ' && wordBuffer[i] != '\0' && wordBuffer[i] != '\n' && wordBuffer[i] != '\t' && wordBuffer[i] != '\r'){
                    currWord[letterCount] = wordBuffer[i];
                    letterCount++;
                }
                else{
                    if(letterCount > 0){
                        currWord[letterCount] = '\0';
                        root = insertNode(currWord, root);
                        letterCount = 0;
                        wordCount++;
                    }
                }
            }
        }
    }
    fclose(fp);
    randomRoot = root;
    travelTree(wordCount, randomRoot);
    int curr = currIndex;
    node * node = createTree(1, curr-1);        
    readTree(node, string);
    freeTree(root);
    freeTree(node);
}
/**
 * If the root is null, create a new node with the string and return it. Otherwise, compare the string
 * to the root's string. If the string is less than the root's string, recursively call insertNode on
 * the left child. If the string is greater than the root's string, recursively call insertNode on the
 * right child. If the string is equal to the root's string, increment the count
 * 
 * @param string the string to be inserted into the tree
 * @param root the root of the tree
 * 
 * @return The root of the tree.
 */

node *insertNode(char * string, node * root){
    int childNum = hasChild(root);
    int height = getHeight(root);
    if (childNum == 0 && height == 0){
        root = createNode(string, 1, 1);
        return root;
    }
    int comp = 0;
    comp = stringComp(string, root->string);
    if (comp == -1){
        root->left = insertNode(string, root->left);
    }
    else if (comp == 1){
        root->right = insertNode(string, root->right);
    }
    else{
        root->count++;
    }
    return root;
}
/**
 * It creates a new node with the given string, total, and count, and returns a pointer to the new
 * node.
 * 
 * @param string the string to be stored in the node
 * @param total the total number of times the string has been seen
 * @param count the number of times the string has been seen
 * 
 * @return A pointer to a node
 */

node *createNode(char *string, float total, float count){
    node *newNode = (node *)malloc(sizeof(node));
    char *newString = malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(newString, string);
    newNode->total = total;
    newNode->count = count;
    newNode->string = newString;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/**
 * It traverses the tree and stores the words and their probabilities in the arrays words and
 * probability
 * 
 * @param totalString the total number of strings in the tree
 * @param root the root of the tree
 * 
 * @return the number of children the node has.
 */

void travelTree(int totalString, node *root){
    int childNum = hasChild(root);
    int height = getHeight(root);
    if (root->left != NULL && childNum == 1 && height != 1){
        travelTree(totalString, root->left);
    }
    words[currIndex] = root->string;
    probability[currIndex] = (float)root->count/totalString;
    currIndex++;
    if (root->right != NULL && childNum == 1 && height != 1){
        travelTree(totalString, root->right);
    }
    if (childNum==0&& height ==1){
        return;
    }
}
/**
 * If the first string is greater than the second string, return 1. If the first string is less than
 * the second string, return -1. If the strings are equal, return 0
 * 
 * @param a The first element to compare.
 * @param b the array to be sorted
 * 
 * @return The difference between the two strings.
 */

int stringComp(const void *a, const void *b){
    if(strcmp(a, b) > 0){
		return 1;
	}
	else if(strcmp(a, b) < 0){
		return -1;
	}
	else{
		return 0;
	}
}
/**
 * It checks if a node has a child.
 * 
 * @param node the node to check
 * 
 * @return the number of children a node has.
 */

int hasChild(node* node){
    if (node != NULL){
        if (node->left != NULL){
            return 1;
        }
        if (node->right != NULL){
            return 1;
        }
    }
    return 0;
}
/**
 * If the node is null, return 0. Otherwise, return the maximum of the left and right subtree heights
 * plus 1.
 * 
 * @param node the node to get the height of
 * 
 * @return The height of the tree.
 */

int getHeight(node* node){
    if (node == NULL){
        return 0;
    }
    else{
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        if (leftHeight > rightHeight){
            return leftHeight + 1;
        }
        else{
            return rightHeight + 1;
        }
    }
}

/**
 * It frees the tree.
 * 
 * @param node the node to be freed
 * 
 * @return the height of the tree.
 */

void freeTree(node * node){
    int childNum = hasChild(node);
    int height = getHeight(node);
    if (childNum==0&& height ==1){
        //free(node);
        return;
    }
    if (node->left != NULL && childNum == 1 && height != 1){
        freeTree(node->left);
    }
    if (node->right != NULL && childNum == 1 && height != 1){
        freeTree(node->right);
    }
    free(node->string);
    free(node);

}
/**
 * It compares the string with the root's string, and if it's equal, it prints out the root's string
 * and total, if it's greater than the root's string, it goes to the right subtree, and if it's less
 * than the root's string, it goes to the left subtree
 * 
 * @param root the root of the tree
 * @param string the string to be searched for
 * 
 * @return The root of the tree.
 */


node * readTree(node * root, char * string){
    if (hasChild(root) != 0){
        if (stringComp(string,root->string) == 0){
            printf("Compared with %s (%.4f), found.\n", root->string, root->total);
        }
        else if (stringComp(string, root->string) == 1){
            printf("Compared with %s (%.4f), go right subtree.\n", root->string, root->total);
            root->right = readTree(root->right, string);
        }
        else{
            printf("Compared with %s (%.4f), go left subtree.\n", root->string, root->total);
            root->left = readTree(root->left, string);
        }
    }
    else {
        printf("Not found.\n");
    }
    return root;
}
/**
 * This function creates a tree by recursively calling itself and creating a node with the word at the
 * probability index
 * 
 * @param i the starting index of the array
 * @param j the last index of the array
 * 
 * @return A pointer to a node.
 */

node * createTree(int i, int j){
    node * node;
    int probabilityIndex = 0;
    probabilityIndex = probabilityFind(i, j);
    if (i<=j){
        char * newString = words[probabilityIndex];
        node = createNode(newString, probability[probabilityIndex], 1);
        node->left = createTree(i, probabilityIndex-1);
        node->right = createTree(probabilityIndex+1, j);
    }
    else{
        node = NULL;
    }
    return node;
}
/**
 * It finds the index of the maximum probability in the range [i, j].
 * 
 * @param i the start index of the array
 * @param j the index of the last word in the sentence
 * 
 * @return The index of the maximum probability in the range of i to j.
 */


int probabilityFind(int i, int j){
    int index = 0;
    double max = 0;
    int k = 0;
    for (k = i; k <= j; k++){
        if (max < probability[k]){
            max = probability[k];
            index = k;
        }
    }
    return index;
}


int main(int argc, char const *argv[])
{
	FILE *file;
	char str[25];

	if ((argc < 2) || (argc > 2))
	{
		printf("Incorrect input\nShould be ./P12 <data file >\n");
		return(-1);
	}
	printf("Please enter a string for Tree  Search:\n");
	scanf("%s", str);

	
	file = fopen(argv[1], "r");
	greedyTree(file, str);

	return 0;
}
