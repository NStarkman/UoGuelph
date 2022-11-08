#include "headerA3.h"
#include "helper.h"

/******
clearList: frees all data from the linked list
 In: head
 Out: NONE
 Post: All of the data from all of the dynamically allocated tweets are freed.
*******/
void clearList(tweet * head) {
    

    //Goes through the linked list and frees all nodes
    tweet* curr = head;
    tweet* temp = head;
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
}