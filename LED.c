// LED.c
#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines

#include "LED.h"
#include "ansi.h"
#include "charset.h"

volatile char flag = 0;	
char length, digit, column, scroll, counter, videoBuffer[5][6];
char *pString;


#pragma interrupt
void timer1int() {
	flag++;
}

void clockDisplay(char ledBlock) {
	switch(ledBlock) {
		case 1:
			PGOUT &= ~(1 << 7);
			PGOUT |= 1 << 7;
			break;

		case 2:
			PEOUT &= ~(1 << 5);
			PEOUT |= 1 << 5;
			break;

		case 3:
			PEOUT &= ~(1 << 6);
			PEOUT |= 1 << 6;
			break;

		default:
			PEOUT &= ~(1 << 7);
			PEOUT |= 1 << 7;
	}
}

void LEDinit() {
	char i;
	PEDD = 0x00;
	PGDD = 0x00;
	PEOUT = 0x1F;
	
	for (i = 0; i < 4; i++)
		clockDisplay(i);
	
	// følgende er til timeren
	DI();
	T1CTL = 0x01; // precale til 000, mode til 001 (contomious mode
	T1H = 0x00; // high byte register (start) 0000
	T1L = 0x01; // low bye register (start)   0001
//	T1RH = 0x24; // Reload high byte register  ((0.0005 * 18432000)/1) = 9216
//	T1RL = 0x00; // Reload low bye register
	T1RH = 0x48; // Reload high byte register  ((0.001 * 18432000)/1) = 18432  DEN MINIMALE CLOCK FREKVENS FOR LEDs
	T1RL = 0x00; // Reload low bye register
	IRQ0ENH &= ~(1 << 6);	// enable Timer1 interrupt, and set low priority
	IRQ0ENL |= 1 << 6; 	// "
	T1CTL |= 1 << 7;  // starter timer
	SET_VECTOR(TIMER1, timer1int);
	EI();
}

void LEDsetString(char string[]) {
	char i, j;
	length = strlength(string);
	pString = string;
	
	for (i = 0; i < 5; i++) {
		pString++;
		if(string[i] == '\0') {
			pString -= length;
			break;
		}
		for (j=0; j < 5; j++) {
			videoBuffer[i][j] = character_data[string[i] - 0x20][j];
		}
	}
	
	if(length < 4) {
		for (i = length; i < 5; i++) {
			for (j=0; j < 5; j++)
			videoBuffer[i][j] = character_data[' ' - 0x20][j];
		}
	}
	 digit = column = scroll = counter = 0;
}

void shiftDigit() {
	char i,j;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (i < 4)
				videoBuffer[i][j] = videoBuffer[i + 1][j]; //Skifter digits til venstre
			else {
				videoBuffer[4][j] = character_data[*pString - 0x20][j]; //saetter en ny char ind på den 5. plads
			}
		}
	}
	pString++; //peger på naeste char i strengen
	if (*pString == '\0') { //sikrer at strengen koerer igen ved at saette den til at pege paa foestre char i strengen
		pString -= length;
	}
}

void LEDupdate() {
	if (flag) {
		flag = 0;

		PGOUT = *(&videoBuffer[0][0] + digit*6 + column + scroll);
		PEOUT |= 0x1F;
		PEOUT &= ~(1 << (4-column)); 

		clockDisplay(digit);
		
		if (++digit == 4) { // skifter mellem LEDbloks
			digit = 0;
			if (++column == 5) { // skifter columns i den bestemte LEDblock
				column = 0; // nu er 4 chars skrevet (streng skrevet en gang)
				if (length > 4 && ++counter == SCROLL_SPEED) { // hastigheden samt betingelse der sikrer den ikke scroller på mindre end 4 digits
					counter = 0;	
					if (++scroll == 6) { // 
						scroll = 0;
						shiftDigit();
					}
				}
			}
		}
	} 
}
