#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Treatment{
    char name[25];
    int price;
    char category[15];
    char availability[25];
};

struct AVLNode{
    struct Treatment data;
    struct AVLNode *left, *right;
    int height;
};

int max(int a, int b){
    return (a > b) ? a : b;
}

int height (struct AVLNode *node){
    return node ? node->height : 0;
}

struct AVLNode* createNode(char name[], int price, char category[], char availability[]){
    struct AVLNode *node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    strcpy(node->data.name, name);
    node->data.price = price;
    strcpy(node->data.category, category);
    strcpy(node->data.availability, availability);
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int getBalance()