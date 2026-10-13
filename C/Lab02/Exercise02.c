#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++){
        for(int j = 0; j < n - i - 1; j++){
            printf(" ");
        }
        for (int j = 0; j < 2 * (i + 1) - 1; j ++){
            printf("*");
        }
        printf("\n");
    }
}