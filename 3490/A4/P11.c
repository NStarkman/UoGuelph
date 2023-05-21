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

void dynamicTree(FILE *fp, char *string);
node *createNode(char *string, float total, float count);
node *insertNode(char * string, node * root);
void freeTree(node * node);
void travel(int totalStrings, node *root);
int stringComp(const void *a, const void *b);
int hasChild(node* treeNode);
node * searchNode(node * root, char * string);
int getHeight(node* treeNode);
node * createTree(int i, int j);

float costTable[2000][2000];
int rootTable[2000][2000];
double probability[2000];
char *words[2000];
int currIndex = 1;

/**
 * This function reads in the text file and creates a binary search tree with the words in the text
 * file. It then creates an optimal binary search tree using the words in the text file. It then
 * searches the optimal binary search tree for the user's inputted word
 * 
 * @param file the file that contains the text
 * @param string the string that the user wants to search for
 */


void dynamicTree (FILE * file, char* string){
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
	while(!feof(file))
	{
		while (fgets(wordBuffer, 520, file) != NULL && wordBuffer[0] != '\n'){
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
	fclose(file);
	randomRoot = root;
	travel(wordCount, randomRoot);
	int num1 = currIndex;
	int num2 = 0;
	double min = 0;
	int num3 = 0;
	int minIndex = 0;
	double sum = 0;
	int num4 = 0;
	int num5 = 0;
	for(i = 1; i <= num1; i++){
		costTable[i][i-1] = 0;
		costTable[i][i] = probability[i];
		rootTable[i][i] = i;	
	}
	costTable[num1+1][num1] = 0;
	
	for(num5 = 1; num5 < num1; num5++){
		for(i = 1; i <= num1-num5; i++){
			num2 = i+num5;
			min = 99999999;
			for(num3 = i; num3 <= num2; num3++){
				if((costTable[i][num3-1] + costTable[num3+1][num2]) < min){
					min = costTable[i][num3-1]+costTable[num3+1][num2];
					minIndex = num3;
				}
			}
			rootTable[i][num2] = minIndex;
			sum = probability[i]; 
			for(num4 = i+1; num4 <= num2; num4++){
				sum = sum + probability[num4];
			}
			costTable[i][num2] = min + sum;
		}
	}
	int treeIndex = currIndex-1;
	node *optBST = createTree(1, treeIndex);
	searchNode(optBST, string);
	freeTree(root);
	freeTree(optBST);
}
/**
 * It creates a new node with the given string, total, and count, and returns a pointer to the new
 * node.
 * 
 * @param string The string that will be stored in the node
 * @param total the total number of times the word has been seen
 * @param count the number of times the string has been seen
 * 
 * @return A pointer to a node
 */

node *createNode(char *string, float total, float count){
    node *newNode = (node *)malloc(sizeof(node));
    newNode->string = (char *)malloc(sizeof(char) * strlen(string));
    strcpy(newNode->string, string);
    newNode->total = total;
    newNode->count = count;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/**
 * If the root is null, create a new node, otherwise, if the string is equal to the root, increment the
 * total and count, otherwise, if the string is less than the root, insert the string into the left
 * subtree, otherwise, insert the string into the right subtree
 * 
 * @param string the string to be inserted into the tree
 * @param root the root of the tree
 * 
 * @return The root node of the tree.
 */
node *insertNode(char * string, node * root){
    if(root == NULL){
        root = createNode(string, 1, 1);
        return root;
    }
    else{
        if(strcmp(string, root->string) == 0){
            root->total++;
            root->count++;
            return root;
        }
        else if(strcmp(string, root->string) < 0){
            root->left = insertNode(string, root->left);
            return root;
        }
        else{
            root->right = insertNode(string, root->right);
            return root;
        }
    }
}

/**
 * The function freeTree() takes in a node pointer and frees the memory of the node and all of its
 * children.
 * 
 * @param node the node to be freed
 * 
 * @return the height of the tree.
 */
void freeTree(node * node){
    int numChildren = hasChild(node);
	int height = getHeight(node);
	if ( numChildren == 0 && height == 1 ) { 
		return; 
	}
	if(node->right != NULL && numChildren == 1 && height != 1){
		freeTree(node->right);
	}
	if(node->left != NULL && numChildren == 1 && height != 1){
		freeTree(node->left);
	}
	free(node->string);
	free(node);
}
/**
 * It traverses the tree in a preorder fashion, and stores the strings and their probabilities in the
 * arrays words and probability
 * 
 * @param totalStrings the total number of strings in the tree
 * @param root the root of the tree
 * 
 * @return the number of children a node has.
 */

void travel(int totalStrings, node *root){
    int numChildren = hasChild(root);
	int height = getHeight(root);
	if(root->left != NULL && numChildren == 1 && height != 1){
		travel(totalStrings, root->left);
	}
	words[currIndex] = root->string;
  	probability[currIndex] = (float)root->count/totalStrings;
    	currIndex++;
	if(root->right != NULL && numChildren == 1 && height != 1){
		travel(totalStrings, root->right);
	}
	if(numChildren == 0 && height == 1){
	        return;
	}
}
/**
 * If the first string is greater than the second string, return 1. If the first string is less than
 * the second string, return -1. If the strings are equal, return 0
 * 
 * @param a The first element to be compared.
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

int hasChild(node *node){
    if(node != NULL){
        if(node->left != NULL){
            return 1;
        }
        if(node->right != NULL){
            return 1;
        	}
    }

    return 0;
}
/**
 * If the node is NULL, return 0. Otherwise, return the maximum of the left and right subtree heights
 * plus 1.
 * 
 * @param node the node to get the height of
 * 
 * @return The height of the tree.
 */

int getHeight(node *node){
    if(node == NULL){
        return 0;
    }
    else{
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        if(leftHeight > rightHeight){
            return leftHeight + 1;
        }
        else{
            return rightHeight + 1;
        }
    }
}

/**
 * If the current word is the first word, then the tree is just the current word. Otherwise, the tree
 * is the current word with the left subtree being the tree of the first word and the right subtree
 * being the tree of the rest of the words
 * 
 * @param i the starting index of the words array
 * @param j the index of the last word in the sentence
 * 
 * @return A pointer to the root of the tree.
 */
node *createTree(int i, int j){
    if(i > j){
        return NULL;
    }
    else{
        int k = rootTable[i][j];
        node *newNode = createNode(words[k], costTable[i][j], 1);
        newNode->left = createTree(i, k-1);
        newNode->right = createTree(k+1, j);
        return newNode;
    }
}
/**
 * If the root has children, compare the string with the root's string. If they are equal, print the
 * root's string and total. If the string is greater than the root's string, go to the right subtree.
 * If the string is less than the root's string, go to the left subtree. If the root has no children,
 * print "not found!"
 * 
 * @param root the root of the tree
 * @param string the string to be searched
 * 
 * @return The root node of the tree.
 */

node * searchNode(node *root, char *string){
    if (hasChild(root) !=0){
        if (stringComp(string, root->string) == 0){
           printf("Compared with %s (%.3f), found.\n", root->string, root->total);
        }
        else if (stringComp(string, root->string) == 1){
            printf("Compared with %s (%.3f), go right subtree.\n", root->string, root->total);
            root->right = searchNode(root->right, string);
        }
        else{
            printf("Compared with %s (%.3f), go left subtree.\n", root->string, root->total);
            root->left = searchNode(root->left, string);
        }
      
    }
    else {
	    printf("not found!\n");
	}
	return root;
}

int main(int argc, char const *argv[])
{
	FILE *file;
	char str[25];

	if ((argc < 2) || (argc > 2))
	{
		printf("Incorrect input\nShould be ./P11 <data file >\n");
		return(-1);
	}
	printf("Please enter a string for Tree  Search:\n");
	scanf("%s", str);

	
	file = fopen(argv[1], "r");
	dynamicTree(file, str);

	return 0;
}
