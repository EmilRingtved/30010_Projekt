#define ESC 0x1B
#include "ANSI.h"
#include <string.h>

void fgcolor(uint8_t foreground) {
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
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
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

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}
void drawPlayer(int32_t x, int32_t y){
     gotoxy(y,x);
     printf("[15C[1;36mÜÜÜÜÜÜÜÜ[0m\n[12C[1;36m²²²ÛÛÛÛÛÛÛÛÛÜ[0m\n[2C[1;30mÜÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÜ[0m\n[1C[1;30mÛ[0;31;40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[1;30mÛ[0m\n[1C[1;30mÛ[0;31;40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[1;30mÛ[0m\n[2C[1;30mÛÛ[0;31;40mÛÛÛÛ[1;30mÛÛÛÛ[0;31;40mÛÛÛÛÛÛÛÛÛÛÛÛ[1;30mÛÛÛÛ[0;31;40mÛÛÛ[1;30mÛß[0m\n[1C[1;30m  [4CßÛÛÛÛß[10CßÛÛÛÛß[0m\n");
 }

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr() {
// clears terminal??
  printf("%c[2J", ESC);
}

void clreol() {
// clears the rest of the current line
  printf("%c[K", ESC);
}

void gotoxy(int32_t y, int32_t x) {//uint eller int, 8 eller 32?
// takes two parameters x and y and moves the cursor to position (x,y)
  printf("%c[%d;%dH", ESC, y, x);
}

void underline(uint8_t on) {
// takes one parameter to turn on/off underline
  if (on == 1)
      printf("%c[4m", ESC);
  if (on == 0)
      printf("%c[24m", ESC);
}

void blink(uint32_t on) {
// takes one parameter to turn on/off blink
  if (on == 1)
      printf("%c[5m", ESC);
  if (on == 0)
      printf("%c[25m", ESC);
}

void inverse(uint32_t on) {
// takes one parameter to turn on/off reverse color text
  if (on == 1)
      printf("%c[7m", ESC);
  if (on == 0)
      printf("%c[27m", ESC);
}

void window(int32_t x1, int32_t y1,int32_t x2, int32_t y2, char text[], int32_t style) {
    int32_t a, i;
    //evt tegn kasse med goto
//ikke f�rdig

    if (style == 1) {
       int32_t width = x2 - x1;
       int32_t height = y2 - y1;
       int32_t length = strlen(text) + 3;
       //top
       printf("%c%c%c%c", 201,205,185,00);
       inverse(1);
       printf("%s", text);//print array
       inverse(0);
       printf("%c%c", 00,204);
       for (a = 1; a < width-length; a++) {
           printf("%c", 205);
       }
       printf("%c\n", 187);
       //middle
       for (i = 1; i < height; i++) {
           printf("%c", 186);
           for (a = 1; a < width; a++) {
               printf(" ");
           }
           printf("%c\n", 186);
       }
       //bottom
       printf("%c", 200);
       for (a = 1; a < width; a++) {
           printf("%c", 205);
       }
       printf("%c\n", 188);

    }
    else if (style == 2) {
       int32_t width = x2 - x1;
       int32_t height = y2 - y1;
       int32_t length = strlen(text) + 3;
       //top
       printf("%c%c%c%c", 218,196,180,00);
       inverse(1);
       printf("%s", text);//print array
       inverse(0);
       //printf("%c%c", 00,204);
       for (a = 1; a < width-length; a++) {
           printf("%c", 219);
       }
       printf("%c%c%c\n", 00, 195, 191);
       //middle
       for (i = 1; i < height; i++) {
           printf("%c", 179);
           for (a = 1; a < width; a++) {
               printf(" ");
           }
           printf("%c\n", 179);
       }
       //bottom
       printf("%c", 192);
       for (a = 1; a < width; a++) {
           printf("%c", 196);
       }
       printf("%c\n", 217);


    }



 }


void bouncewindow(int32_t x, int32_t y) {//draws bounce window
       int32_t a, i;
       gotoxy(0,0);

       //top
       printf("%c", 201);
       for (a = 1; a < x; a++) {
           printf("%c", 205);
       }

       printf("%c\n", 187);
       //middle
       for (i = 1; i < y/2; i++) {
           printf("%c", 186);
           for (a = 1; a < x; a++) {
               printf(" ");
           }
           printf("%c\n", 186);
       }
       //bottom
       printf("%c", 200);
       for (a = 1; a < x; a++) {
           printf("%c", 205);
       }
       printf("%c\n", 188);
 }

 void drawmain(){
     clrscr();
     gotoxy(0,0);
     printf("Title: Top Gun 3");

 }

 void up(int32_t x){
     printf("%c[%dA", ESC, x);
 }

 void down(int32_t x){
     printf("%c[%dB", ESC, x);
 }

  void fwd(int32_t x){
     printf("%c[%dB", ESC, x);
 }

 void bck(int32_t x){
     printf("%c[%dD", ESC, x);
 }

