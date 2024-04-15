#include <stdio.h>
#include <stdlib.h>

#include "../../include/progress.h"

#define STRUCT_SIZE sizeof(PokeGlobalData)


void writePokemonData(PokeGlobalData *pokemon, int structCount, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // 구조체의 총 개수를 파일에 씀
    fwrite(&structCount, sizeof(int), 1, file);

    // 각 구조체 데이터를 파일에 씀
    fwrite(pokemon, STRUCT_SIZE, structCount, file);

    fclose(file);
}

int main() {
    // 저장할 포켓몬 데이터
    PokeGlobalData pokemon[] = {
    {1, "Pikachu", "Electric", 5, 150, 7, {1, 3, 5, 7, 9, 10, 11}},
    {2, "Bulbasaur", "Grass", 5, 120, 6, {2, 4, 6, 8, 10, 12}},
    {3, "Charmander", "Fire", 5, 130, 5, {1, 3, 5, 7, 9}},
    {4, "Squirtle", "Water", 5, 140, 4, {2, 4, 6, 8}},
    {5, "Pidgey", "Normal", 5, 110, 3, {1, 3, 5}},
    {6, "Geodude", "Rock", 5, 160, 6, {2, 4, 6, 8, 10, 12}},
    {7, "Abra", "Psychic", 5, 100, 5, {2, 4, 6, 8, 10}},
    {8, "Gastly", "Ghost", 5, 90, 4, {1, 3, 5, 7}},
    {9, "Eevee", "Normal", 5, 130, 6, {1, 3, 5, 7, 9, 11}},
    {10, "Meowth", "Normal", 5, 120, 5, {2, 4, 6, 8, 10}},
        // 나머지 구조체 데이터 추가
    };

    // 저장할 구조체의 총 개수
    int structCount = sizeof(pokemon) / sizeof(PokeGlobalData);

    // 파일에 구조체 데이터 저장
    writePokemonData(pokemon, structCount, "poke_data.bin");

    printf("구조체 데이터를 파일에 저장했습니다.\n");

    return 0;
}
