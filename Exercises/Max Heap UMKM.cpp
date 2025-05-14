#include <stdio.h>
#define MAX 100

typedef struct warung{
    int size;
    int laba_bersih;
    int hpp;
    int laba_kotor = laba_bersih - hpp;
    int arr[MAX];
}warung;

void swap(warung *a, warung *b){
    warung* temp = a;
    *a = *b;
    *b = *temp;
}

int parent(int i){
    return (i - 1) / 2;
}

int leftChild(int i){
    return i * 2 + 1;
}

int rightChild(int i){
    return i * 2 + 2;
}

void insert(warung *heap, int value){
    if(heap->size == MAX){
        printf("Full\n");
        return;
    }

    int i = heap->size;
    heap->arr[i] = value;
    heap->size++;

    while(i != NULL && heap->arr[parent(i)] > heap->arr[i]){
        swap(&heap->arr[parent(i)], &heap->arr[i]);
        i = parent(i);
    }

}

void DownHeap(MinHeap *heap, int i){
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if(left < heap->size && heap->arr[left] < heap->arr[i]){
        smallest = left;
    }

    if(right < heap->size && heap->arr[right] < heap->arr[i]){
        smallest = right;
    }

    if(smallest != i){
        swap(&heap->arr[i], &heap->arr[smallest]);
        DownHeap(heap, smallest);
    }
}

int extract(MinHeap* heap){
    if(heap->size <= 0){
        printf("Empty\n");
        return -1;
    }

    int root = heap-> arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    DownHeap(heap, 0);
    return root;
}


void printHeap(MinHeap* heap){
    int j = 0;
    while(j < heap->size){
        printf("%d ", heap->arr[j]);
        j++;
    }
    printf("\n");
}

int main(){
    MinHeap heap;
    heap.size = 0;

    insert(&heap, 10);
    insert(&heap, 5);
    insert(&heap, 20);
    insert(&heap, 3);

    printHeap(&heap);

    extract(&heap);

    printHeap(&heap);
    return 0;
}