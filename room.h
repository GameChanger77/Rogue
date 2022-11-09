#ifndef ROGUE_ROOM_H
#define ROGUE_ROOM_H

#include "player.h"

// Room is an opaque type and is defined in room.c
typedef struct Room Room;

// Tick the room based on player input
bool room_move(Direction direction, Player *player, Room *room);

#endif // ROGUE_ROOM_H