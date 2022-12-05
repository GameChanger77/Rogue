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
	
	
	
	/* Debugging stuff
	mvprintw(1, 0, "Coins: %d", player->coins);
	mvprintw(3, 1, "% 4d", desiredX);
	mvprintw(4, 1, "% 4d", desiredY);
	mvprintw(5, 1, "Tile = %d  ", (*room_get_tiles(roomgen_get(player->screen_x,player->screen_y)))[desiredY][desiredX]);
	mvprintw(6, 1, "Tile = %c  ", (*room_get_tiles(roomgen_get(player->screen_x,player->screen_y)))[desiredY][desiredX]);
	*/
	
	// Collision Detection
	if ((*room_get_tiles(roomgen_get(player->screen_x,player->screen_y)))[desiredY][desiredX] != '#' || desiredX < 0 || desiredX > 39 || desiredY < 0 || desiredY > 19){
		player->room_x=desiredX;
		player->room_y=desiredY;
	}
	
	// Give the player a coin 
	if ((*room_get_tiles(roomgen_get(player->screen_x,player->screen_y)))[desiredY][desiredX] == 'C'){
		player->coins++;
		room_set_tile(roomgen_get(player->screen_x,player->screen_y), desiredX, desiredY, ' ');
	}
	
}