#ifndef ROGUE_ROOM_H
#define ROGUE_ROOM_H

#include <stdbool.h>
#include "player.h"
#include "input.h"

#define ROOM_WIDTH 40
#define ROOM_HEIGHT 20

// Room is an opaque type and is defined in room.c
typedef struct Room Room;

// Inner tiles of room
typedef char RoomData[20][40];

// Tick the room based on player input
bool room_move(Direction direction, Player *player, Room *room);

// Get the tiles that make up the room
const RoomData* room_get_tiles(const Room *room);

// Set a specific tile in the room (usually used for clearing coins)
void room_set_tile(Room *room, int x, int y, char tile);

#endif // ROGUE_ROOM_H