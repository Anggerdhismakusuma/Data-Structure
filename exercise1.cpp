#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    int id = 0;
    char title[100];
    int quantity;
};

struct book* dat = (book*)malloc(sizeof(book));

int bookCount = 0;

void printMenu();
void enterToContinue();

void addBook();
void borrowBook();
void deleteBook();
void viewBook();

int main() {
    do {
        int input = -1;
        printMenu();

        do {
            printf(">> ");
            scanf("%d", &input); getchar();
        } while (input < 1 || input > 5);

        switch (input) {
            case 1 :
                addBook();
                break;
            case 2 :
                borrowBook();
                break;
            case 3 :
                deleteBook();
                break;
            case 4 :
                viewBook();
                break;
            case 5 :
                enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}

void printMenu() {
    puts("SUNIB University Library");
    puts("1. Add Book");
    puts("2. Borrow Book");
    puts("3. Delete Stock");
    puts("4. Book List");
    puts("5. Exit");
}

void enterToContinue() {
    printf("Press ENTER to continue ..."); getchar();
}

void addBook() {
    
    // Title
    printf("Input Title : ");
    scanf("%[^\n]", dat[bookCount].title); getchar();

    // Quantity
    printf("Input Quantity : ");
    scanf("%d", &dat[bookCount].quantity); getchar();

    puts("Book added");
    dat[bookCount].id++;
    bookCount++;
    enterToContinue();
}

void viewBook() {
    for (int i = 0; i < bookCount; i++) {
        printf("ID : %d\n", dat[i].id);
        printf("Title : %s\n", dat[i].title);
        printf("Quantity : %d\n", dat[i].quantity);
    }
    enterToContinue();
}

void borrowBook() {
    if (bookCount == 0) {
        puts("No books available");
        enterToContinue();
        return;
    }
    
    viewBook();
    char validation[100];
    do {
        printf("Search by: id or title [id / title] : ");
        scanf("%s", validation); getchar();
    } while (strcmp(validation, "id") != 0 && strcmp(validation, "title") != 0);

    int idx = -1;
    if (strcmp(validation, "title") == 0) {
        do {
            char temp[100];
            printf("Input book title : ");
            scanf("%[^\n]", temp); getchar();

            for (int i = 0; i < bookCount; i++) {
                if (strcmp(temp, dat[i].title) == 0) {
                    idx = i;
                    break;
                }
            }
        } while (idx == -1);
    } else {
        do {
            printf("Input book id : ");
            scanf("%d", &idx); getchar();
            idx--;
        } while (idx < 0 || idx > bookCount);
    }
    
    puts("Book borrowed");
    dat[idx].quantity--;
    enterToContinue();
}

void deleteBook() {
    if (bookCount == 0) {
        puts("There is no book");
        enterToContinue();
        return;
    }
    viewBook();
    int temp;
    do {
        printf("Input book id : ");
        scanf("%d", &temp); getchar();
        temp--;
    } while (temp < 0 || temp > bookCount);

    for (int i =- 0; i < bookCount - 1; i++) {
        dat[i] = dat[i + 1];
    }
    bookCount--;
    puts("Book deleted");
    enterToContinue();
}
