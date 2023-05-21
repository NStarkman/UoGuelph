# Assignemnt 3: CIS*3490

## Description

There are 4 main C files in this project. The first is P11.c, which is the brute force method for the first part. P12.c is the merge sort version of the same concept. P21.c is the brute force method for the string search problem, and P22.c is the Horspool method for the same problem. P23.c is the Boyer-Moore solution. The makefile is used to compile the files, and creates an executable for each of the 4 files.

## Compilation

```C
    make
    ./P11 //Runs the brute force method for the first part
    ./P12 //Runs the merge sort method for the first part

    ./P21 //Runs the brute force method for the second part
    ./P22 //Runs the Horspool method for the second part
    ./P23 //Runs the Boyer-Moore method for the second part

```

## Issues and Limiations

There are none, to my knowledge.

## Analysis

BRUTE:

    PATTERN  - SHIFTS  - TIME  - SHIFTS/MS

    maintain - 3296459 - 16 ms - 206028.59/ms
    of - 3272829 - 20 ms - 163641.45/ms
    university - 3296417 - 16 ms - 206026.06/ms
    Fall - 3296399 - 15 ms - 219759.93/ms
    health - 3296490 - 15 ms - 219766/ms
    procure - 3296596 - 17 ms - 193917.41/ms
    education - 3296381 - 23 ms - 143320.91/ms
    posted - 3296593 - 15 ms - 219772.87/ms
    as - 3284893 - 17 ms - 193229/ms
    protect - 3296575 - 14 ms - 235469.64


    TOTAL BRUTE: 200093.186 shifts/ms

HORSPOOL:

    PATTERN  - SHIFTS - TIME - SHIFTS/MS

    maintain - 499487 - 6 ms - 83247.83/ms
    of - 1691158 - 23 ms - 73528.61/ms
    university - 430557 - 5 ms - 86111.4/ms
    Fall - 877356 - 11 ms - 79759.63636/ms
    health - 639450 - 8 ms - 79931.25/ms
    procure - 523103 - 7 ms - 74729/ms
    education - 460187 - 6 ms - 76697.83/ms
    posted - 653488 - 8 ms - 81686/ms
    as - 1697558 - 21 ms - 80836.09524/ms
    protect - 572512 - 7 ms - 81787.42857/ms


    TOTAL HORSPOOL: 79831.50802 shifts/ms

The result of this analysis is that the Horspool method is much faster than the brute force method. The Horspool method is also much more efficient than the brute force method, as it only shifts the pattern by 1 character when it does not match, whereas the brute force method shifts the pattern by the length of the pattern when it does not match. The Horspool method is also much more efficient than the brute force method, as it only shifts the pattern by 1 character when it does not match, whereas the brute force method shifts the pattern by the length of the pattern when it does not match.

## Author Information

* Nathan Starkman
* 1127811
* nstarkma@uoguelph.ca
