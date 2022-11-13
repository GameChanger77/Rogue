#ifndef ROGUE_PLAYER_H
#define ROGUE_PLAYER_H

#include "input.h"

typedef struct Player {
    int screen_x;
    int screen_y;
} Player;

void move_character(Direction direction, Player* player);

#endif