#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Node{
	char name[20];
	char ticket[20];
	int prio;
	struct Node *next;
	struct Node *prev;
} *h, *t;

int pc = 0;

int getPrio(char *ticket){
	int prio;
	if(strcmp(ticket, "FAST_TRACK")){
		prio = 2; 
	} else if(strcmp(ticket, "REGULER")){
		prio = 1;
	}
	
	return prio;
}

struct Node *newNode(char *name, char *ticket, int prio){
	struct Node *c = (Node*)malloc(sizeof(Node));
	strcpy(c->name, name);
	strcpy(c->ticket, ticket);
	c->prio = prio;
	c->next = NULL;
	c->prev = NULL;
	
	return c;
}

void push(Node *c){
	if(h == NULL){
		h = t = c;
	} else if(c->prio > h->prio){
		c->next = h;
		h->prev = c;
		h = c;
	} else if(c->prio < h->prio){
		t->next = c;
		c->prev = t;
		t = c;
	} else {
		struct Node *temp = h;
		while(temp->prio >= temp->next->prio){
			temp = temp->next;
		}
		c->next = temp->next;
		temp->next = c;
		c->prev = temp;
	}
}

void view(){
	struct Node *temp = h;
	int count = 1;
	while(temp){
		printf("%d %s %s\n", count, temp->name, temp->ticket);
		count++;
		temp = temp->next;
	}
}

void reg(int n){
	char name[20];
	char ticket[20];
	int prio;
	
	scanf("%s %s", name, ticket);
	prio = getPrio(ticket);
	struct Node *c = newNode(name, ticket, prio);
	push(c);
	pc++;
	
	view();
}

void pop(char *name){
	if(strcmp(h->name, name) == 0){
		struct Node *temp = h;
		h = h->next;
		h->prev = NULL;
		free(temp);
	} else if(strcmp(t->name, name)){
		struct Node *temp = t;
		t = t->prev;
		t->next = NULL;
		free(temp); 
	} else {
		struct Node* temp = h;
		while(strcmp(temp->next->name, name) != 0){
			temp = temp->next;
		}
		struct Node *toPop = temp->next;
		temp->next = toPop->next;
		toPop->next->prev = temp;
		free(toPop);
	}
}

void remove(int n){
	for(int i = 0; i < n; i++){
		char name[20];
		scanf("%s", name);
		
		pop(name);
		pc--;
	}
	view();
}

void call(){
	if(h == NULL) return;
	else{
		if (h == NULL) return;
    for (int i = 0; i < 4; i++) {
        if (h == NULL) break;
        Node *temp = h;
        printf("%s ", temp->name);
        h = h->next;
        if (h != NULL) {
            h->prev = NULL;
        }
        free(temp);
        pc--;
    }
    puts("got into the boat.");
    printf("%d queues remaining.\n", pc);

	}
}

int main(){
	char inp[100];
    do {
        scanf("%s", inp);
        if (strcmp(inp, "REGISTER") == 0) {
            int a;
            scanf("%d", &a);
            reg(a);
        } else if (strcmp(inp, "REMOVE") == 0) {
            int a;
            scanf("%d", &a);
            remove(a);
        } else if (strcmp(inp, "CALL") == 0) {
            call();
        }
    } while (1);
    return 0;
}
