#include <stdio.h>
#include <string.h>

int fact(int n){
    if (n <= 1){
        return 1;
    }

    return n * fact(n - 1);
}

int main(){
    int a = 1;
    int b = 200;

    for (int i = a; i <= b; i++) {
        int s = 0;
        int x = i;
        while (x >= 1){
            s += fact(x % 10);
            x /= 10;
        }

        if (s == i){
            printf("%d\n", i);
        }
    }

    return 0;
}