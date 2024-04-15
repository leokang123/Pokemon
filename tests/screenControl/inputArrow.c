#include <ncurses.h>
#include <unistd.h>

int main() {
    initscr(); // ncurses 초기화
    cbreak(); // 입력 버퍼를 사용하지 않도록 설정
    noecho(); // 입력한 문자가 화면에 표시되지 않도록 설정
    keypad(stdscr, TRUE); // 특수 키를 사용할 수 있도록 설정

    // 초기 배경 색상 설정
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE); // 흰색 바탕에 검정색 텍스트
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // 검정색 바탕에 흰색 텍스트

    // 초기 상태 설정
    int left_text_white_bg = 1; // 왼쪽 텍스트에 흰색 배경이 설정된 상태
    int right_text_white_bg = 0;
    while (1) {
        int ch = getch(); // 사용자 입력 받기
        mvprintw(0, 0, "Left Text with Black Background");
        mvprintw(0, COLS / 2, "Right Text with Black Background");
        // 왼쪽 방향키가 눌렸을 때
        if (ch == KEY_LEFT) {
            left_text_white_bg = !left_text_white_bg;
            right_text_white_bg = !right_text_white_bg;
            // 왼쪽 텍스트에 흰색 배경이 설정된 경우
            attron(COLOR_PAIR(2)); // 텍스트 색상 변경
            mvprintw(0, COLS / 2, "Right Text with Black Background");
            attroff(COLOR_PAIR(2)); // 색상 변경 해제

            // 왼쪽 텍스트에 검정색 배경이 설정된 경우
            attron(COLOR_PAIR(1)); // 텍스트 색상 변경
            mvprintw(0, 0, "Left Text with White Background");
            attroff(COLOR_PAIR(1)); // 색상 변경 해제
        }

        // 오른쪽 방향키가 눌렸을 때
        if (ch == KEY_RIGHT) {
            right_text_white_bg = !right_text_white_bg;
            left_text_white_bg = !left_text_white_bg;
            // 왼쪽 텍스트에 흰색 배경이 설정된 경우
            attron(COLOR_PAIR(2)); // 텍스트 색상 변경
            mvprintw(0, 0, "Left Text with Black Background");
            attroff(COLOR_PAIR(2)); // 색상 변경 해제

            // 왼쪽 텍스트에 검정색 배경이 설정된 경우
            attron(COLOR_PAIR(1)); // 텍스트 색상 변경
            mvprintw(0, COLS / 2, "Right Text with Black Background");
            attroff(COLOR_PAIR(1)); // 색상 변경 해제
        }
        refresh(); // 변경 사항 화면에 반영

        if(ch == 10) break;
    }

    if(left_text_white_bg) 
        mvprintw(2,0,"You chose left");
    else 
        mvprintw(2,0,"You chose right");
    refresh();
    sleep(2);
    endwin(); // ncurses 종료
    return 0;
}
