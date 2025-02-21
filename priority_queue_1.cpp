#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    int age;
    char name[50];
    int status;
    struct Node *next;
    struct Node *prev;
} *h, *c, *t;

void viewData(){
    if (h == NULL) {
        puts("No patient");
        return;
    }
    struct Node *temp = h;
    while(temp != NULL)
    {
        printf("Nama: %s || Umur: %d || Status: %d\n", temp->name, temp->age, temp->status);
        temp = temp->next;
    }
    free(temp);
    printf("Press ENTER to continue..."); getchar();
}

void pushMiddle(char tempName[], int tempAge, int tempStatus)
{
    c = (struct Node *)malloc(sizeof(struct Node));
    strcpy(c->name, tempName);
    c->age = tempAge;
    c->status = tempStatus;
    c->next = NULL;
    c->prev = NULL;

    if (!h)
    {
        h = t = c; // If the list is empty, initialize it
    }
    else if (tempStatus < h->status || (tempStatus == h->status && strcmp(tempName, h->name) < 0))
    {
        // Insert at the head
        c->next = h;
        h->prev = c;
        h = c;
    }
    else if (tempStatus > t->status || (tempStatus == t->status && strcmp(tempName, t->name) > 0))
    {
        // Insert at the tail
        t->next = c;
        c->prev = t;
        t = c;
    }
    else
    {
        // Insert in the middle
        struct Node *temp = h;
        while (temp->next != NULL)
        {
            if (temp->next->status > tempStatus || 
                (temp->next->status == tempStatus && strcmp(temp->next->name, tempName) > 0))
            {
                break;
            }
            temp = temp->next;
        }
        c->next = temp->next;
        if (temp->next)
        {
            temp->next->prev = c;
        }
        c->prev = temp;
        temp->next = c;
    }
}

void insertData(){
    printf("Insert Patient Name >> ");
    char tempName[50];
    scanf("%[^\n]", tempName); getchar();
    int tempAge;
    int tempStatus;
    printf("Insert Patient Age >> ");
    scanf("%d", &tempAge); getchar();
    printf("Insert Patient Status\n1. High\n2. Mid\n3. Low\n>> ");
    scanf("%d", &tempStatus); getchar();
    pushMiddle(tempName, tempAge, tempStatus);
}

void deleteData() {
    if (h == NULL) {
        puts("No patient.");
        return;
    }

    struct Node *temp = h;
    if (h == t) {
        h = t = NULL;
    } else {
        h = h->next;
        h->prev = NULL;
    }
    free(temp);
    puts("Successfully deleted.");
}

int main()
{
    int choice = -1;
    while(choice!=4){
        puts("Priority Queue");
        puts("==============");
        puts("1. Create");
        puts("2. View");
        puts("3. Delete");
        puts("4. Exit");
        printf("==============\n>> ");
        scanf("%d", &choice); getchar();
        switch (choice)
        {
        case 1:
            insertData();
            break;
        case 2:
            viewData();
            break;
        case 3:
            deleteData();
            break;
        default:
            break;
        }
    }
}

/*
1
Rizki
33
3
1
Richard
26
3
1
Andi
16
1
1
Nur
74
2
1
Coki
66
3
*/