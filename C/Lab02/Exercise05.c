#include <stdio.h>

int main() {
    char text[1000];
    printf("Enter a line of text: ");
    fgets(text, sizeof(text), stdin);
    FILE *file = fopen("output.txt", "w");
    fputs(text, file);
    fclose(file);
    return 0;
}