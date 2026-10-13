#include <stdio.h>

void input(int rows, int colums, int* p){
    for (int i = 0; i < rows; i++){
        printf("Enter element of %d row: ", i + 1);
        for (int j = 0; j < colums; j++){
            scanf("%d", p + i * colums + j);
        }
    }
}

void print(int rows, int colums, int* p){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < colums; j++){
            printf("%d ", *(p + i * colums + j));
        }
        printf("\n");
    }
}

int main(){
    int rows, colums;
    printf("Enter rows: ");
    scanf("%d", &rows);
    printf("Enter colums: ");
    scanf("%d", &colums);
    
    int matrix[rows][colums];

    input(rows, colums, matrix);
    print(rows, colums, matrix);

    return 0;
}