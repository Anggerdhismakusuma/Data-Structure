#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	char name[101];
	int price;
	char category[30];
	char avail[50];
	int height;
	node *left;
	node *right;
}*Node = NULL;

int count = 0;

node* createNode(char *name, int price, char* category, char* avail){
	node* newNode = (node*)malloc(sizeof(node));
	strcpy(newNode->name, name);
	newNode->price = price;
	strcpy(newNode->category, category);
	strcpy(newNode->avail, avail);
	newNode->height = 1;
	newNode->right = newNode->left = NULL;
	return newNode;	
}

void enterToContinue(){
	printf("Press ENTER to continue ..."); getchar();
}

int max(int a, int b){
	return a > b ? a : b;
}

int height(node* root){
	if(root == NULL) return 0;
	return root->height;
}

int getBalanceFactor(node* root){
	if(root == NULL) return 0;
	return height(root->left) - height(root->right);
}

node* leftRotate(node* x){
	node* y = x->right;
	node* z = y->left;
	
	y->left = x;
	x->right = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

node* rightRotate(node* x){
	node* y = x->left;
	node* z = y->right;
	
	y->right = x;
	x->left = z;
	
	x->height = max(height(x->right), height(x->left)) + 1;
	y->height = max(height(y->right), height(y->left)) + 1;
	
	return y;
}

int validationName(char* name){
	if(strncmp(name, "Sally", 5) != 0 || strlen(name) < 10 || strlen(name) > 25){
		return -1;
	}
	
	int space = 0, letterAfterSpace = 0, flag = 0, x = strlen(name);
	
	for(int i = 0; i < x; i++){
		if(name[i] == ' ' && flag == 0){
			space++;
			flag = 1;
		}
		
		if(name[i] != ' ' && flag == 0){
			letterAfterSpace++;
			flag = 0;
		}
	}
	
	if(space > 0 && letterAfterSpace > 0){
		return 1;
	}
	
	return -1;
}

node* insertAVL(node* root, node* newNode){
	if(root == NULL) return newNode;
	else if(strcmp(root->name, newNode->name) > 0) root->left = insertAVL(root->left, newNode);
	else if(strcmp(root->name, newNode->name) < 0) root->right = insertAVL(root->right, newNode);
	else return root;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = getBalanceFactor(root);
	
	if(balance > 1){
		if(getBalanceFactor(root->left)) return rightRotate(root);
		else{
			root->left = leftRotate(root);
			return rightRotate(root);
		}
	}	
	
	if(balance < -1){
		if(getBalanceFactor(root->right)) return leftRotate(root);
		else{
			root->right = rightRotate(root);
			return leftRotate(root);
		}
	}
	
	return root;
}

node* deleteAVL(node* root, char *name){
	if(root == NULL) return NULL;
	else if(strcmp(root->name, name) > 0) root->left = deleteAVL(root->left, name);
	else if(strcmp(root->name, name) < 0) root->right = deleteAVL(root->right, name);
	else {
		if(root->left == NULL && root->right == NULL){
			free(root);
			return NULL;
		} else if(root->left == NULL || root->right == NULL){
			node* temp = root->left ? root->left : root->right;
			free(root);
			return NULL;
		} else{
			node* temp = root->left;
			
			while(temp->right){
				temp = temp->right;
			}
			
			// copy nilai predecesor
			strcpy(root->name, temp->name);
			strcpy(root->category, temp->category);
			strcpy(root->avail, temp->avail);
			temp->price = root->price;
			
			root->left = deleteAVL(root->left, temp->name);
		}
	}

	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = getBalanceFactor(root);
	
	if(balance > 1){
		if(getBalanceFactor(root->left)) return rightRotate(root);
		else{
			root->left = leftRotate(root);
			return rightRotate(root);
		}
	}	
	
	if(balance < -1){
		if(getBalanceFactor(root->right)) return leftRotate(root);
		else{
			root->right = rightRotate(root);
			return leftRotate(root);
		}
	}
	
	return root;
}

node* insert(node* root){
	system("cls");
	
	char name[101], category[50], availibility[50];
	int price;
	
	do{
		printf("Input the treatment name: ");
		scanf("%[^\n]", name); getchar();
	}while(validationName(name) == -1);
	
	do{
		printf("Input your product category [Hair Care | Body Care | Nail Care]: ");
		scanf("%[^\n]", category); getchar();
	}while(strcmp(category, "Hair Care") != 0 && strcmp(category, "Body Care") != 0 && strcmp(category, "Nail Care") != 0);
	
	do{
		printf("Input treatment availibility for home service [Available | Unavailable]: ");
		scanf("%s", category); getchar();
	}while(strcmp(category, "Available") && strcmp(category, "Unavailable"));
	
	do{
		printf("Input treatment price: ");
		scanf("%d", &price); getchar();
	}while(price < 50000 || price > 10000000);
	
	node* newNode = createNode(name, price, category, availibility);
	root = insertAVL(root, newNode);
	
	printf("New Treatment is Added Successfully\n");
	enterToContinue();
	
	return root;
}

void preOrder(node* root){
	printf("%s\n", root->name);
	printf("Treament: %s\n", root->name);
	printf("Category: %s\n", root->category);
	printf("Price: %d\n", root->price);
	printf("Home Service: %s\n", root->avail);
	printf("---------------------------------\n");
	preOrder(root->left);
	preOrder(root->right);
}

void postOrder(node* root){
	printf("%s\n", root->name);
	postOrder(root->left);
	postOrder(root->right);
	printf("Treament: %s\n", root->name);
	printf("Category: %s\n", root->category);
	printf("Price: %d\n", root->price);
	printf("Home Service: %s\n", root->avail);
	printf("---------------------------------\n");
}

void inOrder(node* root){
	if(!root) return;
	inOrder(root->left);
	printf("Treament: %s\n", root->name);
	printf("Category: %s\n", root->category);
	printf("Price: %d\n", root->price);
	printf("Home Service: %s\n", root->avail);
	printf("---------------------------------\n");
	inOrder(root->right);
}

void view(node* root){
	if(!root) {
		printf("No Data\n");
		return;
	}
	
	char mode[10];
	
	do{
		printf("Insert view mode [pre | in | post]: ");
		scanf("%s", mode);
	}while(strcmp(mode, "pre") != 0 && strcmp(mode, "in") != 0 && strcmp(mode, "post") != 0);

	if(strcmp(mode, "pre") == 0) preOrder(root);
	else if(strcmp(mode, "in") == 0) inOrder(root);
	else if(strcmp(mode, "post") == 0) postOrder(root);
	
	enterToContinue();
}

int alreadyInTree(node* root, char* name){
	if(root == NULL) return -1;
	if(strcmp(root->name, name) == 0) return 1;
	
	int leftSide = alreadyInTree(root->left, name);
	if(leftSide == 1) return 1;
	return alreadyInTree(root->right, name);
}

node* del(node* root){
	system("cls");
	if(!root){
		printf("No Data\n");
		enterToContinue();
		return root;
	}
	
	char name[101];
	
	printf("DELETE TREATMENT:\n");
	printf("Input treatment name to be deleted: ");
	scanf("%[^\n]", name); getchar();
	
	if(alreadyInTree(root, name) == 1){
		deleteAVL(root, name);
		printf("Data Successfully Deleted\n");
		count--;
	} else {
		printf("Data does't exist\n");
	}
	
	enterToContinue();
	return root;
}

int main(){
	int choice = -1;
	do{
		do{
			printf("=====================\n");
			printf("Sally Salon\n");
			printf("=====================\n");
			printf("1. View Available Treatment\n");
			printf("2. Insert New Treatment\n");
			printf("3. Delete Treatment\n");
			printf("4. Exit\n");
			printf("[1-4]\n");
			printf(">> ");
			scanf("%d", &choice); getchar();
		}while(choice < 1 || choice > 4);
		
		switch(choice){
			case 1:
				view(Node);
				break;
			case 2:
				Node = insert(Node);
				count++;
				break;
			case 3:
				Node = del(Node);
				break;
			case 4:
				printf("Sayonalaaa ^_^");
				return 0;
		}
	}while(1);
	return 0;
}
