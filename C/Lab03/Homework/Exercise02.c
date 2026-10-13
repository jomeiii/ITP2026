#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        int duplicate = 0;

        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate == 0) {
            printf("%d ", arr[i]);
        }
    }

    printf("\n");
    return 0;
}