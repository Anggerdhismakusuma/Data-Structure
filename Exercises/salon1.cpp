#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char name[50], cat[50], status[50];
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

Node *createNode(const char *name, const char *cat, const char *status, int price){
    Node *newNode = (Node *) malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->cat, cat);
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
    else if(strcmp(newNode->name, root->name) > 0) root->right = insert(root->right, newNode);
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
        strcpy(root->cat, temp->cat);
        strcpy(root->status, temp->status);
        root->price = temp->price;
        root->right = del(root->right, temp->name);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bal = getBal(root);

    if(bal > 1 && strcmp(name, root->left->name) >= 0) return right(root);
    else if(bal < -1 && strcmp(name, root->right->name) <= 0) return left(root);
    else if(bal > 1 && strcmp(name, root->left->name) < 0){
        root->left = left(root);
        return right(root);
    } else if (bal < -1 && strcmp(name, root->right->name) > 0) {
        root->right = right(root);
        return left(root);
    }
    return root;
}

int nextInt(){
    int n; scanf("%d", &n); getchar(); return n;
}

void preorder(Node *root){
    if(!root) return;
    printf("%s\n", root->name);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root){
    if(!root) return;
    inorder(root->left);
    printf("%s\n", root->name);
    inorder(root->right);
}

void postorder(Node *root){
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%s\n", root->name);
}

void menu(Node *root){
    puts("=== Sally Salon ===");
    if(!root) puts("No data to show");
    else inorder(root);
    puts("\n1. Insert");
    puts("2. View");
    puts("3. Delete");
    puts("4. Exit");
}

char confirm(){
    char c;
    do {
        printf("Are you sure [y | n]: "); scanf("%c", &c); getchar();
    } while(c != 'y' && c != 'n');
    return c;
}

void enter(){
    printf("Press ENTER to continue..."); getchar();
}

bool nameValidation(const char *name){
    return (strncmp(name, "Sally", 5) == 0);
}

bool validWord(const char *name){
    int wordCount = 0, inword = 0;
    for(int i = 0; name[i]; i++){
        if(!isspace(name[i]) && inword == 0){
            inword = 1; wordCount++;
        } else if(isspace(name[i])) inword = 0;
    }
    return wordCount >= 2;
}

void tolowerStr(char *name){
    for(int i = 0; name[i] != '\0'; i++){
        name[i] = tolower(name[i]);
    }
}

void add(Node **root){
    char name[50], cat[50], status[50];
    int price;

    do {
        printf("Name [Start with 'Sally' | 5 - 20 character | 2 words]: "); scanf("%[^\n]", name); getchar();
    } while(!nameValidation(name) || !validWord(name));

    do {
        printf("Price [50000 - 1000000]: "); price = nextInt();
    } while(price < 50000 || price > 1000000);

    do {
        printf("Category [Hair Care | Nail Care | Body Care]: "); scanf("%[^\n]", cat); getchar();
        tolowerStr(cat);
    } while(strcmp(cat, "hair care")!= 0 && strcmp(cat, "nail care") != 0 && strcmp(cat, "body care") != 0);
    
    do {
        printf("Availability [Available | Unavailable]: "); scanf("%[^\n]", status); getchar();
        tolowerStr(status);
    } while(strcmp(status, "available")!= 0 && strcmp(status, "unavailable") != 0);
    char c = confirm();
    if(c == 'y'){
        *root = insert(*root, createNode(name, cat, status, price));
        puts("Success to add");
    } else {
        puts("Cancelled to add");
    }
    enter();
}

void view(Node *root){
    if(!root) puts("No data to show");
    else {
        char name[50];
        do {
            printf("Input view order [pre | in | post]: "); scanf("%[^\n]", name); getchar();
        } while(strcmp(name, "pre") != 0 && strcmp(name, "in") != 0 && strcmp(name, "post") != 0);

        if(strcmp(name, "pre") == 0) preorder(root);
        else if(strcmp(name, "in") == 0) inorder(root);
        else if(strcmp(name, "post") == 0) postorder(root);
    }
    enter();
}

Node *search(Node *root, const char *name){
    if(!root) return NULL;
    else if(strcmp(name, root->name) < 0) return search(root->left, name);
    else if(strcmp(name, root->name) > 0) return search(root->right, name);
    return root;
}

void remove(Node **root){
    if(!*root) {
        puts("No data to show");
    } else {
        char name[50];
        Node *found = NULL;
        do {
            printf("Name [exist]: "); scanf("%[^\n]", name); getchar();
            found = search(*root, name);
        } while(found == NULL);

        char c = confirm();
        if(c == 'y'){
            printf("[%s] is deleted\n", found->name);
            *root = del(*root, name);
        } else {
            puts("Cancelled to delete");
        }
    }
    enter();
}

int main(){
    int choice = -1;
    Node *root = NULL;
    do {
        system("cls"); menu(root);
        do {
            printf(">> "); choice = nextInt();
        } while(choice < 1 || choice > 4);

        switch(choice){
            case 1: add(&root); break;
            case 2: view(root); break;
            case 3: remove(&root); break;
            case 4: return 0;
        }
    } while(1);
    return 0;
}