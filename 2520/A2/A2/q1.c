/******
Assignment 2
 Name:Nathan Starkman
 Student Number: 1127811
 Date: October 21st, 2022
*******/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define AMNTMILEAGE 600
#define AMNTRETDATE 601
#define MAX 9999
#define STACKAMNT 15

typedef struct CarStats
{
    int  mileage;
    int returnDate;
    double charge;
    char* plate;

    struct CarStats *next;

}CarStats;

CarStats *createNode(int newMileage, int returnDate, double charge, char* newPlate);
CarStats *addNodeToList(CarStats *head, CarStats *node, int sortType);
CarStats* deleteNode(CarStats** head, char* plate);
void saveList(CarStats *head, char* fileName);
CarStats* loadList(CarStats *head, char* fileName, int sortType);
void printList(CarStats *head);
CarStats* mileageUpdate(CarStats* node, int mileage);
CarStats* chargeUpdate(CarStats* node, double charge);
CarStats* returnDateUpdate(CarStats* node, int returnDate);
char printMenu(void);
CarStats* addToAvailable(CarStats *availHead);
void rentAvailCar(CarStats** availHead, CarStats** rentHead);
double getCharge(double lastAmount, double newAmount);
void returnCar(CarStats**sendList, CarStats**sourceList, int sendCode);
void repairCar(CarStats** rentHead,CarStats** repairHead);
void repairToAvail(CarStats** availHead, CarStats**repairHead);
double finalCharge(CarStats* head);

int main(){
    char userInput = '0';
    CarStats* availHeadList= NULL;
    CarStats* rentHeadList= NULL;
    CarStats* repairHeadList = NULL;
    double totalCharge = 0.00;

    //Loads files to linked lists to add information
    availHeadList = loadList(availHeadList, "Available.txt", AMNTMILEAGE);
    rentHeadList = loadList(rentHeadList, "Rented.txt", AMNTRETDATE);
    repairHeadList = loadList(repairHeadList, "AtWkshop.txt", AMNTMILEAGE);

    while(userInput != '7'){
        userInput = printMenu();
        //Calls functions for each menu option
        switch (userInput){

        case '1':
            availHeadList = addToAvailable(availHeadList);
            break;
        case '2':
            returnCar(&availHeadList, &rentHeadList, 0);
            break;
        case '3':
            repairCar(&rentHeadList, &repairHeadList);
            break;
        case '4':
			repairToAvail(&availHeadList, &repairHeadList);	
			break;
        case '5':
			rentAvailCar(&availHeadList, &rentHeadList);
            
			break;
		case '6':
            printf("\n\nAVAILABLE LIST");
			printf("\n_______________________");
			printList(availHeadList);
			printf("\n\nRENTED LIST");
			printf("\n_______________________");
			printList(rentHeadList);
			printf("\n\nREPAIR LIST");
			printf("\n_______________________");
			printList(repairHeadList);
			printf("\nPress Enter to return to menu\n");
			getchar();
			getchar();
			break;
        case '7':
            //Creates a total charge for all the linked lists
            totalCharge += finalCharge(availHeadList);
		    totalCharge += finalCharge(rentHeadList);
			totalCharge += finalCharge(repairHeadList);
			printf("\nThe total charge is: %0.2lf\n", totalCharge);
			break;
        default:
            printf("\nThere is no Option on that menu. Try again.\n");
            break;
        }
    }
    //Saves the linked lists back to files
    saveList(availHeadList, "Available.txt");
	saveList(rentHeadList, "Rented.txt");
	saveList(repairHeadList, "AtWkshop.txt");
	getchar();
	return 0;
}

/******
createNode: Creates a new node with updated information
 In: newMileage, newReturnDate, newCharge newPlate
 Out: node
 Post: creates a node that can be added with the given information
*******/


CarStats*createNode(int newMileage, int newReturnDate, double newCharge, char* newPlate){
    CarStats *node;

    node = (CarStats * )malloc(sizeof(CarStats));
    node->plate = (char *)malloc(sizeof(char));
    if (node==NULL){
        return NULL;
    }
    node->mileage = newMileage;
    node->charge = newCharge;
    node->returnDate = newReturnDate;
    strcpy(node->plate, newPlate);
    node->next = NULL;


    return node;
}

/******
addNodeToList: Adds the new node to the specific linked list
 In: head, node, sortType
 Out: node
 Post: Returns the linked list with the new node added
*******/
CarStats* addNodeToList(CarStats *head, CarStats *node, int sortType){
    CarStats* currNode = NULL;
    CarStats* past = NULL;
    CarStats* next = NULL;

    if (head == NULL){
        head = node;
    }
    else{
        past = head;
        currNode = head;
        while(currNode!=NULL){
            next = currNode->next;
            if (sortType==AMNTMILEAGE){
                if (currNode->mileage >= node->mileage){
                    break;
                }
            }
            else if (sortType==AMNTRETDATE){
                if (currNode->returnDate >= node->returnDate){
                    break;
                }
            }
            past = currNode;
            currNode = next;
        }
        if (head == currNode){
            head = node;
        }
        else{
            past->next = node;
        }
        node->next = currNode;
    }
    return head;
}

