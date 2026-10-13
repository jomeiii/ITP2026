#include <stdio.h>
#include <stdlib.h>

void print_triangle(int n){
    printf("Print triangle\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < i + 1; j++){
            printf("*");
        }
        printf("\n");
    }
}

void print_diamond(int n){
    printf("Print diamond\n");
    int height = n / 2;

    for (int i = 0; i < n; i++){
        if (i < height){
            for (int j = 0; j < i + 1; j++){
                printf("*");
            }
            printf("\n");
        }
        else{
            for (int j = height - (i - height); j > 0; j--){
                printf("*");
            }
            printf("\n");
        }
    }
}

void peint_rectangle(int n){
    printf("Print rectangle\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("*");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    print_triangle(n);
    print_diamond(n);
    peint_rectangle(n);
    return 0;
}