#ifndef ROGUE_ROOMGEN_H
#define ROGUE_ROOMGEN_H

#include "room.h"

// Determine room layout in advance and initialize internal arrays
void roomgen_pregen(void);

// Get the room at (x, y), generating it if necessary, and return a reference to it
Room* roomgen_get(int x, int y);

#endif // ROGUE_ROOMGEN_H