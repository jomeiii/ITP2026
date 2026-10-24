#include <stdio.h>
#include <string.h>
#include "data.h"

void print(char* str){
    printf("============ %s ============\n", str);
}

// extern int score;

int a(char* str){
    return 12;
}

int main (){
    print("extern variable");
    extern int score;

    score = 14;
    print_score();

    print("pointers");
    int x;
    int* y;
    x = 1111;
    y = &x;

    (*y)++;
    printf("%d\n", *y);

    print("array pointers");
    int arr[] = {1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10};
    int* arrP;
    arrP = arr;
    printf("%d\n", *arrP++);
    printf("%d\n", *arrP);

    print("pointer to functions");
    extern int score;
    score = 1890;
    void (*pf)(void) = &print_score;
    pf();
    (*pf)();

    int (*pff)(char*) = &a;
    int res = pff("STRING");
    printf("%d\n", pff("STRING"));

    print("string pointer");
    char string1[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char string2[] = "Hello";

    if (strcmp(string1, string2) == 0){
        printf("They're equal\n");
    }
    else{
        printf("They aren't equal\n");
    }

    print("print elements of array using pointer");
    int integers_array[] = {1, 4, 8, 8, 1488, 123, 777};
    int* a_p = integers_array;

    for (int i = 0; i < 7; i++){
        printf("%d\n", *(a_p+i));
    }

    print("loops");
    for(int i = 0; i < 10; i++){
        if (i == 5){
            i++;
        }
        printf("%d ", i);
    }
    printf("\n");

    print("copy of string");
    char source[] = "Tyler Durden";
    char destination[20];

    char* p1 = destination;
    char* p2 = source;

    while (*p1++ = *p2++);

    printf("%s\n", destination);

    return 0;
}