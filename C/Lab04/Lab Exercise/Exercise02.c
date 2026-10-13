#include <stdio.h>
#include <string.h>

int main(){
    struct ExamDay{
        int day;
        char month[20];
        int year;
    } e;

    struct Student{
        char name[20];
        char surname[20];
        int group_number;
        struct ExamDay exam_day;
    } s;

    // -------- exam day --------
    printf("Enter exam day: ");
    scanf("%d", &e.day);

    printf("Enter exam month: ");
    char month[20];
    scanf("%s", month);
    strcpy(e.month, month);

    printf("Enter exam year: ");
    scanf("%d", &e.year);

    // -------- student --------
    printf("Enter student name and surname: ");
    char name[20];
    char surname[20];

    scanf("%s %s", name, surname);
    strcpy(s.name, name);
    strcpy(s.surname, surname);

    printf("Enter study group of student: ");
    scanf("%d", &s.group_number);

    s.exam_day = e;

    printf("Name: %s\nSurname: %s\nGroup number: %d\n", s.name, s.surname, s.group_number);
    printf("Exam day: %d %s %d\n", s.exam_day.day, s.exam_day.month, s.exam_day.year);

    return 0;
}