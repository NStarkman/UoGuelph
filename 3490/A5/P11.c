#include <stdio.h>
#include <time.h>

int main() {
    // Prompt for file name and d
    char filename[100];
    int d;
    printf("Enter the file name: ");
    scanf("%s", filename);
    printf("Enter the value of d: ");
    scanf("%d", &d);

    // Open file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return 1;
    }

    // Read in set A
    int A[100];
    int n = 0;
    while (fscanf(file, "%d", &A[n]) == 1) {
        n++;
    }
    fclose(file);

    // Compute number of subsets whose sum is equal to d
    int count = 0;
    int num_subsets = 1 << n; // number of subsets is 2^n
    clock_t start = clock();
    for (int i = 0; i < num_subsets; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0) {
                sum += A[j];
            }
        }
        if (sum == d) {
            count++;
        }
    }
    clock_t end = clock();

    // Report results
    printf("Number of subsets whose sum is equal to %d: %d\n", d, count);
    printf("Number of subsets evaluated: %d\n", num_subsets);
    printf("Execution time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
