#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct Node {
    char name[50];
    char phone[15];
    char email[50];
    struct Node* next;
} Node;

Node* hashTable[MAX_SIZE];

void initializeTable() {
    for (int i = 0; i < MAX_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

int hashFunction(char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    
    int squared = sum * sum;
    
    char squaredStr[20];
    sprintf(squaredStr, "%d", squared);
    int len = strlen(squaredStr);
    
    int midValue;
    if (len % 2 == 0) {
        midValue = (squaredStr[len / 2 - 1] - '0') * 10 + (squaredStr[len / 2] - '0');
    } else {
        midValue = squaredStr[len / 2] - '0';
    }
    
    return midValue % MAX_SIZE;
}

int uniqueHashFunction(char* name) {
    int hash = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        hash = (hash^name[i]) * 16777619;
    }

    return hash % MAX_SIZE;
}

void insert(char* name, char* phone, char* email) {
    // int index = hashFunction(name);
    int index = uniqueHashFunction(name);

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    strcpy(newNode->email, email);
    newNode->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        Node* temp = hashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Data berhasil ditambahkan pada indeks %d.\n", index);
}

void search(char* name) {
    // int index = hashFunction(name);
    int index = uniqueHashFunction(name);
    Node* temp = hashTable[index];

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Data ditemukan:\n");
            printf("Nama: %s\n", temp->name);
            printf("Telepon: %s\n", temp->phone);
            printf("Email: %s\n", temp->email);
            return;
        }
        temp = temp->next;
    }
    printf("'%s' ngga ada disini.\n", name);
}

void del(char* name) {
    // int index = hashFunction(name);
    int index = uniqueHashFunction(name);
    Node* temp = hashTable[index];
    Node* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) {
                hashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("'%s' berhasil dihapus.\n", name);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("'%s' ngga ada disini.\n", name);
}

void display() {
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("Indeks %d:\n", i);
        Node* temp = hashTable[i];
        while (temp != NULL) {
            printf("  Nama: %s, Telepon: %s, Email: %s\n", temp->name, temp->phone, temp->email);
            temp = temp->next;
        }
    }
}

int main() {
    int choice;
    char name[50], phone[15], email[50];

    initializeTable();

    do {
        printf("\nMenu:\n");
        printf("1. Tambah data\n");
        printf("2. Lihat data\n");
        printf("3. Hapus data\n");
        printf("4. Cari data\n");
        printf("5. Keluar\n");
        printf(">> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nama: ");
                scanf("%s", name);
                printf("Masukkan nomor telepon: ");
                scanf("%s", phone);
                printf("Masukkan email: ");
                scanf("%s", email);
                insert(name, phone, email);
                break;
            case 2:
                display();
                break;
            case 3:
                printf("Masukkan nama yang akan dihapus: ");
                scanf("%s", name);
                del(name);
                break;
            case 4:
                printf("Masukkan nama yang akan dicari: ");
                scanf("%s", name);
                search(name);
                break;
            case 5:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 5);

    return 0;
}