#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_TABLE_SIZE 1000

struct Booking {
    char name[255];
    char phoneNum[15];
    char roomType[10];
    int age;
    int stayDuration;
    char bookingID[10];
    Booking *next;
}*bookings[HASH_TABLE_SIZE];

Booking *createBooking(char *name, char *phoneNum, char *roomType, int age, int stayDuration) {
    Booking *newBooking = (Booking*)malloc(sizeof(Booking));
    strcpy(newBooking->name, name);
    strcpy(newBooking->phoneNum, phoneNum);
    strcpy(newBooking->roomType, roomType);
    newBooking->age = age;
    newBooking->stayDuration = stayDuration;
    strcpy(newBooking->bookingID, generateID(roomType));
    newBooking->next = NULL;
    return newBooking;
}

void pushHash(Booking *newBooking) {
    int key = getHashKeyMidSquare(newBooking->bookingID);
    if(bookings[key] == NULL) {
        bookings[key] = newBooking;
    } else {
        Booking *temp = bookings[key];
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBooking;
    }
}

bool popHash(char *id) {
    int key = getHashKeyMidSquare(id);
    if(bookings[key] == NULL) {
        return false;
    } else if(strcmp(bookings[key]->bookingID, id) == 0) {
        Booking *temp = bookings[key];
        bookings[key] = bookings[key]->next;
        free(temp);
        return true;
    } else {
        Booking *temp = bookings[key];
        while(temp->next != NULL && strcmp(temp->next->bookingID, id) != 0) {
            temp = temp->next;
        }
        Booking *toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        return true;
    }
    return false;
}

void printMenu();
void enterToContinue();
char* generateID(char *roomtype);
int getHashKeyMidSquare(char *id);

int main() {
    do{
        int input = -1;
        printMenu();
        do{
            printf(">> ");
            scanf("%d", &input);
            printf("Invalid option, please try again: ");
        }while(input < 1 || input > 4);
    }while(1);
    return 0;
}

void printMenu() {
    system("clear");
    puts("1. Booking Hotel");
    puts("1. View Booking");
    puts("1. Delete Booking");
    puts("1. Exit");
}

void enterToContinue() {
    printf("Press Enter to continue...");
    getchar();
}

char* generateID(char *roomtype) {
    char *id = (char*)malloc(10);
    sprintf(id, "%c%c%d%d%d", toupper(roomtype[0]), toupper(roomtype[1]), rand() % 10, rand() % 10, rand() % 10);
    return id;
}

// Mid Square Method
int getHashKeyMidSquare(char *id) {
    // Urutan Mid Square Method
    // Jumlahin semuanya, kuadratin, ambil tengahnya
    // Kalo banyak digitnya ganjil, ambil langsung tengahnya
    // kalo banyak digitnya genap, ambil 2 digit tengahnya
    // misal 1234, ambil 23
    int sumID = 0;
    for(int i = 2; i < 5; i++) {
        sumID += id[i] - '0';
    }
    char string[10000000];
    sumID *= sumID;
    sprintf(string, "%d", sumID);
    int len = strlen(string);
    int key = 0;
    if(len % 2 == 1) {
        key = string[len / 2] - '0';
    } else {
        char mid[3] = {string[len / 2 - 1], string[len / 2], '\0'};
        key = atoi(mid);
    }
    return key % HASH_TABLE_SIZE;
}

