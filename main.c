#include <stdio.h>

union unionJob
{
    //defining a union
    char name[33];
    float salary;
    int workerNo;
    double fine;
} uJob;

struct structJob
{
    char name[33];
    float salary;
    int workerNo;
    double fine;
} sJob;

void compareUnionAndStruct()
{
    printf("--------------------unionVsStruct--------------------\n\n");
    printf("Size of union = %lu bytes\n", sizeof(uJob));
    printf("\tAddress of UNION name: %d\n", &uJob.name);
    printf("\tAddress of UNION salary: %d\n", &uJob.salary);
    printf("\tAddress of UNION workerNo: %d\n", &uJob.workerNo);

    printf("Size of structure = %lu bytes\n\n", sizeof(sJob));
    printf("\tAddress of STRUCT name: %d\n", &sJob.name);
    printf("\tAddress of STRUCT salary: %d\n", &sJob.salary);
    printf("\tAddress of STRUCT workerNo: %d\n", &sJob.workerNo);
}

int main(){
    compareUnionAndStruct();
    return 0;
}