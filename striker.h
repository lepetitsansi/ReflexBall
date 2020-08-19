
//striker.h

#ifndef _STRIKER_H_
#define _STRIKER_H_


//#defines

//struckt
#include "typedef.h"

//functions

void initStriker(char start, char length, striker_t* striker);
char drawStriker(buttons_t* move, striker_t* striker);
void buttonUpdate(buttons_t *b);
void moveStriker(buttons_t* input, striker_t* strikerPos, ball_t* ball);


#endif

