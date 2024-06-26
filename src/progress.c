// #include "../../src/everyheader.h"
#include "../src/everyheader.h"
// #define BUF_SIZE 50
// #define PGDSTRUCT_SIZE sizeof(PokeGlobalData)

/*
    파일 경로는 헤더파일을 기준으로 경로설정을 해줘야한다 -> (x) 
    실행파일 기준으로 경로 설정해줘야됌 
*/

// Userdata *readUserData(const char *filename, char * userName) {

Userdata *readUserData(wchar_t * userName) {
    // const char * filename = "../../data/userData/userdata.bin";   // test 디렉토리용 
    const char * filename = "../data/userData/userdata.bin";
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("(READ USER) Failed to open file");
        return NULL;
    }
    int count;
    // 구조체의 총 개수를 파일로부터 읽어옴
    fread(&count, sizeof(int), 1, file);
    // 구조체 데이터를 저장할 메모리 동적 할당`
    Userdata *userData = (Userdata *)malloc(sizeof(Userdata));
    if (userData == NULL) {
        perror("(READ USER) Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // 파일로부터 구조체 데이터를 읽어옴
    for (int i = 0; i < count; i++) {
        fread(userData, sizeof(Userdata), 1, file);
        if (wcscmp(userData->username, userName) == 0) {
            // 아름을 찾으면 유저데이터 반환
            fclose(file);
            return userData;
        }
    }
    // 못찾으면 할당해제 후 NULL반환 
    free(userData);
    fclose(file);
    return NULL;
}

int saveUserData(Userdata *userData, int type) {

    // const char * filename = "../../data/userData/userdata.bin"; //test 디렉토리용 
    const char * filename = "../data/userData/userdata.bin";
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("(SAVE USER) Failed to open file");
        return 1;
    }
    int count = 0;
    fread(&count, sizeof(int),1,file);

    // 새로 생성하는거
    if (type == NEW){ 
        
        // 이름 중복 검사 
        Userdata *user = readUserData(userData->username);
        if(user != NULL) {
            mvprintw(line,ST,"Duplicated Name, Try again");
            getch();
            free(user);
            return 1;
        }
        count += 1;
        rewind(file);
        fwrite(&count,sizeof(int),1,file);
        fclose(file);
        file = fopen(filename,"ab"); // 파일 포인터가 맨뒤에서 시작 
        // 구조체 데이터를 파일에 저장
        fwrite(userData, sizeof(Userdata), 1, file);

        fclose(file);
    }
    
    if (type == EDIT) {
        Userdata readData;
        // 파일로부터 구조체 데이터를 읽어옴
        for (int i = 0; i < count; i++) {
            fread(&readData, sizeof(Userdata), 1, file);
            if (wcscmp(readData.username, userData->username) == 0) {
                // 아름을 찾으면 유저데이터 반환
                fseek(file, -sizeof(Userdata),SEEK_CUR);
                break;
            }
        }
        fwrite(userData, sizeof(Userdata), 1, file);
        fclose(file);
    }
    

    return 0;
}


PokeGlobalData *readPokemonData(int *structCountPtr) {
    // const char *filename = "../../data/pokeData/pokedata.bin";  //test 디렉토리용 
    const char *filename = "../data/pokeData/pokedata.bin";
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("(READ POKE) Failed to open file");
        return NULL;
    }

    // 구조체의 총 개수를 파일로부터 읽어옴
    int structCount;
    fread(&structCount, sizeof(int), 1, file);

    // 구조체의 총 개수를 포인터를 통해 반환
    *structCountPtr = structCount;

    // 구조체 데이터를 저장할 메모리 동적 할당
    PokeGlobalData *pokemon = malloc(structCount * sizeof(PokeGlobalData));
    if (pokemon == NULL) {
        perror("(READ POKE) Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // 파일로부터 구조체 데이터를 읽어옴
    fread(pokemon, PGDSTRUCT_SIZE, structCount, file);

    fclose(file);

    return pokemon;
}

PokeList * makeLink() {
    PokeList * list = (PokeList*)malloc(sizeof(PokeList));
    list->head = NULL;
    list->num = 0;
    append(list);
    return list;
}
void append(PokeList * list) {
    int structCount;
    PokeGlobalData *pokemon = readPokemonData(&structCount); // 얘도 할당해제해줘야함 pokeNode 에 있는 노드
    if (pokemon == NULL) {
        printf("포켓몬 구조체 데이터를 읽어오는 데 실패했습니다.\n");
        return;
    }
    PokeNode *cur;
    for(int i = 0 ; i < structCount ; i++ ){
        PokeGlobalData pdata = pokemon[i];
        PokeNode * newnode = (PokeNode *) malloc(sizeof(PokeNode));
        list->num += 1;
        newnode->data = pdata;
        newnode->next = NULL;
        if(i==0) {
            list->head = newnode;
            cur = newnode;
            continue;
        }
        cur->next = newnode;
        cur = newnode;
    }
    free(pokemon);
}

PokeGlobalData *searchData(PokeList * list, int num) {
    PokeNode * cur = list->head;
    int pokeNum = num;
    for(int i = 0 ; i < pokeNum ; i++ ) {
        cur = cur->next;
    }
    return &(cur->data);
}
void _freeList(PokeList * list) {
    int pokeNum = list->num;
    PokeNode * next;
    for(int i = 0 ; i < pokeNum  ; i++) {
        next = list->head->next; // 할당해제전에 먼저 해줘야 되는듯? 
        free(list->head);
        list->head = next;
        // next = list->head->next; 여기에있으면 마지막요소에서 오류남 // 할당해제전에 먼저 해줘야 되는듯? 
    }
}

// 연결리스트 메모리 해제 함수 
void freePokeList (PokeList * list, Userdata * userData) {
    _freeList(list);
    free(list);
    free(userData);
}

// 스킬 데이터 함수는 좀 더 손봐야할수도 있음 
// 스킬 데이터 함수
// 스킬저장은 한번 등록하면 끝이라 잘 모르겠지만 count는 없애게 할수 있긴함 
void saveSkills(Skill *Skills, int count) {
    const char * filename = "../data/pokeData/skilldata.bin";
    FILE *file = fopen(filename, "wb"); // 이진 쓰기 모드로 파일 열기
    if (file == NULL) {
        perror("(SAVE SKILL) Failed to open file");
        return;
    }

    // 구조체의 총 개수를 파일에 저장
    fwrite(&count, sizeof(int), 1, file);

    // 구조체 데이터를 파일에 저장
    fwrite(Skills, sizeof(Skill), count, file);

    fclose(file); // 파일 닫기
}

// 데이터 읽기 함수
Skill *readSkills(void) {
    const char * filename = "../data/pokeData/skilldata.bin";
    FILE *file = fopen(filename, "rb"); // 이진 읽기 모드로 파일 열기
    if (file == NULL) {
        perror("(READ SKILL) Failed to open file");
        return NULL;
    }
    int count;
    // 파일로부터 구조체의 총 개수를 읽어옴
    fread(&count, sizeof(int), 1, file);

    // 구조체 데이터를 저장할 메모리 동적 할당
    Skill *skills = (Skill *)malloc((count) * sizeof(Skill));
    if (skills == NULL) {
        perror("(READ SKILL) Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // 파일로부터 구조체 데이터를 읽어옴
    fread(skills, sizeof(Skill), count, file);

    fclose(file); // 파일 닫기

    return skills; // 읽은 데이터 반환
}

