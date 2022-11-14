/******
Assignment 3
 Name:Nathan Starkman
 Student Number: 1127811
 Date: November 12th, 2022
*******/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#define MAX 256
#define LENGTH 5

typedef struct tree {
    char expression[LENGTH];
    struct tree * left;
    struct tree * right;
} tree;

tree * createTree(char expression[LENGTH]);
tree * valueStack[MAX];
int valueCount = 0;
char stackExpression[MAX][LENGTH];
int expressionAmnt = 0;
int addToArray(char expressionArray[MAX][LENGTH], char expression[]);
tree * addToTree(char expression[]);
bool findValue(char value[]);
bool findExpression(char operator);
int priority(char operator[]);
void pushExpression(char expression[LENGTH]);
void pushValue(tree * tree);
char * popExpression();
bool noExpression();
char * topExpression();
tree * popValue();
bool noValue();
tree * topValue();
void postorder(tree * root);
void preorder(tree * root);

int main(int argc, char * argv[]) {
    tree * tree;
    int choice;
    bool done = true;
    char temp[strlen(argv[1]) + 2];
    char expression[strlen(argv[1])];
    //Removes the brackets
    temp[0] = '(';
    strcat(temp, argv[1]);
    temp[strlen(argv[1]) + 1] = ')';

    //Copies the values and adds them to the tree
    strcpy(expression, temp);
    strcpy(expression, argv[1]);
    tree = addToTree(expression);

    while (done == true) {
        printf("What Option will you select?:\n");
        printf("1. preorder\n");
        printf("2. postorder\n");
        printf("3. Exit\n");
        scanf("%d", & choice);
        printf("\n");
        if (choice == 1) {
            preorder(tree);
        } else if (choice == 2) {
            postorder(tree);
        } else if (choice == 3) {
            break;
        } else {
            printf("INVALID INPUT. ENDING PROGRAM.\n");
            break;
        }

        printf("\n");
    }
    return 0;
}

/******
 createTree: creates the tree nodes
 In: expression
 Out: result
 Post: creates a tree and adds the expression into it
*******/
tree * createTree(char expression[LENGTH]) {
    tree * result = malloc(sizeof(tree));
    result -> left = NULL;
    result -> right = NULL;
    strcpy(result -> expression, expression);
    return result;
}

/******
 addToArray: Adds each part of the expression into an array
 In: expressionArray, expression
 Out: j
 Post: populates array with the expression inputted
*******/
int addToArray(char expressionArray[MAX][LENGTH], char expression[]) {
    int j = 0;
    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] == '(') {
            strcpy(expressionArray[j], "(");
            j++;
        } else if (expression[i] == ')') {
            strcpy(expressionArray[j], ")");
            j++;
        } else if (findExpression(expression[i])) {
            char operator[2];
            operator[0] = expression[i];
            operator[1] = '\0';
            strcpy(expressionArray[j], operator);
            j++;
        } else if (expression[i] == 'x') {
            char  var [3];
            var [0] = expression[i];
            var [1] = expression[++i];
            var [2] = '\0';
            strcpy(expressionArray[j],var );
            j++;
        } else {
            char num[5];
            num[0] = expression[i];
            num[1] = expression[++i];
            num[2] = expression[++i];
            num[3] = expression[++i];
            num[4] = '\0';
            strcpy(expressionArray[j], num);
            j++;
        }
    }

    return j;
}

/******
 addToTree: Adds each element of the expression into the tree
 In: expression
 Out: tree
 Post: populates tree with the operands inputted
*******/
tree * addToTree(char expression[]) {
    char expressionArray[MAX][LENGTH];
    int num;
    tree * tree, * tree1, * tree2;

    num = addToArray(expressionArray, expression);

    for (int i = 0; i < num; i++) {
        if (strcmp(expressionArray[i], "(") == 0) {
            pushExpression(expressionArray[i]);
        }
        else if (findValue(expressionArray[i])) {
            tree = createTree(expressionArray[i]);
            pushValue(tree);
        }
        else if (priority(expressionArray[i]) > 0) {
            while (!noExpression() &&
                strcmp(topExpression(), "(") != 0 &&
                ((strcmp(expressionArray[i], "^") != 0 && priority(topExpression()) >= priority(expressionArray[i])) ||
                    ((strcmp(expressionArray[i], "^") == 0) && priority(topExpression()) > priority(expressionArray[i])))) {

                tree = createTree(topExpression());
                popExpression();

                tree1 = topValue();
                popValue();

                tree2 = topValue();
                popValue();

                tree -> left = tree2;
                tree -> right = tree1;

                pushValue(tree);
            }
            pushExpression(expressionArray[i]);
        }

        else if (strcmp(expressionArray[i], ")") == 0) {
            while (!noExpression() && strcmp(topExpression(), "(") != 0) {

                tree = createTree(topExpression());
                popExpression();
                tree1 = topValue();
                popValue();
                tree2 = topValue();
                popValue();
                tree -> left = tree2;
                tree -> right = tree1;

                pushValue(tree);
            }
            popExpression();
        }
    }
    tree = topValue();
    return tree;
}

