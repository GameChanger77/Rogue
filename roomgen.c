#include "room.h"
#include "room-internal.h"
#include "roomgen-index.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef Room *RoomPtr; // so that I don't have to type **Room a legitimately painful amount of times

// Rooms will be read from the text file into these arrays and shuffled
RoomPtr easy[NUM_EASY];
RoomPtr medium[NUM_MEDIUM];
RoomPtr hard[NUM_HARD];

// ...then put into this one to be returned as needed.
RoomPtr grid[5][5];

void roomgen_pregen(){
    if(DEBUG_MODE)
        puts("Reading file...");

    FILE *levels = fopen("levels.txt", "r"); // Open file for reading
    int easyi = 0; // Iterators for remembering which level we're on again?
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
    fclose(levels); // This line shuts the f[ile]

    if(DEBUG_MODE)
        puts("Shuffling levels...");

    long seed = IS_SEED_SET?SET_SEED:time(NULL); // Get ready to randomize the thing y'all
    if(DEBUG_MODE)
        printf("Seed: %d\n", seed);
    srand(seed);
    for(int i = NUM_EASY-1; i > 0; i--) { // This randomly swaps each index in the array with one of the ones before it
        int rnum = rand() % i;
        Room *temp = easy[i];
        easy[i] = easy[rnum];
        easy[rnum] = temp;
    }
    for(int i = NUM_MEDIUM-1; i > 0; i--) { // Same thing but with medium rooms
        int rnum = rand() % i;
        Room *temp = medium[i];
        medium[i] = medium[rnum];
        medium[rnum] = temp;
    }
    for(int i = NUM_HARD-1; i > 0; i--) { // ...yeah, you get it
        int rnum = rand() % i;
        Room *temp = hard[i];
        hard[i] = hard[rnum];
        hard[rnum] = temp;
    }

    if(DEBUG_MODE)
        puts("Creating level grid...");
    
    RoomPtr new_grid[5][5] = { // This just fills the grid with levels. It is the only thing in this file that makes sense.
        {easy[0], hard[0], medium[0], hard[1], easy[1]},
        {hard[2], medium[1], easy[2], medium[2], hard[3]},
        {medium[3], easy[3], easy[4], easy[5], medium[4]},
        {hard[4], medium[5], easy[6], medium[6], hard[5]},
        {easy[7], hard[6], medium[7], hard[7], easy[8]}
    };
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            grid[i][j] = new_grid[i][j]; // C, why...?
    // Actually I take it back
}

Room* roomgen_get(int x, int y){
    // Wrap the indexes from 0-4 then return the thing
    x += 2;
    y += 2;
    while(x<0) x += 5;
    while(y<0) y += 5;
    return grid[x%5][y%5];
}
