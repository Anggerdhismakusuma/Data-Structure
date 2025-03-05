#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define gc getchar();
#define SIZE 100

struct Borrower{
	char fullname[255];
	char libraryID[8];
	char borrowingID[8];
	char title[51];
	int borrowDur;
	struct Borrower *next;
} *hashTable[SIZE];

void enterToContinue(){
	printf("Press ENTER to continue...");gc
}

char *generateID(char *title){
	char *id;
	sprintf(id, "%c%c%d%d%d", toupper(title[0]), toupper(title[1]), rand() % 10, rand() % 10, rand() % 10);
	return id;
}

// int getHashKey(char *borrowingID){
// 	int key;
// 	for(int i = 2; i < 5; i++){
// 		key += borrowingID[i] - '0';
// 	}
// 	key *= key;
// 	char skey[8];
// 	sprintf(skey, "%d", key);
// 	int l = strlen(skey);
// 	int middleNumber;
// 	if(l % 2 == 1){
// 		key = skey[l / 2] - '0'; 
// 	} else {
// 		char mid1 = skey[l / 2 - 1] - '0';
// 		char mid2 = skey[l /2] - '0';
// 		middleNumber = (mid1 - '0') * 10 + (mid2 - '0');
// 		key = middleNumber;
// 	}
// 	return key % SIZE;
// }

int generateKey(char *id){
	// HA440

	// 1. Ubah jadi angka
	char tempID[5] = {id[2], id[3], id[4], '\0'};
	// long long int numID = atoi(tempID);
	long long int numID = atoi(&id[2]);

	numID *= numID;

	char stringID[100];
	sprintf(stringID, "%lld", numID);
	int l = strlen(stringID);
	int key = 0;
	if(l % 2 == 0){
		char mid[3] = {stringID[l / 2 - 1], stringID[l / 2], '\0'};
		key = atoi(mid);
	} else {
		key = stringID[l/2] - '0';
	}

	return key % SIZE;
}

void push(Borrower *c){
	int key = getHashKey(c->borrowingID);
	if(hashTable[key] == NULL){
		hashTable[key] = c;
	} else {
		Borrower *temp = c;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = c;
	}
}

Borrower *createBook(char *fullname, char *libraryID, char *title, int borrowDur){
	Borrower *c = (Borrower*)malloc(sizeof(Borrower));
	char *borrowingID = generateID(title);
	strcpy(c->fullname, fullname);
	strcpy(c->libraryID, libraryID);
	strcpy(c->title, title);
	c->borrowDur = borrowDur;
	c->next = NULL;
	strcpy(c->borrowingID, borrowingID);
	return c;
}

bool isName(char *fullname){
	return strlen(fullname) >= 3 && strlen(fullname) <= 30;
}

bool isID(char *ID){
	if(ID[0] != 'L' || ID[1] != 'I' || ID[2] != 'B' || ID[3] != '-') return false;
	return true;
}

bool isTitle(char *title){
	return strlen(title) >= 3 && strlen(title) <= 50;
}

bool isDuration(int dur){
	return dur >= 1 && dur <= 30;
}

void borrowBook(){
	char fullname[255];
	char libraryID[8];
	char title[51];
	int borrowDur;
	
	do{
		printf("Enter your full name: ");
		scanf("%[^\n]", fullname);gc
	} while(!isName(fullname));
	
	do{
		printf("Enter your library ID (format: LIB-xxxxx): ");
		scanf("%s", libraryID);gc
	} while(!isID(libraryID));
	
	do{
		printf("Enter the book title: ");
		scanf("%[^\n]", title);gc
	} while(!isTitle(title));
	
	do{
		printf("Enter borrowing duration (1-30 days): ");
		scanf("%d", &borrowDur);gc
	} while(!isDuration);
	
	Borrower *c = createBook(fullname, libraryID, title, borrowDur);
	push(c);
}

void printMenu(){
	system("cls");
	puts("=======================================");
	puts("      Bookhaven Library Management     ");
	puts("=======================================");
	puts("1. Borrow a Book");
	puts("2. View Borrowed Book");
	puts("3. Return a Book");
	puts("4. Exit");
	puts("=======================================");
}

void viewBorrowed(){
	system("cls");
	bool found = false;
	
	for(int i = 0; i < SIZE; i++){
		Borrower *temp = hashTable[i];
		while(temp != NULL){
			found = true;
			printf("=========================\n");
			printf("   Borrowed Book List    \n");
			printf("=========================\n");
			printf("Borrowing ID : %s\n", temp->borrowingID);
			printf("Borrower Name: %s\n", temp->fullname);
			printf("Library ID   : %s\n", temp->libraryID);
			printf("Book Title   : %s\n", temp->title);
			printf("Duration     : %d\n", temp->borrowDur);
			temp = temp->next;
		}
	}
	
	if(!found) printf("There's No Book");
	enterToContinue();
}

bool pop(char* borrowingID) {
    int key = getHashKey(borrowingID);

    Borrower* c = hashTable[key];

    if (c == NULL) return false;

    if (strcmp(c->borrowingID, borrowingID) == 0) {
        hashTable[key] = NULL;
        free(c);
        return true;
    } else {
        Borrower* temp = hashTable[key];
        while (temp->next != NULL && strcmp(temp->next->borrowingID, borrowingID) != 0) {
            temp = temp->next;
        }
        Borrower* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        return true;
    }
    return false;
}

void returnBook() {
    char borrowingID[100];
    printf("Input Booking ID (Case Sensitive) : ");
    scanf("%[^\n]", borrowingID); gc

    system("cls");
    if(pop(borrowingID)) {
        printf("BookingID %s is Successfully Deleted !\n", borrowingID);
    } else {
        puts("Failed to Delete, There is No Data !");
    }

    enterToContinue();
}

int main(){
	srand(time(NULL));
	do{
		int inp = -1;
		printMenu();
		
		do{
			printf("Enter your choice: ");
			scanf("%d", &inp);
		} while(inp < 1 || inp > 5);
		
		switch(inp){
			case 1:
				borrowBook();
				break;
			case 2:
				viewBorrowed();
				break;
			case 3:
				returnBook();
				break;
			case 4:
				return 0;
		}
	} while(1);
	return 0;
}
