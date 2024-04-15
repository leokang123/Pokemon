#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/progress.h"
// ../../src/includedef/progress.c



// 구조체 정의
// typedef struct {
//     int id;
//     char name[50];
//     char type[10];
//     int power;
//     int count;
// } Skill;

// 데이터 저장 함수


void saveSkills(const char *filename, Skill *Skills, int count) {
    FILE *file = fopen(filename, "wb"); // 이진 쓰기 모드로 파일 열기
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // 구조체의 총 개수를 파일에 저장
    fwrite(&count, sizeof(int), 1, file);

    // 구조체 데이터를 파일에 저장
    fwrite(Skills, sizeof(Skill), count, file);

    fclose(file); // 파일 닫기
}

// 데이터 읽기 함수
Skill *readSkills(const char *filename) {
    FILE *file = fopen(filename, "rb"); // 이진 읽기 모드로 파일 열기
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }
    int count;
    // 파일로부터 구조체의 총 개수를 읽어옴
    fread(&count, sizeof(int), 1, file);

    // 구조체 데이터를 저장할 메모리 동적 할당
    Skill *skills = (Skill *)malloc(count * sizeof(Skill));
    if (skills == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // 파일로부터 구조체 데이터를 읽어옴
    fread(skills, sizeof(Skill), count, file);

    fclose(file); // 파일 닫기

    return skills; // 읽은 데이터 반환
}
int main() {
    // 주어진 데이터를 구조체 배열에 저장
    PokeList * list = makeLink();

    // Skill skills[] = {
    //     {1, "불꽃펀치", "fire", 25, 15},
    //     {2, "불대문자", "fire", 35, 12},
    //     {3, "화염세례", "fire", 30, 10},
    //     {4, "새싹던지기", "grass", 30, 10},
    //     {5, "꽃잎댄스", "grass", 55, 6},
    //     {6, "솔라빔", "grass", 70, 3},
    //     {7, "물대포", "water", 30, 10},
    //     {8, "회오리세례", "water", 50, 8},
    //     {9, "물기", "water", 20, 20},
    //     {10, "백만볼트", "electric", 40, 10},
    //     {11, "번개", "electric", 35, 8},
    //     {12, "몸통박치기", "normal", 20, 15},
    //     {13, "베어클로", "normal", 70, 5},
    //     {14, "바위비", "rock", 50, 7},
    //     {15, "대지의파동", "rock", 75, 3},
    //     {16, "울부짖기", "rock", 40, 10},
    //     {17, "역린", "rock", 80, 3},
    //     {18, "신속", "normal", 0, 5},
    //     {19, "번개", "electric", 120, 5},
    //     {20, "물대포", "water", 150, 2}
    // };
    // int SkillCount = sizeof(skills) / sizeof(skills[0]);

    // // 데이터 저장
    // saveSkills("skills.bin", skills, SkillCount);

    // 데이터 읽기
    Skill *readSkillsArray = readSkills("skills.bin");
    if (readSkillsArray != NULL) {
        // 읽은 데이터 출력
        for (int i = 0; i < 10; i++) {
            printf("%d %s %s %d %d\n", readSkillsArray[i].idenNum, readSkillsArray[i].skillName, readSkillsArray[i].type, readSkillsArray[i].skillAttack, readSkillsArray[i].skillAvail);
        }
        free(readSkillsArray); // 동적 할당된 메

    }
    return 0;
}