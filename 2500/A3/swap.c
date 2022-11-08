#include "headerA3.h"
#include "helper.h"

/******
swap: switches two values
 In: a, b
 Out: NONE
 Post: swaps two tweets in a list
*******/
void swap(tweet *a, tweet *b)
{
    //Swaps two nodes
    int temp = a->id;
    a->id = b->id;
    b->id = temp;
}