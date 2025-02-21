#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Visitor {
    char name[11];
    char ticket[11];
    struct Visitor *next;
    struct Visitor *prev;
};

struct Queue {
    Visitor *head;
    Visitor *tail;
};

void initQueue(Queue *q) {
    q->head = q->tail = NULL;
}

void enqueue(Queue *q, char *name, char *ticket) {
    Visitor *newVisitor = (Visitor*)malloc(sizeof(Visitor));
    strcpy(newVisitor->name, name);
    strcpy(newVisitor->ticket, ticket);
    newVisitor->next = newVisitor->prev = NULL;
    
    if (!q->head) {
        q->head = q->tail = newVisitor;
    } else {
        Visitor *current = q->head;
        while (current && strcmp(current->ticket, "FAST_TRACK") == 0) {
            current = current->next;
        }
        if (!current) {
            q->tail->next = newVisitor;
            newVisitor->prev = q->tail;
            q->tail = newVisitor;
        } else {
            newVisitor->next = current;
            newVisitor->prev = current->prev;
            if (current->prev) {
                current->prev->next = newVisitor;
            } else {
                q->head = newVisitor;
            }
            current->prev = newVisitor;
        }
    }
}

void dequeue(Queue *q) {
    if (!q->head) {
        printf("No visitors in queue\n");
        return;
    }
    int count = 0;
    while (q->head && count < 4) {
        Visitor *temp = q->head;
        printf("%s%s", temp->name, (count < 3 && temp->next) ? ", " : "");
        q->head = q->head->next;
        if (q->head) q->head->prev = NULL;
        free(temp);
        count++;
    }
    printf("got into the boat\n");
    int remaining = 0;
    Visitor *current = q->head;
    while (current) {
        remaining++;
        current = current->next;
    }
    printf("%d queues remaining\n", remaining);
}

void removeVisitor(Queue *q, char *name) {
    Visitor *current = q->head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                q->head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                q->tail = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    }
}

void printQueue(Queue *q) {
    Visitor *current = q->head;
    int index = 1;
    while (current) {
        printf("%d %s %s\n", index++, current->name, current->ticket);
        current = current->next;
    }
}

int main() {
    Queue queue;
    initQueue(&queue);
    char command[10];
    int n;
    while (1) {
        scanf("%s", command);
        if (strcmp(command, "REGISTER") == 0) {
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                char name[11], ticket[11];
                scanf("%s %s", name, ticket);
                enqueue(&queue, name, ticket);
            }
            printQueue(&queue);
        } else if (strcmp(command, "CALL") == 0) {
            dequeue(&queue);
        } else if (strcmp(command, "REMOVE") == 0) {
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                char name[11];
                scanf("%s", name);
                removeVisitor(&queue, name);
            }
            printQueue(&queue);
        } else if (strcmp(command, "EXIT") == 0) {
            break;
        }
    }
    return 0;
}