/* 
Team xx (please insert your team number instead of xx)
We were never given a team number, sorry :(
Team member 1 Matthew Johnson      | 40%
Team member 2 Ray Redondo          | 40%
Team member 3 Jacob Schulmeister V | 40%
*/

// We together put in over 100% effort to make this the most awesome final
// project we could.
// I promise we're not just bad at math.

// SYSTEM INCLUDES //
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//     INCLUDES    //
#include "config.h"
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
int main(int argc, char **argv) {
    Player player;

    puts("Loading...");

    // Argument parser
    bool arg_error = 0;
    for(int i = 1; i < argc; i++) {
        if(!strcmp(argv[i], "--debug") || !strcmp(argv[i], "-d")) {
            if(!DEBUG_MODE) DEBUG_MODE = 1;
            else puts("warning: debug flag set multiple times");
        } else {
            char *end;
            long seed = strtol(argv[i], &end, 10); // Convert to a long
            if(end != (argv[i] + strlen(argv[i]))) { // And if the entire string isn't a number...
                printf("error: unexpected argument \"%s\"; expected -d or a number\n", argv[i]); // crash
                arg_error = 1;
            } else if(IS_SEED_SET) puts("warning: seed set multiple times; using last one");
            else {
                IS_SEED_SET = 1;
                SET_SEED = seed;
            }
        }
    }

    if(arg_error) {
        puts("errors were detected on the command line, exiting");
        return 1;
    }

    // Initialize
    roomgen_pregen();
    render_init();

    player.room_x = 0;
    player.room_y = 10;
    player.screen_x = 0;
    player.screen_y = 0;
    player.coins = 0;

    // Game loop
    do {
        Room *current_room = roomgen_get(player.screen_x, player.screen_y);
        render_enter_room(&player, current_room);

        bool changed_room = false;
        while(!changed_room) {
            // Get input from the controller
            input_scan();
            Direction direction = input_direction();

            // Give the player coins for debugging
            if (get_circle() && DEBUG_MODE)
		            player.coins++;

            // Movement
            if(direction == None) { // Stay Still
                render_anim(&player, current_room);
                if(player.coins >= 15) {
                    while(render_win(&player, current_room)) input_scan();
                    endwin();
                    puts("You win!");
                    goto end;
                }
            } else {
                changed_room = room_move(direction, &player, current_room);
            }
        }
    } while(1);
	endwin(); // End

end:
    // TODO: Scoreboard
    puts("Have a nice day!");
}
