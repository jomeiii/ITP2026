#include <stdio.h>

enum days{
        MONDAY = 1,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    };

char* convert_enum(enum days day){
    switch (day)
    {
    case 1:
        return "MONDAY";
    case 2:
        return "TUESDAY";
    case 3:
        return "WEDNESDAY";
    case 4:
        return "THURSDAY";
    case 5:
        return "FRIDAY";
    case 6:
        return "SATURDAY";
    case 7:
        return "SUNDAY";
    default:
        return "ERROR";
    }
}

int main(){
    int user_input;
    scanf("%d" , &user_input);
    printf("%s\n", convert_enum(user_input));
    return 0;
}