#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SongNode {
    char title[100];
    int no = 0;
    struct SongNode* next;
    struct SongNode* prev;
}*head, *tail, *current;

void addSong(char *title){
    SongNode *newSong = (SongNode*)malloc(sizeof(SongNode));
    strcpy(newSong->title, title);
    
    newSong->no++;
}