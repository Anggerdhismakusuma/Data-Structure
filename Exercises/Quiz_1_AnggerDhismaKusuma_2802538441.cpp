#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vulnerability{
    int id;
    int impact;
    int likelihood;
    int priority;
    struct Vulnerability* next;
} *h;

int priorityTable(int impact, int likelihood){
    if(impact == 1 && likelihood == 1){
        return 3;
    } else if(impact == 1 && likelihood == 0){
        return 2;
    } else if(impact == 0 && likelihood == 1){
        return 1;
    } else if(impact == 0 && likelihood == 0){
        return 0;
    }
}

void enqueue(int id, int impact, int likelihood){
    struct Vulnerability* newNode = (Vulnerability*)malloc(sizeof(Vulnerability));
    newNode->id = id;
    newNode->impact = impact;
    newNode->likelihood = likelihood;
    newNode->priority = priorityTable(impact, likelihood);
    newNode->next = NULL;

    if(!h){
        newNode->next = h;
        h = newNode;
        return;
    } else if(newNode->priority > h->priority){
        newNode->next = h;
        h = newNode;
        return;
    } else {
        struct Vulnerability *temp = h;
        while(temp->next && temp->next->priority >= newNode->priority){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void display(){
    printf("Vulnerability Queue:\n");
    struct Vulnerability *temp = h;
    while(temp){
        printf("ID : %d - ", temp->id);
        if(temp->priority == 3) printf("Critical\n");
        else if(temp->priority == 2) printf("High\n");
        else if(temp->priority == 1) printf("Medium\n");
        else if(temp->priority == 0) printf("Low\n");
        temp = temp->next;
    }
    printf("\n");
}

void process() {
    printf("Processing vulnerabilities...\n");
    printf("\n");
    struct Vulnerability *temp = h;
    h = h->next;
    int index = temp->id % 10; // karena sectara cuma punya 10 vm
    printf("Stored Processed Vulnerabilities:\n");
    printf("Index %d -> ID: %d\n", index, temp->id);
    printf("\n");
    free(temp);
}

int main(){

    enqueue(3001, 0, 0);
    enqueue(3002, 1, 1);
    enqueue(3003, 1, 0);
    enqueue(3004, 0, 1);
    enqueue(3005, 1, 1);
    display();
    process();
    process();
    display();
    return 0;
}