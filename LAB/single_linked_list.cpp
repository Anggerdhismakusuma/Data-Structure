#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Data{
    int key;
    char nama[100];
    Data* next;
} *h, *t, *c;

Data* createData(int key, char *name){
    Data* newData = (Data*)malloc(sizeof(Data));
    newData->key = key;
    strcpy(newData->nama, name);
    newData->next = NULL;

    return newData;
} 

void pushHead(Data* newData){
    if(h == NULL){
        h = t = newData;
    } else {
        newData->next = h;
        h = newData;
    }
}

void pushTail(Data* ){

}

int main(){

    return 0;
}