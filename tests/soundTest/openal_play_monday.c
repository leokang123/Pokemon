#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncursesw/curses.h>
#include <wchar.h>
#include <locale.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define DEFAULT COLOR_PAIR(1)
#define SELECT COLOR_PAIR(2)

struct foo {
    char file[50];
    int x;
    float speed;
};

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

/* 아마 소리를 첨에 넣는다면 
    soundinit같은 함수로 데이터를 
    배열에다 다 저장해 놓고 할듯?
*/
void * textSound(void * arg) {
    ALuint buffer, source;
    ALint state;

    // OpenAL 초기화
    // 오디오 파일 로드
    FILE *file;
    int rand = randomInRange(1,3);
    // push1 은 속도 3.5f가 최고
    file = fopen("push1.wav","rb");
    // FILE* file = fopen("push3.wav", "rb");
    if (!file) {
        printf("Failed to open WAV file\n");
        pthread_exit(NULL);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(size);
    if (!data) {
        printf("Failed to allocate memory for WAV data\n");
        fclose(file);
        pthread_exit(NULL);
    }

    fread(data, 1, size, file);
    fclose(file);

    // 오디오 소스 생성 및 속성 설정
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, data, size, 44100);
    free(data);
    // double speed = randomInRange(1,7);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source,AL_PITCH,3.5f); // 속도 (높낮이))

    // 반복 시킬떄 
    alSourcei(source, AL_LOOPING, AL_TRUE);
    // 오디오 재생
    alSourcePlay(source);
    // 재생이 완료될 때까지 대기
    do {
        if(*(int *)arg == 15){ 
            // printf("text arg : %d\n",*(int *)arg);
            goto EXIT1;

        }
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    } while (state == AL_PLAYING);
EXIT1:

    // 해제
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    // // OpenAL 정리


    // 아마 exit을 다 해주고 쓰래드 결과값정보가 필요없어서 join이 필요없을듯.. 아마.. 
    pthread_detach(pthread_self()); // 현재 스레드를 분리하여 종료
    return NULL;
}
void * titleSound(void * arg) {
    ALuint buffer, source;
    ALint state;

    // OpenAL 초기화
    // 오디오 파일 로드
    FILE *file;
    int rand = randomInRange(1,3);
    // push1 은 속도 3.5f가 최고
    file = fopen("open.wav","rb");
    // FILE* file = fopen("push3.wav", "rb");
    if (!file) {
        printf("Failed to open WAV file\n");
        pthread_exit(NULL);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(size);
    if (!data) {
        printf("Failed to allocate memory for WAV data\n");
        fclose(file);
        pthread_exit(NULL);
    }

    fread(data, 1, size, file);
    fclose(file);

    // 오디오 소스 생성 및 속성 설정
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, data, size, 44100);
    free(data);
    // double speed = randomInRange(1,7);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source,AL_PITCH,3.5f); // 속도 (높낮이))

    // 반복 시킬떄 
    alSourcei(source, AL_LOOPING, AL_TRUE);
    // 오디오 재생
    alSourcePlay(source);
    // 재생이 완료될 때까지 대기
    do {
        if(*(int *)arg == 10){ 
            fprintf(stderr,"title arg : %d\n",*(int *)arg);
            goto EXIT;

        }
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    } while (state == AL_PLAYING);
EXIT:
    // 해제
    fprintf(stderr,"EXIT title arg : %d\n",*(int *)arg);
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    // OpenAL 정리


    // 아마 exit을 다 해주고 쓰래드 결과값정보가 필요없어서 join이 필요없을듯.. 아마.. 
    // pthread_detach(pthread_self()); // 현재 스레드를 분리하여 종료
    // return NULL;
    pthread_exit(NULL);
}
void * arrowSound(void * arg) {
    ALuint buffer, source;
    ALint state;

    // OpenAL 초기화
    // 오디오 파일 로드
    FILE *file;
    int rand = randomInRange(1,3);
    // push1 은 속도 3.5f가 최고
    file = fopen("push.wav","rb");
    // FILE* file = fopen("push3.wav", "rb");
    if (!file) {
        printf("Failed to open WAV file\n");
        pthread_exit(NULL);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(size);
    if (!data) {
        printf("Failed to allocate memory for WAV data\n");
        fclose(file);
        pthread_exit(NULL);
    }

    fread(data, 1, size, file);
    fclose(file);

    // 오디오 소스 생성 및 속성 설정
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, data, size, 44100);
    free(data);
    // double speed = randomInRange(1,7);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source,AL_PITCH,2.0f); // 속도 (높낮이))
    // 반복 시킬떄 
    // 오디오 재생
    alSourcePlay(source);
    // 재생이 완료될 때까지 대기
    do {
        if(*(int *)arg == 10){ 
            printf("arg : %d\n",*(int *)arg);
            goto EXIT;

        }
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    } while (state == AL_PLAYING);
EXIT:
    // 해제
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    // OpenAL 정리


    // 아마 exit을 다 해주고 쓰래드 결과값정보가 필요없어서 join이 필요없을듯.. 아마.. 
    pthread_detach(pthread_self()); // 현재 스레드를 분리하여 종료
    return NULL;
}

