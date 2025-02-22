#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

struct node {
    char value;
    struct node* left;
    struct node* right;
};

struct node *createnode(char value) {
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->value = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

int isoperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void buildpreftree(struct node **root, char prefeq[], int *pos) {
    *root = createnode(prefeq[*pos]);
	if(*root == NULL){
		*root = createnode(prefeq[*pos]);
	}
    if (isoperator(prefeq[*pos])) {
    	*pos = *pos + 1;
        (*root)->left = createnode(prefeq[*pos]);
        buildpreftree(&(*root)->left, prefeq, pos);
        
        *pos = *pos + 1;
        (*root)->right = createnode(prefeq[*pos]);
        buildpreftree(&(*root)->right, prefeq, pos);
    }
}

void buildinfixtree(struct node** root, char infix[], int* pos) {
    *root = NULL;
    struct node* stack[100];
    int top = -1;
    struct node* opStack[100];
    int opTop = -1;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            stack[++top] = createnode(infix[i]);
        } else if (isoperator(infix[i])) {
            while (opTop != -1 && isoperator(opStack[opTop]->value) >= isoperator(infix[i])) {
                struct node* operatorNode = opStack[opTop--];
                operatorNode->right = stack[top--];
                operatorNode->left = stack[top--];
                stack[++top] = operatorNode;
            }
            opStack[++opTop] = createnode(infix[i]);
        }
    }
    while (opTop != -1) {
        struct node* operatorNode = opStack[opTop--];
        operatorNode->right = stack[top--];
        operatorNode->left = stack[top--];
        stack[++top] = operatorNode;
    }
    *root = stack[top];
}

void inorder(struct node* root) {
    if (root == NULL) return;
    if(isoperator(root->value)) putchar('(');
    inorder(root->left);
    printf("%c ", root->value);
    inorder(root->right);
    if(isoperator(root->value)) putchar(')');
}

void preorder(struct node* root) {
    if (root == NULL) return;
    printf("%c ", root->value);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->value);
}

int evaluate(node* root){
	if(root->value == '+'){
		return evaluate(root->left) + evaluate(root->right);
	}else if(root->value == '-'){
		return evaluate(root->left) - evaluate(root->right);
	}else if(root->value == '/'){
		return evaluate(root->left) / evaluate(root->right);
	}else if(root->value == '*'){
		return evaluate(root->left) * evaluate(root->right);
	}else if(root->value == '^'){
		return (int) pow(evaluate(root->left), evaluate(root->right));
	}else{
		return root->value - '0';
	}
}

node* buildposttree(char postfix[]){
	node* stack[100];
	int top = -1;
	for(int i = 0; postfix[i] != '\0'; i++){
		node* newnode = createnode(postfix[i]);
		if(isdigit(postfix[i])){
			stack[++top] = newnode;
		}else if(isoperator(postfix[i])){
			newnode->right = stack[top--];
			newnode->left = stack[top--];
			stack[++top] = newnode;
		}
	}
	return stack[top];
}

int main() {
    char prefeq[] = "+*234"; 
    char posteq[] = "351^+";
    char infeq[] = "(5+3)^2";
    int pos = 0;
    struct node* root = NULL;

    buildpreftree(&root, prefeq, &pos);

    printf("Inorder traversal of expression tree: ");
    inorder(root);
    printf("\n");
    int res = evaluate(root);
    printf("%d\n", res);
    printf("\n");
    
    printf("Preorder traversal of expression tree: ");
    preorder(root);
	printf("\n");
    int res1 = evaluate(root);
    printf("%d\n", res1);
    printf("\n");
    
    printf("Postorder traversal of expression tree: ");
    postorder(root);
    printf("\n");
    int res2 = evaluate(root);
    printf("%d\n", res2);
    printf("\n");
    
    node* posttree = buildposttree(posteq);
    inorder(posttree);
    printf("\n");
    int res3 = evaluate(posttree);
    printf("%d\n", res3);
    
    preorder(posttree);
    printf("\n");
    int res4 = evaluate(posttree);
    printf("%d\n", res4);
    
    buildinfixtree(&root, infeq, &pos);
    printf("\n");
    int res5 = evaluate(root);
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    preorder(root);
    printf("\n");

    printf("%d\n", res5);

    return 0;
}