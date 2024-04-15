// #include <ncurses.h>

#include <wchar.h>
#include <ncursesw/curses.h>
#include <locale.h>
#include <curses.h>

int main() {
    int ch;
    setlocale(LC_CTYPE, ""); /* 로케일 설정을 했는데도 */

    initscr(); // ncurses 초기화
    raw(); // 입력을 즉시 사용 가능한 형태로 설정
    keypad(stdscr, TRUE); // 특수 키를 처리하기 위해 키패드 활성화
    // noecho(); // 키 입력에 대한 에코 비활성화
    // echo();

    printw("Press any key to continue...\n");
    refresh();
    ch = getch(); // 키 입력 받기
    getch();
    printw("You pressed: %c\n", ch);
    printw("True or False: %d\n", ch == 'a');
    if(ch == 'a')printw("hahaha\n");
    wchar_t name[100];
    printw("enter your name\n");
    wget_wstr(stdscr,name);

    printw("Your name is %ls", name);
    refresh();
    
    getch(); // 잠시 기다리기
    endwin(); // ncurses 종료

    return 0;
}