int arrowFunc1(int type, int line, int col, int col2, int args, ...){
    cbreak(); // 입력 버퍼를 사용하지 않도록 설정
    noecho(); // 입력한 문자가 화면에 표시되지 않도록 설정
    keypad(stdscr, TRUE); // 특수 키를 사용할 수 있도록 설정
    // 초기 배경 색상 설정
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // 검정색 바탕에 흰색 텍스트
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // 흰색 바탕에 검정색 텍스트

    pthread_t tid;
    pthread_attr_t attr;
    // 반드시 속성 구조체를 초기화 해줘야 한다 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

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
        wchar_t point[] = L">";
        while (ch != 10) {
            for(int i = 0 ; i < args ; i++) {
                mvprintw(line,gap[i],"%ls", arr[i]);
            }
            refresh();
            if(a > args-1) a = 0;
            if(a < 0) a = args-1;
            int p = 7;
            for(int i = 0 ; i < args ; i++) {
                if(a == i) {
                    // refresh();
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
            }
            ch = getch();
            pthread_create(&tid,&attr,(void *)arrowSound,NULL);
            if(ch == KEY_LEFT) a -= 1;
            if(ch == KEY_RIGHT) a += 1;
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
        int resizeCol = (col2-col);
        for(int i = 0 ; i < args ; i++){
            arr[i] = va_arg(ap,wchar_t *);
        }
        va_end(ap);
        wchar_t point[] = L">";
        while (ch != 10) {
            for(int i = 0 ; i < args ; i++) {
                gap[i] = line + i;
                mvprintw(gap[i],col,"%ls", arr[i]);
            }
            refresh();
            if(a > args-1) a = 0;
            if(a < 0) a = args-1;
            int p = 7;
            for(int i = 0 ; i < args ; i++) {
                if(a == i) {
                    // refresh();
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
            }
            ch = getch();
            pthread_create(&tid,NULL,(void *)arrowSound,NULL);
            if(ch == KEY_UP) a -= 1;
            if(ch == KEY_DOWN) a += 1;
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
        wchar_t point[] = L">";
        int p = (args + 1)/2;        // 위아래이동 시 더하는 값
        while (ch != 10) {
            for(int i = 0 ; i < args ; i++) {
                gap[i][0] = (i/p) * COLS/9.0/2 + line;
                gap[i][1] = (i%p) * COLS/9.0 + col;
                mvprintw(gap[i][0],gap[i][1],"%ls", arr[i]);
            }
            refresh();
            if(a > args-1) a = a - args ;
            if(a < 0) a = a + args ;
            for(int i = 0 ; i < args ; i++) {
                if(a == i) {
                    refresh();
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
            }
            ch = getch();
            pthread_t tid1[10];
            if(num > 9) num = 0;
            mvprintw(30,num,"%d",num);
            refresh();
            int arg = 0;   // arg == 노래 시작 , arg == 10 노래 종료 조건 
            if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN) pthread_create(tid1 + num++,&attr,(void *)arrowSound,&arg);
            if(ch == KEY_LEFT) a -= 1;
            if(ch == KEY_RIGHT) a += 1;
            if(ch == KEY_UP) a -= p;
            if(ch == KEY_DOWN) a += p;
            // 종료조건에 while탈출조건도 써줘야 끝났을때 쓰레드도 할당해제다하고 끝남 
            if(ch == KEY_BACKSPACE || ch == 10) arg = 10;
            
            // pthread_join(tid,NULL);

        }
        refresh();
        for(int i = 0 ; i < 2 ; i++){
            free(gap[i]);
        }
        free(gap);
        free(arr);
    }
    keypad(stdscr, FALSE); 
    nocbreak();
    echo();
    return a;
}
void screen(int a, int b, wchar_t * mess) {
  move(a,b);
  printw("%ls", mess);
  refresh();
}

void serialScreen(int a, int b, wchar_t * mess, int time) {
  int len = wcslen(mess);
  wchar_t buff[100];
  int arg = 0;
  pthread_t tid;
  pthread_attr_t attr;
  // 반드시 속성 구조체를 초기화 해줘야 한다 
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_create(&tid,&attr,textSound,&arg);
  for(int i = 0 ; i <= len ; i++) {
    wmemset(buff,0,i+2);
    wcsncpy(buff,mess,i);
    screen(a, b, buff);
    usleep(time);
  }
  arg = 15;
  refresh();
  
}

int main(){
    setlocale(LC_ALL, ""); // 현재 로케일을 설정하여 멀티바이트 문자열을 wchar_t로 변환할 수 있도록 함
    initscr();  
    refresh();
    ALCdevice* device = alcOpenDevice(NULL);
    ALCcontext* context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    arrowFunc1(2,3,0,100,4,L"FIRST",L"SECOND",L"THIRD",L"FORTH");
    sleep(1);
    pthread_t tid;
    pthread_attr_t attr;
    // 반드시 속성 구조체를 초기화 해줘야 한다 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    struct foo * arg = (struct foo*)malloc(sizeof(struct foo));
    arg->x = 0;
    arg->speed = 2.0f;
    strcpy(arg->file,"title.wav");
    pthread_create(&tid,NULL,(void *)titleSound,&(arg->x));
    clear();
    serialScreen(10,10,L"인녕하세요 소리 테스트입니다",100000);
    usleep(10000);
    serialScreen(11,10,L"인녕하세요 소리 테스트입니다",100000);
    usleep(10000);

    serialScreen(12,10,L"인녕하세요 소리 테스트입니다",100000);
    usleep(10000);

    serialScreen(13,10,L"인녕하세요 소리 테스트입니다",100000);
    sleep(1);


    arg->x = 10;
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
    endwin();
    return 0;
}