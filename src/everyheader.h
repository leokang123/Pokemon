#pragma once 
// curses.h 헤더파일에 이 정보가 있어야 제대로 선언문을 찾음 
// 먼 POSIX 호환성과 관련있는 코드이다 ( 500 이상부터 입력함수가 지원됨 )
#ifndef _XOPEN_SOURCE
    #define _XOPEN_SOURCE 500
#endif

#include "../include/globalVari.h"
#include "../include/func.h"
#include "../include/progress.h"
#include "../include/screen.h"
#include "../include/sound.h"
#include "../include/page.h"
#include "../include/gamefunc.h"

extern int line;
