#include <ncurses.h>

#include "player.h"
#include "input.h"


void move_character(Direction direction, Player* player) {
	switch (direction) {
		case Up:
			player->room_y-=1;
			break;
		case Down:
			player->room_y+=1;
			break;
		case Left:
			player->room_x-=1;
			break;
		case Right:
			player->room_x+=1;
			break;
		default:
			break;
	}
}