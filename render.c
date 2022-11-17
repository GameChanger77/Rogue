#include "render.h"
#include <ncurses.h>

void render_init(void) {
	// stub
    initscr();
    refresh();
}

int prev_player_x = 0;
int prev_player_y = 0;

void render_enter_room(const Player *player, const Room *room) {
	clear();
    mvprintw(0, 0, "Room: (%d, %d)", player->screen_x, player->screen_y);
    for(int i = 0; i < 40; i++) {
        mvaddch(1, 19 + i, '-');
        mvaddch(22, 19 + i, '-');
    }
    for(int i = 0; i < 20; i++) {
        mvaddch(2 + i, 18, '|');
        mvaddch(2 + i, 59, '|');
    }
    mvaddch(1, 18, '+');
    mvaddch(22, 18, '+');
    mvaddch(1, 59, '+');
    mvaddch(22, 59, '+');
    // TODO: render contents of room
    mvaddch(player->room_y + 2, player->room_x + 19, 'A');
    prev_player_x = player->room_x;
    prev_player_y = player->room_y;
    refresh();
}

void render_anim(const Player *player, const Room *room) {
	// stub
    mvaddch(prev_player_y + 2, prev_player_x + 19, ' ');
    mvaddch(player->room_y + 2, player->room_x + 19, 'A');
    prev_player_x = player->room_x;
    prev_player_y = player->room_y;
    refresh();
}