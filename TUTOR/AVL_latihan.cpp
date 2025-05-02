#include <stdio.h>
#include <stdlib.h>

struct nodes {
    int height = 1, value;
    nodes* left;
    nodes* right;
} *root;

int max_child_height(nodes* root){
    return root->left->height > root->right->height ? root->left->height : root->right->height;
}

int balance_factor(nodes* root){
    return root->left->height - root->right->height;
}


nodes *left_rotate(nodes *x){
    nodes *y = x->right;
    nodes *n = y->left;
    y->left = x;
    x->right = n;
    x->height = max_child_height(x) + 1;
    y->height = max_child_height(y) + 1;
    return y;
}

nodes *right_rotate(nodes *x){
    nodes *y= x->left;
    nodes *n = y->right;
    y->right = x;
    x->left = n;
    x->height = max_child_height(x) + 1;
    y->height = max_child_height(y) + 1;
    return y;
}

nodes *balancing(nodes *root, int bf){
    if(bf > 1 && balance_factor(root->left) == 1){
        return right_rotate(root);
    } else if(bf > 1 && balance_factor(root->left) <= 0){
        root->left = left_rotate(root->left);
        return right_rotate(root);
    } else if(bf < -1 && balance_factor(root->right) == -1){
        return left_rotate(root);
    } else if(bf < -1 && balance_factor(root->right) == 1){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
}

nodes* create(int value){
    nodes *newNode = (nodes*)malloc(sizeof(nodes));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

void insert(nodes *root, int value){
    if(value < root->value){
        if(root->left == NULL){
            root->left = create(value);
        } else {
            insert(root->left, value);
        }
    } else if(value > root->value){
        if(root->right == NULL){
            root->right = create(value);
        } else {
            insert(root->right, value);
        }
    } else {
        return;
    }
}

nodes* deletion(){
    
}

void print(nodes *root){
    if(root == NULL){
        return;
    }
    print(root->left);
    printf("%d ", root->value);
    print(root->right);
}

int main(){
    insert(root, 10);
    insert(root, 10);
    insert(root, 10);
    insert(root, 10);
    insert(root, 10);
}