/*
    Nathan Starkman
    1127811
    nstarkma@uoguelph.ca
    Assignment 4
*/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5



/**
 * While there are free men, each free man proposes to his next most preferred woman, and if she
 * prefers him to her current match, they become a couple and her current match becomes free.
 * 
 * @param n the number of men and women
 * @param manPreferences a 2D array of size n x n, where manPreferences[i][j] is the jth preference of
 * man i.
 * @param womenPreferences a 2D array of size n x n, where n is the number of men and women. Each row
 * represents the preferences of a woman, and each column represents the preferences of a man. The
 * value at row i and column j is the preference of woman i for man j.
 * 
 * @return A 2D array of integers.
 */

int** stableMarriage(int n, int** manPreferences, int** womenPreferences) {
    int* freeMen = (int*)malloc(n * sizeof(int));
    int* manMatch = (int*)malloc(n * sizeof(int));
    int* womanMatch = (int*)malloc(n * sizeof(int));
    int* proposalCount = (int*)calloc(n, sizeof(int));
    int** matchTable = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matchTable[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        freeMen[i] = i;
        manMatch[i] = -1;
        womanMatch[i] = -1;
    }

    int freeMenIndex = n - 1;

    while (freeMenIndex >= 0) {
        int m = freeMen[freeMenIndex];
        int w = manPreferences[m][proposalCount[m]++];
        int mPrime = womanMatch[w];
        if (mPrime == -1) {
            manMatch[m] = w;
            womanMatch[w] = m;
            matchTable[m][w] = 1;
            freeMenIndex--;
        } else {
            int wPrefersM = 0;
            for (int i = 0; i < n; i++) {
                if (womenPreferences[w][i] == m) {
                    wPrefersM = 1;
                    break;
                } else if (womenPreferences[w][i] == mPrime) {
                    break;
                }
            }

            if (wPrefersM) {
                manMatch[m] = w;
                womanMatch[w] = m;
                manMatch[mPrime] = -1;
                matchTable[m][w] = 1;
                matchTable[mPrime][w] = 0;
                freeMen[freeMenIndex] = mPrime;
            }
        }
    }

    free(freeMen);
    free(manMatch);
    free(womanMatch);
    free(proposalCount);

    return matchTable;
}



int main(int argc, char const *argv[]) {
    int n;
    char filename[256];
  
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Unable to open file %s\n", filename);
        return 1;
    }
    fscanf(file, "%d", &n);

    int **menPref = malloc(n * sizeof(int*));
    int **womenPref = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        menPref[i] = malloc(n * sizeof(int));
        womenPref[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &menPref[i][j]);
            menPref[i][j]--;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &womenPref[i][j]);
            womenPref[i][j]--;
        }
    }

  

    fclose(file);
    int **result = stableMarriage(n, menPref, womenPref);
    
    printf("Solution:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Free the allocated memory
    for (int i = 0; i < n; i++) {
        free(menPref[i]);
        free(womenPref[i]);
    }
    free(menPref);
    free(womenPref);
    free(result);

    return 0;
}
