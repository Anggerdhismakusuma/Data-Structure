#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

void printMenu(){
	puts("1. Booking Hotel");
	puts("2. View Bookings");
	puts("3. Delete Booking");
	puts("4. Exit");
}

int main(){
	srand(time(NULL));
	do{
		system("cls");
		printMenu();
		int inp = -1;
		do{
			printf(">> ");
			scanf("%d", &inp);
		} while(inp < 1 || inp > 4);
	} while(1);
	return 0;
}
