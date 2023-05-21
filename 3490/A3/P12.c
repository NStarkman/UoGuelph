#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1024

/**
 * It takes two arrays, one of which is a temporary array, and merges them together.
 * 
 * @param data The array to be sorted
 * @param temp temporary array to store the sorted data
 * @param left the left-most index of the subarray
 * @param middle the middle of the array
 * @param right the last index of the array
 */
void arrayMerge(int * data, int * temp, int left, int middle, int right) {
  int mergePoint = left;
  int leftArray = left;
  int rightArray = middle;
  while ((leftArray <= middle - 1) && (rightArray <= right)) {
    if (data[leftArray] <= data[rightArray]) {
      temp[mergePoint++] = data[leftArray++];
    } else {
      temp[mergePoint++] = data[rightArray++];
    }
  }

  while (leftArray <= (middle - 1)) {
    temp[mergePoint++] = data[leftArray++];
  }
  while (rightArray <= right) {
    temp[mergePoint++] = data[rightArray++];
  }
  for (leftArray = left; leftArray <= right; leftArray++) {
    data[leftArray] = temp[leftArray];
  }
}

/**
 * If the right side of the array is greater than the left side, then find the middle of the array, and
 * recursively call merge on the left and right sides of the array, and then merge the two sides
 * together.
 * 
 * @param data the array to be sorted
 * @param temp a temporary array used to store the sorted data
 * @param left the left-most index of the sub-array
 * @param right the right-most index of the sub-array of arr to be sorted
 */
void merge(int * data, int * temp, int left, int right) {
  int mid;

  if (right > left) {
    mid = (right + left) / 2;

    merge(data, temp, left, mid);
    merge(data, temp, mid + 1, right);

    arrayMerge(data, temp, left, mid + 1, right);
  }
}

/**
 * It takes in two arrays of integers, sorts them, and then finds the point where the most intervals
 * overlap
 * 
 * @param startPoints An array of integers that represent the start points of the intervals
 * @param endPoints array of end points
 * @param fileLen The length of the file.
 */
void findCommonInterval(int * startPoints, int * endPoints, int fileLen) {
  int intervalCount = 0;
  int point = 0;

  int * tempPointArray1 = (int * ) malloc(sizeof(int) * fileLen);
  int * tempPointArray2 = (int * ) malloc(sizeof(int) * fileLen);

  printf("Clock Start\n");
  clock_t startTime = clock();

  merge(startPoints, tempPointArray1, 0, fileLen - 1);
  merge(endPoints, tempPointArray2, 0, fileLen - 1);

  int i = 1;
  int j = 0;
  int count = 0;
  while (i < fileLen && j < fileLen) {
    if (startPoints[i] < endPoints[j]) {
      count++;
      if (count > intervalCount) {
        intervalCount = count;
        point = startPoints[i] + 1;
      }
      i++;
    } else if (startPoints[i] == endPoints[j]) {
      j++;
      i++;
    } else {
      count--;
      j++;
    }
  }

  clock_t endTime = clock();

  double timeTaken = (endTime - startTime) / 1000;

  printf("Interval Number: %d\n", intervalCount);
  printf("Common Point: %d\n", point);
  printf("Time: %0.0lf ms\n", timeTaken);

  free(tempPointArray1);
  free(tempPointArray2);
}

/**
 * It takes an array of start points and an array of end points, and finds the longest common interval
 * between them
 * 
 * @return the length of the longest common interval.
 */
int main() {
  char filename[MAX_LENGTH];
  char * string = (char * ) malloc(sizeof(char));
  int * startPoints = (int * ) malloc(sizeof(int));
  int * endPoints = (int * ) malloc(sizeof(int));
  int i = 0;
  printf("Enter filename: ");
  fgets(filename, MAX_LENGTH, stdin);
  int len = strlen(filename);
  filename[len - 1] = '\0';

  FILE * inputFile = fopen(filename, "r");
  if (!inputFile) {
    fprintf(stderr, "Error opening file\n");
    free(startPoints);
    free(endPoints);
    free(string);
    exit(-1);
  }

  int start, end;

  while (fscanf(inputFile, "%d %d", & start, & end) == 2) {
    startPoints[i] = start;
    endPoints[i] = end;
    i++;
    startPoints = (int * ) realloc(startPoints, sizeof(int) * (i + 1));
    endPoints = (int * ) realloc(endPoints, sizeof(int) * (i + 1));
  }

  startPoints[i] = -1;
  endPoints[i] = -1;

  fclose(inputFile);

  findCommonInterval(startPoints, endPoints, i);

  free(startPoints);
  free(endPoints);
  free(string);

  return 0;
}