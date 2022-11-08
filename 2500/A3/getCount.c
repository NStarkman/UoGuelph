#include "headerA3.h"
#include "helper.h"

/******
getCount: Calculates the amount of nodes in a linked list
 In: head
 Out: count
 Post: Produces the amount of nodes in the linked list
*******/
int getCount(tweet* head)
{
    //Count: manages the amount of tweets by going through the list and adding one each time it goes through a node
    int count = 0;  
    tweet * current = head;  
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}