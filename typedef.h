// typedef.h
// En hjaelpe fil med alle struct, som bliver benyttet


#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_


//typedefs struct 
typedef struct {
	char dummy : 5;
	char left : 1;
	char center : 1;
	char right : 1;
} buttons_t;


// signed chars, saa der kan benyttes negative vaerdier
typedef struct {
	long x;
	long y;
	long dx;
	long dy;
	char move;
} ball_t;

typedef struct {
	char leftEnd, length;
}striker_t;

#endif


