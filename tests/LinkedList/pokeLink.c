#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../include/progress.h"


#define MAX_SKILLS 10
#define MAX_POKEMON 10


void createPokeData(PokeGlobalData *pokeData, unsigned int idenNum, const char *name, const char *type, unsigned int level, unsigned int health, unsigned int skillNum, int *skills) {
    pokeData->idenNum = idenNum;
    strcpy(pokeData->pokename, name);
    strcpy(pokeData->type, type);
    pokeData->level = level;
    pokeData->health = health;
    pokeData->skillNum = skillNum;
    for (int i = 0; i < skillNum; i++) {
        pokeData->skillarr[i] = skills[i];
    }
}

void saveDataToFile(PokeGlobalData *pokemon, size_t count) {
    FILE *file = fopen("poke_data.bin", "wb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fwrite(pokemon, sizeof(PokeGlobalData), count, file);

    fclose(file);
}

PokeGlobalData *loadDataFromFile(size_t *count) {
    FILE *file = fopen("poke_data.bin", "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    // 파일 끝까지 데이터 개수 확인
    fseek(file, 0, SEEK_END);
    *count = ftell(file) / sizeof(PokeGlobalData);
    rewind(file);

    // 메모리 할당
    PokeGlobalData *pokemon = malloc((*count) * sizeof(PokeGlobalData));
    if (pokemon == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // 파일에서 데이터 읽기
    fread(pokemon, sizeof(PokeGlobalData), *count, file);

    fclose(file);
    return pokemon;
}

PokeGlobalData *searchPokemonById(PokeGlobalData *pokemon, size_t count, unsigned int id) {
    for (size_t i = 0; i < count; ++i) {
        if (pokemon[i].idenNum == id) {
            return &pokemon[i];
        }
    }
    return NULL;
}

int main() {
    PokeGlobalData pokemon[MAX_POKEMON] = {0};
    int skills1[] = {1, 3, 5, 7, 9, 10, 11};
    createPokeData(&pokemon[0], 1, "Pikachu", "Electric", 5, 150, 7, skills1);

    int skills2[] = {2, 4, 6, 8, 10, 12};
    createPokeData(&pokemon[1], 2, "Bulbasaur", "Grass", 5, 120, 6, skills2);

    int skills3[] = {1, 3, 5, 7, 9};
    createPokeData(&pokemon[2], 3, "Charmander", "Fire", 5, 130, 5, skills3);

    int skills4[] = {2, 4, 6, 8};
    createPokeData(&pokemon[3], 4, "Squirtle", "Water", 5, 140, 4, skills4);

    int skills5[] = {1, 3, 5};
    createPokeData(&pokemon[4], 5, "Pidgey", "Normal", 5, 110, 3, skills5);

    int skills6[] = {2, 4, 6, 8, 10, 12};
    createPokeData(&pokemon[5], 6, "Geodude", "Rock", 5, 160, 6, skills6);

    int skills7[] = {2, 4, 6, 8, 10};
    createPokeData(&pokemon[6], 7, "Abra", "Psychic", 5, 100, 5, skills7);

    int skills8[] = {1, 3, 5, 7};
    createPokeData(&pokemon[7], 8, "Gastly", "Ghost", 5, 90, 4, skills8);

    int skills9[] = {1, 3, 5, 7, 9, 11};
    createPokeData(&pokemon[8], 9, "Eevee", "Normal", 5, 130, 6, skills9);

    int skills10[] = {2, 4, 6, 8, 10};
    createPokeData(&pokemon[9], 10, "Meowth", "Normal", 5, 120, 5, skills10);
    // 나머지 포켓몬 데이터 생성 생략

    // 데이터를 파일에 저장
    saveDataToFile(pokemon, MAX_POKEMON);

    // 파일에서 데이터 읽기
    size_t count;
    PokeGlobalData *loadedPokemon = loadDataFromFile(&count);

    // ID를 사용하여 포켓몬 검색
    unsigned int searchId = 10;
    PokeGlobalData *foundPokemon = searchPokemonById(loadedPokemon, count, searchId);
    if (foundPokemon != NULL) {
        printf("ID: %d, Name: %s, Type: %s, Level: %d, Health: %d, Skill Num: %d, Skills: ", foundPokemon->idenNum, foundPokemon->pokename, foundPokemon->type, foundPokemon->level, foundPokemon->health, foundPokemon->skillNum);
        for (int j = 0; j < foundPokemon->skillNum; ++j) {
            printf("%d ", foundPokemon->skillarr[j]);
        }
        printf("\n");
    } else {
        printf("Pokemon with ID %d not found.\n", searchId);
    }
    free(loadedPokemon);

    // 동적 할당된 메모리 해제

    return 0;
}
