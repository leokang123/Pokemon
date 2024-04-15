#pragma once

#include <stdlib.h>
#include <wchar.h>
#include <ncursesw/curses.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>

#define MTOS        1000000
#define FAST        MTOS/120
#define NORMAL      MTOS/60
#define SLOW        MTOS/30

#define DEFAULT     COLOR_PAIR(1) 
#define SELECT      COLOR_PAIR(2)
#define ST          2 * COLS/13.0
#define ED          11 * COLS/13.0

void endRoutine(int lines);
void lineControl();
void screen(int a, int b, wchar_t *mess);
void serialScreen(int a, int b, wchar_t *mess, int time);
int pokeImage1(int imline, int imcol, int num);
int pokeImage2(int imline, int imcol, int num);
void randomScreen(void); 
void dynamicClear(int type, int start, int num);
void borderLine(int line, int st, int ed);
void staticClear(int line1, int line2, int col1, int col2);
