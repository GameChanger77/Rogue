#ifndef ROGUE_PLAYER_H
#define ROGUE_PLAYER_H

#include "input.h"

typedef struct Player {
    // X and Y of the screen (room) we're in; sorry for the weird naming
    int screen_x;
    int screen_y;
    // X and Y within the room we're in
    int room_x;
    int room_y;
	int coins; // Keep track of score based on coins
} Player;

void move_character(Direction direction, Player* player);

#endif