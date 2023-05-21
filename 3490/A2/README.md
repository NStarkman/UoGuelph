# Assignemnt 2: CIS*3490

## Description

There are 4 main C files in this project. The first is P1.c, which is the brute force method for the first part. P12.c is the recursive, merge sort version of the same concept. P2.c is the brute force method for the convex hull problem, and P22.c is the divide and conquer method for the same problem. The makefile is used to compile the files, and creates an executable for each of the 4 files.

## Compilation

```C
    make
    ./P1 //Runs the brute force method for the first part
    ./P12 //Runs the recursive, merge sort method for the first part
            //NOTE: this method requires file input, WITH the txt extension included in the title
    ./P2 //Runs the brute force method for the second part
    ./P22 //Runs the divide and conquer method for the second part
            //NOTE: This method takes in an input for both of the leftmost and rightmost extreme points. IT IS ASSUMED THAT THE POINTS ARE INCLUDED ON THE HULL

```

## Issues and Limiations

To my knowledge, there are no real limitations to the code, however, distance for my P2 code is different based on if the points are going clockwise vs counterclockwise. Also, thanks to it using the Jarvis method, the first P2 code, the brute force one, is actually faster. It uses more comparisons and is a slower efficiency, but for some reason is faster. Otherwise, I am not aware of any issues in my code.

## Author Information

* Nathan Starkman
* 1127811
* nstarkma@uoguelph.ca
