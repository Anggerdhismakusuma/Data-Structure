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

Mahasiswa *rightRotate(Mahasiswa *curr){
    Mahasiswa *currLeft = curr->left;
    Mahasiswa *currLeftRight = curr->left->right;

    // Rotate
    currLeft->left->right = curr;
    curr->left = currLeftRight;

    // Update height
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    currLeft->height = 1 + max(getHeight(currLeft->left), getHeight(currLeft->right));

    return currLeft; 
}

Mahasiswa *leftRotate(Mahasiswa *curr){
    Mahasiswa *currRight = curr->right;
    Mahasiswa *currRightLeft = curr->right->left;

    // Rotate
    currRight->left = curr;
    curr->right = currRightLeft;

    // Update height
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    currRight->height = 1 + max(getHeight(currRight->left), getHeight(currRight->right));

    return currRight;

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
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    // Identify imbalance case
    if(getBalance(curr) > 1 && getBalance(curr->left) >= 0){ // LL
        // LL
        return rightRotate(curr);
    }

    // RR
    else if(getBalance(curr) < -1 && getBalance(curr->right) <= 0){
        return leftRotate(curr);
    }

    // LR
    else if(getBalance(curr) > 1 && getBalance(curr->left) < 0){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }

    // RL
    else if(getBalance(curr) < -1 && getBalance(curr->right) > 0){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
}

int main(){

    return 0;
}