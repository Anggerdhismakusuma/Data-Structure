#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    int height;
    node *left;
    node *right;
};

node *createNode(int val){
    node *c = (node*)malloc(sizeof(node));
    c->val = val;
    c->height = 1;
    c->left = c->right = NULL;
    return c;
}

int height(node *root){
    return (root) ? root->height : 0;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int getBalance(node *root){
    return (root) ? height(root->left) - height(root->right) : 0;
}

node *leftRotate(node *x){
    node *y = x->right;
    node *T2 = y->left;

    x->right = T2;
    y->left = x;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

node *rightRotate(node *x){
    node *y = x->left;
    node *T2 = y->right;

    x->left = T2;
    y->right = x;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

node *insert(node *root, int val){
    if(!root) return createNode(val);
    if(val < root->val) root->left = insert(root->left, val);
    else if(val > root->val) root->right = insert(root->right, val);
    else return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    
    int balance = getBalance(root);

    if(balance < -1 && val > root->right->val){
        // Right Right Case
        // Rotate Left
        return leftRotate(root);
    }

    if(balance > 1 && val < root->left->val){
        // Left Left Case
        // Rotate Right
        return rightRotate(root);
    }

    if(balance < -1 && val < root->right->val){
        // Right Left Case
        // Rotate Right -> Rotate Left
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    if(balance > 1 && val > root->left->val){
        // Left Right Case
        // Rotate Left -> Rotate Right
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    return root;
}

int main(){
    return 0;
}