#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Contact {
    char name[50];
    char phone[20];
    char email[50];
    struct Contact* next;
} Contact;

Contact* hashTable[TABLE_SIZE];

int uniqueHashFunction(char* name) {
    unsigned int hash = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        hash = (hash ^ name[i]) * 16777619;
    }
    return hash % TABLE_SIZE;
}

void insertContact(char* name, char* phone, char* email) {
    int index = uniqueHashFunction(name);
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->email, email);
    newContact->next = NULL;
    
    if (hashTable[index] == NULL) {
        hashTable[index] = newContact;
    } else {
        Contact* temp = hashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newContact;
    }
}

Contact* searchContact(char* name) {
    int index = uniqueHashFunction(name);
    Contact* temp = hashTable[index];
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteContact(char* name) {
    int index = uniqueHashFunction(name);
    Contact* temp = hashTable[index];
    Contact* prev = NULL;
    
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Contact not found!\n");
        return;
    }
    
    if (prev == NULL) {
        hashTable[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
    printf("Contact deleted successfully!\n");
}

void displayContacts() {
    int collisionCount = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Contact* temp = hashTable[i];
        int count = 0;
        while (temp != NULL) {
            printf("[%s, %s, %s] -> ", temp->name, temp->phone, temp->email);
            temp = temp->next;
            count++;
        }
        if (count > 1) {
            collisionCount += (count - 1);
        }
        printf("NULL\n");
    }
    printf("Total Collisions: %d\n", collisionCount);
}

int main() {
    insertContact("Sam", "123456789", "sam@example.com");
    insertContact("El", "987654321", "el@example.com");
    insertContact("Angger", "555123456", "angger@example.com");
    insertContact("Theo", "111222333", "theo@example.com");
    insertContact("Yos", "444555666", "yos@example.com");
    insertContact("Ken", "777888999", "ken@example.com");
    
    displayContacts();
    
    Contact* found = searchContact("Angger");

    if (found) {
        printf("Contact Found: %s, %s, %s\n", found->name, found->phone, found->email);
    } else {
        printf("Contact Not Found\n");
    }
    
    deleteContact("Angger");
    displayContacts();
    
    return 0;
}