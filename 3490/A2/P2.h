
#include "P2Extra.h"

void bruteConvexHull(Point *points, int n, Point *hull, int *hullSize, int *operations);
void findConvexHull(Point *arr, int len, int *operations);
void findHalfHull(Point *points, int length, Point leftmost, Point rightmost, Point *finalResult, int *resultCount, int *operations);
