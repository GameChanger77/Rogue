#include "input.h"
#include "render.h"
#include <ncurses.h>

void render_init(void) {
	// Init ncurses
    initscr();
    start_color();
    // We use different colors for different objects; let's set them up
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

// I got tired of writing this call every time, so I made it into a function
static void plot_char(int x, int y, char ch) {
    mvaddch(2 + y, 19 + x, ch);
}

// This function handles animating coins
static char render_get_coin_char() {
    int time = input_time() % 400; // The coin runs on a 0.4 frame cycle
    if(time >= 100 && time < 200) init_pair(1, COLOR_WHITE, COLOR_BLACK); // If we're on frame 2/4, turn the coin white for a shine.
    else                          init_pair(1, COLOR_YELLOW, COLOR_BLACK); // If we're on any other frame, it's yellow.
    if(time < 100) return '@'; // Don't ask why we
    if(time < 200) return '0'; // we chose these characters;
    if(time < 300) return '!'; // they just happened
    else           return '0'; // to look good here.
}

// Check to see if we need to start a coin collection animation
// This used to be more complicated; now it just checks when the coin count changes
static void render_check_coin(int x, int y, int coins) {
    if(coins != prev_coins) {
        plot_char(x, y, ' '); // Erase the coin. It should be erased anyway, but just to be careful.
        coin_anim_x = x;
        coin_anim_y = y;
        coin_anim_start = input_time();
        coin_anim_on = 1;
    }
    prev_coins = coins;
}

// During the coin animation, we break the room layout a bit.
// This function is used in both the initial rendering and in the coin reset to fix the room layout.
static void render_room_tile(int x, int y, const RoomData *room_data) {
    if(x < 0 || x > 39 || y < 0 || y > 19) { // If we're out of the room bounds, assume we're drawing the border.
        attron(COLOR_PAIR(2));
        mvaddch(2 + y, 19 + x, ' ');
        attroff(COLOR_PAIR(2));
        return;
    }
    char coin_char = render_get_coin_char(); // Handle coin animation
    switch((*room_data)[y][x]) {
        case ' ':
            plot_char(x, y, ' ');
            break;
        case '#':
            attron(COLOR_PAIR(2)); // Walls are solid white
            mvaddch(2 + y, 19 + x, ' ');
            attroff(COLOR_PAIR(2));
            break;
        case 'C':
            attron(COLOR_PAIR(1)); // Coins are... coins.
            mvaddch(2 + y, 19 + x, coin_char);
            attroff(COLOR_PAIR(1));
            break;
        default:
            break;
    }
}

void render_enter_room(const Player *player, const Room *room) {
	clear();
    // Display a mini-HUD
    mvprintw(0, 0, "Room: (%d, %d)", player->screen_x, player->screen_y);

    // Border time!
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
    attroff(COLOR_PAIR(2)); // No longer border time :(

    const RoomData *room_data = room_get_tiles(room);
    for(int x = 0; x < 40; x++) {
        for(int y = 0; y < 20; y++) {
            render_room_tile(x, y, room_data);
        }
    }

    // Based on where the player came from, make it look different
    if(prev_player_y > player->room_y) player_char = 'v';
    else if(prev_player_y < player->room_y) player_char = '^';
    else if(prev_player_x > player->room_x) player_char = '>';
    else if(prev_player_x < player->room_x) player_char = '<';

    attron(COLOR_PAIR(3));
    mvaddch(player->room_y + 2, player->room_x + 19, player_char);
    attroff(COLOR_PAIR(3));

    if(coin_anim_on)
        attron(COLOR_PAIR(1)); // If we collected a coin, blink the coin display
    mvprintw(1, 0, "Coins: %d", player->coins); // The reason this is last is to put the ncurses cursor in a nice spot
    if(coin_anim_on)
        attroff(COLOR_PAIR(1));

    // Update data for next time
    prev_player_x = player->room_x;
    prev_player_y = player->room_y;
    refresh();
}

void render_anim(const Player *player, const Room *room) {
    // Simplified rendering; we only care about the coins
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

    // If we moved, check if we got a coin
    if(prev_player_x != player->room_x || prev_player_y != player->room_y) {
        render_check_coin(player->room_x, player->room_y, player->coins);
    }

    // Alright; since we don't have time to rig a proper animation system, we have hardcoded nonsense :)
    if(coin_anim_on) {
        int timer = input_time() - coin_anim_start;
        if(timer < 100) {
            attron(COLOR_PAIR(4));
            plot_char(coin_anim_x, coin_anim_y, ' '); // Lellow
            attroff(COLOR_PAIR(4));
        } else if(timer < 200) {
            attron(COLOR_PAIR(4));
            plot_char(coin_anim_x-1, coin_anim_y-1, ' '); // Bigger lellow
            plot_char(coin_anim_x-1, coin_anim_y, ' ');
            plot_char(coin_anim_x-1, coin_anim_y+1, ' ');
            plot_char(coin_anim_x, coin_anim_y-1, ' ');
            plot_char(coin_anim_x, coin_anim_y+1, ' ');
            plot_char(coin_anim_x+1, coin_anim_y-1, ' ');
            plot_char(coin_anim_x+1, coin_anim_y, ' ');
            plot_char(coin_anim_x+1, coin_anim_y+1, ' ');
            attroff(COLOR_PAIR(4));
            render_room_tile(coin_anim_x, coin_anim_y, room_data); // but fix the middle tile
        } else if(timer < 300) {
            attron(COLOR_PAIR(4));
            for(int i = -1; i <= 1; i++) {                    // #    ###  #    #    ###  # # #
                plot_char(coin_anim_x+i, coin_anim_y-2, ' '); // #    #    #    #    # #  # # #
                plot_char(coin_anim_x+i, coin_anim_y+2, ' '); // #    ##   #    #    # #  # # #
                plot_char(coin_anim_x-2, coin_anim_y+i, ' '); // #    #    #    #    # #  # # #
                plot_char(coin_anim_x+2, coin_anim_y+i, ' '); // ###  ###  ###  ###  ###  #####
            }
            attroff(COLOR_PAIR(4));
            render_room_tile(coin_anim_x-1, coin_anim_y-1, room_data); // And even more fixing
            render_room_tile(coin_anim_x-1, coin_anim_y, room_data);
            render_room_tile(coin_anim_x-1, coin_anim_y+1, room_data);
            render_room_tile(coin_anim_x, coin_anim_y-1, room_data);
            render_room_tile(coin_anim_x, coin_anim_y+1, room_data);
            render_room_tile(coin_anim_x+1, coin_anim_y-1, room_data);
            render_room_tile(coin_anim_x+1, coin_anim_y, room_data);
            render_room_tile(coin_anim_x+1, coin_anim_y+1, room_data);
        } else {
            for(int i = -1; i <= 1; i++) {
                render_room_tile(coin_anim_x+i, coin_anim_y-2, room_data); // Just fixing
                render_room_tile(coin_anim_x+i, coin_anim_y+2, room_data);
                render_room_tile(coin_anim_x-2, coin_anim_y+i, room_data);
                render_room_tile(coin_anim_x+2, coin_anim_y+i, room_data);
            }
            coin_anim_on = 0; // because we're done now
        }
    }

    // Erase the player's previously known position, then draw the new one
    mvaddch(prev_player_y + 2, prev_player_x + 19, ' ');
    if(prev_player_y > player->room_y) player_char = '^';
    else if(prev_player_y < player->room_y) player_char = 'v';
    else if(prev_player_x > player->room_x) player_char = '<';
    else if(prev_player_x < player->room_x) player_char = '>';
    attron(COLOR_PAIR(3));
    mvaddch(player->room_y + 2, player->room_x + 19, player_char);
    attroff(COLOR_PAIR(3));

    // Coin display! :D
    if(coin_anim_on) {
        attron(COLOR_PAIR(1));
    }
    mvprintw(1, 0, "Coins: %d", player->coins);
    if(coin_anim_on) {
        attroff(COLOR_PAIR(1));
    }

    // Update data
    prev_player_x = player->room_x;
    prev_player_y = player->room_y;
    refresh();
}

// When did we start the win animation?
static int win_time = 0;

// When the player has accomplished their goal, the marble walls blink to and from being grass.
// Obviously that's how this works.
bool render_win(const Player *player, const Room *room) {
    if(!win_time) win_time = input_time();
    int time = input_time() - win_time;
    if(time < 3000) {
        if(time % 1000 < 750 && time % 1000 > 250) {
            init_pair(2, COLOR_GREEN, COLOR_GREEN); // Change the walls to gren
        } else {
            init_pair(2, COLOR_WHITE, COLOR_WHITE); // Change the walls to whit
        }
        refresh();
        return 1; // Yes, keep going
    }
    return 0; // No, stop going
}