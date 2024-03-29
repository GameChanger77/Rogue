#include "room.h"
#include "room-internal.h"
#include <stdbool.h>

/**
* return true if the player is out of the bounds of the current room
**/
bool room_move(Direction direction, Player *player, Room *room) {
	move_character(direction, player);

	bool changed_room = false;

	if (player->room_x < 0) {
		player->room_x = ROOM_WIDTH - 1;
		player->screen_x--;
		changed_room = true;
	} else if (player->room_x >= ROOM_WIDTH) {
		player->room_x = 0;
		player->screen_x++;
		changed_room = true;
	}
	if (player->room_y < 0) {
		player->room_y = ROOM_HEIGHT - 1;
		player->screen_y--;
		changed_room = true;
	} else if (player->room_y >= ROOM_HEIGHT) {
		player->room_y = 0;
		player->screen_y++;
		changed_room = true;
	}
		
	return changed_room;
}

// Get the room's tiles
const RoomData* room_get_tiles(const Room *room) {
	return &room->tiles;
}

// Set the room's tile to a different character
void room_set_tile(Room *room, int x, int y, char tile) {
	room->tiles[y][x] = tile;
}