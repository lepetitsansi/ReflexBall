#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "applications.h"
#include "hardware.h"
#include "timer.h"
#include "ball.h"
#include "LED.h"
#include "striker.h"
#include "bricks.h"


void main() {
	char strikerPos = 56;
	char length = 10;
	char life = 3;
	long temp = 0;
	striker_t striker;
	buttons_t input = {0,0,0,0};
	char theBricks[20][20];
	char lastBricks[20][20];
	ball_t leBall; //{56 + 4, 49, 0, 0, 0};
	ball_t lastBallPos;
	init_uart(_UART0,_DEFFREQ,BAUD_115200); // set-up UART0 to 57600 (nu 115200), 8n1
	
	initScreen();
	initButton();
	//LEDinit();
	initBall(&leBall, strikerPos);
	initStriker(strikerPos, length, &striker);
	initTimer0();
	initBricks(theBricks);

	do {
		//	LEDupdate();
		//updateBricks(theBricks, lastBricks);
		checkBrickCollision(&leBall, theBricks);	
		checkStrikerCollision(&striker, &leBall);
		printBall(&leBall, &lastBallPos);
		lastBallPos = leBall;
		if(leBall.move == 0) {
			temp = striker.leftEnd;
			leBall.x = (temp + 4) << FIX14_SHIFT;
		}
		moveBall(&leBall);
		
		gameOver(&leBall, &striker, &life);

		moveStriker(&input, &striker, &leBall); 

	} while (1 != 2); // stay here forever
}

