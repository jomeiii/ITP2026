#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ACTIVE,
    RETIRED,
    DISQUALIFIED
} DriverStatus;

typedef enum {
    NORMAL_RACE,
    SPRINT_RACE
} RaceType;

typedef enum {
    FINISHED,
    DID_NOT_FINISH,
    DISQUALIFIED_RESULT
} ResultType;

typedef union {
    float finish_time;
    char *dnf_reason;
    char *disqualification_reason;
} ResultExtra;

typedef struct {
    int driver_id;
    int position;
    ResultType result_type;
    ResultExtra extra;
} RaceResult;

typedef struct {
    int driver_id;
    char *name;
    char *team;

    DriverStatus status;

    int races_completed;
    int wins;
    int points;
} Driver;

typedef struct{
    int race_id;
    RaceType race_type;

    RaceResult *results;
    int result_count;

    int finished;
    int dnf;
    int disqualified;
    int winner_id;
} FinishedRaceResult;


int normalRacePoints[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1, 0};
int sprintRacePoints[] = {8, 7, 6, 5, 4, 3, 2, 1, 0};

int find_drivers_index(int *driversIndexces, int driverID){
    return driversIndexces[driverID];
}

char* get_status_string(DriverStatus status){
    switch (status){
        case ACTIVE:
            return "ACTIVE";
        case RETIRED:
            return "RETIRED";
        case DISQUALIFIED:
            return "DISQUALIFIED";
    }
}

