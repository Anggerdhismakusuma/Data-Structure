#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char *name;
	int ID;
	int price;
	struct node *next;
} *h, *t;

int count = 1;

void pushMid(char *poke){
	node* c = (node*) malloc(sizeof(node));
	c->name = (char*)malloc(strlen(poke));
	strcpy(c->name, poke);
	c->next = NULL;
	c->ID = count++;
	c->price = 100;

	if(!h){
		h = t = c;
		return;
	}
	
	if(strcmp(poke, h->name) < 0){
		c->next = h;
		h = c;
		return;
	}
	
	if(strcmp(poke, t->name) > 0){
		t->next = c;
		t = c;
		return;
	}
	
	node *temp = h;
	while(temp->next != NULL && strcmp(temp->next->name, poke) < 0){
		temp = temp->next;
	}

	c->next = temp->next;
	temp->next = c;
}

void tukerPokemon(char *dicari, char *diganti){
    if (h == NULL){ // Kalau Head ga ada
        return;
	}

    if(strcmp(h->name, dicari) == 0){ // Kalau di head ketemu target
        struct node *temp = h; // buat temp untuk nampung head
        h = h->next; // Buat title head ke setelah head
        temp->next = NULL; // Temp yang tadinya punya title head awal di putus dengan Next di jadiin NULL
        free(temp); // Jangan lupa Free biar ga kepake
    } else { // Kalau di mid - akhir ketemu target
        struct node *temp1 = h; // Buat temp 1 buat ke target - 1
        struct node *temp2 = h->next;  // Buat temp 2 buat ke target
        while (strcmp(temp2->name, dicari) != 0){ // Selama belum nemu, di next next mulu kedua temp
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        temp1->next = temp2->next; // Buat si target - 1 itu nyambung ke nextnya target
        temp2->next = NULL; // Putus si target dengan Next jadiin Null
        free(temp2); // Jangan lupa Free target
    }
	
	count--;
	pushMid(diganti);
}

void jualPokemon(char *dicari){
    if (h == NULL){ // Kalau Head ga ada
        return;
	}

    if(strcmp(h->name, dicari) == 0){ // Kalau di head ketemu target
        struct node *temp = h; // buat temp untuk nampung head
        h = h->next; // Buat title head ke setelah head
        temp->next = NULL; // Temp yang tadinya punya title head awal di putus dengan Next di jadiin NULL
        free(temp); // Jangan lupa Free biar ga kepake
    } else { // Kalau di mid - akhir ketemu target
        struct node *temp1 = h; // Buat temp 1 buat ke target - 1
        struct node *temp2 = h->next;  // Buat temp 2 buat ke target
        while (strcmp(temp2->name, dicari) != 0){ // Selama belum nemu, di next next mulu kedua temp
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        temp1->next = temp2->next; // Buat si target - 1 itu nyambung ke nextnya target
        temp2->next = NULL; // Putus si target dengan Next jadiin Null
        free(temp2); // Jangan lupa Free target
    }
}

void printList(){
	struct node *temp = h;
	while (temp != NULL){
		puts("======================");
		printf("Name: %s\n", temp->name);
		printf("ID: %d\n", temp->ID);
		printf("Price: 100 Gold\n");
		temp = temp->next;
	}
	puts("======================");
}

int main(){
	int n;
	char *poke = NULL;
	
	// INPUT POKEMON
	printf("Masukkan berapa pokemon yang anda punya: ");
	scanf("%d", &n);
	
	for(int i = 0 ; i < n; i++){
		printf("Masukkan Nama Pokemon %d: ", i+1);
		poke = (char *)malloc(100 * sizeof(char));
		getchar();
		scanf("%[^\n]", poke);
		pushMid(poke);
	}
	
	printList();
	
	// tuker Nidoran sama Charmander
    char *dicari = (char*) malloc(sizeof(char));
    char *diganti = (char*) malloc(sizeof(char));
    
    printf("Masukkan pokemon yang ingin ditukar: ");
    scanf("%s", dicari); getchar();
    
    printf("Masukkan pokemon yang akan diganti: ");
    scanf("%s", diganti); getchar();
    
    tukerPokemon(dicari, diganti);
	
	printList();

    puts("#########################################");

    // beli pikachu
    char *nama = (char*)malloc(sizeof(char));
    printf("Masukkan nama pokemon yang diincar: ");
    scanf("%s", nama); getchar();
    pushMid(nama);

    printList();

    puts("#########################################");

    // jual zubat
    char *jualZubat = (char*)malloc(sizeof(char));
    printf("Masukkan nama pokemon yang ingin dijual: ");
    scanf("%s", jualZubat); getchar();
    jualPokemon(jualZubat);
    
    printList();

    puts("#########################################");
	return 0;
}