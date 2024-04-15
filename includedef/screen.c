#include "../../src/everyheader.h"

/*
  걍 모든 print함수에서 개행문자 들어가면 그 줄은 flush되서 빈공간으로 남는다고 생각하자 
  난 어처피 line++ 로 개행을 하니까 굳이 개행문자 안써줘도됌 
  오히려 써주면 그 줄이 다 비워져서 안예쁘게 나옴 

  ncurses에서 제공하는 전역변수로 LINES, COLS가 있다 터미널의 행 열을 알려줌 
*/
void endRoutine(int lines) {
    for(int i = 3 ; i > 0; i--) {
        mvprintw(lines,ST,"close by %d", i);
        refresh();
        sleep(1);
    }
    mvprintw(lines,ST,"          "); // close by %d만큼만 비워줌 
    mvprintw(lines,ST,"(END)");
    refresh();
    sleep(1);
}

void lineControl() {
    if(line > 30) {
        line = 10;
        clear();
        move(line,0);
    }
    return;
    
}

void screen(int a, int b, wchar_t * mess) {
  move(a,b);
  printw("%ls", mess);
  refresh();
}

void serialScreen(int a, int b, wchar_t * mess, int time) {
  int len = wcslen(mess);
  wchar_t buff[100];
  pthread_t tid;
  pthread_attr_t attr;
  // 반드시 속성 구조체를 초기화 해줘야 한다 
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  struct foo * arg = (struct foo*)malloc(sizeof(struct foo));
  arg->x = 0;
  arg->speed = 5.0f;
  strcpy(arg->file,TEXTSOUND);
  pthread_create(&tid,NULL,(void *)loopSound,arg);
  pthread_attr_destroy(&attr);
  
  while(arg->x != 1) {} // 준비될때까지 대기 
  for(int i = 0 ; i <= len ; i++) {
    wmemset(buff,0,i+2);
    wcsncpy(buff,mess,i);
    mvprintw(a,b,"%ls",buff);
    refresh();
    // screen(a, b, buff);
    if(i == len ) arg->x = 10; // 종료 신호 
    usleep(time);
  }
  free(arg);
  refresh();
  
}
int pokeImage1(int imline, int imcol, int num) {
  // FILE * file = fopen("../../assets/pokeImage.txt","r");    // test 디렉토리용 
  FILE * file = fopen("../assets/pokeImage.txt","r");
  int find = 0;
  int maxline = line;   // 이미지사이즈가 콘솔창을 넘어가면 break;
  wchar_t buff[100], buff2[1000];
  swprintf(buff,100, L"idenNum%d", num);

  while(fgetws(buff2,1000,file) != NULL){
    if(find) break;
    if(wcsstr(buff2,buff)){
      find = 1;
      while(fgetws(buff2,1000,file) != NULL){
        // line++;
        if(wcsstr(buff2,L"END") != NULL) break;
        if(maxline >= LINES) break;
        maxline++;
        // buff2[50] = L'\0';
        mvprintw(imline++,imcol,"%ls",buff2);
        refresh();
        napms(30);
      }
    }
  }
  fclose(file);
  return maxline;
}

// type : 오른쪽 정렬일때 0 왼쪽 정렬일때 1 
int pokeImage2(int imline, int imcol, int num, int type) {
  // FILE * file = fopen("../../assets/pokeImage.txt","r");    // test 디렉토리용 
  FILE * file = fopen("../assets/pokeImage.txt","r");
  int find = 0;
  int len = 0;
  int maxline = line;   // 이미지사이즈가 콘솔창을 넘어가면 break;
  wchar_t buff[100], buff2[1000];
  swprintf(buff,100, L"idenNum%d", num);

  while(fgetws(buff2,1000,file) != NULL){
    if(find) break;
    if(wcsstr(buff2,buff)){
      find = 1;
      while(fgetws(buff2,1000,file) != NULL){
        // line++;
        if(len == 0){
          len = wcslen(buff2);  // 처음 가로 길이 가져오기 
        }
        if(wcsstr(buff2,L"END") != NULL) break;
        if(maxline >= LINES) break;
        maxline++;
        // buff2[50] = L'\0';
        if(!type) mvprintw(imline++,imcol,"%ls",buff2);
        if(type) mvprintw(imline++,imcol + len,"%ls",buff2);
        refresh();
        napms(30);
      }
    }
  }
  fclose(file);
  return len;
}



