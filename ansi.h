// ansi.h

#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines

#ifndef _ANSI_H_
#define _ANSI_H_

//Defines
#define ESC 0x1B

//functions
void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void gotoxy(char x, char y);
void clrscr();
void clreol();
void underline(char on);
void blink(char on);
void reverse(char on);
int strlength(char * s);
void window(char x1, char y1, char x2, char y2, char * title, char style);
void goUp (char x);
void goDown (char x);
void goRight (char x);
void goLeft (char x);
void hideCursor(char on);

#endif /*! _ANSI_H_ */
