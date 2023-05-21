#include "P1.h"

int getInvCount(int arr[], int n, int *operations)
{
  int invCount = 0;

  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      (*operations) += 1;
      if (arr[i] > arr[j])
      {
        invCount++;
      }
    }
  }
  return invCount;
}

int main()
{
  int arrayLen = 0, operations = 0;
  char name[128];
  printf("Enter .txt file name\n");
  scanf("%s", name);
  clock_t start, end;
  FILE *fp = NULL;
  char line[LINE_LENGTH];

  if ((fp = fopen(name, "r")) == NULL)
  {
    fprintf(stderr, "Error - Could not open file '%s'.\n", name);
    exit(0);
  }

  char *token;
  const char s[2] = " ";
  int *arr = (int *)malloc(sizeof(int));

  while (fgets(line, LINE_LENGTH, fp) != NULL)
  {
    strtok(line, "\n");
    token = strtok(line, s);
    while (token != NULL)
    {
      if (arrayLen > 0)
      {
        arr = (int *)realloc(arr, sizeof(int) * (arrayLen + 1));
      }

      arr[arrayLen++] = atoi(token);
      token = strtok(NULL, s);
    }
  }

  if (fp)
    fclose(fp);


  start = clock();
  int num = getInvCount(arr, arrayLen, &operations);
  end = clock();
  printf("Finished 1.1 in %.4lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
  printf("Inversions: %d, Operations: %d\n", num, operations);
  free(arr);
  return 0;
}