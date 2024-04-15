#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
// #include <ncursesw/curses.h>

#define MTOS 1000000
#define SCNLEN 20  // 줄수 
/*
    ./test $(echo $LINES) $(echo $COLUMNS) 
    이렇게 실행하면 실행한 기준 터미널의 행수와 열수가 나온다 
*/


/*
    한줄을 다이나믹하게 화면띄우는거 까지함
    이제 읽고 정해놓은 줄만큼 읽으면 포인터를 이동시켜서 다음걸로 전환가능 
    그럼 이제 할건 정해놓은 줄만큼 읽으면 포인터의 자리에 개행문자를 넣어서 
    밑으로 이동하게 만들고 위아래 규격만든 길이를  -1 해주고 
    개행문자 넣고 screen함수 들어가기 전에 매개인자 하나 추가해서 
    어느 줄부터 출력할지 넣는 인자 넣고 그 인자에 +1 한다음에 
    그 인자마저 정해놓은 행수를 넘어가면 
    말끔히 치우고 다시 읽는 거 구현할거임
*/

/*
    a : 전체 행수 
    b : 전체 열수 
    start : 글 시작하는 열수 
    end : 글 끝나는 열수 
*/

void screen(wchar_t ** arr, wchar_t *arr2, wchar_t * mess, int a, int b, int start ,int end) {
    wprintf(L"%ls\n", arr2);
    for(int i = 0 ; i < a ; i++) {
        if(i >= start && i <= end){
            if(i == start)wprintf(L"%ls\n", mess);
            continue;
        }
        wprintf(L"%ls\n", arr[i]);
    }
    wprintf(L"%ls\n", arr2);
    usleep(MTOS/20); // 0.05초
}

void serialScreen(wchar_t ** arr, wchar_t *arr2, wchar_t * mess, int a, int b) {
    int start = a/3;
    int end = start;
    int len = wcslen(mess);
    wchar_t dest[1000];
    wchar_t dest2[1000];
    wcscpy(dest2,mess);
    size_t dest_size = sizeof(dest) / sizeof(wchar_t); // dest 배열의 요소 개수를 계산합니다.
    // sizeof(dest)으로 wmemset 초기화 하면 segfault하면 오류남 
    for(int i = 1, s = 1 ; i <= len ; i++, s++) {
        if (s >= SCNLEN) {
            s = 0;
            end += 1;
            wmemset(dest,0,i+1);        // dest배열 초기화 
            wcsncpy(dest,dest2,i);      // dest  dest2(원본 mess)의 요소 i개 복사 
            // wprintf(L"%ls\n", dest);
            wcscat(dest,L"\n");         // dest i+1에 개행 추가 
            wcscat(dest,dest2+i+1);     // dest에 dest2의 i+1번 째요소부터 이어붙임 
            wmemset(dest2,0,dest_size); 
            wcscpy(dest2,dest);
            wmemset(dest,0,dest_size); 
            }
        // 여기서 i+1에 위치하는자리는 메모리크기가 아니고 할당 갯수를 의미
        wmemset(dest,0,i+1); 
        wcsncpy(dest,dest2,i);

        screen(arr,arr2,dest,a,b,start,end);
    }
}

int main(int argc, char ** argv) {

    setlocale(LC_ALL, ""); // 현재 로케일을 설정하여 멀티바이트 문자열을 wchar_t로 변환할 수 있도록 함
    int a = atoi(argv[1]) - 3; // 윤곽선을 풀 화면을 잡으려면 이렇게 (입력칸 하나 빼기)
    int b = atoi(argv[2]);

    wprintf(L"lines : %d, cols: %d\n", a, b);

    wchar_t ** arr = (wchar_t **)malloc(sizeof(wchar_t*)*a);
    for(int i = 0 ; i < a ;i++)  {
        arr[i] = (wchar_t *)malloc(sizeof(wchar_t)* b);
        wmemset(arr[i],L' ',b);
    }

    wchar_t * arr2 = (wchar_t *)malloc(sizeof(wchar_t) *b);
    wmemset(arr2,L'-',b);

// test screen
    char *temp = (char *)malloc(sizeof(char) * 500);
    fgets(temp,sizeof(char) * 500,stdin);
    wchar_t * mess = (wchar_t *)malloc(sizeof(wchar_t) * 1000);
    mbstowcs(mess, temp, 500);
    serialScreen(arr,arr2,mess,a,b);
    
// free allocation
    for(int i = 0 ; i < a ;i++) {
        free(arr[i]);
    }
    free(arr);
    free(arr2);
    free(mess);
    free(temp);
    return 0;
}

/*  한줄 테스트 글귀 
1. 큰 목표를 이루고 싶으면 허락을 구하지 마라. – 미상2. 상황을 가장 잘 활용하는 사람이 가장 좋은 상황을 맞는다. – 존 우든3. 창조적인 삶을 살려면 내가 틀릴지도 모른다는 공포를 버려야 한다. – 미상4. 일반적인 것을 잃을 위험을 감수하지 않으면 평범한 것에 만족해야 한다. – 짐 론5. 신뢰의 이유는 안전하거나 확실해서가 아니라, 위험을 감수할 용의가 있어서이다. – 미상6. 한 가지 생각을 
*/

