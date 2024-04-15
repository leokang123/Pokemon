#include <ncurses.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#define DEFAULT COLOR_PAIR(1) 
#define SELECT COLOR_PAIR(2)
#define ST          2 * COLS/9.0
#define ED          7 * COLS/9.0

void borderLine(int line) {
    move(line,ST);
    for (int i = ST; i < ED; ++i) {
        addch('=');
    }
    refresh();
}
/* line 의 row에서 col ~ col2까지 args 갯수만큼 균일하게 선택창을 만드는 함수  */
int arrowFunc(int type, int line, int col, int col2, int args, ...){
    cbreak(); // 입력 버퍼를 사용하지 않도록 설정
    noecho(); // 입력한 문자가 화면에 표시되지 않도록 설정
    keypad(stdscr, TRUE); // 특수 키를 사용할 수 있도록 설정
    // 초기 배경 색상 설정
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // 검정색 바탕에 흰색 텍스트
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // 흰색 바탕에 검정색 텍스트

    int a = 0;
    int ch = 0;
    if(type == 0){
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
        wchar_t point[] = L">";
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
                    // refresh();
                    attron(DEFAULT);
                    mvprintw(line,gap[(i-1 + args) % args]-1," ");
                    mvprintw(line,gap[(i-1 + args) % args],"%ls", arr[(i-1 + args) % args]);
                    attroff(DEFAULT);

                    attron(DEFAULT);
                    mvprintw(line,gap[(i+1 + args) % args]-1," ");
                    mvprintw(line,gap[(i+1 + args) % args],"%ls", arr[(i+1 + args) % args]);
                    attroff(DEFAULT);

                    attron(SELECT);
                    mvprintw(line,gap[i]-1,">");
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
        free(arr);
        free(gap);
    }
    if(type == 1) {

        va_list ap;
        va_start(ap, args);
        // 초기 상태 설정
        int * gap = (int *)malloc(sizeof(int) * args);
        wchar_t ** arr = (wchar_t **)malloc(sizeof(wchar_t*)*args);
        int resizeCol = (col2-col);
        for(int i = 0 ; i < args ; i++){
            arr[i] = va_arg(ap,wchar_t *);
        }
        va_end(ap);
        wchar_t point[] = L">";
        while (ch != 10) {
            for(int i = 0 ; i < args ; i++) {
                gap[i] = line + i;
                mvprintw(gap[i],col,"%ls", arr[i]);
            }
            refresh();
            if(a > args-1) a = 0;
            if(a < 0) a = args-1;
            for(int i = 0 ; i < args ; i++) {
                if(a == i) {
                    // refresh();
                    attron(DEFAULT);
                    mvprintw(gap[(i - 1 + args) % args],col-1," ");
                    mvprintw(gap[(i - 1 + args) % args],col,"%ls", arr[(i-1 + args) % args]);
                    attroff(DEFAULT);

                    attron(DEFAULT);
                    mvprintw(gap[(i + 1 + args) % args],col-1," ");
                    mvprintw(gap[(i + 1 + args) % args],col,"%ls", arr[(i+1 + args) % args]);
                    attroff(DEFAULT);

                    attron(SELECT);
                    mvprintw(gap[i],col-1,">");
                    mvprintw(gap[i],col,"%ls", arr[i]);
                    attroff(SELECT);
                    refresh();
                    
                } 
            }
            ch = getch();
            if(ch == KEY_UP) a -= 1;
            if(ch == KEY_DOWN) a += 1;
        }
        refresh();
        free(arr);
        free(gap);
    }
    if (type == 2) {

        va_list ap;
        va_start(ap, args);
        // 초기 상태 설정
        int ** gap = (int **)malloc(sizeof(int *) * args);
        for(int i = 0 ; i < args ; i++){
            gap[i] = (int *)malloc(sizeof(int) * 2);
        }
        wchar_t ** arr = (wchar_t **)malloc(sizeof(wchar_t*)*args);
        for(int i = 0 ; i < args ; i++){
            arr[i] = va_arg(ap,wchar_t *);
        }
        int resizeCol = col2 - col;
        va_end(ap);
        wchar_t point[] = L">";
        int p = (args + 1)/2;        // 위아래이동 시 더하는 값
        int x = p + 1;               // 양옆 열간 간격 맞춰주기 위해 씀 
        while (ch != 10) {
            for(int i = 0 ; i < args ; i++) {
                gap[i][0] = (i/p) * resizeCol/9.0/2 + line;
                gap[i][1] = ((i%p)+1) * resizeCol/x + col;
                mvprintw(gap[i][0],gap[i][1],"%ls", arr[i]);
            }
            refresh();
            if(a > args-1) a = a - args ;
            if(a < 0) a = a + args ;
            for(int i = 0 ; i < args ; i++) {
                if(a == i) {
                    refresh();
                    attron(DEFAULT);
                    mvprintw(gap[(i-p+args)%args][0],gap[(i-p+args)%args][1] - 1, " ");
                    mvprintw(gap[(i-p+args)%args][0],gap[(i-p+args)%args][1],"%ls", arr[(i-p+args)%args]);
                    attroff(DEFAULT);

                    attron(DEFAULT);
                    mvprintw(gap[(i+p+args)%args][0],gap[(i-p+args)%args][1] - 1, " ");
                    mvprintw(gap[(i+p+args)%args][0],gap[(i-p+args)%args][1],"%ls", arr[(i+p+args)%args]);
                    attroff(DEFAULT);

                    attron(DEFAULT);
                    mvprintw(gap[(i-1+args)%args][0],gap[(i-1+args)%args][1] - 1, " ");
                    mvprintw(gap[(i-1+args)%args][0],gap[(i-1+args)%args][1],"%ls", arr[(i-1+args)%args]);
                    attroff(DEFAULT);

                    attron(DEFAULT);
                    mvprintw(gap[(i+1+args)%args][0],gap[(i+1+args)%args][1] - 1, " ");
                    mvprintw(gap[(i+1+args)%args][0],gap[(i+1+args)%args][1],"%ls", arr[(i+1+args)%args]);
                    attroff(DEFAULT);

                    attron(SELECT);
                    mvprintw(gap[i][0],gap[i][1]-1,">");
                    mvprintw(gap[i][0],gap[i][1],"%ls", arr[i]);
                    attroff(SELECT);
                    refresh();
                    
                } 
            }
            ch = getch();
            if(ch == KEY_LEFT) a -= 1;
            if(ch == KEY_RIGHT) a += 1;
            if(ch == KEY_UP) a -= p;
            if(ch == KEY_DOWN) a += p;

        }
        refresh();
        for(int i = 0 ; i < 2 ; i++){
            free(gap[i]);
        }
        free(gap);
        free(arr);
    }
    keypad(stdscr, FALSE); 
    nocbreak();
    echo();
    return a;
}
void gameScreen() {
    borderLine(LINES/10.0);
    borderLine(LINES/10.0*8);
    borderLine(LINES-1);
}


int main() {
    initscr(); // ncurses 초기화
    gameScreen();
    refresh();
    // int select = arrowFunc2(2,30,COLS, 10, L"FIRST",L"SECOND",L"THIRD",L"FORTH",L"FIFTH",L"SIXTH",L"SEVENTH",L"EIGHTH",L"NINETH",L"TENTH");
    int select = arrowFunc(2, LINES/10.0*8 + 4, ST,(ST+ED)/2, 4, L"FIRST",L"SECOND",L"THIRD",L"FORTH");

    clear();
    mvprintw(10,10,"You chose %d", select);
    refresh();
    sleep(1);
    endwin(); // ncurses 종료
    return 0;
}

