#include "room.h"
#include <stdbool.h>

#define room_width 40 // change to the real value
#define room_height 20 // change to the real value

/**
* return true if the player is out of the bounds of the current room
**/
bool room_move(Direction direction, Player *player, Room *room) {
	move_character(direction, player);

	bool changed_room = false;

	if (player->room_x < 0) {
		player->room_x = room_width - 1;
		player->screen_x--;
		changed_room = true;
	} else if (player->room_x >= room_width) {
		player->room_x = 0;
		player->screen_x++;
		changed_room = true;
	}
	if (player->room_y < 0) {
		player->room_y = room_height - 1;
		player->screen_y--;
		changed_room = true;
	} else if (player->room_y >= room_height) {
		player->room_y = 0;
		player->screen_y++;
		changed_room = true;
	}
		
	return changed_room;
}
