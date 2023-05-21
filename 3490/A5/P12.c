#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count_subsets(int A[], int n, int d, int current_sum, int index, int *dead_ends) {
    if (current_sum == d) {
        return 1;
    } else if (index == n || current_sum > d) {
        (*dead_ends)++;
        return 0;
    }

    return count_subsets(A, n, d, current_sum + A[index], index + 1, dead_ends) +
           count_subsets(A, n, d, current_sum, index + 1, dead_ends);
}

int main() {
    char file_name[256];
    int d;
    int A[25], n = 25;
    int dead_ends = 0;
    FILE *file;

    printf("Enter the file name: ");
    scanf("%s", file_name);
    printf("Enter the positive integer d: ");
    scanf("%d", &d);

    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error: cannot open file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &A[i]);
    }
    fclose(file);

    clock_t start_time = clock();

    int num_subsets = count_subsets(A, n, d, 0, 0, &dead_ends);

    double running_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    printf("Number of subsets whose sum is equal to %d: %d\n", d, num_subsets);
    printf("Number of dead ends: %d\n", dead_ends);
    printf("Running time: %.6f seconds\n", running_time);

    return 0;
}