/******
deleteNode: Removes specific node from linked list
 In: head, plate
 Out: currNode, NULL
 Post: Updates the linked list by removing the specified node
*******/

CarStats* deleteNode(CarStats** head, char* plate){
    CarStats* currNode = NULL;
    CarStats* past = NULL;
    CarStats* next = NULL;

     if (*head == NULL){
        return *head;
    }
    else{
        past = *head;
        currNode = *head;
        while(currNode !=NULL){
            next = currNode->next;
            if (strcmp(currNode->plate, plate)==0){
                break;
            }
            past = currNode;
            currNode = next;
        }
        if (*head==currNode){
            *head = currNode->next;
        }
        else{
            if (currNode !=NULL){
                past->next = currNode->next;
            }
        }
        if (currNode !=NULL){
            currNode ->next = NULL;
        }
        return currNode;
    }
    return NULL;
}

/******
saveList: Updates the file for the specific list with the information in the linked list
 In: head, fileName
 Out: node
 Post: All information in specified linked list is added to the file specified
*******/
void saveList(CarStats *head, char* fileName){
    FILE *fptr = fopen(fileName, "w");
    CarStats * currNode = head;

    if (fptr==NULL){
        printf("FAILED TO SAVE STATS TO FILE\n");
        return;
    }
    if (currNode != NULL){
        do{
            fprintf(fptr, "%d %d %lf %s\n", currNode->mileage, currNode->returnDate, currNode->charge, currNode->plate);
            currNode = currNode->next;
        }while(currNode !=NULL);
    }
    fclose(fptr);
}

/******
loadList: loads information from file to be added to linked list
 In: head, sortType, sortType
 Out: head
 Post: Returns the linked list with the loaded information
*******/
CarStats* loadList(CarStats *head, char* fileName, int sortType){
    FILE * fptr = fopen(fileName, "r");
    char listLine[MAX];
    int i;
    int mileage;
    int returnDate;
    double charge;
    char plate[MAX];
    char * data;

    while(fgets(listLine, MAX, fptr)!=NULL){
        i = 0;
        data = strtok(listLine, " ");
        while(data !=NULL){
            switch (i){
                case 0:
                    mileage = atoi(data);
                case 1:
                    returnDate = atoi(data);
                case 2:
                    charge = atoi(data);
                case 3:
                    strcpy(plate, data);
            }
            i++;
            data = strtok(NULL, " ");
        }
        if (plate[strlen(plate)-1]<33){
            plate[strlen(plate)-1]=0;
        }
        head = addNodeToList(head, createNode(mileage,returnDate,charge,plate), sortType);
    }
    fclose(fptr);
    return head;
}

/******
printList: Prints the entire list with their specified information labeled
 In: head
 Out: node
 Post: Prints linked list
*******/
void printList(CarStats *head){
    CarStats *currNode = head;
    if (currNode !=NULL){
        //system("clear");
        do{
            printf("\nPlate: %s", currNode->plate);
            printf("\nMileage: %d", currNode->mileage);
            printf("\nReturn Date: %d", currNode->returnDate);
            printf("\nCharge: %0.2lf", currNode->charge);
            printf("\n");
            currNode = currNode->next;
        }while (currNode !=NULL);   
    }
}
/******
mileageUpdate: Updates mileage at a specific node in a linked list
 In: head, node, mileage
 Out: node
 Post: the mileage at the node was updated
*******/
CarStats* mileageUpdate(CarStats*node, int mileage){
    node->mileage=mileage;
    return node;
}
/******
chargeUpdate: Updates charge at a specific node in a linked list
 In: head, node, charge
 Out: node
 Post: the charge at the node was updated
*******/
CarStats* chargeUpdate(CarStats*node, double charge){
    node->charge +=charge;
    return node;

}
/******
mileageUpdate: Updates return date at a specific node in a linked list
 In: head, node, returnDate
 Out: node
 Post: the returnDate at the node was updated
*******/
CarStats* returnDateUpdate(CarStats*node, int returnDate){
    node->returnDate +=returnDate;
    return node;
}

