// Ketika kita mengalokasikan memori secara dynamic
// sebenarnya itu adalah memori dari struct (node)

#include <stdio.h>
#include <stdlib.h>

struct Student{
    int age;
    int height;
}arrStudent[5];

int main(){
    Student student;
    // akses anggota struct
    student.age = 20;
    student.height = 170;

    // Alokasi memory untuk struct
    Student* ptr = (Student*)malloc(sizeof(Student));

    // Akses anggota dari struct pointer
    ptr->age = 21;
    ptr->height = 175;

    printf("Age: %d, Height: %d\n", ptr->age, ptr->height);
    free(ptr);

    // akses anggota dari array of struct
    arrStudent[0].age = 12;
    arrStudent[1].age = 13;
    return 0;
}