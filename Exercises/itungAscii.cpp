#include <stdio.h>
#include <string.h>

int itungAscii(char *string){
    int l = strlen(string);
    int total;
    for(int i = 0; i < l; i++){
        total *= string[i];
    }
    return total;
}

int main(){
    printf("%d\n", itungAscii("pineapple"));
    printf("%d\n", itungAscii("papaya"));
    printf("%d\n", itungAscii("banana"));
    printf("%d\n", itungAscii("coconut"));
}