/******
printMenu: Prints the menu for player query
 In: none
 Out: getchar()
 Post: returns the specific menu option requested by the user
*******/
char printMenu(){
    printf("1. add a new car to the available-for-rent list\n");
    printf("2. add a returned car to the available-for-rent list\n");
    printf("3. add a returned car to the repair list\n");
    printf("4. transfer a car from the repair list to the available-for-rent list\n");
    printf("5. rent the first available car\n");
    printf("6. Print All Lists\n");
    printf("7. Quit\n");
    printf("\nChoice: \n");
    return (getchar());
}
/******
addToAvailable: Adds new car node to the available cars linked list
 In: availHead
 Out: availHead
 Post: adds new node to the available cars linked list
*******/
CarStats* addToAvailable(CarStats* availHead){
    int mileage = 0;
    char plate[10];

    printf("Please enter mileage: ");
    scanf("%d", &mileage);
    getchar();
    printf("Please enter plate: ");
    scanf("%s", plate);
    getchar();
    
    if (strlen(plate) >8 || strlen(plate)<2){
		printf("\nPLATE NUMBER UNACCESSABLE\n");
		return availHead;
	}
    availHead = addNodeToList(availHead, createNode(mileage, 0,0.00, plate),AMNTMILEAGE);
    printf("\nThe Car has Been Added to the Available List\n\n");

    return availHead;
}

/******
rentAvailCar: Rents the first available car on the available list and adds to the rented list
 In: availHead, rentHead
 Out: node
 Post: tthe most recent and available car in the available list is added to the rented list
*******/
void rentAvailCar(CarStats** availHead, CarStats** rentHead){
    
    int returnDate = 0;
    CarStats * node = NULL;

    printf("Enter Return Date: (YYMMDD)");
    scanf("%d", &returnDate);
    getchar();
    if (returnDate < 221022){
        printf("RETURN DATE TOO EARLY\n\n");
        return;
    }

    node = deleteNode (availHead, (*availHead)->plate);
    if (node ==NULL){
        printf("Car was Not in List\n\n");
        return;
    }
    node = returnDateUpdate(node, returnDate);
    *rentHead = addNodeToList(*rentHead, node, AMNTRETDATE);
    printf("\nYou have rented the first available car. it is not in the Rented List\n\n");
}
/******
getCharge: gets the charge of the rented car after return
 In: lastAmount, newAmount
 Out: new car charge
 Post: The charge of the return car is updated based on the formula
*******/
double getCharge(double lastAmount, double newAmount){
    double extraMileage = newAmount - lastAmount;
    if(extraMileage <=200.0){
        return 80.0;
    }
    else{
        return (80.0 +((extraMileage-200)*0.15));
    }

    return 0;
}

/******
returnCar: returns the car to the desired linked list
 In: sendList, sourceList, sendCode
 Out: node
 Post: rented car is added to one of the other two linked lists
*******/
void returnCar(CarStats**sendList, CarStats**sourceList, int sendCode){
    char plate[10];
    int mileage = 0;
    double charge = 0;
    CarStats* node = NULL;

    printf("Enter your plate to return: ");
    scanf("%s", plate);
    getchar();
    printf("Enter your the new mileage: ");
    scanf("%d", &mileage);
    getchar();

    node = deleteNode(sourceList, plate);
    if (node == NULL){
        printf("Car was not found\n\n");
        return;
    }
    charge = getCharge(node->mileage, mileage);

    node = chargeUpdate(node, charge);
    node = mileageUpdate(node, mileage);
    node = returnDateUpdate(node, 0);

    *sendList = addNodeToList(*sendList, node, AMNTMILEAGE);

    if (sendCode == 0){
        printf("\n Car has been returned to the Available List.\n\n");
    }
    else{
        printf("\n Car has been returned to the Repair List.\n\n");
    }
}

/******
repairCar: Sends the returned car to the workshop linked list
 In: rentHead, repairHead
 Out: node
 Post: Sends the returned car to the workshop linked list
*******/
void repairCar(CarStats** rentHead,CarStats** repairHead){
    returnCar(repairHead, rentHead, 1);
}

/******
repairToAvail: Sends a repaired car to the available car list
 In: availHead, repairHead
 Out: node
 Post: moves the specified car to the available linked list
*******/
void repairToAvail(CarStats** availHead, CarStats**repairHead){
    char plate [10];
    CarStats * node = NULL;

    printf("Enter Plate Number: ");
    scanf("%s", plate);
    node = deleteNode(repairHead, plate);
    if (node == NULL){
        printf("Car Not in the List. Please Try again. \n\n");
        return;
    }
    *availHead = addNodeToList(*availHead, node, AMNTMILEAGE);
    printf("\n The Car has been repaired and Added to the Available List.\n\n");

}

/******
finalCharge: Creates overall charge from all individal car charges
 In: head
 Out: totalCharge
 Post: A final charge of all of the individual charges is added up and returned
*******/
double finalCharge(CarStats* head){
    CarStats *node = head;
    double totalCharge = 0.00;
    if (node !=NULL){
        do{
            totalCharge += node->charge;
            node = node->next;
        }while(node!=NULL);
    }
    return totalCharge;
}
