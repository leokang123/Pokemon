#pragma once 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>

#define NEW         111
#define EDIT        222

#define BUF_SIZE    100

#define PGDSTRUCT_SIZE sizeof(PokeGlobalData)

#define NAME_SIZE 40


struct battleInter {
    int interCol;
    int healthLine;
    int barLine;
    int nameLine;
};

typedef struct _skill {
    int idenNum;
    wchar_t skillName[NAME_SIZE];
    wchar_t type[10];
    int skillAttack;
    int skillAvail;        // 스킬 원래 갯수; 남은 갯수는 함수 내부에서 처리할거같음 
    int skillUsed;         // 위의 주석 번복 여기서 처리해야할거같음 
} Skill;

typedef struct _pokeglobaldata{
    wchar_t pokename[NAME_SIZE];    // 포켓몬 고유이름 
    wchar_t type[10];               // 포켓몬 타입 
    int idenNum;        // 포켓몬 도감번호 
    int level;          // 포켓몬 최소 레벨 
    int health;         // 포켓몬 최소피 
    int skillNum;       // 총 스킬 갯수 
    int totalskill[10];            // 포켓몬 총 스킬
    // 도감에서는 인트형으로 스킬도감번호를 저장하고 PokeData 불러올때 스킬데이터랑 매핑시킨다 
} PokeGlobalData;

typedef struct _pokedata{
    wchar_t pokename[NAME_SIZE];       // 포켓몬 이름 
    char level;             // 현재 포켓몬 이름 
    int skillLearned;
    int usedHealth;
    int fullHealth;
    int point;
    Skill skillarr[4];             // 포켓몬 현재 스킬
    PokeGlobalData pokedata;        // 도감상의 포켓몬 특징 
} PokeData;

/* 
 암만 생각해봐도 도감에 들어갈 포켓몬 정보랑 사용자가 사용할 포켓몬 정보를 
 같은 구조체를 쓰면 먼가 꼬임 (특히 스킬부분)
*/

typedef struct _pokeNode{
    PokeGlobalData  data;
    struct _pokeNode *next;
    // struct _pokeNode *prev; 필요한가  걍 오름차순으로 정렬할거니까 필요없을듯 
} PokeNode;

typedef struct _linklist {
    int num; // 각 노드 할당해제 얼마나 해야하는지 표시
    PokeNode * head;
} PokeList;

typedef struct _item{
    char heal;
    char ball1;
    char ball2;
    char ball3;
    char drug;
} Item;

typedef struct _userdata{
    wchar_t username[NAME_SIZE];
    char progress;
    char pokenum;
    int balance;
    int userPoke;
    PokeData own[6];
    Item item;
} Userdata;


// 유저 데이터를 읽어와서 해당 이름의 정보를 반환하는 함수
// inputName: 찾고자 하는 유저 이름
// 반환값: 찾은 유저 정보 (텍스트 형식)
// const char * getUserData(const char *inputName);
int saveUserData(Userdata *userData, int type);

Userdata *readUserData(wchar_t * userName);


// 바이너리 파일에서 포켓몬 데이터를 읽어와 구조체 배열로바이너리 파일 이름
// structCountPtr: 읽어온 구조체의 총 개수를 저장할 포인터
// 반환값: 읽어온 포켓몬 데이터를 담은 구조체 배열의 포인터
PokeGlobalData *readPokemonData(int *structCountPtr);

// 읽어온 포켓몬 데이터를 연결 리스트에 추가하는 함수
// list: 포켓몬 데이터를 추가할 연결 리스트
void append(PokeList * list);


// 포켓몬 데이터를 담은 연결 리스트를 생성하는 함수
// 반환값: 생성된 연결 리스트의 포인터
PokeList * makeLink(void);

// 연결 리스트에서 해당 번호의 포켓몬 데이터를 filename으로 검색하여 반환하는 함수
// list: 검색을 수행할 연결 리스트
// num: 검색할 포켓몬의 번호
// 반환값: 검색된 포켓몬 데이터의 포인터
PokeGlobalData *searchData(PokeList * list, int num);

// 연결 리스트의 메모리를 해제하는 함수 (내부 함수)
// list: 메모리를 해제할 연결 리스트
void _freeList(PokeList * list);

// 연결 리스트의 메모리를 해제하는 함수
// list: 메모리를 해제할 연결 리스트
void freePokeList (PokeList * list, Userdata * userData);

// save함수는 오직 bin파일 생성을 위해 필요한 함수 한번 저장하고나면 쓸일 없다
void saveSkills(Skill *Skills, int count);

// 스킬정보 다 받아오는 함수 
Skill *readSkills(void);

void learnSkill(PokeData * pokemon);
void levelup(PokeData * pokemon);
