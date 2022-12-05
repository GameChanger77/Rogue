#include "input.h"
#include "render.h"
#include <ncurses.h>

void render_init(void) {
	// stub
    initscr();
    start_color();
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    refresh();
}

char player_char = '>';

int prev_player_x = 0;
int prev_player_y = 10;

bool coin_north, coin_south, coin_west, coin_east;

static char render_get_coin_char() {
    int time = input_time() % 400;
    if(time >= 100 && time < 200) init_pair(1, COLOR_WHITE, COLOR_BLACK);
    else                          init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    if(time < 100) return '@';
    if(time < 200) return '0';
    if(time < 300) return '!';
    else           return '0';
}

static void render_check_coin(int x, int y, const Room *room) {
    const RoomData *room_data = room_get_tiles(room);
    coin_north = y > 0 && (*room_data)[x - 1][y] == 'C';
    coin_south = y > 0 && (*room_data)[x - 1][y] == 'C';
    coin_west = x > 0 && (*room_data)[x - 1][y] == 'C';
    coin_east = x > 0 && (*room_data)[x - 1][y] == 'C';
}

void render_enter_room(const Player *player, const Room *room) {
	clear();
    mvprintw(0, 0, "Room: (%d, %d)", player->screen_x, player->screen_y);
    char coin_char = render_get_coin_char();
    attron(COLOR_PAIR(2));
    for(int i = -1; i < 41; i++) {
        if(i < 18 || i >= 22) {
            mvaddch(1, 19 + i, ' ');
            mvaddch(22, 19 + i, ' ');
        }
    }
    for(int i = 0; i < 20; i++) {
        if(i < 9 || i >= 11) {
            mvaddch(2 + i, 18, ' ');
            mvaddch(2 + i, 59, ' ');
        }
    }
    attroff(COLOR_PAIR(2));
    const RoomData *room_data = room_get_tiles(room);
    for(int x = 0; x < 40; x++) {
        for(int y = 0; y < 20; y++) {
            switch((*room_data)[y][x]) {
                case ' ': break;
                case '#':
                    attron(COLOR_PAIR(2));
                    mvaddch(2 + y, 19 + x, ' ');
                    attroff(COLOR_PAIR(2));
                    break;
                case 'C':
                    attron(COLOR_PAIR(1));
                    mvaddch(2 + y, 19 + x, coin_char);
                    attroff(COLOR_PAIR(1));
                    break;
                default:
                    break;
            }
        }
    }
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
    char coin_char = render_get_coin_char();
    const RoomData *room_data = room_get_tiles(room);
    for(int x = 0; x < 40; x++) {
        for(int y = 0; y < 20; y++) {
            switch((*room_data)[y][x]) {
                case 'C':
                    attron(COLOR_PAIR(1));
                    mvaddch(2 + y, 19 + x, coin_char);
                    attroff(COLOR_PAIR(1));
                    break;
                default:
                    break;
            }
        }
    }
    mvaddch(prev_player_y + 2, prev_player_x + 19, ' ');
    if(prev_player_y > player->room_y) player_char = '^';
    else if(prev_player_y < player->room_y) player_char = 'v';
    else if(prev_player_x > player->room_x) player_char = '<';
    else if(prev_player_x < player->room_x) player_char = '>';
    mvaddch(player->room_y + 2, player->room_x + 19, player_char);

    if(prev_player_x != player->room_x || prev_player_y != player->room_y) {
        render_check_coin(player->room_x, player->room_y, room);
    }

    prev_player_x = player->room_x;
    prev_player_y = player->room_y;
    refresh();
}