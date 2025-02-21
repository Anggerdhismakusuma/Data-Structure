#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define gc getchar();

struct data{
    char id[10];
    char name[101];
    int price;
    data* next;
} *h, *t, *c;

void printMenu(){

}

void enterToContinue(){
    printf("Press ENTER to continue..."); gc
}

void pushMid(char name[]){
    c = (data*)malloc(sizeof(data));
    *c->id = rand() % 100;
    strcpy(c->name, name);
    c->price = 100;
    c->next = NULL;

    if(!h) {
        h = t = c;
    } else if(strcmp(c->name, h->name) < 0) {
        c->next = h;
        h = c;
    } else if (strcmp(c->name, t->name) > 0) {
        t->next = c;
        c = t;
    } else {
        data *temp = h;
        while(strcmp(temp->next->name, c->name)){
            temp = temp->next;
            c->next = temp->next;
            temp->next = c; 
        }
    }
}

void pop(char name[]){
    if(!h){
        return;
    } else if (strcmp(h->name, name) == 0){
        data *temp1 = h;
        temp1->next = h;
        h = h->next;
        temp1->next = NULL;
        free(temp1);
    } else {
        data *temp1 = h;
        data *temp2 = h->next;

        while(strcmp(temp2->name, name) != 0){
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        temp1->next = temp2->next;
        temp2->next = NULL;
        free(temp2);
    }
}

void sellCard(){
    if(!h){
        printf("There is no card");
        enterToContinue();
    }
    char name[100];
    printf("Input card name");
    scanf("%s", name); gc
    int found = -1;
    data *temp = h;
    while(!temp){
        if(strcmp(temp->name, name) == 0){
            found = 1;
            break;
        } else {
            temp = temp->next;
        }
    }

    if(found == -1){
        
    }
}

void buyCard(){
    char name[101];
    do{
        printf("Enter Card Name: ");
        scanf("%s", name); gc
    } while(strcmp(name, "Ratatta") != 0);

    int found = -1;
    data *temp = h;
    while(temp != NULL){
        if(strcmp(name, temp->name) == 0){
            found = 1;
            break;
        } else {
            temp = temp->next;
        }
    }

    if(found == 1){
        printf("Card has been bough before");
        enterToContinue();
    } else {
        pushMid(name);
        printf("Card has been added");
        enterToContinue();
    }
}

int main(){
    do{
        int input;
        printMenu();
        do{
            scanf("%d", &input);
        } while(input < 1 && input > 5);
    } while(1);
    return 0;
}