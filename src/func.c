// #include "../../src/everyheader.h"
#include "../src/everyheader.h"


/* first ~ last 사이 랜덤값 반환 */
int randomInRange(int min, int max) {
    // mvprintw(0,0,"%d",rand());
    return min + rand() % (max - min + 1);
}

void * inputlenRange(void) {
    static wchar_t namebuf[200]; // 전역변수나 다를거 없음 
    wmemset(namebuf,0,200);
    int namelen = 0;
    int fline = line;
    while(1) {
        line = fline;
        mvprintw(line++,ST,"입력: ");
        refresh();
        curs_set(1);
        wget_wstr(stdscr,namebuf);
        curs_set(0);
        // refresh();
        namelen = wcslen(namebuf);
        if(namelen >= 2 && namelen < NAME_SIZE) break;
        serialScreen(line++,ST,L"잘못된 입력양식입니다",NORMAL);
        serialScreen(line++,ST,L"다시해주세요",NORMAL);
        visualgetch();
        for(int i = 2 ; i >= 0; i--) {
            mvprintw(fline+i,ST,"%*s",20,"");
            napms(90);
            refresh();
        }
    }

    return namebuf;
}

void blinkString(wchar_t *str, int bline) {
    int len = wcslen(str) * 2;
    line = bline;
    mvprintw(line, ST, "%*s", len, "");
    refresh();
    napms(100);
    mvprintw(line,ST,"%ls",str);
    refresh();
    napms(100);
    mvprintw(line, ST, "%*s", len, "");
    refresh();
    napms(100);
    mvprintw(line,ST,"%ls",str);
    refresh();
}

/* 
    line 의 row에서 col ~ col2까지 args 갯수만큼 균일하게 선택창을 만드는 함수 
    가르키는 곳을 > 로 한번 더 알려줌 
    type 0 : 수평하게 , type 1: 수직하게, type 2 : 2xn 하게 
*/

int arrowFunc(int type, int line1, int col, int col2, int args, ...){
    noecho(); // 입력한 문자가 화면에 표시되지 않도록 설정
    keypad(stdscr, TRUE); // 특수 키를 사용할 수 있도록 설정
    // 초기 배경 색상 설정
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // 검정색 바탕에 흰색 텍스트
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // 흰색 바탕에 검정색 텍스트


    pthread_t tid; 
    struct foo * arg = (struct foo*)malloc(sizeof(struct foo));
    arg->x = 0;
    arg->speed = 5.0f;
    strcpy(arg->file,ARROWSOUND);

    int a = 0;
    int ch = 0;

    wchar_t ** arr = (wchar_t **)malloc(sizeof(wchar_t*)*(args));  // 공간을 빡빡하게 잡았더니 께속 에러났음 (왠진 모름 .. )
    for(int i = 0 ; i < args  ; i++) {
        arr[i] = (wchar_t *)malloc(sizeof(wchar_t) * 100);
        wmemset(arr[i],0,100);
    }
    // 왠진 모르겠는데 동적할당하면 할당해제할때 에러남 
    // int * gap = (int *)malloc(sizeof(int) * (args+1));
    // memset(gap,0,sizeof(int) * (args+1));
    int gap[50] = {0,};
    va_list ap;
    va_start(ap, args);

    for(int i = 0 ; i < args ; i++) wcscpy(arr[i],va_arg(ap,wchar_t *));

    va_end(ap);

    if(type == 0){

        int resizeCol = (col2-col);
        for(int i = 0 ; i < args ; i++){
            gap[i] = resizeCol/(args) * i  + resizeCol/args * (1.0/2) + col;
        }
        refresh();

        while (ch != 10) {
            for(int i = 0 ; i < args ; i++) {
                mvprintw(line1,gap[i],"%ls", arr[i]);
            }
            refresh();
            for(int i = 0 ; i < args ; i++) {
                if(a != i) continue;
                attron(DEFAULT);
                mvprintw(line1,gap[(i-1 + args) % args]-1 ," %ls", arr[(i-1 + args) % args]);
                mvprintw(line1,gap[(i+1 + args) % args]-1 ," %ls", arr[(i+1 + args) % args]);
                attroff(DEFAULT);

                attron(SELECT);
                mvprintw(line1,gap[i]-1,">%ls", arr[i]);
                attroff(SELECT);
                refresh();
            }
            flushinp();
            ch = getch();
            if(ch == KEY_LEFT) a = (a - 1 + args) % args;
            else if(ch == KEY_RIGHT) a = (a + 1) % args;
            else if(ch == 10) {}
            else continue;
            arg->x = 0;
            pthread_create(&tid,NULL,singleSound,arg);            
        }
    }
    if(type == 1) {

        while (ch != 10) {
            for(int i = 0 ; i < args ; i++) {
                gap[i] = line1 + i;
                mvprintw(gap[i],col,"%ls", arr[i]);
            }
            refresh();
            for(int i = 0 ; i < args ; i++) {
                if(a != i) continue;
                attron(DEFAULT);
                mvprintw(gap[(i - 1 + args) % args],col-1," %ls", arr[(i-1 + args) % args]);
                mvprintw(gap[(i + 1 + args) % args],col-1 ," %ls", arr[(i+1 + args) % args]);
                attroff(DEFAULT);

                attron(SELECT);
                mvprintw(gap[i],col-1,">%ls", arr[i]);
                attroff(SELECT);
                refresh();
            }
            flushinp();
            ch = getch();
            arg->x = 0;
            if(ch == KEY_UP) a = (a - 1 + args) % args;
            else if(ch == KEY_DOWN) a = (a + 1) % args;
            else if(ch == 10) {}
            else continue;
            pthread_create(&tid,NULL,singleSound,arg);
        }
    }
    // mvprintw(line1++,ST,"HERE");
    // refresh();
    for(int i = 0 ; i < args ; i++) free((wchar_t*)arr[i]);
    free((wchar_t*)arr);
    // mvprintw(line1++,ST,"HERE");
    // refresh();
    // free((int*)gap);

    while(arg->x != 10) {}

    free((struct foo*)arg);
    // mvprintw(line1++,ST,"HERE");
    // refresh();
    keypad(stdscr, FALSE); 
    echo();
    return a;
}

