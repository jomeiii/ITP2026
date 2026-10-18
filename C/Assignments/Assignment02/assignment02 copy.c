#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ACTIVE,
    RETIRED,
    DISQUALIFIED
} DriverStatus;

typedef struct {
    int driver_id;
    char *name;
    char *team;

    DriverStatus status;

    int races_completed;
    int wins;
    int points;
} Driver;

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

typedef struct
{
    int race_id;

    RaceResult *results;
    int count_of_results;

    int finished;
    int dnf;
    int disqualified;
    int winner_id;

} RaceFinishedResult;

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

int calculate_points(RaceType type, int position){
    if (position < 1){
        return 0;
    }

    if (type == NORMAL_RACE){
        int points[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
        if (position <= 10){
            return points[position - 1];
        }
    }
    else if (type == SPRINT_RACE){
        int points[] = {8, 7, 6, 5, 4, 3, 2, 1};
        if (position <= 8){
            return points[position -1];
        }
    }
    return 0;
}

int find_driver_index(Driver* drivers, int id, int k){
    for (int i = 0; i < k; i++){
        if (drivers[i].driver_id == id){
            return i;
        }
    }
    return - 1;
}

int main(){
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    // input drivers
    int N;
    fscanf(input, "%d", &N);

    int driver_capacity = N > 0 ? N : 1;
    Driver* drivers = malloc(sizeof(Driver) * driver_capacity);
    int driver_count = N;

    for (int i = 0; i < N; i++){
        drivers[i].name = malloc(sizeof(char) * 31);
        drivers[i].team = malloc(sizeof(char) * 31);
        fscanf(input, "%d %30s %30s", &drivers[i].driver_id, drivers[i].name, drivers[i].team);
        drivers[i].status = ACTIVE;
        drivers[i].races_completed = 0;
        drivers[i].wins = 0;
        drivers[i].points = 0;
    }

    // input races
    int R;
    fscanf(input, "%d", &R);

    // Rusluts of races
    RaceFinishedResult* race_results = malloc(sizeof(RaceFinishedResult) * R); 

    for (int i = 0; i < R; i++){
        int race_id;
        char type[35];
        int k;

        RaceType race_type;
        fscanf(input, "%d %s %d", &race_id, type, &k);
        if (strcmp(type, "NORMAL_RACE") == 0){
            race_type = NORMAL_RACE;
        }
        else if (strcmp(type, "SPRINT_RACE") == 0){
            race_type = SPRINT_RACE;
        }
        
        // init race results
        race_results[i].race_id = race_id;
        race_results[i].count_of_results = k;
        race_results[i].finished = 0;
        race_results[i].dnf = 0;
        race_results[i].disqualified = 0;
        race_results[i].winner_id = 0;
        race_results[i].results = malloc(sizeof(RaceResult) * k);

        // Drivers results
        for (int j = 0; j < k; j++){
            RaceResult race_result;
            char driver_result_type_str[35];
            fscanf(input, "%d %d %s", &race_result.driver_id, &race_result.position, driver_result_type_str);
            if(strcmp(driver_result_type_str, "FINISHED") == 0){
                int driverIndex = find_driver_index(drivers, race_result.driver_id, driver_count);

                drivers[driverIndex].races_completed++;
                drivers[driverIndex].points += calculate_points(race_type, race_result.position);

                if (race_result.position == 1){
                    drivers[driverIndex].wins++;
                    race_results[i].winner_id = race_result.driver_id;
                }

                race_results[i].finished++;
                race_result.result_type = FINISHED;
                fscanf(input, "%f", &race_result.extra.finish_time);
            }
            else if (strcmp(driver_result_type_str, "DID_NOT_FINISH") == 0){
                race_results[i].dnf++;
                race_result.extra.dnf_reason = malloc(sizeof(char) * 12);
                race_result.result_type = DID_NOT_FINISH;
                fscanf(input, "%11s", race_result.extra.dnf_reason);
            }
            else if (strcmp(driver_result_type_str, "DISQUALIFIED_RESULT") == 0){
                int driverIndex = find_driver_index(drivers, race_result.driver_id, driver_count);
                race_results[i].disqualified++;
                race_result.extra.disqualification_reason = malloc(sizeof(char) * 12);
                race_result.result_type = DISQUALIFIED_RESULT;
                fscanf(input, "%11s", race_result.extra.disqualification_reason);
            }
            race_results[i].results[j] = race_result;
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
        else if(strcmp(command, "DRIVER") == 0){
            int driver_id;
            fscanf(input, "%d", &driver_id);
            int index = find_driver_index(drivers, driver_id, driver_count);
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
            int points = 0;
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
            fprintf(output, "POINTS %d\n", points);
            fprintf(output, "WINS %d\n", wins);
        }
        else if (strcmp(command, "TOP") == 0){
            if (N > 0){
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

            if (driver_count == driver_capacity){
                int new_capacity = driver_capacity * 2;

                Driver* temp = realloc(drivers, new_capacity * sizeof(Driver));
                if (temp != NULL){
                    drivers = temp;
                    driver_capacity = new_capacity;
                }
            }

            sorted_sorted = 0;
            drivers[driver_count].driver_id = driver_id;
            drivers[driver_count].name = (char *)malloc(sizeof(char) * 31);
            drivers[driver_count].team = (char *)malloc(sizeof(char) * 31);
            strcpy(drivers[driver_count].name, name);
            strcpy(drivers[driver_count].team, team);
            drivers[driver_count].status = ACTIVE;
            drivers[driver_count].races_completed = 0;
            drivers[driver_count].wins = 0;
            drivers[driver_count].points = 0;
            driver_count++;
        }
        else if (strcmp(command, "RETIRE") == 0){
            int driver_id;
            fscanf(input, "%d", &driver_id);
            int index = find_driver_index(drivers, driver_id, driver_count);
            if (index != -1){
                drivers[index].status = RETIRED;
            }
        }
        else if (strcmp(command, "DISQUALIFY") == 0){
            int driver_id;
            fscanf(input, "%d", &driver_id);
            int index = find_driver_index(drivers, driver_id, driver_count);
            if (index != -1){
                drivers[index].status = DISQUALIFIED;
            }
        }
        else if (strcmp(command, "RACE_STATS") == 0){
            int race_id;
            fscanf(input, "%d", &race_id);
            int found = -1;
            for (int j = 0; j < R; j++){
                if (race_results[j].race_id == race_id){
                    found = 1;
                    fprintf(output, "RACE %d\n", race_id);
                    fprintf(output, "FINISHED %d\n", race_results[j].finished);
                    fprintf(output, "DNF %d\n", race_results[j].dnf);
                    fprintf(output, "DISQUALIFIED %d\n", race_results[j].disqualified);
                    fprintf(output, "WINNER %d\n", race_results[j].winner_id);
                    break;
                }
            }
            if (found == -1){
                fprintf(output, "NOT FOUND\n");
            }
        }
    }
}