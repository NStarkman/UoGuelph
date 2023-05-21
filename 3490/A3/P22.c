#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLENGTH 1024

void horspoolSearch(const char * text,
  const char * pattern) {
  int table[MAXLENGTH];
  int fileLen = strlen(text);
  int patternLen = strlen(pattern);
  int patternMatch = 0;
  int shifts = 0;
  
  printf("Clock Start\n");
  clock_t startTime = clock();

  for (int i = 0; i < MAXLENGTH; i++) {
    table[i] = patternLen;
  }

  for (int i = 0; i < patternLen - 1; i++) {
    int asciiIndex = pattern[i];
    table[asciiIndex] = patternLen - 1 - i;
  }

  int shiftVal = patternLen - 1;
  while (shiftVal < fileLen) {
    int index = 0;
    while (index < patternLen && pattern[patternLen - 1 - index] == text[shiftVal - index]) {
      index++;
    }
    int index2 = text[shiftVal];
    if (index == patternLen) {
      patternMatch++;
      shiftVal += patternLen;
    } else {
      shiftVal += table[index2];
    }
    shifts++;
  }
  clock_t endTime = clock();
  double timeTaken = (endTime - startTime) / 1000;
  printf("Matches: %d\n", patternMatch);
  printf("Shifts: %d\n", shifts);
  printf("Time taken: %0.0lf ms\n", timeTaken);
}

char * readFile(const char * fileName) {
  char fileText[MAXLENGTH];
  char * text = (char * ) malloc(sizeof(char));
  int finalLen = 1;

  FILE * textFile = fopen(fileName, "r");
  if (!textFile) {
    fprintf(stderr, "Error opening file\n");
    free(text);
    exit(1);
  }
  while (fgets(fileText, MAXLENGTH, textFile)) {
    int fileLen = strlen(fileText);
    finalLen += fileLen;
    text = (char * ) realloc(text, sizeof(char) * finalLen);
    strcat(text, fileText);
  }
  fclose(textFile);

  return text;
}

int main() {
  char patternBuffer[MAXLENGTH];

  char * fileText = readFile("data_A3_Q2.txt");

  printf("Enter search pattern: \n");
  if (!fgets(patternBuffer, MAXLENGTH, stdin)) {
    fprintf(stderr, "Pattern entered is too long\n");
    free(fileText);
    exit(1);
  }
  patternBuffer[strlen(patternBuffer) - 1] = '\0';

  horspoolSearch(fileText, patternBuffer);

  free(fileText);

  return 0;
}