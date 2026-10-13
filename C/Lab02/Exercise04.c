#include <stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[]){
    int a, b;
    printf("Enter two inteeger numbers: ");
    scanf("%d %d", &a, &b);
    printf("a = %d, b= %d\n", a, b);
    swap(&a, &b);
    printf("a = %d, b= %d\n", a, b);
    return 0;
}