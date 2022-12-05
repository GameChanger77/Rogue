#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "input.h"

int t = 0, Triangle = 0, Circle = 0, X = 0, Square = 0, JLX = 0, JLY = 0, JRX = 0, JRY = 0; 
int tFlag = 0, cFlag = 0, xFlag = 0, sFlag = 0, JLXFlag = 0, JLYFlag = 0;
int timeIntervalX = 150, timeIntervalY = 250, startTime = 0;

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
	

	if (JLY > 100 && JLYFlag == 0){ // Move Player Down
		JLYFlag = 1;
		startTime = t;
		return Down;
	} else if (JLY < -100 && JLYFlag == 0){ // Move Player Up
		JLYFlag = 1;
		startTime = t;
		return Up;
	} 
	else if ((JLY <= 80 && JLY >= 0) || (JLY >= -80 && JLY < 0) || (startTime + timeIntervalY <= t)){
		JLYFlag = 0;
	} 
	
	if (JLX > 100 && JLXFlag == 0){ // Move Player Right
		JLXFlag = 1;
		startTime = t;
		return Right;
	} else if (JLX < -100 && JLXFlag == 0){ // Move Player Left
		JLXFlag = 1;
		startTime = t;
		return Left;
	} 
	else if ((JLX <= 80 && JLX >= 0) || (JLX >= -80 && JLX < 0) || (startTime + timeIntervalX <= t)){
		JLXFlag = 0;
	} 
	
	return None; // Stand Still
}