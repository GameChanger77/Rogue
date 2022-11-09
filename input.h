#ifndef ROGUE_INPUT_H
#define ROGUE_INPUT_H

typedef enum Direction {
    None,
    Up,
    Down,
    Left,
    Right
} Direction;

// Scan controller input
void input_scan(void);

// Return a direction if the player finished inputting one; otherwise, return None
Direction input_direction(void);

// Return the most recent time value scanned in
int input_time(void);

#endif // ROGUE_INPUT_H