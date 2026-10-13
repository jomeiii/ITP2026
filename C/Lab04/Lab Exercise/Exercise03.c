#include <stdio.h>
#include <string.h>

union Union
{
    unsigned long long num;
    char mask[sizeof(unsigned long long)];
};

void encryption(union Union *u)
{
    for (int i = 0; i < sizeof(unsigned long long); i += 2)
    {
        char temp = u->mask[i];
        u->mask[i] = u->mask[i + 1];
        u->mask[i + 1] = temp;
    }
}

int main()
{
    union Union u;

    scanf("%llu", &u.num);
    printf("Original number: %llu\n", u.num);

    encryption(&u);
    printf("Encrypted number: %llu\n", u.num);

    encryption(&u);
    printf("Decrypted number: %llu\n", u.num);

    return 0;
}