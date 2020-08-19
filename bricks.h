//bricks.h
#ifndef _BRICKS_H_
#define _BRICKS_H_

// structs


//#defines

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / (b) )
#define brickLength 10
#define brickHeight 2


//functions

void initBricks(char brick[][20]);
void updateBricks(char brick[][20], char lastBrick[][20]);
void printBrick(char lives, char column, char row);

#endif
