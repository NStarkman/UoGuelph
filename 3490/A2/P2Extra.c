#include "P2Extra.h"

Point *readPointsFromFile(char *fileName, int *pointsCount)
{
    FILE *fp = NULL;
    char line[LINE_LENGTH];

    if ((fp = fopen(fileName, "r")) == NULL)
    {
        fprintf(stderr, "Error - Could not open file '%s'.\n", fileName);
        exit(0);
    }

    char *token;
    const char separator[2] = " ";
    int inputPointCount = 0;
    Point *inputPoints = (Point *)malloc(sizeof(Point));

    while (fgets(line, LINE_LENGTH, fp) != NULL)
    {
        int count = 0;
        Point currentPoint;
        if (inputPointCount > 0)
        {
            inputPoints = (Point *)realloc(inputPoints, sizeof(Point) * (inputPointCount + 1));
        }

        strtok(line, "\n");
        token = strtok(line, separator);

        while (token != NULL)
        {
            if (count == 0)
            {
                currentPoint.x = atof(token);
            }
            else
            {
                currentPoint.y = atof(token);
            }
            count++;
            token = strtok(NULL, separator);
        }
        inputPoints[inputPointCount++] = currentPoint;
    }
    *pointsCount = inputPointCount;
    if (fp)
    {
        fclose(fp);
    }
    return inputPoints;
}

double findSide(Point pointA, Point pointB, Point pointC)
{
    return (pointB.y - pointA.y) * (pointC.x - pointB.x) - (pointB.x - pointA.x) * (pointC.y - pointB.y);
}

void displayPoints(Point *pointsArray, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%d.     %.1lf, %.1lf\n", i + 1, pointsArray[i].x, pointsArray[i].y);
    }
    printf("Found with %d points\n", count);
}

int compareXCoordinates(const void *a, const void *b)
{
    Point *ptA = (Point *)a;
    Point *ptB = (Point *)b;

    double aX = (double)ptA->x;
    double bX = (double)ptB->x;

    if (aX > bX)
    {
        return 1;
    }
    else if (aX < bX)
    {
        return -1;
    }

    return 0;
}

int isPointInArray(Point *pointsArray, int count, Point currentPoint)
{
    for (int i = 0; i < count; i++)
    {
        if (pointsArray[i].x == currentPoint.x && pointsArray[i].y == currentPoint.y)
        {
            return i;
        }
    }
    return -1;
}

double distance(Point p1, Point p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

void cleanPointList(Point *pointsArray, int *pointsCount)
{
    for (int i = 0; i < *pointsCount; i++)
    {
        int numberOfOccurrences = 0;
        int firstIndex = -1;
        int lastIndex = -1;

        for (int j = 0; j < *pointsCount; j++)
        {
            if (pointsArray[j].x == pointsArray[i].x)
            {
                numberOfOccurrences++;
                if (firstIndex == -1)
                {
                    firstIndex = j;
                }
            }
        }
        if (numberOfOccurrences > 2)
        {
            for (int j = *pointsCount - 1; j >= 0; j--)
            {
                if (pointsArray[j].x == pointsArray[i].x)
                {
                    lastIndex = j;
                    break;
                }
            }
            int k = 0;
            *pointsCount -= numberOfOccurrences - 2;
            for (int j = firstIndex + 1; j < *pointsCount; j++)
            {
                pointsArray[j] = pointsArray[lastIndex + (k++)];
            }
        }
    }
}

void shortestPathOnConvexHull(Point *points, int n, Point *hull, int hullSize, int pIndex1, int pIndex2)
{
    srand(time(NULL));
    int p1Index = pIndex1;
    int p2Index = pIndex2;
    Point p1 = hull[p1Index];
    Point p2 = hull[p2Index];
    printf("Shortest path between (%.2lf, %.2lf) and (%.2lf, %.2lf) on the convex hull:\n", p1.x, p1.y, p2.x, p2.y);
    int i, j;
    double length = 0;
    double orientation = 0;
    for (i = 0; i < hullSize; i++)
    {
        j = (i + 1) % hullSize;
        orientation += (hull[j].x - hull[i].x) * (hull[j].y + hull[i].y);
    }
    orientation /= 2.0;
    if (orientation > 0)
    {
        if (p1Index < p2Index)
        {
            for (i = p1Index; i != p2Index; i = (i + 1) % hullSize)
            {
                printf("(%.2lf, %.2lf) -> ", hull[i].x, hull[i].y);
                length += distance(hull[i], hull[(i + 1) % hullSize]);
            }
        }
        else
        {
            for (i = p1Index; i != p2Index; i = (i - 1 + hullSize) % hullSize)
            {
                printf("(%.2lf, %.2lf) -> ", hull[i].x, hull[i].y);
                length += distance(hull[i], hull[(i - 1 + hullSize) % hullSize]);
            }
        }
    }
    else
    {
        if (p1Index < p2Index)
        {
            for (i = p1Index; i != p2Index; i = (i - 1 + hullSize) % hullSize)
            {
                printf("(%.2lf, %.2lf) -> ", hull[i].x, hull[i].y);
                length += distance(hull[i], hull[(i - 1 + hullSize) % hullSize]);
            }
        }
        else
        {
            for (i = p1Index; i != p2Index; i = (i + 1) % hullSize)
            {
                printf("(%.2lf, %.2lf) -> ", hull[i].x, hull[i].y);
                length += distance(hull[i], hull[(i + 1) % hullSize]);
            }
        }
    }
    printf("(%.2lf, %.2lf)\n", hull[p2Index].x, hull[p2Index].y);
    length += distance(p1, hull[p1Index + 1]) + distance(p2, hull[p2Index - 1]);
    printf("Length: %.2lf\n", length);
}
