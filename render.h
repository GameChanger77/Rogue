#ifndef ROGUE_RENDER_H
#define ROGUE_RENDER_H

#include "room.h"

// Initialize the rendering system
void render_init(void);

// We just entered a new room, render it for the first time.
void render_enter_room(Room *room);

// Nothing has happened, run animations
void render_anim(void);

#endif // ROGUE_RENDER_H