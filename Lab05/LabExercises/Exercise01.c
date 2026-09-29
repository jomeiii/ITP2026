#include <stdio.h>
#define BASE_YEAR 1898

int main(){
    struct date {
        unsigned short day : 5;
        unsigned short month : 4;
        unsigned short year : 7;
    };

    struct date my_date = {
        1, 1, 2008 - BASE_YEAR
    };

    printf("DAY: %d, MOUTH: %d, YEAR: %d\n", my_date.day, my_date.month, BASE_YEAR + my_date.year);

    return 0;
}