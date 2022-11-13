#include "room.h"
#include <stdbool.h>

#define room_width 80 // change to the real value
#define room_height 80 // change to the real value

/**
* return true if the player is out of the bounds of the current room
**/
bool room_move(Direction direction, Player *player, Room *room){
	if (player->screen_x >= room_width || player->screen_x <= 0)
		return true;
	if (player->screen_y >= room_width || player->screen_y <= 0)
		return true;
		
	return false; // stub
}
