#include <stdio.h>

int main(){
    char str[1000];
    char letters[26];
    int count[26];

    fgets(str, sizeof(str), stdin);

    for (int i = 0; i < 26; i++){
        count[i] = 0;
        letters[i] = 'a' + i;
    }

    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] >= 'a' && str[i] <= 'z'){
            count[str[i] - 'a']++;
        }
    }

    for (int i = 0; i < 26; i++){
        int max = i;
        for (int j = i + 1; j < 26; j++){
            if (count[j] > count[max]){
                max = j;
            }
        }
        int temp = count[i];
        count[i] = count[max];
        count[max] = temp;

        char charTemp = letters[i];
        letters[i] = letters[max];
        letters[max] = charTemp;
    }

    for (int i = 0; i < 26; i++){
        if (count[i] != 0){
            printf("%c ", letters[i]);
            for (int j = 0; j < count[i]; j++){
                printf(".");
            }
            printf("\n");
        }
    }
    printf("\n");
    for (int i = 0; i < 26; i++){
        if (count[i] != 0){
            printf("%c ", letters[i]);
        }
    }
    printf("\n");
    for (int i = 1; i <= count[0]; i++){
        for (int j = 0; j < 26; j++){
            if (count[j] >= i){
                printf(". ");
            }
        }
        printf("\n");
    }

    return 0;
}