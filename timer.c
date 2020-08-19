// timer. c

#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines

#include "timer.h"

//Globals
volatile char flagBall = 0;
volatile char flagStriker = 0;

//functions
#pragma interrupt
void timer0int() {
	flagBall++; // 10 mili sec
	flagStriker++;
}

void initTimer0() {
	DI();

	T0CTL = (7 << 3) | 1; // precale til 7, mode til 1 (continous mode)
	T0H = 0x00; // high byte register (start)
	T0L = 0x01; // low bye register (start)
	T0RH = 0x05; // Reload high byte register
	T0RL = 0xA0; // Reload low bye register
	
	IRQ0ENH |= 1 << 5;	// enable Timer0 interrupt, and set nominal priority
	IRQ0ENL &= ~(1 << 5); 	// "

	T0CTL |= 1 << 7; 
		
	SET_VECTOR(TIMER0, timer0int);

	EI();
}
