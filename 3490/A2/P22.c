#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "P2.h"
#include "P2Extra.h"

void findConvexHull(Point *points, int length, int *operations)
{
    if (length < 3)
    {
        printf("Set was not meeting size parameters.\n");
        return;
    }

    qsort(points, length, sizeof(Point), compareXCoordinates);
    Point leftmost = points[0];
    Point rightmost = points[length - 1];

    Point aboveLine[length], belowLine[length], finalResult[length];
    int aboveLineCount = 0;
    int belowLineCount = 0;
    int finalResultCount = 0;
    int p1, p2;

    for (int i = 0; i < length; i++)
    {
        double value = findSide(leftmost, rightmost, points[i]);
        (*operations)++;
        if (value < 0)
            aboveLine[aboveLineCount++] = points[i];
        else if (value > 0)
            belowLine[belowLineCount++] = points[i];
    }
    findHalfHull(aboveLine, aboveLineCount, leftmost, rightmost, finalResult, &finalResultCount, operations);
    findHalfHull(belowLine, belowLineCount, rightmost, leftmost, finalResult, &finalResultCount, operations);

    qsort(finalResult, finalResultCount, sizeof(Point), compareXCoordinates);
    cleanPointList(finalResult, &finalResultCount);
    displayPoints(finalResult, finalResultCount);
    printf("What are the two points you would like to find the shortest distance between?\n");
    scanf("%d %d", &p1, &p2);
    shortestPathOnConvexHull(points, length, finalResult, finalResultCount, p1 - 1, p2 - 1);
}

void findHalfHull(Point *points, int length, Point leftmost, Point rightmost, Point *finalResult, int *resultCount, int *operations)
{
    if (!points || length == 0)
        return;

    double maxValue = 0;
    int maxIndex = -1;

    for (int i = 0; i < length; i++)
    {
        double value = findSide(leftmost, rightmost, points[i]);
        (*operations)++;
        if (findSide(leftmost, rightmost, points[i]) < 0 && value < maxValue)
        {
            maxIndex = i;
            maxValue = value;
        }
    }

    if (maxIndex == -1)
    {
        if (isPointInArray(finalResult, *resultCount, leftmost) == -1)
        {
            finalResult[(*resultCount)++] = leftmost;
        }
        if (isPointInArray(finalResult, *resultCount, rightmost) == -1)
        {
            finalResult[(*resultCount)++] = rightmost;
        }
        return;
    }
    findHalfHull(points, length, leftmost, points[maxIndex], finalResult, resultCount, operations);
    findHalfHull(points, length, points[maxIndex], rightmost, finalResult, resultCount, operations);
}

int main()
{
    int numPoints = 0, numOperations = 0;
    char fileName[128] = "data_A2_Q2.txt";
    Point *pointList = readPointsFromFile(fileName, &numPoints);

    clock_t startTime = clock();
    findConvexHull(pointList, numPoints, &numOperations);
    clock_t endTime = clock();
    printf("Operations: %d\n", numOperations);
    printf("Finished Recursive Convex Hull in %.4lf seconds.\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

    free(pointList);
    return 0;
}