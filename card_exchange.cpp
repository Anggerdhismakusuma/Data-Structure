#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int id = 0;
    char poke[101];
    int price = 100;
    struct Node* Next;
} *head, *tail, *current;

void Push_Ultimate(char *input){
    current = (Node*)malloc(sizeof(Node)); // Declare Dynamic Array Struct
    strcpy(current->poke, input); // Isi Node yang dibuat
    current->Next = NULL; // Buat next dari Current adalah NULL
    if (!head){ // Kalau belum ada apa apa buat head, tail, current di satu tempat
        head = tail = current;
    } else if(strcmp(input, head->poke) > 0){ // Buat kondisi inputan apa yang di atas
        current->Next = head;
        head = current;
    } else if(strcmp(input, tail->poke) < 0){ // Buat kondisi inputan apa yang di bawah
        tail->Next = current;
        tail = current;
    } else { // Kalau mau langsung masuk kasih langsung yang else
        Node *temp = head;
        while(strcmp(temp->Next->poke, input) < 0){
            temp = temp->Next;
        }
        current->Next = temp->Next;
        temp->Next = current;
    }
}

void Pop_Ultimate(char *input){
    if (head == NULL){ // Kalau Head ga ada
        return;
    }
    if(strcmp(head->poke, input) == 0){ // Kalau di head ketemu target
        struct Node *temp = head; // buat temp untuk nampung head
        head = head->Next; // Buat title head ke setelah head
        temp->Next = NULL; // Temp yang tadinya punya title head awal di putus dengan Next di jadiin NULL
        free(temp); // Jangan lupa Free biar ga kepake
    } else { // Kalau di mid - akhir ketemu target
        struct Node *temp1 = head; // Buat temp 1 buat ke target - 1
        struct Node *temp2 = head->Next;  // Buat temp 2 buat ke target
        while (strcmp(temp2->poke,input) != 0){ // Selama belum nemu, di next next mulu kedua temp
            temp1 = temp1->Next;
            temp2 = temp2->Next;
        }
        temp1->Next = temp2->Next; // Buat si target - 1 itu nyambung ke nextnya target
        temp2->Next = NULL; // Putus si target dengan Next jadiin Null
        free(temp2); // Jangan lupa Free target
    }
}

void printList(){
    Node *temp = head;
    printf(" POKE POKE\n");
    printf("===========\n");
    while(temp != NULL){
        printf("ID : %d\n", temp->id);
        printf("Name : %s\n", temp->poke);
        printf("Price : %d\n", temp->price);
        printf("-------------\n");
        temp = temp->Next;
    }
    printf("===========\n");
}

int main(){
    // Masukkan nama Pokemon = Vulpix, Diglett, Zubat, Nidoran
    for(int i = 0; i < 4; i++){
        char *name = (char*)malloc(sizeof(char));
        scanf("%s", name); getchar();
        Push_Ultimate(name);
    }
    printList();
    // Menukar Nidoran dengan Charmander
    // char *pokemon = (char*) malloc(sizeof(char));
    // printf("Masukkan nama pokemon yang inin di tukar: ");
    // scanf("%s", pokemon);
    
    return 0;
}
