#include <stdio.h>
#include <stdlib.h>

#include "../../include/progress.h"

#define STRUCT_SIZE sizeof(PokeGlobalData)


PokeGlobalData *readPokemonData(const char *filename, int *structCountPtr) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
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
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // 파일로부터 구조체 데이터를 읽어옴
    fread(pokemon, STRUCT_SIZE, structCount, file);
    fclose(file);

    return pokemon;
}
void append(PokeList * list) {
    int structCount;
    PokeGlobalData *pokemon = readPokemonData("poke_data.bin", &structCount); // 얘도 할당해제해줘야함 pokeNode 에 있는 노드
    if (pokemon == NULL) {
        printf("구조체 데이터를 읽어오는 데 실패했습니다.\n");
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

Skill * getSkillData(PokeList *list, int idenNum) {

}

PokeList * makeLink() {
    PokeList * list = (PokeList*)malloc(sizeof(PokeList));
    list->head = NULL;
    list->num = 0;
    append(list);
    return list;
}

PokeGlobalData *searchData(PokeList * list, int num) {
    PokeNode * cur = list->head;
    int pokeNum = num;
    for(int i = 0 ; i < pokeNum-1 ; i++ ) {
        cur = cur->next;
    }
    return &(cur->data);
}
void _freeList(PokeList * list) {
    int pokeNum = list->num;
    PokeNode * cur = list->head;
    PokeNode * next;
    for(int i = 0 ; i < pokeNum  ; i++) {
        next = list->head->next; // 할당해제전에 먼저 해줘야 되는듯? 
        free(list->head);
        list->head = next;
        // next = list->head->next; 여기에있으면 마지막요소에서 오류남 // 할당해제전에 먼저 해줘야 되는듯? 
    }
}

// 연결리스트 메모리 해제 함수 
void freePokeList (PokeList * list) {
    _freeList(list);
    free(list);
}

Skill * getSkillData(PokeList *list, int idenNum) {
    
}
int main() {
    // 읽어온 데이터 출력
    PokeList * list = makeLink();
    PokeGlobalData *pdata = searchData(list,1);
    printf("%s\n",pdata->pokename);
    // 메모리 해제
    freePokeList(list);
    return 0;
}
