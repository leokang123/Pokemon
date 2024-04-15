#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

#define MTOS 1000000
#define SCNLEN 20
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
void screen(wchar_t ** arr, wchar_t *arr2, wchar_t * mess, int a, int b) {

    wprintf(L"%ls\n", arr2);
    for(int i = 0 ; i < a ; i++) {
        if(i == a/2){
            wprintf(L"%ls\n", mess);
            continue;
        }
        wprintf(L"%ls\n", arr[i]);
    }
    wprintf(L"%ls\n", arr2);
    usleep(MTOS/20); // 0.05초
}

void serialScreen(wchar_t ** arr, wchar_t *arr2, wchar_t * mess, int a, int b) {
    int len = wcslen(mess);
    // if(len >= b) {
    //     mess = mess + b;
    // }
    wchar_t dest[1000];
    size_t dest_size = sizeof(dest) / sizeof(wchar_t); // dest 배열의 요소 개수를 계산합니다.
    for(int i = 1 ; i <= len ; i++) {
        if (i >= SCNLEN) {
            i = 1;
            len -=  SCNLEN - 1; 
            mess += SCNLEN - 1;
            }
        // 여기서 i+1에 위치하는자리는 메모리크기가 아니고 할당 갯수를 의미
        wmemset(dest,0,i+1); 
        wcsncpy(dest,mess,i);
        dest[i+1] = L'\0';
        screen(arr,arr2,dest,a,b);
    }
}

int main(int argc, char ** argv) {

    setlocale(LC_ALL, ""); // 현재 로케일을 설정하여 멀티바이트 문자열을 wchar_t로 변환할 수 있도록 함
    int a = atoi(argv[1]) - 3; // 윤곽선을 풀 화면을 잡으려면 이렇게 (입력칸 하나 빼기)
    int b = atoi(argv[2]);
    int num = 3;
    wprintf(L"lines : %d, cols: %d\n", a, b);

    wchar_t ** arr = (wchar_t **)malloc(sizeof(wchar_t*)*a);
    for(int i = 0 ; i < a ;i++)  arr[i] = (wchar_t *)malloc(sizeof(wchar_t)* b);
    for(int i = 0 ; i < a;i++) wmemset(arr[i],L' ',b);

    wchar_t * arr2 = (wchar_t *)malloc(sizeof(wchar_t) *b);
    wmemset(arr2,L'-',b);

// test screen
    char *temp = (char *)malloc(sizeof(char) * 500);
    fgets(temp,sizeof(char) * 500,stdin);
    wchar_t * mess = (wchar_t *)malloc(sizeof(wchar_t) * 1000);
    printf("%s\n", temp);
    mbstowcs(mess, temp, 300);
    wprintf(L"%ls\n",mess);
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
1. 큰 목표를 이루고 싶으면 허락을 구하지 마라. – 미상2. 상황을 가장 잘 활용하는 사람이 가장 좋은 상황을 맞는다. – 존 우든3. 창조적인 삶을 살려면 내가 틀릴지도 모른다는 공포를 버려야 한다. – 미상4. 일반적인 것을 잃을 위험을 감수하지 않으면 평범한 것에 만족해야 한다. – 짐 론5. 신뢰의 이유는 안전하거나 확실해서가 아니라, 위험을 감수할 용의가 있어서이다. – 미상6. 한 가지 생각을 선택하라. 그 생각을 당신의 삶으로 만들어라. 그걸 생각하고, 꿈꾸고, 그에 기반해서 살아가라. 당신의 몸의 모든 부분, 뇌, 근육, 신경을 그 생각으로 가득 채우고 다른 생각은 다 내버려둬라. 이것이 성공하는 방법이다. – 스와미 비베카난다7. 추구할 수 있는 용기가 있다면 우리의 모든 꿈은 이뤄질 수 있다. – 월트 디즈니8. 기다리는 사람에게 좋은 일이 생기지만, 찾아나서는 사람에게는 더 좋은 일이 생긴다. – 미상9. 늘 하던 대로 하면 늘 얻던 것을 얻는다. – 미상10. 열정을 잃지 않고 실패에서 실패로 걸어가는 것이 성공이다. – 윈스턴 처칠11. 애벌레가 세상이 끝났다고 생각하는 순간 나비로 변했다. - 속담
*/

