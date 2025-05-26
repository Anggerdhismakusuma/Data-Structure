#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char name[50], category[50], status[50];
    int price, height = 1;
    Node *left, *right;
};

int getHeight(Node *root){
    return (!root) ? 0 : root->height;
}

int getBal(Node *root){
    return (!root) ? 0 : getHeight(root->left)-getHeight(root->right);
}

int max(int a, int b){
    return (a > b) ? a : b;
}

Node *findmin(Node *root){
    while(root && root->left) root = root->left;
    return root;
}

Node *createNode(const char *name, const char *category, const char *status, int price){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->category, category);
    strcpy(newNode->status, status);
    newNode->price = price;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *left(Node *x){
    Node *y = x->right;
    Node *t = y->left;
    x->right = t;
    y->left = x;
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    return y;
}

Node *right(Node *x){
    Node *y = x->left;
    Node *t = y->right;
    x->left = t;
    y->right = x;
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    return y;
}

Node *insert(Node *root, Node *newNode){
    if(!root) return newNode;
    else if(strcmp(newNode->name, root->name) < 0) root->left = insert(root->left, newNode);
    else if(strcmp(newNode->name, root->name) > 0)root->right = insert(root->right, newNode);
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bal = getBal(root);

    if(bal > 1 && strcmp(newNode->name, root->left->name) >= 0) return right(root);
    else if(bal < -1 && strcmp(newNode->name, root->right->name) <= 0) return left(root);
    else if(bal > 1 && strcmp(newNode->name, root->left->name) < 0){
        root->left = left(root);
        return right(root);
    } else if (bal < -1 && strcmp(newNode->name, root->right->name) > 0) {
        root->right = right(root);
        return left(root);
    }
    return root;
}

Node *del(Node *root, const char *name){
    if(!root) return NULL;
    else if(strcmp(name, root->name) < 0) root->left = del(root->left, name);
    else if(strcmp(name, root->name) > 0) root->right = del(root->right, name);
    else {
        if(!root->left || !root->right){
            Node *temp = (root->left) ? root->left : root->right;
            free(root);
            return temp;
        }
        Node *temp = findmin(root->right);
        strcpy(root->name, temp->name);
        strcpy(root->category, temp->category);
        strcpy(root->status, temp->status);
        root->price = temp->price;
        root->right = del(root->right, temp->name);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bal = getBal(root);

    if(bal > 1 && strcmp(name, root->left->name) >= 0) return right(root);
    else if(bal < -1 && strcmp(name, root->right->name) <= 0) return left(root);
    else if(bal > 1 && strcmp())
}

int main(){

    return 0;
}