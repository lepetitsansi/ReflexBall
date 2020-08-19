// ansi.c

#include "ansi.h"

void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color      
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);  
}

void gotoxy(char x, char y) {
	printf("%c[%d;%dH", ESC, y, x);
}

void clrscr() {
	gotoxy(0,0);
	printf("%c[2J", ESC);
	
}

void clreol() {
	printf("%c[K", ESC);
}

void underline(char on) {
	char c = 4;
	if (on == 0) 
		c += 20;
	printf("%c[%dm", ESC, c);
}

void blink(char on) {
	char c = 5;
	if (on == 0) 
		c += 20;
	printf("%c[%dm", ESC, c);

}

void reverse(char on) {
	char c = 7;
	if (on == 0) 
		c += 20;
	printf("%c[%dm", ESC, c);
}

int strlength(char * s){
	int i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

void window(char x1, char y1, char x2, char y2, char * title, char style) {
	int length = strlength(title);	
	int width = x2 - x1;
    int height = y2 - y1;
	int i;
	int blanklength = width - 4 - length;  //To calculate the lenght of spaces for centering purpose

	switch (style) {
	  case 1: 
		//top
		gotoxy(x1,y1);
		printf("%c%c" , 201, 185);

		reverse(1);

		if(blanklength > 4) {
			printf("  %s  ", title);
			reverse(0);
			printf("%c", 204);
			for(i = 0;  i < blanklength - 4; i++)
 		    	printf("%c", 205);
			printf("%c", 187);
		} else {
			if (length > width - 4) {
				for (i = 0; i < width - 4; i++)
					printf("%c" , title[i]);
			} else
				printf("%s", title);
	
			for(i = 0; i < width - length - 4; i++)
				printf(" ");
			reverse(0);
			printf("%c%c" , 204, 187);
		}
	
		//sides
		for(i = 1; i < height ; i++) {
    		gotoxy(x1, y1 + i);
			printf("%c", 186);
    		gotoxy(x2 - 1, y1 + i);
			printf("%c", 186);
		}
		//bottom
		gotoxy(x1,y2);
		printf("%c", 200);
		for(i = 0; i < width-2; i++)
			printf("%c",205);
		printf("%c" ,188);

	  break;
	
	  case 2:
	    //top
		gotoxy(x1,y1);
		printf("%c%c" , 218, 180);
	
		reverse(1);
		
		for(i = 0; i < blanklength / 2; i++) //spaces on lhs
			printf(" ");

		if (length > width - 4) {
			for (i = 0; i < width - 4; i++)
				printf("%c" , title[i]);
		} else
			printf("%s", title);

		if(blanklength % 2 > 0) { //spaces on rhs if unequal length
			for(i = 0; i < blanklength / 2 + 1; i++)
				printf(" ");
		} else {
			for(i = 0; i < blanklength / 2 ; i++)
				printf(" ");
		}
		reverse(0);
		printf("%c%c" , 195, 191);
		
		//sides
		for(i = 1; i < height ; i++) {
	    	gotoxy(x1, y1 + i);
			printf("%c", 179);
	    	gotoxy(x2 - 1, y1 + i);
			printf("%c", 179);
		}
	
		//bottom
		gotoxy(x1,y2);
		printf("%c", 192);
		for(i = 0; i < width-2; i++)
			printf("%c",196);
		printf("%c" ,217);

	  break;
	  
	default:
		//top
		gotoxy(x1,y1);
		printf("%c" , 218);
	
		for(i = 0; i < width-2; i++)
			printf("%c",196);
		printf("%c" , 191);
		
		//sides
		for(i = 1; i < height ; i++) {
	    	gotoxy(x1, y1 + i);
			printf("%c", 179);
	    	gotoxy(x2 - 1, y1 + i);
			printf("%c", 179);
		}
	
		//bottom
		gotoxy(x1,y2);
		printf("%c", 192);
		for(i = 0; i < width-2; i++)
			printf("%c",196);
		printf("%c" ,217);
	}	
}

void goUp (char x) {
	printf("%c[%dA", ESC, x);
}

void goDown (char x) {
	printf("%c[%dB", ESC, x);
}

void goRight (char x) {
	printf("%c[%dC", ESC, x);
}

void goLeft (char x) {
	printf("%c[%dD", ESC, x);
}

void hideCursor(char on) {
	if(on)
		printf("%c[?25h", ESC);
	else
		printf("%c[?25l", ESC);
}


