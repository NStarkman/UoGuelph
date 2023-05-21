#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLENGTH 1024

/**
 * It returns the larger of two integers.
 * 
 * @param first the first number
 * @param second The second number to compare.
 * 
 * @return The maximum of the two numbers.
 */
int max(int first, int second) {
  if (first > second) {
    return first;
  } else {
    return second;
  }
}

/**
 * BoyerMooreSearch(char * string, char * buffer)
 * 
 * This function takes in a string and a buffer and searches for the buffer in the string
 * 
 * @param string The string to be searched
 * @param buffer the word to be searched for
 */
void BoyerMooreSearch(char * string, char * buffer) {
  int badTable[MAXLENGTH];
  int fileLen = strlen(string);
  int wordNum = 0;
  int shifts = 0;
  int patternLen = strlen(buffer) - 1;
  int goodTable[patternLen];
  int patternIndex = patternLen - 1;

  clock_t start = clock();

  for (int i = 0; i < MAXLENGTH; i++) {
    badTable[i] = patternLen;
  }
  for (int i = 0; i < patternLen; i++) {
    int charIndex = buffer[i];
    badTable[charIndex] = patternIndex - i;
    goodTable[i] = 0;
  }

  int latestChar = 1;
  int i, j;
  for (i = patternIndex; i > -1; i--) {
    int flag = 1;
    int tempVal;
    int currChar = patternLen - (i + 1);

    for (tempVal = 0; tempVal < currChar; tempVal++) {
      if (buffer[tempVal] != buffer[(i + 1) + tempVal]) {
        flag = 0;
      } else {
        flag = 1;
      }
    }
    if (flag == 1) {
      latestChar = i + 1;
    }
    goodTable[i] = (patternIndex - i) + latestChar;
  }

  for (j = 0; j < patternIndex; j++) {
    int tempVal;
    char index1 = '\0';
    char index2 = '\0';
    for (tempVal = 0;
      (index1 == index2) && (tempVal < j); tempVal++) {
      index1 = buffer[j - tempVal];
      index2 = buffer[patternIndex - tempVal];
    }
    if (index1 != index2) {
      goodTable[patternIndex - tempVal] = patternIndex - j + tempVal;
    } else {
      goodTable[patternIndex - tempVal] = 0;
    }

  }

  int shiftValue = patternIndex;
  while (shiftValue < fileLen) {
    int wordIndex = patternIndex;
    int currShift = shiftValue;
    while (wordIndex >= 0 && buffer[wordIndex] == string[currShift]) {
      wordIndex--;
      currShift--;
    }
    if (currShift < 0) {
      currShift = 0;
    }
    int currIndex = string[currShift];
    int holderShift = max(badTable[currIndex], 1);
    int goodShift;
    if (wordIndex < 0) {
      goodShift = goodTable[0];
    } else {
      goodShift = goodTable[wordIndex];
    }

    if (wordIndex < 0) {
      wordNum++;
      currShift += goodShift;
    } else {
      currShift += max(holderShift, goodShift);
    }
    shiftValue = currShift;
    shifts++;
  }

  clock_t end = clock();
  double ms = (double)(end - start) / 1000;


  printf("Matches: %d\n", wordNum);
  printf("shifts: %d\n", shifts);
  printf("Time taken: %.2f ms\n", ms);
}

/**
 * It reads the contents of a file into a string, then searches for a pattern in that string using the
 * Boyer-Moore algorithm
 * 
 * @return the number of times the pattern is found in the file.
 */
int main() {
  char * fileContents = NULL;
  char buffer[MAXLENGTH];
  size_t fileSize = 0;
  FILE * filePtr = fopen("data_A3_Q2.txt", "r");

  if (!filePtr) {
    fprintf(stderr, "Error opening file\n");
    exit(1);
  }

  while (fgets(buffer, MAXLENGTH, filePtr)) {
    size_t bufferLen = strlen(buffer);
    fileContents = (char * ) realloc(fileContents, (fileSize + bufferLen + 1) * sizeof(char));
    if (!fileContents) {
      fprintf(stderr, "Error allocating memory\n");
      exit(1);
    }
    strcat(fileContents, buffer);
    fileSize += bufferLen;
  }

  fclose(filePtr);

  char * pattern = (char * ) malloc(MAXLENGTH * sizeof(char));
  printf("Enter pattern: ");
  if (!fgets(pattern, MAXLENGTH, stdin)) {
    fprintf(stderr, "Pattern entered is too long\n");
    exit(-1);
  }

  BoyerMooreSearch(fileContents, pattern);
  free(fileContents);
  free(pattern);
  return 0;
}