#include <stdio.h>

int main(){
    int numberOfAttempts = 0;
    char userPassword[4];
    fgets(userPassword, sizeof(userPassword), stdin);

    for (int i = 0; userPassword[i] != '\0'; i++){
        if (userPassword[i] == '\n'){
            userPassword[i] = '\0';
            break;
        }
    }
    
    // 1 char
    for (int i = 32; i < 127; i++){
        char tryPassword[4] = {i,'\0'};
        numberOfAttempts++;
        if(userPassword[0] == tryPassword[0] && userPassword[1] == tryPassword[1]){
                printf("found = %s\n", tryPassword);
                printf("number of attempts = %d\n", numberOfAttempts);
                return 0;
            }
    }

    // 2 chars
    for (int i = 32; i < 127; i++){
        for (int j = 32; j < 127; j++){
            char tryPassword[4] = {i, j,'\0'};
            numberOfAttempts++;
            if(userPassword[0] == tryPassword[0] && userPassword[1] == tryPassword[1] &&
                userPassword[2] == tryPassword[2]){
                    printf("found = %s\n", tryPassword);
                    printf("number of attempts = %d\n", numberOfAttempts);
                    return 0;
                }
        }
    }

    // 3 chars
    for (int i = 32; i < 127; i++){
        for (int j = 32; j < 127; j++){
            for (int k = 32; k < 127; k++){
                char tryPassword[4] = {i, j, k, '\0'};
                numberOfAttempts++;
                if(userPassword[0] == tryPassword[0] && userPassword[1] == tryPassword[1] &&
                    userPassword[2] == tryPassword[2] && userPassword[3] == tryPassword[3]){
                        printf("found = %s\n", tryPassword);
                        printf("number of attempts = %d\n", numberOfAttempts);
                        return 0;
                    }
            }
        }
    }
    return 0;
}