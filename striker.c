
//striker.c
#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines

#include "striker.h"
#include "ansi.h"
#include "hardware.h"
#include "timer.h"
#include "ball.h"

//globals


//functions

void initStriker(char start, char length, striker_t* striker) {
	char i;
	striker->length = length;
	striker->leftEnd = start;
	gotoxy(start,50);
	for(i = 0; i < length; i++) 
		printf("%c", 219);
}


char drawStriker(buttons_t* move, striker_t* striker) {
	if(move->right && !move->left) {
		if(striker->leftEnd < 112) {
			gotoxy(striker->leftEnd, 50);
			printf(" ");
			striker->leftEnd++;
			gotoxy(striker->leftEnd + striker->length - 1, 50);
 		    printf("%c", 219);
			return striker->leftEnd;
		}
	}
	if(move->left && !move->right) {
		if(striker->leftEnd > 2) {
			gotoxy(striker->leftEnd + striker->length - 1, 50);
			printf(" ");
			striker->leftEnd--;
			gotoxy(striker->leftEnd, 50);
 		    printf("%c", 219);
			return striker->leftEnd;
		}
	}
	return striker->leftEnd;
}


void buttonUpdate(buttons_t *b) {
	char key;
	key = readkey();
	*b = *((buttons_t*) &key);
}

void moveStriker(buttons_t* input, striker_t* strikerPos, ball_t* ball) {
		buttonUpdate(input);
		if (input->right && input->right) {
			if(flagStriker){ 
				flagStriker = 0;
				strikerPos->leftEnd = drawStriker(input, strikerPos);
			}
		}
		if (input->center && input->center){
			if(flagStriker){ 
				flagStriker = 0;
				if(ball->move++ == 0) {
					
					releaseBall(ball);
				}
			}
		}
		if (input->left && input->left) {
			if(flagStriker){ 
				flagStriker = 0;
				strikerPos->leftEnd = drawStriker(input, strikerPos);
			}
		}
}
