#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5 // Jumlah Vertex

void createMatrix(int matrix[][MAX], int vertices){
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            matrix[i][j] = 0;
        }
    }
}

void addEdgeMatrix(int matrix[][MAX], int src, int dest){
    matrix[src][dest] = 1;
    matrix[dest][src] = 1;
}

void bfsMatrix(int matrix[][MAX], int vertices, int startVertex){
    //Step 1: Buat array untuk menyimpan status kunjungan vertex
    // dan inisialisasi semua vertex sebagai belum dikunjungi
    bool visited[vertices];
    for(int i = 0; i < vertices; i++){
        visited[i] = false; // belum ada vertex yang dikunjungi
    }

    // Step 2: Buat antrian untuk BFS
    int queue[vertices], front = -1, rear = -1;

    visited[startVertex] = true; // tandai vertex awal sebagai dikunjungi
    queue[rear++] = startVertex; // Masukkin vertex awal ke antrian
    
    // kita pengen looping BFS
    while(front < rear){
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // kita pengen explore vertex tersebut punya neighbors
        for(int i = 0; i < vertices; i++){
            if(matrix[currentVertex][i] == 1 && !visited[i]){
                visited[i] = true;
                queue[rear++] = i; // enqueue vertex yang belum dikunjungi
            }
        }
    }
}

void dfsMatrix(int matrix[][MAX], int vertices, int startVertex){
    bool visited[vertices]; // tandai vertex sebagai dikunjungi
    for(int i = 0; i < vertices; i++){
        visited[i] = false; // belum ada vertex yang dikunjungi
    }

    int stack[150], top = -1; // buat stack untuk DFS
    stack[++top] = startVertex; // masukkan vertex awal ke stack
    while(top >= 0){
        int currentVertex = stack[top--]; // ambil vertex dari stack
        if(!visited[currentVertex]){
            printf("%d ", currentVertex); // cetak vertex
            visited[currentVertex] = true; // tandai sebagai dikunjungi
        }

        // visit semua neighbors
        for(int i = vertices - 1; i >= 0; i--){
            if(matrix[currentVertex][i] == 1 && !visited[i]){
                stack[++top] = i; // masukkan neighbor ke stack
            }
        }
    }
}

void printMatrix(int matrix[][MAX], int vertices){
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int vertices = MAX;
    int matrix[MAX][MAX];
    
    createMatrix(matrix, vertices);

    addEdgeMatrix(matrix, 0, 1);
    addEdgeMatrix(matrix, 0, 2);
    addEdgeMatrix(matrix, 1, 2);
    addEdgeMatrix(matrix, 1, 3);
    addEdgeMatrix(matrix, 2, 4);

    puts("Matrix Adjacency:");
    printMatrix(matrix, vertices);
    
    puts("\nBFS Matrix:");
    bfsMatrix(matrix, vertices, 0); // Mulai dari vertex 0

    puts("\n\nDFS Matrix:");
    dfsMatrix(matrix, vertices, 0); // Mulai dari vertex 0

    return 0;
}