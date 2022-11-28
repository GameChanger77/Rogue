#include <stdio.h>
#include "input.h"

int t = 0, Triangle = 0, Circle = 0, X = 0, Square = 0, JLX = 0, JLY = 0, JRX = 0, JRY = 0; 
int tFlag = 0, cFlag = 0, xFlag = 0, sFlag = 0, JRXFlag = 0, JRYFlag = 0;

void input_scan(){
	scanf("%d, %d,%d,%d,%d, %d, %d, %d, %d ", &t, &Triangle, &Circle, &X, &Square, &JLX, &JLY, &JRX, &JRY);
}

int input_time(){
	return t;
}

Direction input_direction(){

	if (JRY > 100 && JRYFlag == 0){ // Down
		JRYFlag = 1;
		return Down;
	} else if (JRY < -100 && JRYFlag == 0){ // Up
		JRYFlag = 1;
		return Up;
	} 
	else if ((JRY <= 80 && JRY >= 0) || (JRY >= -80 && JRY < 0)){
		JRYFlag = 0;
	} 
	
	if (JRX > 100 && JRXFlag == 0){ // Right
		JRXFlag = 1;
		return Right;
	} else if (JRX < -100 && JRXFlag == 0){ // Left
		JRXFlag = 1;
		return Left;
	} 
	else if ((JRX <= 80 && JRX >= 0) || (JRX >= -80 && JRX < 0)){
		JRXFlag = 0;
	} 
	
	return None;
}