/******
Assignment 4
 Name:Nathan Starkman
 Student Number: 1127811
 Date: November 29th, 2022
*******/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void readFile(int rows, int cols, int heapArray[rows][cols]);
void createHeap(int rows, int cols, int array[rows][cols]);
void switchContent(int firstLine[12], int secondLine[12]);
void makeKey(int rows, int cols, int heapArray[rows][cols]);

//Reads the file with the given name and adds the data found into the passed heap Array
void readFile(int rows, int cols, int heapArray[rows][cols]) {
    FILE * fp;
    if (!(fp= fopen("f.dat", "r"))){
        printf("File does not exist. Please try again.\n");
        exit(0);
    }
    char buffer[1000];
    char * token;
    int row = 0;
    int col = 2;
    while (fgets(buffer, 1000, fp) != NULL) {
        col = 2;
        token = strtok(buffer, " ");
        while (token != NULL) {
            if (strlen(token) > 1) {
                heapArray[row][col] = atoi(token);
            }
            col++;
            token = strtok(NULL, " ");
        }
        row++;
    }
    fclose(fp);
}

//Creates the heap with the specific flags and rules for if a child is less than or greater than its parent
void createHeap(int rows, int cols, int array[rows][cols]) {
    int parentPosition;
    int childIndex;
    int x;
    
    for (parentPosition = 0; parentPosition < rows; parentPosition++) {
        x = 0;
        childIndex = (parentPosition * 2) + 1;
        if (childIndex >= rows) {
            return;
        }
        if (array[parentPosition][1] > array[childIndex][1]) {
            switchContent(array[parentPosition], array[childIndex]);
            x = 1;
        }
        if (childIndex + 1 >= rows) {
            return;
        }
        if (array[parentPosition][1] > array[childIndex + 1][1]) {
            switchContent(array[parentPosition], array[childIndex + 1]);
            x = 1;
        }

        if (x == 1) {
            parentPosition = -1;
        }
    }
}

//Switches the two arrays of the same size (12)
void switchContent(int firstLine[12], int secondLine[12]) {
    int temp = 0;
    for (int i = 0; i < 12; i++) {
        temp = firstLine[i];
        firstLine[i] = secondLine[i];
        secondLine[i] = temp;
    }
}

/*create the key by adding the first 3 elements, put key at front of array*/
void makeKey(int rows, int cols, int heapArray[rows][cols]) {

    for (int i = 0; i < rows; i++) {
        heapArray[i][0] = i;
        heapArray[i][1] = heapArray[i][2] + heapArray[i][3] + heapArray[i][4];
    }
}


// Takes the name of the file with the data, creates the 2D array  og the data, creates the key with the first 3 elements, and creates the heap. Then it sorts it in a down-heap and prints the result
int main() {
    int rows = 20;
    int cols = 12;
    int heapArray[rows][cols];

    readFile(rows, cols, heapArray);
    makeKey(rows, cols, heapArray);
    createHeap(rows, cols, heapArray);
    for (int i = 0; i < rows; i++) {
        for (int j = 2; j < cols; j++) {
            if (heapArray[i][j] < 10) {
                printf("0%d ", heapArray[i][j]);
            } else {
                printf("%d ", heapArray[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}