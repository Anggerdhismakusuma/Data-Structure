#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_PRIORITY 10

struct Customer {
    char name[MAX_NAME];
    char priority[MAX_PRIORITY]; // Store priority as a string
    struct Customer *next;
} *front;

int comparePriority(char *p1, char *p2) {
    char *priorities[] = {"VVIP", "VIP", "Member", "Guest"};
    int i1 = 4, i2 = 4;
    for (int i = 0; i < 4; i++) {
        if (strcmp(p1, priorities[i]) == 0) i1 = i;
        if (strcmp(p2, priorities[i]) == 0) i2 = i;
    }
    return i1 - i2;
}

void enqueue(char *name, char *priority) {
    struct Customer *newCustomer = (struct Customer *)malloc(sizeof(struct Customer));
    strcpy(newCustomer->name, name);
    strcpy(newCustomer->priority, priority);
    newCustomer->next = NULL;

    if (front == NULL || comparePriority(priority, front->priority) < 0) {
        newCustomer->next = front;
        front = newCustomer;
    } else {
        struct Customer *temp = front;
        while (temp->next != NULL && comparePriority(priority, temp->next->priority) >= 0) {
            temp = temp->next;
        }
        newCustomer->next = temp->next;
        temp->next = newCustomer;
    }
}

void serveOne() {
    if (front == NULL) {
        printf("No customers in queue.\n");
        return;
    }
    struct Customer *temp = front;
    printf("Attention! %s is being served at %s table.\n", temp->name, temp->priority);
    front = front->next;
    free(temp);
}

void serveAll() {
    while (front != NULL) {
        serveOne();
    }
}

void dismissQueue() {
    printf("End of the day.\n");
    while (front != NULL) {
        struct Customer *temp = front;
        front = front->next;
        free(temp);
    }
}

void displayQueue() {
    printf("Current Queue:\n");
    struct Customer *temp = front;
    while (temp != NULL) {
        printf("[%s] %s\n", temp->priority, temp->name);
        temp = temp->next;
    }
    if (front == NULL) printf("No customers in queue.\n");
}

int main() {
    int choice;
    char membership[MAX_PRIORITY], name[MAX_NAME];

    while (1) {
        displayQueue();
        printf("\n1. Add Customer to Queue\n");
        printf("2. Serve One\n");
        printf("3. Serve All\n");
        printf("4. Dismiss Queue\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter [Membership Status] [Customer Name]: ");
                scanf("%s %[^\n]", membership, name);
                enqueue(name, membership);
                break;
            case 2:
                serveOne();
                break;
            case 3:
                serveAll();
                break;
            case 4:
                dismissQueue();
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
}