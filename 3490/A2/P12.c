#include "P1.h"

int startMerge(int arr[], int arrLen, int *operations)
{
  int temp[arrLen];
  return mergeSort(arr, temp, 0, arrLen - 1, operations);
}

int mergeSort(int arr[], int temp[], int left, int right, int *operations)
{
  int mid, invCount = 0;
  if (right > left)
  {
    mid = (right + left) / 2;
    invCount += mergeSort(arr, temp, left, mid, operations);
    invCount += mergeSort(arr, temp, mid + 1, right, operations);
    invCount += merge(arr, temp, left, mid + 1, right, operations);
  }
  return invCount;
}

int merge(int arr[], int temp[], int left, int mid, int right, int *operations)
{
  int i, j, k;
  int invCount = 0;
  i = left;
  j = mid;
  k = left;

  while ((i <= mid - 1) && (j <= right))
  {
    (*operations)++;
    if (arr[i] <= arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];
      invCount = invCount + (mid - i);
    }
  }
  while (i <= mid - 1)
  {
    temp[k++] = arr[i++];
  }
  while (j <= right)
  {
    temp[k++] = arr[j++];
  }
  for (i = left; i <= right; i++)
  {
    arr[i] = temp[i];
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

  // Check for valid file
  if ((fp = fopen(name, "r")) == NULL)
  {
    fprintf(stderr, "Error - Could not open file '%s'.\n", name);
    exit(0);
  }

  char *token;
  const char s[2] = " ";
  int *arr = (int *)malloc(sizeof(int));

  // Load data into array
  while (fgets(line, LINE_LENGTH, fp) != NULL)
  {
    // Splits up line garbage into array stored in argv
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
  int numX = startMerge(arr, arrayLen, &operations);
  end = clock();
  printf("Finished 1.2 in %.4lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
  printf("Inversions: %d, Operations: %d\n", numX, operations);

  free(arr);
  return 0;
}