/******
 findValue: checks if the value is a digit or a   var 
 In: value
 Out: boolean value
 Post: Returns the boolean value if it is a number or var 
*******/
bool findValue(char value[]) {
    if (isdigit(value[0])) {
        return true;
    }
    if (value[0] == 'x') {
        return true;
    }
    return false;
}

/******
 findExpression: Checks if the value in the expression is an operation value
 In: operator
 Out: boolean value
 Post: Returns the boolean value if it is an operator or not
*******/
bool findExpression(char operator) {
    if (operator == '+' || operator == '-' || operator == '*' || operator == '/') {
        return true;
    }
    return false;
}

/******
 priority: Creates a priority of expressions so that the tree is in proper order
 In: operator
 Out: 1,2,3,0
 Post: Shows the priority value of each operand
*******/
int priority(char operator[]) {

    if (strcmp(operator, "+") == 0 || strcmp(operator, "-") == 0) {
        return 1;
    }
    if (strcmp(operator, "*") == 0 || strcmp(operator, "/") == 0) {
        return 2;
    }
    if (strcmp(operator, "^") == 0) {
        return 3;
    }
    return 0;
}

/******
 pushExpression: Add the expression to the stack
 In: expression
 Out: void
 Post: Pushes expression to the stack
*******/
void pushExpression(char expression[LENGTH]) {
    if (expressionAmnt == MAX) {
        printf("Overflow.");
        return;
    }
    strcpy(stackExpression[expressionAmnt], expression);
    expressionAmnt++;
}

/******
 pushValue: pushes the value of the operand to a stack
 In: tree
 Out: void
 Post: Updates stack
*******/
void pushValue(tree * tree) {
    if (valueCount == MAX) {
        printf("Overflow.");
        return;
    }
    valueStack[valueCount] = tree;
    valueCount++;
}

/******
 popExpression: Removes the expression from the stack
 In: none
 Out: result
 Post: Gives the popped off expression from the stack
*******/
char * popExpression() {
    if (expressionAmnt == 0) {
        printf("Underflow.");
        exit(0);
    }
    char * result = stackExpression[expressionAmnt - 1];
    expressionAmnt--;
    return result;
}
/******
 noExpression: Checks if there are no expressions
 In: none
 Out: boolean value
 Post: checks if the expression stack/amount is empty
*******/
bool noExpression() {
    if (expressionAmnt == 0) {
        return true;
    }
    return false;
}

/******
 topExpression: Add the expression to the stack
 In: expression
 Out: void
 Post: Pushes expression to the stack
*******/
char * topExpression() {
    if (expressionAmnt == 0) {
        printf("Underflow.");
    }
    char * result = stackExpression[expressionAmnt - 1];
    return result;
}

/******
 popValue: pops the value from the value stack
 In: 
 Out: tree
 Post: Updates the tree with the popped Stack
*******/
tree * popValue() {
    if (valueCount == 0) {
        printf("Underflow.");
    }
    tree * tree = valueStack[valueCount - 1];
    valueCount--;
    return tree;
}

/******
 noValue: Checks if the value stack is empty
 In: 
 Out: boolean value
 Post: Says if the value is empty or not
*******/
bool noValue() {
    if (valueCount == 0) {
        return true;
    }
    return false;
}


tree * topValue() {
    if (valueCount == 0) {
        printf("Underflow.");
    }
    tree * t = valueStack[valueCount - 1];
    return t;
}

/******
 postorder: prints the postorder of the expression
 In: root
 Out: void
 Post: prints the expression in postorder
*******/
void postorder(tree * root) {
    if (root == NULL) {
        return;
    }
    postorder(root -> left);
    postorder(root -> right);
    if (root -> expression[0] == 'x') {
        printf("%s[0.00]   ", root -> expression);
    } else {
        printf("%s   ", root -> expression);
    }
}

/******
 preorder: prints the preorder of the expression
 In: root
 Out: void
 Post: prints the expression in preorder
*******/
void preorder(tree * root) {
    if (root == NULL) {
        return;
    }
    if (root -> expression[0] == 'x') {
        printf("%s[0.00]   ", root -> expression);
    } else {
        printf("%s   ", root -> expression);
    }
    preorder(root -> left);
    preorder(root -> right);
}
