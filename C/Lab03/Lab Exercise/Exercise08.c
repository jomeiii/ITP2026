#include <stdio.h>

int main(){
    char str[1000];
    fgets(str, sizeof(str), stdin);

    int lenght = 0;
    char* p;

    p = str;

    while (*p != '\0'){
        if (*p != '\n'){
            lenght++;
        }
        p++;
    }

    printf("Length of string is: %d\n", lenght);
    return 0;
}