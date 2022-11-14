/******
Assignment 2
 Name:Nathan Starkman
 Student Number: 1127811
 Date: October 21st, 2022
*******/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 20
#define MAX 100

typedef struct stack{
    int top;
	double array[SIZE];
	
}stack;

void createStack(stack *stack);
double asciiFix(int x);
double calculateOperation(char operation, double num1, double num2);
int isFull(stack* stack);
void push(stack *stack, double num);
double pop(stack *stack);

int main (int argc, char *argv[]){
    stack stack;
    double num1;
    double num2;
    char numCalc[MAX];
    double total;
    int i = 0;

    //Checks the size of the command line arguments (needs to be two)
    if (argc != 2){
        printf("ERROR! INPUT ON COMMAND LINE DOES NOT MEET THE REQUIRED LENGTH AMOUNT!\n");
        return 0;
    }

    strcpy(numCalc, argv[1]);
    createStack(&stack);
    //Checks the characters of the argument, and completes the operation after changing into ints
    for (i = 0; i<strlen(numCalc);i++){
        if (isdigit(numCalc[i])){
            double d = asciiFix(numCalc[i]);
            push (&stack, d);
        } 
        else{
            num2 = pop(&stack);
            num1 = pop(&stack);
            total = calculateOperation(numCalc[i], num1, num2);
            push(&stack,total);
        }
    }
    total = pop(&stack);
    printf("%s =  %0.2lf\n", argv[1], total);
    return 0;
}

/******
createStack: creates the stack
 In: stack
 Out: node
 Post: initialize top of stack to 0
*******/
void createStack(stack *stack){
    stack->top = 0;
}

/******
asciiFix: changes the char into an int
 In: x
 Out: c
 Post: Turns variable into the integer equivalent
*******/
double asciiFix(int x){
	double c = (double)x-'0';
	return c;
}

/******
calculateOperation: Checks the specified operation and calculates it
 In: operation, num1, num2
 Out: final answer from operation and numbers
 Post: calculates the expression
*******/
double calculateOperation(char operation, double num1, double num2){
    switch(operation){
        case '+':
            return num1+num2;
        case '-':
            return num1-num2;
        case '*':
            return num1*num2;
        case '/':
            return num1/num2;
        default:
            return 0.00;
    }
}
/******
isFull: Checks if the stack is full yet
 In: stack
 Out: stack->top >=  SIZE- 1
 Post: none
*******/
int isFull(stack* stack){
    return stack->top >=  SIZE- 1;
}

/******
isEmpty: Checks if stack is empty
 In: stack
 Out: stack->top == -1
 Post: none
*******/
int isEmpty(stack *stack){
    return stack->top == -1;
}

/******
push: Adds a value onto the stack
 In: stack, num
 Out: none
 Post: adds number to the stack
*******/
void push(stack *stack, double num){
    if (isFull(stack)){
        printf("Stack Full. Try Again");
        return;
    }
    stack->array[++stack->top] = num;
}

/******
pop: removes value from the top of the stack
 In: stack
 Out: stack->array[stack->top--]
 Post: Returns the value at the top of the stack
*******/
double pop(stack *stack){
    if (isEmpty(stack)){
        printf("Stack Empty. Try Again");
        return 0;
    }
    return stack->array[stack->top--];
}
