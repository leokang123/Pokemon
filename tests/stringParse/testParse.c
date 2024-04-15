#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    unsigned int idenNum;
    char type[10];
    char skillName[20];
    unsigned int skillAttack;
    unsigned int skillAvail;        // 스킬 원래 갯수; 남은 갯수는 함수 내부에서 처리할거같음 
} Skill;
typedef struct {
    unsigned int idenNum;        // 포켓몬 도감번호 
    unsigned int level;          // 포켓몬 최소 레벨 
    unsigned int health;         // 포켓몬 최소피 
    char pokename[20];           // 포켓몬 이름 
    char type[10];               // 포켓몬 타입 
    unsigned int skillNum;       // 현재 배운 총 갯수 
    int skillarr[10];          // 포켓몬 총 스킬
    
} PokeGlobalData;



int main(void) {
    char str[] = "1 picachuy electric 5 150:7/1 3 5 7 9 10 11/";
    PokeGlobalData data;
    int i = 0;
    char *q, *p;
    int * arr;
    int num;
    p = str;
    q = strsep(&p, " ");
    data.idenNum = atoi(q);

    q = strsep(&p, " ");
    strcpy(data.pokename,q);

    q = strsep(&p, " ");
    strcpy(data.type,q);

    q = strsep(&p, " ");
    data.level = atoi(q);

    q = strsep(&p, ":");
    data.health = atoi(q);

    // q 에 스킬 전체 갯수 저장됌 
    q = strsep(&p, "/");
    data.skillNum = atoi(q);

    arr = (int * ) malloc(sizeof(int) * num);
    // 스킬목록 + '/'이 q에 저장됌 
    // while(num--) {
    //     int a; 
    //     q = strsep(&p, " \t/");
    //     arr[i++] = atoi(q);
    //     printf("%d\n",arr[i-1]);
    // }
    for(int j = 0 ; j < data.skillNum ; j++) {
        q = strsep(&p, " \t/");
        data.skillarr[j] = atoi(q);
        printf("%d\n", data.skillarr[j]);
    }
    printf("%s\n", data.type);
    free(arr);

    // 문자열 조립 
    char buf3[100] = "%d %s %s %d %d %d/";
    char buf4[50];
    // "1 picachuy electric 5 150:7/1 3 5 7 9 10 11/"
    sprintf(buf3,"%d %s %s %d %d %d/",data.idenNum, data.pokename, data.type, data.level, data.health, data.skillNum);

    for(int i = 0 ; i < data.skillNum - 1; i++) {
        sprintf(buf4,"%d",data.skillarr[i]);
        strcat(buf3, buf4);
        strcat(buf3, " ");    
    }
    sprintf(buf4,"%d",data.skillarr[data.skillNum - 1]);
    strcat(buf3, buf4);
    strcat(buf3, "/");  
    // "1 picachuy electric 5 150:7/1 3 5 7 9 10 11/"
    printf("%s",buf3);
}