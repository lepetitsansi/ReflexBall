//ball.c
#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "ball.h"
#include "ansi.h"
#include "timer.h"
#include "LED.h"
#include "bricks.h"

//global variables

char counterB = 0;

// functions
void printBall(ball_t* start, ball_t* last){
	if((start->x != last->x || start->move) && (start->y == last->y || start->move)) {
		gotoxy(last->x >> FIX14_SHIFT, last->y >> FIX14_SHIFT);
		printf(" ");
	 }
	 gotoxy(start->x >> FIX14_SHIFT, start->y >> FIX14_SHIFT);
	 printf("O");
	 
}

void moveBall(ball_t* move) {
	if(flagBall){
		flagBall = 0;
		if(++counterB >= BALLSPEED) {
			counterB = 0;
			if(move->x > (2 << FIX14_SHIFT)  && move->x < (121 << FIX14_SHIFT)){
				move->x += move->dx;
			} else {
				move->dx = -move->dx;
				move->x += move->dx;
			}
			if(move->y > (2 << FIX14_SHIFT) ) { //&& move->y <= 49
				move->y += move->dy;
			} else {
				move->dy = -move->dy;
				move->y += move->dy;
			}
		}
	}
}

void checkStrikerCollision(striker_t* striker, ball_t* ballPosition) {
	long intervalLength;
	if(ballPosition->y == (50 << FIX14_SHIFT)) {
		intervalLength = striker->length / 5; // skal bruge macros  FIX14_DIV(striker->length(FIX14), 5 << FIX14_shift)
		if((striker->leftEnd - 1) <= ballPosition->x >> FIX14_SHIFT && ballPosition->x >> FIX14_SHIFT < (striker->leftEnd + intervalLength)) { 
			ballPosition->dx = -FIX14_DIV(3<<FIX14_SHIFT,2<<FIX14_SHIFT);
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;
		} 
		if((striker->leftEnd + intervalLength) << FIX14_SHIFT <= ballPosition->x && ballPosition->x < (striker->leftEnd + (intervalLength << 1)) << FIX14_SHIFT) { 
			ballPosition->dx = -1
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;
		}
		if((striker->leftEnd + (intervalLength << 1)) << FIX14_SHIFT <= ballPosition->x && ballPosition->x < (striker->leftEnd + (intervalLength << 1) + intervalLength) << FIX14_SHIFT ) { 
			ballPosition->dx = 0
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;
		}
		if((striker->leftEnd + (intervalLength << 1) + intervalLength) << FIX14_SHIFT <= ballPosition->x && ballPosition->x < (striker->leftEnd + (intervalLength << 2)) << FIX14_SHIFT) { 
			ballPosition->dx = 1;
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;
		}
		if((striker->leftEnd + (intervalLength << 2)) << FIX14_SHIFT <= ballPosition->x && ballPosition->x < (striker->leftEnd + (intervalLength << 2) + intervalLength) << FIX14_SHIFT ) { 
			ballPosition->dx = FIX14_DIV(3<<FIX14_SHIFT,2<<FIX14_SHIFT);
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;

		}
	}
}
/*
void checkStrikerCollision(striker_t* striker, ball_t* ballPosition) {
	long intervalLength, leftEnd, strikerlngth;
	if(ballPosition->y == (50 << FIX14_SHIFT)) {
//		intervalLength = FIX14_DIV((striker->length << FIX14_SHIFT), (5 << FIX14_SHIFT)); // dividere med nul
		strikerlngth = striker->length; //<< FIX14_SHIFT;
		intervalLength = strikerlngth / 5; //FIX14_DIV(strikerlngth, 5); // Vil ikke reflect
		leftEnd = striker->leftEnd << FIX14_SHIFT;
		if(leftEnd - (1 << FIX14_SHIFT) <= ballPosition->x && ballPosition->x < leftEnd + intervalLength) { 
			ballPosition->dx = -2 << FIX14_SHIFT;
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;
		} 
		if(leftEnd + intervalLength <= ballPosition->x && ballPosition->x < leftEnd + (intervalLength << 1)) { 
			ballPosition->dx = -1 << FIX14_SHIFT;
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;
		}
		if(leftEnd + (intervalLength << 1) <= ballPosition->x && ballPosition->x < leftEnd + (intervalLength << 1) + intervalLength) { 
			ballPosition->dx = 0;
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;
		}
		if(leftEnd + (intervalLength << 1) + intervalLength <= ballPosition->x && ballPosition->x < leftEnd + (intervalLength << 2)) { 
			ballPosition->dx = 1 << FIX14_SHIFT;
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;
		}
		if(leftEnd + (intervalLength << 2) <= ballPosition->x && ballPosition->x < leftEnd + (intervalLength << 2) + intervalLength ) { 
			ballPosition->dx = 2 << FIX14_SHIFT;
			ballPosition->dy = -ballPosition->dy;
			ballPosition->y += ballPosition->dy;

		}
	}

}*/

void releaseBall(ball_t* ball) {
		ball->dy = -1 << FIX14_SHIFT;
		ball->dx = 1 << FIX14_SHIFT;
}

void initBall(ball_t* ball , char startPos) {
	long x = startPos;
	ball->x = (x+4) << FIX14_SHIFT;
	ball->y = 49 << FIX14_SHIFT;
	ball->dx = 0;
	ball->dy = 0;
	ball->move = 0;
}

void gameOver(ball_t* ball, striker_t* striker, char* life) {
	if(ball->y >= (51 << FIX14_SHIFT)) {
		if(*life > 1) {
			goLeft(1);
			printf(" ");
			initBall(ball, striker->leftEnd);
			(*life)--;
			LEDsetString("lives left:");
		} else
			LEDsetString("GAME OVER ");
	}
}

void checkBrickCollision(ball_t* ball, char brick [][20]) {
	char brickX, brickY;
	if (ball->y < (48 /brickHeight + 2) << FIX14_SHIFT) {
		brickX = ((ball->x >> FIX14_SHIFT) + brickLength - 2)/brickLength - 1;
		brickY = ((ball->y >> FIX14_SHIFT) + brickHeight - 2)/brickHeight - 1;
		if (brick[brickY][brickX] >= 1) {
			brick[brickY][brickX]--;
			
			printBrick(0, brickX, (ball->y - 1) >> FIX14_SHIFT);
			ball->dy = -ball->dy;
			ball->y += ball->dy;
			
		
		}
	}
}
