# Assignemnt 2: CIS*3110 Letter Frequency Calculator

## Description

This program takes a text file and calculates the frequency of each letter in the alphabet. It then prints out the frequency of each letter in the alphabet, and the total number of letters in the file. It does this by forking a new process for each file, and then using pipes to communicate between the processes.

## Running Information

Run the makefile, or the command that is in that makefile. If you just want the running command, which is:

```makefile
    gcc -Wall -g -std=c11 -o A2 A2.c A2.h
```

either that, or just use the makefile

```makefile
    make
```

and to remove the executable

```makefile
    make clean
```

Ensure that the text file to be opened is in the same folder as the code.

## Author Information

* Nathan Starkman
* 1127811
* nstarkma@uoguelph.ca
