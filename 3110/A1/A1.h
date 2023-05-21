#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define MODE_ASCII 0
#define MODE_HEX 1

void displayASCII(char * buffer, int size);
void displayHEX(char * buffer, int size);
