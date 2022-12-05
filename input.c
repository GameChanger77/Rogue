#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "input.h"

int t = 0, Triangle = 0, Circle = 0, X = 0, Square = 0, JLX = 0, JLY = 0, JRX = 0, JRY = 0;
int deadZone = 10, PJLX = 0, PJLY = 0, xCount = 0, yCount = 0, limitX = 1000, limitY = 600;

void input_scan(){ // Scan in the input
	scanf("%d, %d,%d,%d,%d, %d, %d, %d, %d ", &t, &Triangle, &Circle, &X, &Square, &JLX, &JLY, &JRX, &JRY);
}

int input_time(){ // Gets the time from the controller
	return t;
}

Direction input_direction(){
	
	if (Triangle){ // Exit the game
		endwin();
		exit(0);
	}

	if(JLX > deadZone && PJLX <= deadZone) xCount = limitX;
	if(JLX < -deadZone && PJLX >= -deadZone) xCount = -limitX;
	if(JLY > deadZone && PJLY <= deadZone) yCount = limitY;
	if(JLY < -deadZone && PJLY >= -deadZone) yCount = -limitY;

	PJLX = JLX;
	PJLY = JLY;

	if (JLX < -deadZone || JLX > deadZone) xCount += JLX;
	if (JLY < -deadZone || JLY > deadZone) yCount += JLY;

	if (xCount > limitX){
		xCount = 0;
		return Right;
	}
	
	if (xCount < -limitX){
		xCount = 0;
		return Left;
	}

	if (yCount > limitY){
		yCount = 0;
		return Down;
	}

	if (yCount < -limitY){
		yCount = 0;
		return Up;
	}
	
	return None; // Stand Still
}