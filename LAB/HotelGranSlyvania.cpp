#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100
#define getch while(getchar()!='\n')
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

int main(){

    return 0;
}