int main(){
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    
    // input drivers
    int N;
    fscanf(input, "%d", &N);

    int drivers_indeces[500000];
    for (int i = 0; i < 500000; i++){
        drivers_indeces[i] = -1;
    }
    
    int driver_capacity = N > 0 ? N : 1;
    Driver* drivers = (Driver *)malloc(sizeof(Driver) * driver_capacity);
    int driver_count = N;

    for (int i = 0; i < N; i++){
        drivers[i].name = (char *)malloc(sizeof(char) * 31);
        drivers[i].team = (char *)malloc(sizeof(char) * 31);
        fscanf(input, "%d %30s %30s", &drivers[i].driver_id, drivers[i].name, drivers[i].team);
        drivers[i].status = ACTIVE;
        drivers[i].races_completed = 0;
        drivers[i].wins = 0;
        drivers[i].points = 0;

        drivers_indeces[drivers[i].driver_id] = i;
    }

    // input races 
    int R;
    fscanf(input, "%d", &R);
    // rusluts of races
    FinishedRaceResult* finishedRaceResult = (FinishedRaceResult *)malloc(sizeof(FinishedRaceResult) * R);
    for (int i = 0; i < R; i++){
        char race_type_str[20];
        RaceType race_type;

        fscanf(input, "%d %s %d", &finishedRaceResult[i].race_id, race_type_str, &finishedRaceResult[i].result_count);

        if (strcmp(race_type_str, "NORMAL_RACE") == 0){
            race_type = NORMAL_RACE;
        }
        else if (strcmp(race_type_str, "SPRINT_RACE") == 0){
            race_type = SPRINT_RACE;
        }
        finishedRaceResult[i].race_type = race_type;
        finishedRaceResult[i].results = malloc(sizeof(RaceResult) * finishedRaceResult[i].result_count);

        // init values
        finishedRaceResult[i].finished = 0;
        finishedRaceResult[i].dnf = 0;
        finishedRaceResult[i].disqualified = 0;
        finishedRaceResult[i].winner_id = 0;
        for (int j = 0; j < finishedRaceResult[i].result_count; j++){
            RaceResult raceResult;
            char resultTypeStr[30];

            fscanf(input, "%d %d %s", &raceResult.driver_id, &raceResult.position, resultTypeStr);
            if (strcmp(resultTypeStr, "FINISHED") == 0){
                raceResult.result_type = FINISHED;
                fscanf(input, "%f", &raceResult.extra.finish_time);
                finishedRaceResult[i].finished++;
            }
            else if (strcmp(resultTypeStr, "DID_NOT_FINISH") == 0){
                raceResult.result_type = DID_NOT_FINISH;
                raceResult.extra.dnf_reason = malloc(sizeof(char) * 16);
                fscanf(input, "%15s", raceResult.extra.dnf_reason);
                finishedRaceResult[i].dnf++;
            }
            else if (strcmp(resultTypeStr, "DISQUALIFIED_RESULT") == 0){
                raceResult.result_type = DISQUALIFIED_RESULT;
                raceResult.extra.disqualification_reason = malloc(sizeof(char) * 31);
                fscanf(input, "%30s", raceResult.extra.disqualification_reason);
                finishedRaceResult[i].disqualified++;
            }

            finishedRaceResult[i].results[j] = raceResult;
        }

        // find the original driver id of the first position
        int first_finished = -1;
        for (int j = 0; j < finishedRaceResult[i].result_count; j++){
            RaceResult *r = &finishedRaceResult[i].results[j];

            if (r->result_type == FINISHED &&
                (first_finished == -1 || r->position < first_finished)){
                first_finished = r->position;
            }
        }

        int skipped = 0;
        for (int j = 0; j < finishedRaceResult[i].result_count; j++){
            RaceResult *r = &finishedRaceResult[i].results[j];

            if (r->result_type != FINISHED &&
                first_finished != -1 &&
                r->position < first_finished) {
                skipped++;
            }
        }

        for (int j = 0; j < finishedRaceResult[i].result_count; j++) {
            RaceResult *r = &finishedRaceResult[i].results[j];

            if (r->result_type != FINISHED){
                r->position = finishedRaceResult[i].result_count;
                continue;
            }
            r->position -= skipped;
            int driverIndex = find_drivers_index(drivers_indeces, r->driver_id);
            if (driverIndex == -1){
                continue;
            }

            drivers[driverIndex].races_completed++;

            if (r->position == 1){
                drivers[driverIndex].wins++;
                finishedRaceResult[i].winner_id = r->driver_id;
            }

            if (race_type == NORMAL_RACE &&
                r->position >= 1 &&
                r->position <= sizeof(normalRacePoints) / sizeof(int)){

                drivers[driverIndex].points += normalRacePoints[r->position - 1];

            } 
            else if (race_type == SPRINT_RACE &&
                    r->position >= 1 &&
                    r->position <= sizeof(sprintRacePoints) / sizeof(int)){

                drivers[driverIndex].points += sprintRacePoints[r->position - 1];
            }
        }
    }

    int Q;
    int sorted_sorted = 0;
    fscanf(input, "%d", &Q);
    for (int i = 0; i < Q; i++){
        char command[11];
        fscanf(input, "%10s", command);
        if (strcmp(command, "STANDINGS") == 0){
            if (sorted_sorted == 0){
                for (int j = 0; j < driver_count; j++){
                    for (int k = j + 1; k < driver_count; k++){
                        if (drivers[k].points > drivers[j].points ||
                                (drivers[k].points == drivers[j].points &&
                                drivers[k].wins > drivers[j].wins) ||
                                (drivers[k].points == drivers[j].points &&
                                drivers[k].wins == drivers[j].wins &&
                                drivers[k].driver_id < drivers[j].driver_id)){
                            Driver temp = drivers[j];
                            drivers[j] = drivers[k];
                            drivers[k] = temp;

                            int id1 = drivers[j].driver_id;
                            int id2 = drivers[k].driver_id;

                            drivers_indeces[id1] = k;
                            drivers_indeces[id2] = j;
                        }
                    }
                }
                sorted_sorted = 1;
            }
            for (int j = 0; j < driver_count; j++){
                fprintf(output, "%d %s %s %d %d\n", drivers[j].driver_id, drivers[j].name, 
                    drivers[j].team, drivers[j].points, drivers[j].wins);
            }
        }
        else if (strcmp(command, "DRIVER") == 0){
            int driver_id;
            fscanf(input, "%d", &driver_id);
            int index = -1;
            for (int j = 0; j < driver_count; j++){
                if (drivers[j].driver_id == driver_id){
                    index = j;
                    break;
                }
            }

            if (index != -1){
                fprintf(output, "%d %s %s\n", drivers[index].driver_id, drivers[index].name, drivers[index].team);
                fprintf(output, "STATUS %s\n", get_status_string(drivers[index].status));
                fprintf(output, "RACES %d\n", drivers[index].races_completed);
                fprintf(output, "WINS %d\n", drivers[index].wins);
                fprintf(output, "POINTS %d\n", drivers[index].points);
            
            }
            else{
                fprintf(output, "NOT FOUND\n");
            }
        }
        else if (strcmp(command, "TEAM") == 0){
            char team[31];
            fscanf(input, "%30s", team);
            int count_of_drivers = 0;
            long long points = 0;
            int wins = 0;

            for (int j = 0; j < driver_count; j++){
                if (strcmp(drivers[j].team, team) == 0){
                    count_of_drivers++;
                    points += drivers[j].points;
                    wins += drivers[j].wins;
                }
            }

            fprintf(output, "%s\n", team);
            fprintf(output, "DRIVERS %d\n", count_of_drivers);
            fprintf(output, "POINTS %lld\n", points);
            fprintf(output, "WINS %d\n", wins);
        }
        else if (strcmp(command, "TOP") == 0){
            if (driver_count > 0){
                int index = 0;
                for (int j = 1; j < driver_count; j++){
                    if (drivers[j].points > drivers[index].points ||
                            (drivers[j].points == drivers[index].points &&
                            drivers[j].wins > drivers[index].wins) ||
                            (drivers[j].points == drivers[index].points &&
                            drivers[j].wins == drivers[index].wins &&
                            drivers[j].driver_id < drivers[index].driver_id)) {
                        index = j;
                    }
                }
                fprintf(output, "%d %s %s %d\n", drivers[index].driver_id, drivers[index].name,
                        drivers[index].team, drivers[index].points);
            }
            else{
                fprintf(output, "NO DATA\n");
            }
        }
        else if (strcmp(command, "ADD_DRIVER") == 0){
            int driver_id;
            char name[31];
            char team[31];
            fscanf(input, "%d %30s %30s", &driver_id, name, team);
            sorted_sorted = 0;
            if (driver_count == driver_capacity){
                int new_capacity = driver_capacity * 2;
                
                Driver* temp = realloc(drivers, new_capacity * sizeof(Driver));
                if (temp != NULL){
                    drivers = temp;
                    driver_capacity = new_capacity;
                }
            }

            drivers[driver_count].driver_id = driver_id;
            drivers[driver_count].name = (char *)malloc(sizeof(char) * 31);
            drivers[driver_count].team = (char *)malloc(sizeof(char) * 31);
            strcpy(drivers[driver_count].name, name);
            strcpy(drivers[driver_count].team, team);
            drivers[driver_count].status = ACTIVE;
            drivers[driver_count].races_completed = 0;
            drivers[driver_count].wins = 0;
            drivers[driver_count].points = 0;

            drivers_indeces[driver_id] = driver_count;

            driver_count++;
        }
        else if (strcmp(command, "RETIRE") == 0){
            int driver_id;
            fscanf(input, "%d", &driver_id);
            for (int j = 0; j < driver_count; j++){
                if (drivers[j].driver_id == driver_id){
                    drivers[j].status = RETIRED;
                    break;
                }
            }
        }
        else if (strcmp(command, "DISQUALIFY") == 0){
            int driver_id;
            fscanf(input, "%d", &driver_id);
            for (int j = 0; j < driver_count; j++){
                if (drivers[j].driver_id == driver_id){
                    drivers[j].status = DISQUALIFIED;
                    break;
                }
            }
        }
        else if (strcmp(command, "RACE_STATS") == 0){
            int race_id;
            fscanf(input, "%d", &race_id);
            int found = -1;
            for (int j = 0; j < R; j++){
                if (finishedRaceResult[j].race_id == race_id){
                    found = 1;
                    fprintf(output, "RACE %d\n", race_id);
                    fprintf(output, "FINISHED %d\n", finishedRaceResult[j].finished);
                    fprintf(output, "DNF %d\n", finishedRaceResult[j].dnf);
                    fprintf(output, "DISQUALIFIED %d\n", finishedRaceResult[j].disqualified);
                    fprintf(output, "WINNER %d\n", finishedRaceResult[j].winner_id);
                    break;
                }
            }
            if (found == -1){
                fprintf(output, "NOT FOUND\n");
            }
        }
    }

    // free memory
    for (int i = 0; i < driver_count; i++){
        free(drivers[i].name);
        free(drivers[i].team);
    }
    free(drivers);

    for (int i = 0; i < R; i++){
        for (int j = 0; j < finishedRaceResult[i].result_count; j++){
            RaceResult* result = &finishedRaceResult[i].results[j];
            if (result->result_type == DID_NOT_FINISH){
                free(result->extra.dnf_reason);
            }
            else if (result->result_type == DISQUALIFIED_RESULT){
                free(result->extra.disqualification_reason);
            }
        }
        free(finishedRaceResult[i].results);
    }
    free(finishedRaceResult);
    return 0;
}