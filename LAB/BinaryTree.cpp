#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    int id;
    char name[101];
    struct Student *left, *right;
};

struct Student *createStudent(int id, char *name){
    struct Student *newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

struct Student *insert(struct Student *root, int id, char *name){
    // kalo tree belum kebuat, bikin root node
    if(root == NULL){
        return createStudent(id, name);
    }

    // id yang mau di insert > current node punya id
    if(id > root->id){
        root->right = insert(root->right, id, name);
    }

    // id yang kita mau insert < current node punya id
    if(id < root->id){
        root->left = insert(root->left, id, name);
    }

    return root;
}

void inorder(struct Student *root){
    if(root == NULL) return;
    inorder(root->left);
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
    inorder(root->right);
}

struct Student *search(struct Student *root, int id){
    // Search ga ketemu
    if(root == NULL){
        puts("Not found...");
        return NULL;
    }

    // kalo search ketemu
    if(root->id == id){
        puts("Found!");
        return root;
    }

    // kalo id yang mau di search lebih gede dari current punya id
    if(id > root->id){
        return search(root->right, id);
    }

    // kalo id yang mau di search lebih kecil dari current punya id
    if(id < root->id){
        return search(root->left, id);
    }
}

struct Student *update(struct Student *root, int id, char *newName){
    if(root == NULL){
        puts("Not found");
        return NULL;
    }

    else if(root->id == id){
        puts("Found!");
        strcpy(root->name, newName);
        return root;
    }
}

int main(){
    struct Student *root = NULL;
    puts("Inserting: ");
    root = insert(root, 3, "bill");
    root = insert(root, 1, "tom");
    root = insert(root, 16, "jake");
    root = insert(root, 78, "diana");
    root = insert(root, 33, "eve");

    puts("Insert Successfull!");
    
    // Transversal
    puts("Inorder Transversal: ");
    inorder(root);

    // searching
    struct Student *searchedStudent = search(root, 78);
    if(searchedStudent != NULL){
        printf("Found Student witd id %d and name %s\n", searchedStudent->id, searchedStudent->name);
    } else {
        printf("Student not found...");
    }
    
    // Updating
    puts("\nUpdatin:");
    struct Student *updateStudent = update(root, 1, "tommy");
    if(updateStudent != NULL){
        printf("Updated student with id %d, New Name is %s\n", updateStudent->id, updateStudent->name);
    }

    puts("Transversal After Updating");
    inorder(root);

    return 0;
}