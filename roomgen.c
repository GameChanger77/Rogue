#include "room.h"
#include "room-internal.h"
#include "roomgen-index.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Room *easy;
Room *medium;
Room *hard;

void roomgen_pregen(){
    FILE *levels = fopen("levels.txt", "r");
    easy = (Room*) malloc(sizeof(Room) * NUM_EASY);
    medium = (Room*) malloc(sizeof(Room) * NUM_MEDIUM);
    hard = (Room*) malloc(sizeof(Room) * NUM_HARD);
    int easyi = 0;
    int mediumi = 0;
    int hardi = 0;
    char buffer[43];
    while (fgets(buffer, 43, levels) != NULL) {
        if (strlen(buffer) == 0) {
            break;
        }
        Room *current_room =
            buffer[0] == 'e' ? &easy[easyi++] :
            (buffer[0] == 'm' ? &medium[mediumi++] :
            &hard[hardi++]);
        printf("%d %d %d\n", easyi, mediumi, hardi);
        for(int y = 0; y < 20; ++y) {
            fgets(buffer, 43, levels);
            memcpy(&current_room->tiles[y], buffer, 40);
        }
    }
    fclose(levels);
    puts("Done!");
}

Room* roomgen_get(int x, int y){
    // stub
    
    return &easy[abs(x + y) % 2];
}