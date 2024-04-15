#include <locale.h>
#include <unistd.h>
#include <wchar.h>
#include <ncursesw/curses.h>

void screen(wchar_t * mess, int a, int b) {
  move(a,b);
  printw("%ls", mess);
  refresh();
}

void serialScreen(wchar_t * mess, int a, int b, int time) {
  int len = wcslen(mess);
  wchar_t buff[2000];
  for(int i = 0 ; i <= len ; i++) {
    wmemset(buff,0,i+2);
    wcsncpy(buff,mess,i);
    screen(buff,a, b);
    usleep(time);
  }
  refresh();
}

void pokeImage(int imline, int imcol, int num) {
  FILE * file = fopen("test.txt","r");
  int a = imline;
  int b = imcol;
  int find = 0;
  wchar_t buff[100], buff2[1000];
  swprintf(buff,100, L"idenNum%d", num);
  while(fgetws(buff2,1000,file) != NULL){
    if(find) break;
    if(wcsstr(buff2,buff)){
      find = 1;
      while(fgetws(buff2,1000,file) != NULL){
        if(wcsstr(buff2,L"END") != NULL) break;
        screen(buff2,a++,b);
        refresh();
        usleep(20000);
      }
    }
  }
  fclose(file);
}

void storyPack() {
    
}
int main() {
  setlocale(LC_CTYPE, ""); /* 로케일 설정을 했는데도 */
  initscr();  
  // 색상 페어 초기화
  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLACK); // 색상 페어 1에 빨간색 텍스트 설정 (빨간글씨에 검정 배경을 pair 색으로 가지겠다는 뜻 )
  attron(A_BOLD); // 굵은 텍스트 속성 활성화
  attron(A_ITALIC); // 이탈릭 활성화
  attron(COLOR_PAIR(1));// 색상 페어를 설정하여 텍스트 색상 변경
  getch();
  attroff(A_BOLD); // 굵은 텍스트 속성 활성화
  attroff(A_ITALIC); // 이탈릭 활성화
  attroff(COLOR_PAIR(1));// 색상 페어를 설정하여 텍스트 색상 변경
  endwin();
  return 0;
}
