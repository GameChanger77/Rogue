#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "input.h"
#include "config.h"

int t = 0, Triangle = 0, Circle = 0, X = 0, Square = 0, JLX = 0, JLY = 0, JRX = 0, JRY = 0;
int deadZone = 30, PJLX = 0, PJLY = 0, xCount = 0, yCount = 0, limitX = 1200, limitY = 2000;

// Scan in the input
void input_scan(){ 
	scanf("%d, %d,%d,%d,%d, %d, %d, %d, %d ", &t, &Triangle, &Circle, &X, &Square, &JLX, &JLY, &JRX, &JRY);
}

// Gets the time from the controller
int input_time(){ 
	return t;
}

Direction input_direction(){
	
	// Exit the game
	if (Triangle){ 
		endwin();
		exit(0);
	}

	// if (Circle && DEBUG_MODE) player

	// Add to the movement buffers
	if(JLX > deadZone && PJLX <= deadZone) xCount = limitX;
	if(JLX < -deadZone && PJLX >= -deadZone) xCount = -limitX;
	if(JLY > deadZone && PJLY <= deadZone) yCount = limitY;
	if(JLY < -deadZone && PJLY >= -deadZone) yCount = -limitY;

	PJLX = JLX;
	PJLY = JLY;

	// Reset the movement buffers when the joystick is in the center
	if (JLX < -deadZone || JLX > deadZone) xCount += JLX;
	else xCount = 0;
	if (JLY < -deadZone || JLY > deadZone) yCount += JLY;
	else yCount = 0;

	// Return the direction to move
	if (xCount > limitX){ // Right
		xCount = 0;
		return Right;
	}
	
	if (xCount < -limitX){ // Left
		xCount = 0;
		return Left;
	}

	if (yCount > limitY){ // Down
		yCount = 0;
		return Down;
	}

	if (yCount < -limitY){ // Up
		yCount = 0;
		return Up;
	}
	
	return None; // Stand Still
}

int get_circle(){
	return Circle;
}