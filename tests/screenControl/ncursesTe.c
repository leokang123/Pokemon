#include <ncursesw/curses.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>

void screen(wchar_t *arr, int a, int b) {
    int len = wcslen(arr);
    for(int i = 0 ; i < len; i++) {
        mvprintw(a,i,"%lc",arr[i]);
        refresh();
        usleep(100000);
    }
}

int main(void) {
    setlocale(LC_ALL, ""); // 현재 로케일을 설정하여 멀티바이트 문자열을 wchar_t로 변환할 수 있도록 함
    initscr();  
    wchar_t arr[100] = L"안녕하세요 저는 강정훈입니다";
    screen(arr,5,0);
    sleep(10);
    endwin();
    return 0;
}