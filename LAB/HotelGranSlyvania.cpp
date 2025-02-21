#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 100
// define satu variable global buat ukuran hash nya

struct Booking{
    char fullname[35];
    char phoneNumber[20];
    int age;
    char roomType[10];
    int stayDuration;
    char bookingID[7];
    struct Booking *next;
}*bookings;

int main(){

    return 0;
}