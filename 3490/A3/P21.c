#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1024

void bruteForceSearch(const char * text,
  const char * pattern) {
  int fileLen = strlen(text);
  int patternLen = strlen(pattern);
  int patternMatch = 0;
  int shifts = 0;
  
  printf("Clock Start\n");
  clock_t startTime = clock();

  for (int i = 0; i <= fileLen - patternLen; i++) {
    int matching = 0;
    for (int j = 0; j < patternLen; j++) {
      if (text[i + j] != pattern[j]) {
        break;
      } else {
        matching++;
      }
    }
    if (patternLen == matching) {
      patternMatch++;
    } else {
      shifts++;
    }
  }
  clock_t endTime = clock();
  double timeTaken = (endTime - startTime) / 1000;

  printf("Matches: %d\n", patternMatch);
  printf("Shifts: %d\n", shifts);
  printf("Time taken: %0.0lf ms\n", timeTaken);
}

char * readFile(const char * fileName) {
  char fileText[MAX_LENGTH];
  char * text = (char * ) malloc(sizeof(char));
  int finalLen = 1;

  FILE * textFile = fopen(fileName, "r");
  if (!textFile) {
    fprintf(stderr, "Error opening file\n");
    free(text);
    exit(1);
  }
  while (fgets(fileText, MAX_LENGTH, textFile)) {
    int fileLen = strlen(fileText);
    finalLen += fileLen;
    text = (char * ) realloc(text, sizeof(char) * finalLen);
    strcat(text, fileText);
  }
  fclose(textFile);

  return text;
}

int main() {
  char patternBuffer[MAX_LENGTH];

  char * fileText = readFile("data_A3_Q2.txt");

  printf("Enter search pattern:\n");
  if (!fgets(patternBuffer, MAX_LENGTH, stdin)) {
    fprintf(stderr, "Pattern entered is too long\n");
    free(fileText);
    exit(1);
  }
  patternBuffer[strlen(patternBuffer) - 1] = '\0';

  bruteForceSearch(fileText, patternBuffer);

  free(fileText);

  return 0;
}