#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1024

/**
 * It loops through the array of start points and end points, finds the minimum and maximum points,
 * then loops through all the points between the minimum and maximum points, and counts the number of
 * intervals that contain each point
 * 
 * @param startPoints an array of integers that represent the start points of the intervals
 * @param endPoints an array of integers that represent the end points of the intervals
 * @param pointLen The number of intervals
 */
void findCommonInterval(int * startPoints, int * endPoints, int pointLen) {
  int intervalCount = 0;
  int point = 0;
  int minPoint = startPoints[0];
  int maxPoint = endPoints[0];

  printf("Clock Start\n");
  clock_t startTime = clock();

  for (int i = 0; i < pointLen; i++) {
    if (startPoints[i] < minPoint) {
      minPoint = startPoints[i];
    }
    if (endPoints[i] > maxPoint) {
      maxPoint = endPoints[i];
    }
  }

  for (int i = minPoint + 1; i < maxPoint; i++) {
    int count = 0;
    for (int j = 0; j < pointLen; j++) {
      if (startPoints[j] < i && endPoints[j] > i) {
        count++;
      }
    }
    if (count > intervalCount) {
      intervalCount = count;
      point = i;
    }
  }

  clock_t endTime = clock();
  double finalTime = (endTime - startTime) / 1000.0;

  printf("The number of intervals: %d\n", intervalCount);
  printf("The common interval point: %d\n", point);
  printf("Time taken: %0.0lf ms\n", finalTime);
}


/**
 * It takes in an array of start points and an array of end points, and finds the largest common
 * interval between them
 * 
 * @return the length of the common interval.
 */

int main() {
  char fileName[MAX_LENGTH];
  int * startPoints = (int * ) malloc(sizeof(int));
  int * endPoints = (int * ) malloc(sizeof(int));
  int startPoint, endPoint;

  printf("Enter filename: ");
  fgets(fileName, MAX_LENGTH, stdin);
  int len = strlen(fileName);
  fileName[len - 1] = '\0';

  FILE * inputFile = fopen(fileName, "r");
  int fileLen = 0;

  if (!inputFile) {
    fprintf(stderr, "Error opening file\n");
    free(startPoints);
    free(endPoints);
    exit(1);
  }

  while (fscanf(inputFile, "%d %d", & startPoint, & endPoint) == 2) {
    startPoints[fileLen] = startPoint;
    endPoints[fileLen] = endPoint;
    fileLen++;
    startPoints = (int * ) realloc(startPoints, sizeof(int) * (fileLen + 1));
    endPoints = (int * ) realloc(endPoints, sizeof(int) * (fileLen + 1));
  }

  startPoints[fileLen] = -1;
  endPoints[fileLen] = -1;
  fclose(inputFile);
  findCommonInterval(startPoints, endPoints, fileLen);
  free(startPoints);
  free(endPoints);
  return 0;
}