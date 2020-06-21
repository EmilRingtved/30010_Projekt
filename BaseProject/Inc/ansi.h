#include "stdint.h" // Whatever needs to be included
#include "stdio.h"

#ifndef _ANSI_H_
#define _ANSI_H_

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void clrscr();
void clreol();
void gotoxy(int32_t x, int32_t y);
void underline(uint8_t on);
void blink(uint32_t on);
void inverse(uint32_t on);
void window(int32_t x1, int32_t y1,int32_t x2, int32_t y2, char text[], int32_t style);
void bouncewindow(int32_t x, int32_t y);
void drawmain();
void up();
void down();
void fwd();
void bck();
void drawPlayer(int32_t x, int32_t y);

//void bouncewindow(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2, char text[], uint8_t style);
#endif /* _ANSI_H_ */
