#include <ncurses.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#define DEFAULT     COLOR_PAIR(1) 
#define SELECT      COLOR_PAIR(2)
#define ST          2 * COLS/9.0
#define ED          7 * COLS/9.0

/* line 의 row에서 col ~ col2까지 args 갯수만큼 균일하게 선택창을 만드는 함수  */
int arrowFunc(int line, int col, int col2, int args, ...){
    cbreak(); // 입력 버퍼를 사용하지 않도록 설정
    noecho(); // 입력한 문자가 화면에 표시되지 않도록 설정
    keypad(stdscr, TRUE); // 특수 키를 사용할 수 있도록 설정
    // 초기 배경 색상 설정
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // 검정색 바탕에 흰색 텍스트
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // 흰색 바탕에 검정색 텍스트

    int a = 0;
    int ch = 0;

    va_list ap;
    va_start(ap, args);
    // 초기 상태 설정
    int * gap = (int *)malloc(sizeof(int) * args);
    wchar_t ** arr = (wchar_t **)malloc(sizeof(wchar_t*)*args);
    int resizeCol = (col2-col);
    for(int i = 0 ; i < args ; i++){
        gap[i] = resizeCol/(args) * i  + resizeCol/args * (1.0/2) + col;
        arr[i] = va_arg(ap,wchar_t *);
    }
    va_end(ap);

    while (ch != 10) {
        for(int i = 0 ; i < args ; i++) {
            mvprintw(line,gap[i],"%ls", arr[i]);
        }
        refresh();
        if(a > args-1) a = 0;
        if(a < 0) a = args-1;
        int p = 7;
        for(int i = 0 ; i < args ; i++) {
            if(a == i) {
                attron(DEFAULT);
                mvprintw(line,gap[(i-1 + args) % args],"%ls", arr[(i-1 + args) % args]);
                attroff(DEFAULT);
                attron(SELECT);
                mvprintw(line,gap[i],"%ls", arr[i]);
                attroff(SELECT);
                refresh();
            } 
        }
        ch = getch();
        if(ch == KEY_LEFT) a -= 1;
        if(ch == KEY_RIGHT) a += 1;
    }
    refresh();
    keypad(stdscr, FALSE); 
    nocbreak();
    free(arr);
    free(gap);
    echo();
    return a;
}

void startPage(int line1, int line2, int st, int ed ){
    for(int i = st ; i < ed ; i++) {
        mvprintw(line1,i,"-");
        mvprintw(line1+1,i,"-");
    }
    for(int i = st ; i < ed ; i++) {
        mvprintw(line1 + 10,i,"-");
        mvprintw(line1+9,i,"-");
    }
    // for(int i = line1 ; i <= line2 ; i++) {
    //     mvprintw(i,st,"|");
    //     mvprintw(i,ed,"|");
    // }
    refresh();
    getch();
}

int main() {
    initscr(); // ncurses 초기화
    refresh();
    startPage(10, 20, ST, ED);
    // int select = arrowFunc(2,30,120, 4, L"FIRST",L"SECOND",L"THIRD",L"FORTH");
    // clear();
    sleep(1);
    startPage(40, 50, ST, ED);
    endwin(); // ncurses 종료
    return 0;
}

