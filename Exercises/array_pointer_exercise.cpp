#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct mahasiswa{
    char NIM[10];
    char nama[50];
}mahasiswa;


int main(){
    // mahasiswa ppti21[100];
    // strcpy(ppti21[0].NIM, "280182302");

    // printf("%s\n", ppti21[0].NIM);

    struct mahasiswa* ppti = (struct mahasiswa*)malloc(sizeof(struct mahasiswa));

    return 0;
}