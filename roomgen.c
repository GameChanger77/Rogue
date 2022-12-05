#include "room.h"
#include "room-internal.h"
#include "roomgen-index.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef Room *RoomPtr;

RoomPtr easy[NUM_EASY];
RoomPtr medium[NUM_MEDIUM];
RoomPtr hard[NUM_HARD];

RoomPtr grid[5][5];

void roomgen_pregen(){
    if(DEBUG_MODE)
        puts("Reading file...");

    FILE *levels = fopen("levels.txt", "r");
    int easyi = 0;
    int mediumi = 0;
    int hardi = 0;
    char buffer[43];
    while (fgets(buffer, 43, levels) != NULL) {
        if (strlen(buffer) == 0) break;

        Room **current_room_p =
            buffer[0] == 'e' ? &easy[easyi++] :
            (buffer[0] == 'm' ? &medium[mediumi++] :
            &hard[hardi++]);

        *current_room_p = malloc(sizeof(Room));

        Room *current_room = *current_room_p;

        if(DEBUG_MODE)
            printf("%d %d %d\n", easyi, mediumi, hardi); // Debug line

        for(int y = 0; y < 20; ++y) {
            fgets(buffer, 43, levels);
            memcpy(&current_room->tiles[y], buffer, 40);
        }
    }
    fclose(levels);

    if(DEBUG_MODE)
        puts("Shuffling levels...");
    srand(IS_SEED_SET?SET_SEED:time(NULL));
    for(int i = NUM_EASY; i > 0; i--) {
        int rnum = rand() % i;
        Room *temp = easy[i];
        easy[i] = easy[rnum];
        easy[rnum] = temp;
    }
    for(int i = NUM_MEDIUM; i > 0; i--) {
        int rnum = rand() % i;
        Room *temp = medium[i];
        medium[i] = medium[rnum];
        medium[rnum] = temp;
    }
    for(int i = NUM_HARD; i > 0; i--) {
        int rnum = rand() % i;
        Room *temp = hard[i];
        hard[i] = hard[rnum];
        hard[rnum] = temp;
    }

    if(DEBUG_MODE)
        puts("Creating level grid...");
    
    RoomPtr new_grid[5][5] = {
        {easy[0], hard[0], medium[0], hard[1], easy[1]},
        {hard[2], medium[1], easy[2], medium[2], hard[3]},
        {medium[3], easy[3], easy[4], easy[5], medium[4]},
        {hard[4], medium[5], easy[6], medium[6], hard[5]},
        {easy[7], hard[6], medium[7], hard[7], easy[8]}
    };
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            grid[i][j] = new_grid[i][j]; // C why...

            /*
EHMHE
HMEMH
MEEEM
HMEMH
EHMHE            */

}

Room* roomgen_get(int x, int y){
    x += 2;
    y += 2;
    while(x<0) x += 5;
    while(y<0) y += 5;
    return grid[x%5][y%5];
}
