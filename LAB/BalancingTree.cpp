// AVL Tree -> bst self balancing tree
// Insert & update

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa{
    int age;
    char name[100];
    Mahasiswa *left;
    Mahasiswa *right;
    int height;
};

Mahasiswa *createNewMhs(int age, char name[100]){
    Mahasiswa *newMhs = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    newMhs->age = age;
    strcpy(newMhs->name, name);
    newMhs->left = NULL;
    newMhs->right = NULL;
    newMhs->height = 1;
    return newMhs;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int getHeight(Mahasiswa *curr){
    if(curr == NULL){
        return 0;
    } else{
        return curr->height;
    }
}

int getBalance(Mahasiswa *curr){
    if(curr == NULL){
        return 0;
    } else{
        return getHeight(curr->left) - getHeight(curr->right);
    }
}

Mahasiswa *insertAVL(Mahasiswa *curr, int age, char name[100]){
    // kosong
    if(curr == NULL){
        return createNewMhs(age, name);
    }

    if(age < curr->age){
        curr->left = insertAVL(curr->left, age, name);
    } else if(age > curr->age){
        curr->right = insertAVL(curr->right, age, name);
    } else {
        return curr;
    }

    // upfate height
    // curr->height = 1 + max(height(curr->left), height(curr->right));

}

int main(){

    return 0;
}