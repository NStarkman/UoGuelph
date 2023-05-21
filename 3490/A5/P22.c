#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

typedef struct {
    int value;
    int *assignment;
    int level;
} Node;
int read_matrix(const char *file_name, int ***matrix) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int n = 12;

    *matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        (*matrix)[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &((*matrix)[i][j]));
        }
    }
    fclose(file);
    return n;
}

int get_upper_bound(int **matrix, int *assignment, int n) {
    int total_value = 0;
    for (int i = 0; i < n; i++) {
        if (assignment[i] == -1) {
            int max_value = INT_MIN;
            for (int j = 0; j < n; j++) {
                int in_assignment = 0;
                for (int k = 0; k < i; k++) {
                    if (assignment[k] == j) {
                        in_assignment = 1;
                        break;
                    }
                }
                if (!in_assignment) {
                    if (matrix[i][j] > max_value) {
                        max_value = matrix[i][j];
                    }
                }
            }
            total_value += max_value;
        } else {
            total_value += matrix[i][assignment[i]];
        }
    }
    return total_value;
}
void branch_and_bound(int **matrix, int n, int *best_assignment, int *best_value, int *count) {
    *best_value = INT_MIN;
    *count = 0;

    Node *stack = (Node *)malloc(n * n * n * sizeof(Node));
    int stack_top = -1;

    Node root;
    root.value = 0;
    root.assignment = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        root.assignment[i] = -1;
    }
    root.level = 0;
    stack[++stack_top] = root;

    clock_t start_time = clock();

    while (stack_top >= 0) {
        Node node = stack[stack_top--];
        if (node.level == n) {
            if (node.value > *best_value) {
                *best_value = node.value;
                memcpy(best_assignment, node.assignment, n * sizeof(int));
            }
            free(node.assignment);
            continue;
        }

        int upper_bound = get_upper_bound(matrix, node.assignment, n);
        printf("Max Upper Bound: %d\n", upper_bound);

        if (upper_bound <= *best_value) {
            free(node.assignment);
            continue;
        }

        for (int j = n - 1; j >= 0; j--) {
            int in_assignment = 0;
            for (int k = 0; k < node.level; k++) {
                if (node.assignment[k] == j) {
                    in_assignment = 1;
                    break;
                }
            }
            if (!in_assignment) {
                Node child;
                child.value = node.value + matrix[node.level][j];
                child.assignment = (int *)malloc(n * sizeof(int));
                memcpy(child.assignment, node.assignment, n * sizeof(int));
                child.assignment[node.level] = j;
                child.level = node.level + 1;
                stack[++stack_top] = child;
                (*count)++;
            }
        }

        if (node.level == 0) {
            int max_upper_bound = INT_MIN;
            for (int j = 0; j < n; j++) {
                int temp_assignment[n];
                memcpy(temp_assignment, node.assignment, n * sizeof(int));
                temp_assignment[0] = j;
                int temp_upper_bound = get_upper_bound(matrix, temp_assignment, n);
                if (temp_upper_bound > max_upper_bound) {
                    max_upper_bound = temp_upper_bound;
                }
            }
        }
        free(node.assignment);
    }

    clock_t end_time = clock();
    double running_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Branch and Bound Algorithm:\n");
    printf("Assignment: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", best_assignment[i]);
    }
    printf("\nTotal Value Created: %d\n", *best_value);
    printf("Number of Assignments Evaluated: %d\n", *count);
    printf("Running Time (seconds): %lf\n", running_time);
}

int main() {
    char file_name[256];
    printf("Enter file name: ");
    scanf("%s", file_name);

    int **matrix;
    int n = read_matrix(file_name, &matrix);

    int *best_assignment = (int *)malloc(n * sizeof(int));
    int best_value;
    int count;

    branch_and_bound(matrix, n, best_assignment, &best_value, &count);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix); 

    free(best_assignment);

    return 0;
}
