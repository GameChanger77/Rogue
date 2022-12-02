#include "render.h"
#include <ncurses.h>

void render_init(void) {
	// stub
    initscr();
    refresh();
}

char player_char = '>';

int prev_player_x = 0;
int prev_player_y = 0;

void render_enter_room(const Player *player, const Room *room) {
	clear();
    mvprintw(0, 0, "Room: (%d, %d)", player->screen_x, player->screen_y);
    for(int i = -1; i < 41; i++) {
        if(i < 18 || i >= 22) {
            mvaddch(1, 19 + i, '#');
            mvaddch(22, 19 + i, '#');
        }
    }
    for(int i = 0; i < 20; i++) {
        if(i < 9 || i >= 11) {
            mvaddch(2 + i, 18, '#');
            mvaddch(2 + i, 59, '#');
        }
    }
    // TODO: render contents of room
    if(prev_player_y > player->room_y) player_char = 'v';
    else if(prev_player_y < player->room_y) player_char = '^';
    else if(prev_player_x > player->room_x) player_char = '>';
    else if(prev_player_x < player->room_x) player_char = '<';
    mvaddch(player->room_y + 2, player->room_x + 19, player_char);
    prev_player_x = player->room_x;
    prev_player_y = player->room_y;
    refresh();
}

void render_anim(const Player *player, const Room *room) {
	// stub
    mvaddch(prev_player_y + 2, prev_player_x + 19, ' ');
    if(prev_player_y > player->room_y) player_char = '^';
    else if(prev_player_y < player->room_y) player_char = 'v';
    else if(prev_player_x > player->room_x) player_char = '<';
    else if(prev_player_x < player->room_x) player_char = '>';
    mvaddch(player->room_y + 2, player->room_x + 19, player_char);
    prev_player_x = player->room_x;
    prev_player_y = player->room_y;
    refresh();
}