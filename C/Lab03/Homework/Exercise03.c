#include <stdio.h>

int main(){
    char str[1000];
    fgets(str, sizeof(str), stdin);

    char* pOld;
    char* pNew;
    char nStr[1000];

    pOld = str;
    pNew = nStr;
    while(*pOld != '\0'){
        if (*pOld != '\n'){
            *pNew = *pOld;
            pNew++;
        }
        pOld++;
    }

    printf("Old string: %s", str);
    printf("Copy string: %s\n", nStr);

    return 0;
}