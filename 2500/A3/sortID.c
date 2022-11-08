#include "headerA3.h"
#include "helper.h"


/******
sortID: sorts link list based on ID number
 In: head
 Out: NONE
 Post: the linked list is ordered based on ID number in ascending order
*******/
void sortID (tweet ** head){
    //swapped: Flag for successful sort
    int swapped;
    // ptr/lptr: pointers for note data 
    tweet *ptr;
    tweet *lptr = NULL;

    if (*head == NULL){
       printf("NO LINKED LIST TO SORT! Please try Again\n");
       return;
    }
    //Checks the linked list and swaps them
    do{
        swapped = 0;
        ptr = *head;
        while(ptr->next !=lptr){
            if (ptr->id > ptr->next->id){
                swap(ptr, ptr->next);
                swapped = 1;
           }
            ptr = ptr->next;
       }
       lptr = ptr;
    }while(swapped);
    printf("Sorted!\n");
}