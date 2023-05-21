#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 12

int n = 12;
int V[MAX_N][MAX_N];
int best_assignment[MAX_N];
int best_value = -1;
int num_assignments = 0;

void print_assignment()
{
    printf("Assignment: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", best_assignment[i]);
    }
    printf("\n");
}

void evaluate_assignment(int* assignment)
{
    int value = 0;
    for (int i = 0; i < n; i++) {
        value += V[i][assignment[i]];
    }
    if (value > best_value) {
        best_value = value;
        for (int i = 0; i < n; i++) {
            best_assignment[i] = assignment[i];
        }
    }
    num_assignments++;
}

void brute_force(int i, int* assignment)
{
    if (i == n) {
        evaluate_assignment(assignment);
        return;
    }
    for (int j = 0; j < n; j++) {
        if (assignment[j] == -1) {
            assignment[j] = i;
            brute_force(i+1, assignment);
            assignment[j] = -1;
        }
    }
}

int main()
{
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &V[i][j]);
        }
    }
    fclose(fp);

    clock_t start_time = clock();
    int assignment[MAX_N];
    for (int i = 0; i < n; i++) {
        assignment[i] = -1;
    }
    brute_force(0, assignment);
    clock_t end_time = clock();

    printf("Total value created: %d\n", best_value);
    print_assignment();
    printf("Number of assignments evaluated: %d\n", num_assignments);
    printf("Running time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
