// Pointer: Variable yang bisa menyimpan / menunjuk memory address
// pointer data_type* varName = value; ex: int* ptr = &a;
// & untuk menunjuk ke memory
// * untuk menunjuk value

#include <stdio.h>
#include <stdlib.h>

// int main(){
//     int a = 10;
//     int* ptr = &a;
//     *ptr = 50;
//     printf("memory dari ptr: %d\n", &ptr);
//     printf("value dari ptr: %d\n", ptr);
//     printf("value dari memory yang disimpan: %d\n", *ptr);
//     return 0;
// }

// STATIC ALLOCATION (array)
// int arr[3];
// sebelum run time sudah menentukan besaran memori yang akan dipakai

// DYNAMIC ALLOCATION (malloc, calloc) #stdlib.h
// untuk mengalokasikan memori dengan menentukan seberapa besar byte yang kita inginkan
int main() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 20;
    printf("value : %d\n", *ptr);
    printf("alamat : %d", ptr);
    return 0;
}