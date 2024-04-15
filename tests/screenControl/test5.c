#include <locale.h>
// #include <curses.h>
#include <unistd.h>
#include <wchar.h>
#include <ncursesw/curses.h>

void screen(wchar_t * str, int a, int b) {
  // static int a = 5;
  move(a,0);
  a += 5;
  
  printw("%s", "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
  printw("%ls", str);
  refresh();

}

int main() {
  setlocale(LC_CTYPE, ""); /* 로케일 설정을 했는데도 */
  initscr();
  wchar_t arr[100] =  L"가나다라마바사아자차카타파하\n";
  screen(arr, 5, 0);
  printw("123\n");

  sleep(3);
  endwin();
  return 0;
}