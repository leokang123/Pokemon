#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ncursesw/curses.h>

#include "Backup.h"



void * inputlenRange() {
    static char namebuf[200]; // 전역변수나 다를거 없음 
    int namelen = 0;
    while(1) {
        scanf("%s",namebuf);
        getchar();
        namelen = strlen(namebuf);
        if(namelen >= 2 && namelen < NAME_SIZE) break;
        printf("Unvalid input size\n");
        printf("do it again\n");
    }
    return namebuf;
}

int main (void) {
    // int a = randomInRange(0, 100);
    // printf("%d\n", a);
    PokeList * list = makeLink();
    int namelen = 0 ;
    char namebuf[200];
    /*
        돈 아이템 포켓몬배열 포켓몬수 진행도 이름 설정해야함 
    */
    Userdata * newUser = (Userdata *) malloc(sizeof(Userdata));
    // while(1) {
    //     memset(namebuf,0,sizeof(namebuf)); 
    //     printf("enter your name:\n");
    //     scanf("%s", namebuf);
    //     namelen = strlen(namebuf);
    //     if(namelen >=2 && namelen < 20) break;
    //     printf("string length should be 2 to 50\n");
    // }
    printf("enter your name:\n");
    char * q = (char *)inputlenRange();
    strcpy(newUser->username, q);
    strcpy(newUser->username,namebuf);
    newUser->balance = 10000;
    printf("You have 10000won\n");
    newUser->pokenum = 0;
    newUser->progress = 0;
    saveUserData(newUser);
    printf("%s\n",newUser->username);
    // 일단 우려중이였던게 애초에 더미 데이터를 기반으로 짜다보니 일어나지 않을 상황에대해 걱정했음 
    // 애초에 처음부터 사용자생성하고 데이터를 축적하다보면 Userdata 구조체가 어떤멤버변수는 비어있고 이럴수가 없는데 
    // 비어있는 경우도 생각해서 짜다보니 뭔가 복잡해졌음 
    free(newUser);
    Userdata * userdata = readUserData(namebuf);
    printf("Your Name: %s, Your Balance: %d, Your Progress: %d\n",userdata->username, userdata->balance, userdata->progress);
    for(int i = 1 ; i <= 3 ; i++) {
        PokeGlobalData * data = searchData(list,i); // 이미 리스트에서 할당한 주소만 가져오는거임 
        printf("%d %s %s\n", data->idenNum, data->pokename, data->type); 
    }
    printf("Please choose one Pokemon for your adventure\n");
    int chosen = 0 ;
    scanf("%d", &chosen);
    getchar();
    // 여기도 나중엔 이미 만들어놓은 값에서 주소만 가져오게 할수 있을거같음
    // 근데 일단은 더미 데이터를 활요해야해서 쩔수임 
    PokeData * pokemon = &(userdata->own[0]);
    pokemon->pokedata = *searchData(list,chosen); 
    printf("You chose : %d %s %s\n", pokemon->pokedata.idenNum, pokemon->pokedata.pokename, pokemon->pokedata.type); 
    Skill * skills = readSkills();
    pokemon->skillarr[0] = skills[0];
    free(skills);
    printf("You can rename your Pokemon (y/n)\n");
    char c;
    scanf("%c", &c); // 버퍼에 개행문자가 남아있으면 그걸 바로 받아서 이상하게 흘러감 
    getchar(); //getchar();
    if(c == 'y') {
        q = inputlenRange();
        strcpy(pokemon->pokename,q);
        printf("Your %s name is %s\n", pokemon->pokedata.pokename, pokemon->pokename);
    }
    else if(c == 'n') strcpy(pokemon->pokename,pokemon->pokedata.pokename);
    
    printf("Your %s learned : %s\n", pokemon->pokename, pokemon->skillarr[0].skillName);
    printf("byebye\n");
    
    freePokeList(list,userdata);
    return 0;
}