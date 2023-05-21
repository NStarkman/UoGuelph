#include "P2.h"
#include "P2Extra.h"

void bruteConvexHull(Point *points, int n, Point *hull, int *hullSize, int *operations)
{
    int i, j, k, p1, p2;
    int leftmost = 0;
    for (i = 1; i < n; i++)
    {
        if (points[i].x < points[leftmost].x)
        {
            leftmost = i;
        }
    }
    j = leftmost;
    *hullSize = 0;
    do
    {
        hull[*hullSize] = points[j];
        (*hullSize)++;
        k = (j + 1) % n;
        for (i = 0; i < n; i++)
        {
            (*operations)++;
            if (findSide(points[j], points[i], points[k]) > 0)
            {
                k = i;
            }
        }
        j = k;
    } while (j != leftmost);
    displayPoints(hull, *hullSize);
    printf("What are the two points you would like to find the shortest distance between?\n");
    scanf("%d %d", &p1, &p2);
    shortestPathOnConvexHull(points, n, hull, *hullSize, p1 - 1, p2 - 1);
}

int main()
{
    int numPoints = 0, numOperations = 0;
    char fileName[128] = "data_A2_Q2.txt";
    Point *pointList = readPointsFromFile(fileName, &numPoints);
    Point *hull = (Point *)malloc(numPoints * sizeof(Point));
    int hullSize;

    clock_t startTime = clock();
    bruteConvexHull(pointList, numPoints, hull, &hullSize, &numOperations);

    clock_t endTime = clock();
    printf("Operations: %d\n", numOperations);
    printf("Finished 2.1 in %.4lf seconds.\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

    free(hull);
    free(pointList);
    return 0;
}