//bricks.c
#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines

#include "bricks.h"
#include "ansi.h"

//global variables



// functions

void initBricks(char brick[][20]) {
	char i, j;
	for(i = 0; i < 120 / brickLength; i++) {
		for (j = 0; j < 48 / (2 * brickHeight); j++) 
			brick[i][j] = 1;
	}
	for(i = 0; i < 120 / brickLength; i++) {
		for (j = 0; j < 48 / (2 * brickHeight); j++)  
			printBrick(brick[i][j], i, j * brickHeight + 2);
	}
}

/*
void updateBricks(char brick[][20], char lastBrick[][20]) {
	char i, j;
	
	for(i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			if(brick[i][j] != lastBrick[i][j]) 
				printBrick(brick[i][j], i, j);
			}
	}

	fgcolor(15);
}
*/

void printBrick(char lives, char column, char row) {
	char i, j;
	//gotoxy(2 + column * 6, row);
	switch(lives) {
		case 0:
			fgcolor(0);
			break;
		case 1:	
			fgcolor(9);
			break;
		case 2:
			fgcolor(2);
			break;	
		case 3:
			fgcolor(5);
			break;
	}
	for(i = 0; i < brickHeight; i++) {
		gotoxy(2 + column * brickLength, row + i); // 2 for at tage hoejde for kanten
		for(j = 0; j <brickLength; j++)
			printf("%c", 219);
	}
	fgcolor(15);

}

