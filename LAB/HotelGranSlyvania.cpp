#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASH_SIZE 100
#define getch while(getchar()!='\n');
// define satu variable global buat ukuran hash nya

struct Booking{
    char fullname[35];
    char phoneNumber[20];
    int age;
    char roomType[10];
    int stayDuration;
    char bookingID[7];
    struct Booking *next;
}*bookings[HASH_SIZE];

int getHashKey(char *id){
    int x = 0;
    for(int i = 2; i < 5; i++){
        x += id[i] - '0';
    }
    return (x -1) % HASH_SIZE;
}

bool validFullName(char *fullname){
    int len = strlen(fullname);
    return 3 <= len && len <= 30;
}

bool validPhoneNumber(char *phoneNumber){
    if(phoneNumber[0] != '+' || phoneNumber[1] != '6' || phoneNumber[2] != '2') return false;
    int space = 0;
    int len = strlen(phoneNumber);
    for(int i = 3; i < len; i++){
        if(phoneNumber[i] == ' '){
            space++;
        }
    }
    return space >= 1 && len - (space + 3) == 11;
}

bool validAge(int age){
    return age >= 18;
}

bool validRoomType(char* roomType){
    return strcmp(roomType, "Deluxe") == 0 || strcmp(roomType, "Regular") == 0 || strcmp(roomType, "Suite") == 0;
}

bool validStayDuration(int stayDuration){
    return 1 <= stayDuration && stayDuration <= 30;
}

char toUpper(char x){
    return 'a' < x && x <= 'z' ? x - ('a'-'A') : x;
}

char* generateID(char* roomType){
    // rand() % (max - min) + min
    char* id = (char*)malloc(sizeof(char)*7);
    for(int i = 0; i < 5; i++){
        id[i] = i < 2 ? toUpper(roomType[i]) : rand() % 10 + '0';
    }
    id[5] = '\0';
}

struct Booking* newBooking(char *fullName, char *phoneNumber, int age, char *roomType, int stayDuration){
    char *bookingID = generateID(roomType);
    struct Booking* curr = (struct Booking*)malloc(sizeof(struct Booking));
    strcpy(curr->fullname, fullName);
    strcpy(curr->phoneNumber, phoneNumber);
    curr->age = age;
    strcpy(curr->roomType, roomType);
    curr->stayDuration = stayDuration;
    strcpy(curr->bookingID, bookingID);

    curr->next = NULL;

    return curr;
}

void pushTail(struct Booking* newData){
    int hash = getHashKey(newData->bookingID);
    if(bookings[hash] == NULL){
        bookings[hash] = newData;
    } else {
        struct Booking* curr = bookings[hash];
        while(curr->next){
            curr = curr->next;
        }
        curr->next = newData;
    }
}

void book(){
	char fullname[35];
    char phoneNumber[20];
    int age;
    char roomType[10];
    int stayDuration;
    char bookingID[7];
	
	do{
		printf("Input Name: ");
		scanf("%[^\n]", fullname); getch
	}while(!validFullName);
	
	do{
		printf("Input Number: ");
		scanf("%[^\n]", phoneNumber); getch
	}while(!validPhoneNumber);
	
	do{
		printf("Input Age: ");
		scanf("%d", &age); getch
	}while(age < 18);
	
	do{
		printf("Input Roomtype: ");
		scanf("%[^\n]", roomType); getch
	}while(strcmp(roomType, "Regular") != 0 &&
		strcmp(roomType, "Deluxe") != 0 &&
		strcmp(roomType, "Suite") != 0);	
	do{
		printf("Input Duration: ");
		scanf("%d", &stayDuration);getch
	}while(stayDuration < 1 || stayDuration > 30);

    pushTail(newBooking(fullname, phoneNumber, age, roomType, stayDuration));
}

void pushHead(struct Booking* newData){
    int hash = getHashKey(newData->bookingID);
    struct Booking* curr = bookings[hash];
    newData->next = curr;
    bookings[hash] = newData;
}

void createBooking(){
    char fullname[35];
    char phoneNumber[20];
    int age;
    char roomType[10];
    int stayDuration;

    printf("Input Name:");
    scanf("%[^\n]", fullname);
    
    printf("Input Phone Number:");
    scanf("%[^\n]", phoneNumber);
    
    printf("Input Age:");
    scanf("%d", &age);
    
    printf("Input Room Type:");
    scanf("%[^\n]", roomType);
    
    printf("Input Stay Duration:");
    scanf("%d", &stayDuration);
}

bool viewBooking(){
    bool found = false;
    for(int i = 0; i < HASH_SIZE; i++){
        struct Booking *curr = bookings[i];
        while(curr){
            printf("Booking ID: %s\n", curr->bookingID);
            curr = curr->next;
            found = true;
        }
    }
    if(!found){
        puts("Not found");
    }
    return found;
}

bool pop(char *bookingID){
    int hash = getHashKey(bookingID);
    struct Booking *curr = bookings[hash];
    if(strcmp(curr->bookingID, bookingID) == 0){
        bookings[hash] = curr->next;
        free(curr);
    } else {
        while(curr->next){
            if(strcmp(curr->next->bookingID, bookingID) == 0){
                struct Booking *temp = curr->next;
                curr->next = temp->next;
                free(temp);
                return true;
            }
            curr = curr->next;
        }
    }
    return false;
}

void deleteBooking(){
    if(!viewBooking()){
        return;
    }

    char bookingID[7];
    printf("Input Booking ID: ");
    scanf("%[^\n]", bookingID);
    pop(bookingID);
}

int main(){
    srand(time(NULL));
    int menu = 0;
    do{
        puts("1. Insert");
        puts("2. View");
        puts("3. Delete");
        puts("4. Exit");
        scanf("%d", &menu); getch
        switch (menu){
            case 1:
                createBooking();
                break;
            case 2:
                viewBooking();
                break;
            case 3:
                deleteBooking();
                break;
            case 4:
                return 0;
        }
    }while(menu != 4);
    return 0;
}