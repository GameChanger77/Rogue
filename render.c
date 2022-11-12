#include "render.h"
#include <ncurses.h>

void render_init(void){
	// stub
    initscr();
    refresh();
}

void render_enter_room(Room *room){
	// stub
}

void render_anim(void){
	// stub
    refresh();
}