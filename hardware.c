 



//hardware.c
#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines

#include "hardware.h"
#include "timer.h"

//global variables



//functions
void initButton() {
	PDDD = (1 << 3);
	PFDD = (1 << 7) | (1 << 6);
}
char readkey() {
	char portD, portF;
	
	portD = (~PDIN >> 3) & 0x01;
	portF = (~PFIN >> 6);

	return (portD << 2) | (portF >> 1) | ((portF << 1) & 0x02);
}
