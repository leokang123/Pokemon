#pragma once 

#include <stdio.h>
#include <ncursesw/curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#define DEFAULT COLOR_PAIR(1) 
#define SELECT COLOR_PAIR(2)

/* first ~ last 사이 랜덤값 반환 */
int randomInRange(int first, int last);

void * inputlenRange(void);

void blinkString(wchar_t *str, int bline);

/* line 의 row에서 col ~ col2까지 args 갯수만큼 균일하게 선택창을 만드는 함수  */
int arrowFunc(int type, int line1, int col, int col2, int args, ...);

void visualgetch();