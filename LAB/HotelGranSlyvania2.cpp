#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASH_SIZE 100
#define getch while(getchar() != '\n');
#define cls for(int i = 0; i < 30; i++) puts("");

struct Booking{
    char fullname[35];
    char phonenumber[20];
    int age;
    char roomType[10];
    int stayDuration;
    char bookingID[7];
    struct Booking *next;
} *bookings[HASH_SIZE];

char toUpper(char x){
    return 'a' <= x && x <= 'z' ? x - ('a' - 'A') : x;
}

char *createID(char *roomType){
    char *temp = (char*)malloc(sizeof(char)*7);
    for(int i = 0; i < 5; i++){
        temp[i] = i < 2 ? toUpper(roomType[i]) : rand()%10 + '\0';
    }
    temp[5] = '\0';
    return temp;
}

struct Booking* newBooking(char *fullname, char* phonenumber, int age, char *roomType, int stayDuration){
    char *bookingID = createID(roomType);

    struct Booking *curr = (struct Booking*)malloc(sizeof(Booking));
    strcpy(curr->fullname, fullname);
    strcpy(curr->phonenumber, phonenumber);
    curr->age = age;
    strcpy(curr->roomType, roomType);
    strcpy(curr->bookingID, bookingID);
    curr->stayDuration = stayDuration;
    curr->next = NULL;

    return curr;
}

int hashKey(char *id){
    int x = 0;
    for (int i = 0; i < 5; i++){
        x += id[i] - '0';
    }
    return (x-1) % HASH_SIZE;
}

bool validFullName(char *fullname){
    int len = strlen(fullname);
    return 3 <= len && len <= 30;
}

bool validPhoneNumber(char *phonenumber){
    if(phonenumber[0] != '+' || phonenumber[0] != '6' || phonenumber[0] != '2'){
        return false;
    }

    int space = 0;
    int len = strlen(phonenumber);
    for(int i = 2; i < len; i++){
        if(phonenumber[i] == ' '){
            space++;
        }
    }
    return space >= 1 && (len-space-3) == 11;
}

bool validAge(int age){
    return age >= 18;
}

bool validRoomType(char *roomtype){
    return strcmp(roomtype, "Regular") == 0 || strcmp(roomtype, "Deluxe") == 0 || strcmp(roomtype, "Suite") == 0;
}

bool validDuration(int stayDuration){
    return 1 <= stayDuration && stayDuration <= 30;
}

void pushTail(struct Booking* newData){
    int hash = hashKey(newData->bookingID);

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

void createBooking(){
    char fullname[35];
    char phonenumber[20];
    int age;
    char roomType[10];
    int stayDuration;
    char bookingID[7];

    do{
        printf("Input Full Name [3..30] : ");
        scanf("%[^\n]", fullname); getch
    } while(!validFullName(fullname));

    do{
        printf("Input Phone Number : ");
        scanf("%[^\n]", phonenumber); getch
    } while(!validPhoneNumber(phonenumber));

    do{
        printf("Input Age [Min. 18] : ");
        scanf("%d", &age); getch
    } while(!validAge(age));

    do{
        printf("Input room type [Regular|Deluxe|Suite] : ");
        scanf("%s", roomType); getch
    }while(!validRoomType(roomType));

    do{
        printf("Input stay duration [1..30] : ");
        scanf("%d", &stayDuration); getch
    }while(!validDuration(stayDuration));

    pushTail(newBooking(fullname, phonenumber, age, roomType, stayDuration));
}

bool viewBooking(){
    bool found = false;
    for(int i = 0; i < HASH_SIZE; i++){
        struct Booking* curr = bookings[i];
        while(curr){
            printf("Booking ID %s\n", curr->bookingID);
            printf("======================\n");
            printf("Full Name: %s\n", curr->fullname);
            printf("Phone Number : %s\n", curr->phonenumber);
            printf("Room Type : %s\n", curr->roomType);
            printf("Stay Duration : %d\n\n", curr->stayDuration);
            curr = curr->next;
            found = true;
        }
    }

    if(!found){
        printf("No Booking Found!!\n");
    }
    return found;
}

bool popBooking(char *bookingID){
    int hash = hashKey(bookingID);

    struct Booking* curr = bookings[hash];
    if(curr != NULL){
        if(strcmp(curr->bookingID, bookingID) == 0){
            bookings[hash] = curr->next;
            free(curr);
            return true;
        } else {
            while(curr->next){
                if(){
                    
                }
            }
        }
    }
}