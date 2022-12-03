#include <ncurses.h>

#include "player.h"
#include "input.h"
#include "roomgen.h"


void move_character(Direction direction, Player* player) {
	int desiredX = player->room_x;
	int desiredY = player->room_y;
	
	switch (direction) {
		case Up:
			desiredY-=1;
			break;
		case Down:
			desiredY+=1;
			break;
		case Left:
			desiredX-=1;
			break;
		case Right:
			desiredX+=1;
			break;
		default:
			break;
	}
	
	//mvprintw(1, 1, "% 4d", desiredX);
	//mvprintw(2, 1, "% 4d", desiredY);
	//mvprintw(3, 1, "Tile = %d  ", room_get_tiles(roomgen_get(0,0))[0][desiredY][desiredX]);
	//mvprintw(4, 1, "Tile = %c  ", room_get_tiles(roomgen_get(0,0))[0][desiredY][desiredX]);
	
	if ((*room_get_tiles(roomgen_get(player->screen_x,player->screen_y)))[desiredY][desiredX] != '#'){
		player->room_x=desiredX;
		player->room_y=desiredY;
	}
}