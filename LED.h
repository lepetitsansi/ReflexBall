// LED.h

#ifndef _LED_H_
#define _LED_H_

#define SCROLL_SPEED 10

void clockDisplay(char ledBlock);
void LEDinit();
void LEDsetString(char string[]);
void shiftDigit();
void LEDupdate();

#endif
