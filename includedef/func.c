#include "../../src/everyheader.h"


/* first ~ last 사이 랜덤값 반환 */
int randomInRange(int min, int max) {
    // mvprintw(0,0,"%d",rand());
    return min + rand() % (max - min + 1);
}

/* 
    line 의 row에서 col ~ col2까지 args 갯수만큼 균일하게 선택창을 만드는 함수 
    가르키는 곳을 > 로 한번 더 알려줌 
    type 0 : 수평하게 , type 1: 수직하게, type 2 : 2xn 하게 
*/

int arrowFunc(int type, int line, int col, int col2, int args, ...){
    cbreak(); // 입력 버퍼를 사용하지 않도록 설정
    noecho(); // 입력한 문자가 화면에 표시되지 않도록 설정
    keypad(stdscr, TRUE); // 특수 키를 사용할 수 있도록 설정
    // 초기 배경 색상 설정
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // 검정색 바탕에 흰색 텍스트
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // 흰색 바탕에 검정색 텍스트

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // pthread 가 리소스를 끝나면 해제를 기다리지않고 바로 해제한다 
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    struct foo * arg = (struct foo*)malloc(sizeof(struct foo));
    arg->x = 1;
    arg->speed = 5.0f;
    strcpy(arg->file,ARROWSOUND);
    int num = 0;
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
        while (ch != 10) {
            for(int i = 0 ; i < args ; i++) {
                mvprintw(line,gap[i],"%ls", arr[i]);
            }
            refresh();
            if(a > args-1) a = 0;
            if(a < 0) a = args-1;
            for(int i = 0 ; i < args ; i++) {
                if(a != i) continue;
                while(arg->x != 1) {}
                arg->x = 0;
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
            flushinp();
            ch = getch();
            pthread_t tid; 

            if(ch == KEY_LEFT) {
                pthread_create(&tid,&attr,(void *)singleSound,arg);
                a -= 1;
            }
            else if(ch == KEY_RIGHT) {
                pthread_create(&tid,&attr,(void *)singleSound,arg);
                a += 1;
            }
            else arg->x = 1;
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
        for(int i = 0 ; i < args ; i++){
            arr[i] = va_arg(ap,wchar_t *);
        }
        va_end(ap);
        while (ch != 10) {
            for(int i = 0 ; i < args ; i++) {
                gap[i] = line + i;
                mvprintw(gap[i],col,"%ls", arr[i]);
            }
            refresh();
            if(a > args-1) a = 0;
            if(a < 0) a = args-1;
            for(int i = 0 ; i < args ; i++) {
                if(a != i) continue;
                while(arg->x != 1) {}
                arg->x = 0;
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
            flushinp();
            ch = getch();
            pthread_t tid; 
            
            if(ch == KEY_UP) {
                pthread_create(&tid,&attr,(void *)singleSound,arg);
                a -= 1;
            }
            else if(ch == KEY_DOWN) {
                pthread_create(&tid,&attr,(void *)singleSound,arg);
                a += 1;
            }
            else arg->x = 1;
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
        int resizeCol = (col2-col);
        for(int i = 0 ; i < args ; i++){
            arr[i] = va_arg(ap,wchar_t *);
        }
        va_end(ap);
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
                if(a != i) continue;
                while(arg->x != 1) {}
                arg->x = 0;
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
            flushinp();
            ch = getch();
            pthread_t tid1[10];
            if(num > 9) num = 0;
            refresh();
            if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN) pthread_create(tid1 + num++,&attr,(void *)loopSound,arg);
            if(ch == KEY_LEFT) a -= 1;
            if(ch == KEY_RIGHT) a += 1;
            if(ch == KEY_UP) a -= p;
            if(ch == KEY_DOWN) a += p;
            // 종료조건에 while탈출조건도 써줘야 끝났을때 쓰레드도 할당해제다하고 끝남 
            if(ch == KEY_BACKSPACE || ch == 10) arg->x = 10;
            
            // pthread_join(tid,NULL);

        }
        refresh();
        for(int i = 0 ; i < 2 ; i++){
            free(gap[i]);
        }
        free(gap);
        free(arr);
    }
    free(arg);
    pthread_attr_destroy(&attr);
    keypad(stdscr, FALSE); 
    nocbreak();
    echo();
    return a;
}

