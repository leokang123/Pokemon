#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

// 랜덤한 범위 내의 정수를 반환하는 함수
int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

void randomScreen() {
    // ncurses 초기화
    initscr();
    // 화면 갱신을 위한 설정
    refresh();
    // 난수 초기화
    srand(time(NULL));

    // 원하는 시간(초)을 설정
    int duration = 5; // 5초 동안 루프를 실행하려는 경우
    // 시작 시간 저장
    time_t start_time = time(NULL);
    double r = LINES;
    while ((time(NULL) - start_time) < duration) {
        // 무작위 좌표 계산
        int row = randomInRange(0, LINES - 1); // 화면 행의 끝을 벗어나지 않도록 함
        int col = randomInRange(0, COLS - 8); // "Warning" 문자열의 길이는 7이므로, 화면 열의 끝을 벗어나지 않도록 함

        // "Warning" 문자열을 화면에 출력
        
        // 출력한 내용을 화면에 갱신
        refresh();
        
        // 1초 대기
        if((row-LINES/2)*(row-LINES/2) + (col-COLS/2)/2 * (col-COLS/2)/2 >= r/1.5*r/1.5) continue;  
        if((row-LINES/2)*(row-LINES/2) + (col-COLS/2)/2 * (col-COLS/2)/2 <= r/2*r/2) continue; 
        mvprintw(row, col, "WARNING");
        r -= 0.8;
        napms(70); // millisecond 단위 대기 함수
    }

    // 화면 종료 전 사용자 입력을 기다림
    getch();
    // ncurses 종료
    endwin();
}

int main() {
    randomScreen();
    return 0;
}
