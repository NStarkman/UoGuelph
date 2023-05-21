#ifndef P2EXTRA_H
#define P2EXTRA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define LINE_LENGTH 256

typedef struct
{
    double x, y;
} Point;

Point *readPointsFromFile(char *name, int *len);
void displayPoints(Point *arr, int len);
double findSide(Point a, Point b, Point c);
int isPointInArray(Point *arr, int len, Point p);
int compareXCoordinates(const void *a, const void *b);
void cleanPointList(Point *arr, int *len);
double hullLength(Point *pointsArray, int arrayLen);
double distance(Point p1, Point p2);
void shortestPathOnConvexHull(Point *points, int n, Point *hull, int hullSize, int p1, int p2);
double squareRoot(double x);
#endif