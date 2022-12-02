#include <stdio.h>
#include "input.h"

int t = 0, Triangle = 0, Circle = 0, X = 0, Square = 0, JLX = 0, JLY = 0, JRX = 0, JRY = 0; 
int tFlag = 0, cFlag = 0, xFlag = 0, sFlag = 0, JLXFlag = 0, JLYFlag = 0;

void input_scan(){
	scanf("%d, %d,%d,%d,%d, %d, %d, %d, %d ", &t, &Triangle, &Circle, &X, &Square, &JLX, &JLY, &JRX, &JRY);
}

int input_time(){
	return t;
}

Direction input_direction(){

	if (JLY > 100 && JLYFlag == 0){ // Down
		JLYFlag = 1;
		return Down;
	} else if (JLY < -100 && JLYFlag == 0){ // Up
		JLYFlag = 1;
		return Up;
	} 
	else if ((JLY <= 80 && JLY >= 0) || (JLY >= -80 && JLY < 0)){
		JLYFlag = 0;
	} 
	
	if (JLX > 100 && JLXFlag == 0){ // Right
		JLXFlag = 1;
		return Right;
	} else if (JLX < -100 && JLXFlag == 0){ // Left
		JLXFlag = 1;
		return Left;
	} 
	else if ((JLX <= 80 && JLX >= 0) || (JLX >= -80 && JLX < 0)){
		JLXFlag = 0;
	} 
	
	return None;
}