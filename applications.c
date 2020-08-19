// applications.c

#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "applications.h"
#include "hardware.h"
#include "ansi.h"
#include "ball.h"
#include "striker.h"


//global variables
#include "timer.h" // her skal 'flag' benyttes




//functions
void initScreen() {
	clrscr();
	hideCursor(0);
	window(1,1, 123,50, "ReflexBall", 0); // (0,0 ... illegal argument)
	gotoxy(1,50);
	clreol();
}


