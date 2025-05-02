#include <stdio.h>
#define MAX_HEAP_SIZE 1000

int heap[MAX_HEAP_SIZE];
int heapSize = 0;

int left(int n){
    return 2 * n + 1;
}

int right(int n){
    return 2 * n + 2;
}

int parent(int n){
    return (n - 1) / 2;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertHeap(int value){
    if(heapSize == MAX_HEAP_SIZE){
        printf("Heap is full\n");
        return;
    }
    int n = heapSize++;
    heap[n] = value;
    while(n != 0 && heap[n] < heap[parent(n)]){
        swap(&heap[parent(n)], &heap[n]);
        n = parent(n);
    }
}

int popHeap(){
    if(heapSize == 0){
        printf("Heap is empty\n");
        return -1;
    }
    int toPop = heap[0];
    heap[0] = heap[--heapSize];
    int n = 0;
    while(left(n) < heapSize){
        int t = left(n);
        if(right(n) < heapSize && heap[right(n)] < heap[left(n)]){
            t = right(n);
        }
        if(heap[t] < heap[n]){
            swap(&heap[t], &heap[n]);
            n = t;
        } else {
            break;
        }
    }
    return toPop;
}

void printHeapAsArray(){
    for(int i = 0; i < heapSize; i++){
        printf("%d -> ", heap[i]);
    }
    printf("\n");
}

int main() {
    insertHeap(9);
    printHeapAsArray();
    insertHeap(19);
    printHeapAsArray();
    insertHeap(36);
    printHeapAsArray();
    insertHeap(8);
    printHeapAsArray();
    insertHeap(10);
    printHeapAsArray();
    insertHeap(12);
    printHeapAsArray();
    insertHeap(5);
    printHeapAsArray();
    
    puts("==========================");
    printf("You have pop: %d\n", popHeap());
    printHeapAsArray();
    printf("You have pop: %d\n", popHeap());
    printHeapAsArray();
    printf("You have pop: %d\n", popHeap());
    printHeapAsArray();
    printf("You have pop: %d\n", popHeap());
    printHeapAsArray();
    printf("You have pop: %d\n", popHeap());
    printHeapAsArray();

    return 0;
}