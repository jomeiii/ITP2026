#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// write the result of a command to the output file
void write_result(FILE* output, int code){
    fprintf(output, "R %d\n", code);
}

// Writes the rover state to the output file.
void write_state(FILE* output, char type, int x, int y, int battery,
                 int heat, int cargo, int mode, int distance,
                 int accepted, int rejected, int restores,
                 int checkpoint_valid){
    fprintf(output, "%c %d %d %d %d %d %d %d %d %d %d %d\n",
            type, x, y, battery, heat, cargo, mode, distance,
            accepted, rejected, restores, checkpoint_valid);
}

// applies the successful move command to the rover
void move_rover(int* x, int* y, int* battery, int* heat, int* distance, int dx, int dy, int cargo){
    int d = abs(dx) + abs(dy);
    int energy = d * (2 + cargo);

    *x += dx;
    *y += dy;
    *battery -= energy;
    *distance += d;
    *heat += d + cargo;
}

int main(){
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    int B0, BMAX, H0, CAP, L;
    int N;

    fscanf(input, "%d %d %d %d %d", &B0, &BMAX, &H0, &CAP, &L);
    fscanf(input, "%d", &N);

    int x = 0;
    int y = 0;
    int battery = B0;
    int heat = H0;
    int cargo = 0;
    int mode = 0; // 0=idle, 1=active, 2=safe
    int distance = 0;
    int accepted = 0;
    int rejected = 0;
    int restores = 0;
    int checkpoint_valid = 0;

    // x, y, baterry, heat, cargo
    int checkpoint[5] = {x, y, B0, H0, cargo};

    char command[9];
    for (int i = 0; i < N; i++){        
        fscanf(input, "%s", command);
        if (strcmp(command, "START") == 0){
            if (mode == 1){
                write_result(output, -1);
                rejected++;
            }
            else if (mode == 2){
                write_result(output, -2);
                rejected++;
            }
            else if (battery < 5){
                write_result(output, -3);
                rejected++;
            }
            else if (heat >= 80){
                write_result(output, -4);
                rejected++;
            }
            else{
                mode = 1;
                write_result(output, 1);
                accepted++;
            }
        }
        else if (strcmp(command, "STOP") == 0){
            if (mode != 1){
                write_result(output, -5);
                rejected++;
            }
            else{
                mode = 0;
                write_result(output, 2);
                accepted++;
            }
        }
        else if (strcmp(command, "MOVE") == 0){
            int dx, dy;
            fscanf(input, "%d %d", &dx, &dy);
            int d = abs(dx) + abs(dy);
            int energy = d * (2 + cargo);

            int newX = x + dx;
            int newY = y + dy;

            if (mode != 1){
                write_result(output, -10);
                rejected++;
            }
            else if (dx == 0 && dy == 0){
                write_result(output, -11);
                rejected++;
            }
            else if (abs(newX) > L || abs(newY) > L){
                write_result(output, -12);
                rejected++;
            }
            else if (battery < energy){
                write_result(output, -13);
                rejected++;
            }
            else{
                write_result(output, 3);
                accepted++;
                
                move_rover(&x, &y, &battery, &heat, &distance, dx, dy, cargo);

                if (heat >= 100 || battery == 0){
                    mode = 2;
                }
            }
        }
        else if (strcmp(command, "LOAD") == 0){
            int w;
            fscanf(input, "%d", &w);
            if (mode != 0){
                write_result(output, -20);
                rejected++;
            }
            else if (x != 0 || y != 0){
                write_result(output, -21);
                rejected++;
            }
            else if (w <= 0){
                write_result(output, -22);
                rejected++;
            }
            else if (cargo + w > CAP){
                write_result(output, -23);
                rejected++;
            }
            else{
                accepted++;
                write_result(output, 4);
                cargo += w;
            }
        }
        else if(strcmp(command, "UNLOAD") == 0){
            int w;
            fscanf(input, "%d", &w);
            if (mode == 1){
                write_result(output, -30);
                rejected++;
            }
            else if(w <= 0){
                write_result(output, -31);
                rejected++;
            }
            else if (w > cargo){
                write_result(output, -32);
                rejected++;
            }
            else{
                write_result(output, 5);
                accepted++;
                cargo -= w;
            }
        }
        else if(strcmp(command, "COOL") == 0){
            if (mode == 1){
                write_result(output, -40);
                rejected++;
            }
            else{
                if (heat < 25)
                    heat = 0;
                else
                    heat -= 25;

                if (mode == 2 && heat < 80 && battery > 0)
                    mode = 0;

                accepted++;
                write_result(output, 6);
            }
        }
        else if(strcmp(command, "RECHARGE") == 0){
            int amount;
            fscanf(input, "%d", &amount);
            if (mode == 1){
                write_result(output, -50);
                rejected++;
            }
            else if (x != 0 || y != 0){
                write_result(output, -51);
                rejected++;
            }
            else if (amount <= 0){
                write_result(output, -52);
                rejected++;
            }
            else{
                if (BMAX < battery + amount){
                    battery = BMAX;
                }
                else{
                    battery += amount;
                }

                if (mode == 2 && heat < 80 && battery > 0)
                    mode = 0;
                
                accepted++;
                write_result(output, 7);
            }
        }
        else if (strcmp(command, "SAVE") == 0){
            if (mode != 0){
                write_result(output, -60);
                rejected++;
            }
            else{
                checkpoint[0] = x;
                checkpoint[1] = y;
                checkpoint[2] = battery;
                checkpoint[3] = heat;
                checkpoint[4] = cargo;
                checkpoint_valid = 1;

                accepted++;
                write_result(output, 8);
            }
        }
        else if (strcmp(command, "RESTORE") == 0){
            if (mode == 1){
                write_result(output, -70);
                rejected++;
            }
            else if (checkpoint_valid == 0){
                write_result(output, -71);
                rejected++;
            }
            else{
                x = checkpoint[0];
                y = checkpoint[1];
                battery = checkpoint[2];
                heat = checkpoint[3];
                cargo = checkpoint[4];
                mode = 0;

                write_result(output, 9);
                accepted++;
                restores++;
            }
        }
        else if (strcmp(command, "STATUS") == 0){
            write_state(output, 'S', x, y, battery, heat, cargo, mode, distance, accepted, rejected, restores, checkpoint_valid);
        }
    }
    write_state(output, 'F', x, y, battery, heat, cargo, mode, distance, accepted, rejected, restores, checkpoint_valid);
    fclose(input);
    fclose(output);
    return 0;
}