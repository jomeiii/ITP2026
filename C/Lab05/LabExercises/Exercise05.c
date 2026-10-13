#include <stdio.h>
#include <string.h>

typedef enum {
    STUDENT,
    TA,
    PROFESSOR
} moodle_role;

typedef enum {
    SECONDARY,
    BACHELOR,
    MASTER,
    PHD
} degree;

typedef struct {
    char name[20];
    moodle_role moodleRole;
    degree degree;
} moodle_member;

const char* role[] = {"Student", "TA", "Professor"};
const char* degrees[] = {"Secondary", "Bachelor", "Master", "PhD"};

moodle_role convert_to_role(char* str) {
    if (strcmp(str, role[STUDENT]) == 0) {
        return STUDENT;
    }
    else if (strcmp(str, role[TA]) == 0) {
        return TA;
    }
    else if (strcmp(str, role[PROFESSOR]) == 0) {
        return PROFESSOR;
    }
}

// Converts a string to a degree.
degree convert_to_degree(char* str) {
    if (strcmp(str, degrees[SECONDARY]) == 0) {
        return SECONDARY;
    }
    else if (strcmp(str, degrees[BACHELOR]) == 0) {
        return BACHELOR;
    }
    else if (strcmp(str, degrees[MASTER]) == 0) {
        return MASTER;
    }
    else if (strcmp(str, degrees[PHD]) == 0) {
        return PHD;
    }
}

int main() {
    int amount_user;

    printf("Enter how many Moodle users to read: ");
    scanf("%d", &amount_user);

    moodle_member users[amount_user];

    for (int i = 0; i < amount_user; i++) {
        printf("Enter name of %d user: ", i + 1);
        scanf("%s", users[i].name);

        char role_buff[20], degree_buff[20];

        printf("Enter role and degree of user: ");
        scanf("%s %s", role_buff, degree_buff);

        users[i].moodleRole = convert_to_role(role_buff);
        users[i].degree = convert_to_degree(degree_buff);
    }

    for (int i = 0; i < amount_user - 1; i++) {
        for (int j = i + 1; j < amount_user; j++) {

            if (users[i].moodleRole > users[j].moodleRole ||
                (users[i].moodleRole == users[j].moodleRole &&
                 users[i].degree > users[j].degree)) {

                moodle_member temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    for (int i = 0; i < amount_user; i++) {
        printf("%s %s %s\n",
               users[i].name,
               role[users[i].moodleRole],
               degrees[users[i].degree]);
    }

    return 0;
}