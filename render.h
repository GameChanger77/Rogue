#ifndef ROGUE_RENDER_H
#define ROGUE_RENDER_H

#include "player.h"
#include "room.h"

// Initialize the rendering system
void render_init(void);

// We just entered a new room, render it for the first time.
void render_enter_room(const Player *player, const Room *room);

// Nothing has happened, run animations
void render_anim(const Player *player, const Room *room);

// Win the game. Ez
// Returns false when the win animation is over
bool render_win(const Player *player, const Room *room);

#endif // ROGUE_RENDER_H