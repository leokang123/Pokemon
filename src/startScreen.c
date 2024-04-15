#include "everyheader.h"
extern int line;

// 형 명시하고 사용해야 함 

int main (void) {
    srand(time(NULL));

    // OpenAl 초기화는 처음에 해주고 마지막에 닫는거임 
    ALCdevice* device = alcOpenDevice(NULL);
    ALCcontext* context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    setlocale(LC_ALL, ""); // 현재 로케일을 설정하여 멀티바이트 문자열을 wchar_t로 변환할 수 있도록 함
    initscr(); // ncurses 초기화
    curs_set(0); // 커서 안보이게함 
    echo();
    start_color(); // 색상 사용을 위한 초기화
    // init_pair(1, COLOR_WHITE, COLOR_BLACK); // 색상 쌍 정의 (배경을 검게 설정)
    // bkgdset(COLOR_PAIR(1)); // 배경 색상을 색상 쌍 1로 설정    
    clear();
    refresh();

    // 배경 색상 설정
    attron(A_ITALIC); // 왠진 모르지만 이거 해야 유니코드 대로 출력이 됌  아마 이후론 유니코드로 다 출력하는듯 
    // raw();
    // cbreak();
    // keypad(stdscr, TRUE); // 특수 키를 처리하기 위해 키패드 활성화 (강종키 안댐 아마 다른키가있을듯)

    // 반드시 속성 구조체를 초기화 해줘야 한다 
    // pthread_t tid;
    // pthread_attr_t attr;
    // pthread_attr_init(&attr);
    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    struct foo * arg = (struct foo*)malloc(sizeof(struct foo));       // 배경음을 메인에서 조정하기 위함 
    struct foo * arg2 = (struct foo*)malloc(sizeof(struct foo));    // 부가음을 메인에서 조정하기 위함(원래는 개별함수에서 각각하려했는데 그럼 할당해제가 너무 애매해짐)
    line = LINES/2 - 10;
    refresh();
    PokeList * list = makeLink();
    Userdata * user;
    
    // 시작 페이지 
    int sel = startPage(arg);    // debug1

    // 사용자정보 로드 페이지 
    // int sel = 1;            // debug2
    user = (sel)? loadUserPage(arg) : makeUserPage(list, arg);
    if(user == NULL) {
        clear();
        printw("Error Making User");
        return 1;
    }
    clear();
    line = 2;
    mainStoryLine(user, list, arg, arg2);  
    arg->x = 10;
    arg2->x = 10;
    attroff(A_ITALIC);
    free(arg);
    free(arg2);
    freePokeList(list,user);

    endwin();
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
    return 0;
}