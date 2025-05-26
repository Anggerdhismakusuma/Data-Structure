#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char name[101];
    int price;
    char category[101];
    char availability[101];
    int height;
    struct node *left;
    struct node *right;
}*node = NULL;

node* createNode(char *name, int price, char *category, char *availability){
    struct node* newNode = (node*)malloc(sizeof(node));
    strcpy(newNode->name, name);
    newNode->price = price;
    strcpy(newNode->category, category);
    strcpy(newNode->availability, availability);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void enterToContinue(){
    printf("Press Enter to continue..."); getchar();
}

node* insert(){
    system("cls");

    char name[101], category[101], availability[101];
    int price;

    do{
        printf("Enter Treatment Name: ");
        scanf("%[^\n]", name); getchar();
    }while(validationName(name) == -1);
    
    do{
        printf("Enter Treatment Price: ");
        scanf("%d", &price); getchar();
    }while(price < 50000 || price > 1000000);
    
    do{
        printf("Enter Treatment Category [Hair Care | Nail Care | Body Care]: ");
        scanf("%[^\n]", category); getchar();
    }while(strcmp(category, "Hair Care") != 0 && strcmp(category, "Nail Care") != 0 && strcmp(category, "Body Care") != 0);

    do{
        printf("Enter Treatment Availability [Available | Not Available]: ");
        scanf("%[^\n]", availability); getchar();
    }while(strcmp(availability, "Available") != 0 && strcmp(availability, "Not Available") != 0);

    struct node *newNode = createNode(name, price, category, availability);
    node = insertAVL(node, newNode);

    printf("New treatment is successfully added!\n");
    enterToContinue();

    return node;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int height(node* root){
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

int getBalance(node* root){
    if (root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

node* rightRotate(node* root){
    node* newRoot = root->left;
    node* temp = newRoot->right;

    newRoot->right = root;
    root->left = temp;

    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

node* leftRotate(node* root){
    node* newRoot = root->right;
    node* temp = newRoot->left;

    newRoot->left = root;
    root->right = temp;

    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

int validationName(char *name){
    if(strncmp(name, "Sally", 5) != 0 || strlen(name) < 5 || strlen(name) > 20){
        return -1;
    }

    int space = 0, letterAfterSpace = 0, flag = 0, x = strlen(name);
    for(int i = 0; i < x; i++){
        if(name[i] == ' ' && flag == 0){
            space++;
            flag = 1;
        }
        if(name[i] == ' ' && flag == 1){
            letterAfterSpace++;
        }
    }

    if(space > 0 && letterAfterSpace > 0){
        return 1;
    } else {
        return -1;
    }
}

void preOrder(node* root){
    if (root != NULL) {
        printf("%s\n", root->name);
        printf("%d\n", root->price);
        printf("%s\n", root->category);
        printf("%s\n", root->availability);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(node* root){
    if (root != NULL) {
        inOrder(root->left);
        printf("%s\n", root->name);
        printf("%d\n", root->price);
        printf("%s\n", root->category);
        printf("%s\n", root->availability);
        inOrder(root->right);
    }
}

void postOrder(node* root){
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%s\n", root->name);
        printf("%d\n", root->price);
        printf("%s\n", root->category);
        printf("%s\n", root->availability);
    }
}

void view(node* node){
    system("cls");
    if(node == NULL){
        printf("No treatment available.\n");
    } else {
        printf("Treatment Name: %s\n", node->name);
        printf("Price: %d\n", node->price);
        printf("Category: %s\n", node->category);
        printf("Availability: %s\n", node->availability);
    }

    char mode[10];

    do{
        printf("Insert View Mode [Pre | in | Post]: ");
        scanf("%[^\n]", mode); getchar();
    } while(strcmp(mode, "Pre") != 0 && strcmp(mode, "in") != 0 && strcmp(mode, "Post") != 0);
    
    if(strcmp(mode, "Pre") == 0){
        printf("Pre-order Traversal:\n");
        preOrder(node);
    } else if(strcmp(mode, "in") == 0){
        printf("In-order Traversal:\n");
        inOrder(node);
    } else if(strcmp(mode, "Post") == 0){
        printf("Post-order Traversal:\n");
        postOrder(node);
    } else {
        printf("Invalid mode. Please try again.\n");
    }
    enterToContinue();
}

node* insertAVL(node* root, node* newNode){
    if (root == NULL) {
        return newNode;
    } if (strcmp(newNode->name, root->name) < 0) {
        root->left = insertAVL(root->left, newNode);
    } else if (strcmp(newNode->name, root->name) > 0) {
        root->right = insertAVL(root->right, newNode);
    } else {
        return root; // Duplicate names are not allowed
    }

    // Update height and balance the tree
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && strcmp(newNode->name, root->left->name) < 0) {
        return rightRotate(root);
    }
    // Right Right Case
    if (balance < -1 && strcmp(newNode->name, root->right->name) > 0) {
        return leftRotate(root);
    }
    // Left Right Case
    if (balance > 1 && strcmp(newNode->name, root->left->name) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Left Case
    if (balance < -1 && strcmp(newNode->name, root->right->name) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

node* delete(node* root){
    system("cls");
    if(root == NULL){
        printf("No treatment available.\n");
    } else {
        char name[101];
        printf("Enter Treatment Name to delete: ");
        scanf("%[^\n]", name); getchar();
        
        if(alreadyInTree(root, name) == 1){
            root = deleteAVL(root, name);
            printf("Treatment %s is successfully deleted!\n", name);
        } else {
            printf("Treatment %s not found.\n", name);
        }
        enterToContinue();
    }
}

node* deleteAVL(node* root, char* name){
    if(root == NULL){
        return root;
    } else if(strcmp(name, root->name) < 0){
        root->left = deleteAVL(root->left, name);
    } else if(strcmp(name, root->name) > 0){
        root->right = deleteAVL(root->right, name);
    } else {
        // Node with only one child or no child
        if((root->left == NULL) || (root->right == NULL)){
            node* temp = root->left ? root->left : root->right;
            if(temp == NULL){
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            node* temp = minValueNode(root->right);
            strcpy(root->name, temp->name);
            root->price = temp->price;
            strcpy(root->category, temp->category);
            strcpy(root->availability, temp->availability);
            root->right = deleteAVL(root->right, temp->name);
        }
    }
}

int main(){
    int choice = -1;
    do{
        do{
            printf("Sally Saloon\n");
            printf("================\n");
            printf("1. View Available Treatment\n");
            printf("2. Insert New Treatment\n");
            printf("3. Delete Treatment\n");
            printf("4. Exit\n");
            printf("[1-4]\n");
            printf(">> ");
            scanf("%d", &choice); getchar();
        } while (choice < 1 || choice > 4);
        switch(choice){
            case 1:
                view(node);
                break;
            case 2:
                node = insert(node);
                break;
            case 3:

            case 4:
        }
    } while (1);  
}