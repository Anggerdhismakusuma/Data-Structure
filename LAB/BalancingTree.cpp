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
    currLeft->right = curr;
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

    // update height
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    // Identify imbalance case
    int balance = getBalance(curr);

    // LL
    if(balance > 1 && age < curr->left->age){
        return rightRotate(curr);
    }

    // RR
    if(balance < -1 && age > curr->right->age){
        return leftRotate(curr);
    }

    // LR
    if(balance > 1 && age > curr->left->age){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }

    // RL
    if(balance < -1 && age < curr->right->age){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

void inOrder(Mahasiswa *curr){
    if(curr == NULL){
        return;
    }
    inOrder(curr->left);
    printf("Age: %d, Name: %s\n", curr->age, curr->name);
    inOrder(curr->right);
}

void updateTree(Mahasiswa *root, int age, char name[100]){
    if(root == NULL){
        printf("Data not found\n");
        return;
    }

    else if(age < root->age){
        updateTree(root->left, age, name);
    } else if(age > root->age){
        updateTree(root->right, age, name);
    } else if (age == root->age){
        strcpy(root->name, name);
        printf("Data updated\n");
    }
}

int main(){
    Mahasiswa *root = NULL;

    root = insertAVL(root, 3, "cindy");
    root = insertAVL(root, 18, "cindy");
    root = insertAVL(root, 21, "cindy");
    root = insertAVL(root, 8, "cindy");
    root = insertAVL(root, 7, "cindy");
    root = insertAVL(root, 6, "cindy");
    root = insertAVL(root, 23, "cindy");

    inOrder(root);

    updateTree(root, 21, "jovita");
    printf("============\n");
    inOrder(root);
    return 0;
}