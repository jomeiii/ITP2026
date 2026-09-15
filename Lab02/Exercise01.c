#include <stdio.h>

int main(){
    int stringSize;
    printf("Enter the string lenth: ");
    scanf("%d", &stringSize);
    char str[stringSize + 1];
    printf("Enter the string: ");
    scanf("%s", str);

    for (int i = stringSize - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }
    printf("\n");
    return 0;
}