void visualgetch(){
    flushinp();
    curs_set(1);
    move(line,ST);
    getch();
    curs_set(0);
}
    // else if (type == 2) {
    //     int resizeCol = (col2-col);

    //     int p = (args + 1)/2;        // 위아래이동 시 더하는 값
    //     int x = p + 1;               // 양옆 열간 간격 맞춰주기 위해 씀 
    //     while (ch != 10) {
    //         for(int i = 0 ; i < args ; i++) {
    //             gap2[i][0] = (i/p) * resizeCol/9.0/2 + line1;
    //             gap2[i][1] = ((i%p)+1) * resizeCol/x + col;
    //             mvprintw(gap2[i][0],gap2[i][1],"%ls", arr[i]);
    //         }
    //         refresh();
    //         if(a > args-1) a = a - args ;
    //         if(a < 0) a = a + args ;
    //         for(int i = 0 ; i < args ; i++) {
    //             if(a != i) continue;
    //             while(arg->x != 1) {}
    //             arg->x = 0;
    //             attron(DEFAULT);
    //             mvprintw(gap2[(i-p+args)%args][0],gap2[(i-p+args)%args][1] - 1, " ");
    //             mvprintw(gap2[(i-p+args)%args][0],gap2[(i-p+args)%args][1],"%ls", arr[(i-p+args)%args]);
    //             attroff(DEFAULT);

    //             attron(DEFAULT);
    //             mvprintw(gap2[(i+p+args)%args][0],gap2[(i-p+args)%args][1] - 1, " ");
    //             mvprintw(gap2[(i+p+args)%args][0],gap2[(i-p+args)%args][1],"%ls", arr[(i+p+args)%args]);
    //             attroff(DEFAULT);

    //             attron(DEFAULT);
    //             mvprintw(gap2[(i-1+args)%args][0],gap2[(i-1+args)%args][1] - 1, " ");
    //             mvprintw(gap2[(i-1+args)%args][0],gap2[(i-1+args)%args][1],"%ls", arr[(i-1+args)%args]);
    //             attroff(DEFAULT);

    //             attron(DEFAULT);
    //             mvprintw(gap2[(i+1+args)%args][0],gap2[(i+1+args)%args][1] - 1, " ");
    //             mvprintw(gap2[(i+1+args)%args][0],gap2[(i+1+args)%args][1],"%ls", arr[(i+1+args)%args]);
    //             attroff(DEFAULT);

    //             attron(SELECT);
    //             mvprintw(gap2[i][0],gap2[i][1]-1,">");
    //             mvprintw(gap2[i][0],gap2[i][1],"%ls", arr[i]);
    //             attroff(SELECT);
    //             refresh();
                    
    //         }
    //         flushinp();
    //         ch = getch();
    //         if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN) pthread_create(&tid,NULL,singleSound,arg);
    //         if(ch == KEY_LEFT) a -= 1;
    //         else if(ch == KEY_RIGHT) a += 1;
    //         else if(ch == KEY_UP) a -= p;
    //         else if(ch == KEY_DOWN) a += p;
    //         else if(ch == 10){
    //             pthread_create(&tid,NULL,singleSound,arg);
    //             while(arg->x != 1) {}
    //         }
    //         else arg->x = 1;
    //     }

    // }