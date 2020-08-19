//ball.h
#ifndef _BALL_H_
#define _BALL_H_

// structs
#include "typedef.h"

//#defines
#define BALLSPEED 5

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / (b) )

//functions
void printBall(ball_t* start, ball_t* last);
void moveBall(ball_t* move);
void checkStrikerCollision(striker_t* striker, ball_t* ballPosition);
void releaseBall(ball_t* ball);
void initBall(ball_t* ball , char startPos);
void gameOver(ball_t* ball, striker_t* striker, char* life);

void checkBrickCollision(ball_t* ball, char brick [][20]);

#endif 