// int pokeImageBattle(int imline, int imcol, int num) {
//   // FILE * file = fopen("../../assets/pokeImage.txt","r");    // test 디렉토리용 
//   FILE * file = fopen("../assets/pokeImage.txt","r");
//   int find = 0;
//   int maxline = line;   // 이미지사이즈가 콘솔창을 넘어가면 break;
//   wchar_t buff[100], buff2[1000];
//   swprintf(buff,100, L"idenNum%d", num);

//   while(fgetws(buff2,1000,file) != NULL){
//     if(find) break;
//     if(wcsstr(buff2,buff)){
//       find = 1;
//       while(fgetws(buff2,1000,file) != NULL){
//         // line++;
//         if(wcsstr(buff2,L"END") != NULL) break;
//         if(maxline >= LINES) break;
//         maxline++;
//         buff2[20] = L'\0';
//         mvprintw(imline++,imcol,"%ls",buff2);
//         refresh();
//         napms(30);
//       }
//     }
//   }
//   fclose(file);
//   return maxline;
// }

void randomScreen() {
    // ncurses 초기화
    // 화면 갱신을 위한 설정
    clear();
    refresh();
    // 난수 초기화
    srand(time(NULL));

    // 원하는 시간(초)을 설정
    int duration = 4; // 4초 동안 루프를 실행하려는 경우
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
        r -= 1;
        napms(100); // millisecond 단위 대기 함수
    }
    // 화면 종료 전 사용자 입력을 기다림
    // ncurses 종료
    napms(50);
    clear();
    refresh();
}
/* type 0 위에서 아래로 , 1 : 아래에서 위로 2 : 커틀 콜  */
void dynamicClear(int type, int start, int num) {
  if(type == 0) {
      int end = (start + num > LINES)? LINES : start + num;
      for(int i = start ; i < end; i++) {
        mvprintw(i, ST-2, "%*s", COLS, "");
        refresh();
        napms(30);
      }
      line = start;
  }
  if(type == 1) {
      int end = (start + num > LINES)? LINES : start + num;
      for(int i = end - 1 ; i >= start ; i--) {
        mvprintw(i, ST-2, "%*s", COLS, "");
        refresh();
        napms(30);
      }
      line = start;
  }
  if(type == 2) {
      for(int i = ST ; i <= COLS/2; i++) {
        for(int j = 0 ; j < LINES ; j++) {
          mvprintw(j, i, " ");
          mvprintw(j, COLS - i, " ");
        }
        refresh();
        napms(30);
      }
      line = 5;
  }
  if(type == 3) {
      char buffer3[500];
      
      int b = (num > start - 1) ? start - 1: num;
      mvprintw(start, ST, "%*s", COLS, "");
      while(b--){
          for(int i = 1 ; i <= start ; i++){
              mvinnstr(i, ST, buffer3, sizeof(buffer3)); // 5번째 라인의 내용을 buffer3에 복사
              mvprintw(i-1,ST,"%s", buffer3);
          }
          mvprintw(4, ST, "%*s", COLS, "");
          refresh();
          napms(30);
      }
      if(num > start - 1) line = 5;
      else line = start - num;
  }
  // clear(); // 먼가 꺼림직해서 깔끔하게 마지막에 clear();
}
void staticClear(int line1, int line2, int col1, int col2) {
  line = line1;
  int num1 = line2 - line1 + 1;
  int num2 = col2 - col1 + 1;
  for(int i = 0 ; i < num1 ;i++){
    mvprintw(line1+i,col1,"%*s",num2,"");
  }
  refresh();
}

void borderLine(int line, int st, int ed) {
    move(line,st);
    for (int i = st; i < ed; ++i) {
        addch('=');
    }
    refresh();
}