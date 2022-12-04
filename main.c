/* 
Team xx (please insert your team number instead of xx)
Team member 1 Matthew Johnson      | 40%
Team member 2 Ray Redondo          | 40%
Team member 3 Jacob Schulmeister V | 40%
*/

// We together put in over 100% effort to make this the most awesome final
// project we could.
// I promise we're not just bad at math.

// SYSTEM INCLUDES //
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

//     INCLUDES    //
#include "input.h"
#include "player.h"
#include "render.h"
#include "room.h"
#include "roomgen.h"

// You may notice a lack of structures, prototypes or definitions. This is
// because we put almost every functional piece of code into a separate file
// from the main function. Prototypes are in headers, definitions are in source
// files.

//   DEFINITIONS   //
int main(void) {
    Player player;

    puts("Loading...");
    roomgen_pregen();
    render_init();

    player.room_x = 0;
    player.room_y = 10;
    player.screen_x = 0;
    player.screen_y = 0;
    player.coins = 0;

    do {
        Room *current_room = roomgen_get(player.screen_x, player.screen_y);
        render_enter_room(&player, current_room);

        bool changed_room = false;
        while(!changed_room) {
            input_scan();
            Direction direction = input_direction();
            if(direction == None) {
                render_anim(&player, current_room);
            } else {
                changed_room = room_move(direction, &player, current_room);
            }
        }
    } while(1);

    puts("Have a nice day!");
	endwin();
}
