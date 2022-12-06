#include "input.h"
#include "render.h"
#include <ncurses.h>

void render_init(void) {
	// stub
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
    refresh();
}

char player_char = '>';

int prev_player_x = 0;
int prev_player_y = 10;
int prev_coins = 0;

int coin_anim_x, coin_anim_y, coin_anim_start, coin_anim_on = 0;

static void plot_char(int x, int y, char ch) {
    mvaddch(2 + y, 19 + x, ch);
}

static char render_get_coin_char() {
    int time = input_time() % 400;
    if(time >= 100 && time < 200) init_pair(1, COLOR_WHITE, COLOR_BLACK);
    else                          init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    if(time < 100) return '@';
    if(time < 200) return '0';
    if(time < 300) return '!';
    else           return '0';
}

static void render_check_coin(int x, int y, int coins) {
    if(
        coins != prev_coins
    ) {
        plot_char(x, y, ' ');
        coin_anim_x = x;
        coin_anim_y = y;
        coin_anim_start = input_time();
        coin_anim_on = 1;
    }
    prev_coins = coins;
}

void render_room_tile(int x, int y, const RoomData *room_data) {
    if(x < 0 || x > 39 || y < 0 || y > 19) {
        attron(COLOR_PAIR(2));
        mvaddch(2 + y, 19 + x, ' ');
        attroff(COLOR_PAIR(2));
        return;
    }
    char coin_char = render_get_coin_char();
    switch((*room_data)[y][x]) {
        case ' ':
            plot_char(x, y, ' ');
            break;
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

void render_enter_room(const Player *player, const Room *room) {
	clear();
    mvprintw(0, 0, "Room: (%d, %d)", player->screen_x, player->screen_y);
    mvprintw(1, 0, "Coins: %d", player->coins);
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
            render_room_tile(x, y, room_data);
        }
    }
    render_check_coin(player->room_x, player->room_y, player->coins);
    if(prev_player_y > player->room_y) player_char = 'v';
    else if(prev_player_y < player->room_y) player_char = '^';
    else if(prev_player_x > player->room_x) player_char = '>';
    else if(prev_player_x < player->room_x) player_char = '<';
    attron(COLOR_PAIR(3));
    mvaddch(player->room_y + 2, player->room_x + 19, player_char);
    attroff(COLOR_PAIR(3));
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

    if(prev_player_x != player->room_x || prev_player_y != player->room_y) {
        render_check_coin(player->room_x, player->room_y, player->coins);
    }

    if(coin_anim_on) {
        int timer = input_time() - coin_anim_start;
        if(timer < 100) {
            attron(COLOR_PAIR(4));
            plot_char(coin_anim_x, coin_anim_y, ' ');
            attroff(COLOR_PAIR(4));
        } else if(timer < 200) {
            attron(COLOR_PAIR(4));
            plot_char(coin_anim_x-1, coin_anim_y-1, ' ');
            plot_char(coin_anim_x-1, coin_anim_y, ' ');
            plot_char(coin_anim_x-1, coin_anim_y+1, ' ');
            plot_char(coin_anim_x, coin_anim_y-1, ' ');
            plot_char(coin_anim_x, coin_anim_y+1, ' ');
            plot_char(coin_anim_x+1, coin_anim_y-1, ' ');
            plot_char(coin_anim_x+1, coin_anim_y, ' ');
            plot_char(coin_anim_x+1, coin_anim_y+1, ' ');
            attroff(COLOR_PAIR(4));
            render_room_tile(coin_anim_x, coin_anim_y, room_data);
        } else if(timer < 300) {
            attron(COLOR_PAIR(4));
            for(int i = -1; i <= 1; i++) {
                plot_char(coin_anim_x+i, coin_anim_y-2, ' ');
                plot_char(coin_anim_x+i, coin_anim_y+2, ' ');
                plot_char(coin_anim_x-2, coin_anim_y+i, ' ');
                plot_char(coin_anim_x+2, coin_anim_y+i, ' ');
            }
            attroff(COLOR_PAIR(4));
            render_room_tile(coin_anim_x-1, coin_anim_y-1, room_data);
            render_room_tile(coin_anim_x-1, coin_anim_y, room_data);
            render_room_tile(coin_anim_x-1, coin_anim_y+1, room_data);
            render_room_tile(coin_anim_x, coin_anim_y-1, room_data);
            render_room_tile(coin_anim_x, coin_anim_y+1, room_data);
            render_room_tile(coin_anim_x+1, coin_anim_y-1, room_data);
            render_room_tile(coin_anim_x+1, coin_anim_y, room_data);
            render_room_tile(coin_anim_x+1, coin_anim_y+1, room_data);
        } else {
            for(int i = -1; i <= 1; i++) {
                render_room_tile(coin_anim_x+i, coin_anim_y-2, room_data);
                render_room_tile(coin_anim_x+i, coin_anim_y+2, room_data);
                render_room_tile(coin_anim_x-2, coin_anim_y+i, room_data);
                render_room_tile(coin_anim_x+2, coin_anim_y+i, room_data);
            }
            coin_anim_on = 0;
        }
    }

    mvaddch(prev_player_y + 2, prev_player_x + 19, ' ');
    if(prev_player_y > player->room_y) player_char = '^';
    else if(prev_player_y < player->room_y) player_char = 'v';
    else if(prev_player_x > player->room_x) player_char = '<';
    else if(prev_player_x < player->room_x) player_char = '>';
    attron(COLOR_PAIR(3));
    mvaddch(player->room_y + 2, player->room_x + 19, player_char);
    attroff(COLOR_PAIR(3));

    if(coin_anim_on) {
        attron(COLOR_PAIR(1));
    }
    mvprintw(1, 0, "Coins: %d", player->coins);
    if(coin_anim_on) {
        attroff(COLOR_PAIR(1));
    }

    prev_player_x = player->room_x;
    prev_player_y = player->room_y;
    refresh();
}

int win_time = 0;
bool already_rerendered = 0;

bool render_win(const Player *player, const Room *room) {
    if(!win_time) win_time = input_time();
    int time = input_time() - win_time;
    if(time < 3000) {
        if(time % 1000 < 500) {
            init_pair(1, COLOR_WHITE, COLOR_WHITE);
            bkgd(COLOR_PAIR(1) | ' ');
            clear();
            already_rerendered = 0;
        } else {
            init_pair(1, COLOR_YELLOW, COLOR_BLACK);
            init_pair(2, COLOR_WHITE, COLOR_WHITE);
            init_pair(3, COLOR_CYAN, COLOR_BLACK);
            init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
            bkgd(' ');
            if(!already_rerendered) render_enter_room(player, room); // Re-render the room
            already_rerendered = 1;
        }
        refresh();
        return 1;
    }
    return 0;
}