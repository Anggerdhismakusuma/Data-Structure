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

void inOrder(node *root){
    if(root){
        inOrder(root->left);
        printf("%d ", root->val);
        inOrder(root->right);
    }
}

node *deleteNode(node *root, int val){
    if(!root) return root;
    if(val < root->val) root->left = deleteNode(root->left, val);
    else if(val > root->val) root->right = deleteNode(root->right, val);
    else{
        if(!root->left || !root->right){
            node *temp = root->left ? root->left : root->right;
            if(!temp){
                temp = root;
                root = NULL;
            }else{
                *root = *temp;
            }
            free(temp);
        }else{
            node *temp = root->right;
            while(temp->left) temp = temp->left;
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
    }

    if(!root) return root;
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);
    
    if(balance > 1 && getBalance(root->left) >= 0){
        return rightRotate(root);
    }

    if(balance > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance < -1 && getBalance(root->right) <= 0){
        return leftRotate(root);
    }

    if(balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

int main(){
    node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, 20);

    inOrder(root);

    printf("\n");

    printf("Root: %d\n", root->val);
    return 0;
}