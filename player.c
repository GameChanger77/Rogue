#include <ncurses.h>

#include "player.h"
#include "input.h"


void move_character(Direction direction, Player* player){
	int oldX = player->screen_x, oldY = player->screen_y;
	switch (direction){
		case Up:
			player->screen_y-=1;
			break;
		case Down:
			player->screen_y+=1;
			break;
		case Left:
			player->screen_x-=1;
			break;
		case Right:
			player->screen_x+=1;
			break;
	}
	
	mvaddch(player->screen_y, player->screen_x, 'A');
	mvaddch(oldY, oldX, ' ');
	
}