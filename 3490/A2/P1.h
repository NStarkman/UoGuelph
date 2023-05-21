#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define LINE_LENGTH 256

int getInvCount(int arr[], int n, int *operations);
int merge(int arr[], int temp[], int left, int mid, int right, int *operations);
int mergeSort(int arr[], int temp[], int left, int right, int *operations);
int startMerge(int arr[], int array_size, int *operations);