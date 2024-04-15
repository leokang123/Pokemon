#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/progress.h"
// ../../src/includedef/progress.c

// 데이터 저장 함수
void saveSkills1(Skill *Skills, int count) {
    const char *filename = "./skilldata.bin";
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

// // 데이터 읽기 함수
// Skill *readSkills(void) {
//     const char *filename = "../data/pokeData/skilldata.bin";
//     FILE *file = fopen(filename, "rb"); // 이진 읽기 모드로 파일 열기
//     if (file == NULL) {
//         perror("Failed to open file");
//         return NULL;
//     }
//     int count;
//     // 파일로부터 구조체의 총 개수를 읽어옴
//     fread(&count, sizeof(int), 1, file);

//     // 구조체 데이터를 저장할 메모리 동적 할당
//     Skill *skills = (Skill *)malloc(count * sizeof(Skill));
//     if (skills == NULL) {
//         perror("Memory allocation failed");
//         fclose(file);
//         return NULL;
//     }

//     // 파일로부터 구조체 데이터를 읽어옴
//     fread(skills, sizeof(Skill), count, file);

//     fclose(file); // 파일 닫기

//     return skills; // 읽은 데이터 반환
// }
int main() {
    // 주어진 데이터를 구조체 배열에 저장
    // PokeList * list = makeLink();
    // 풀 물 불 돌 전기 노말 
    Skill skills[] = {
        {1, L"새싹던지기", L"grass", 30, 10, 0},
        {2, L"꽃잎댄스", L"grass", 55, 6, 0},
        {3, L"솔라빔", L"grass", 70, 3, 0},
        {4, L"잎날가르기", L"grass", 40, 15, 0},
        {5, L"풀묶기", L"grass", 50, 12, 0},
        {6, L"풀뽑기", L"grass", 65, 8, 0},
        {7, L"풀의노래", L"grass", 45, 14, 0},
        {8, L"리프스톰", L"grass", 60, 7, 0},
        {9, L"뿌리기", L"grass", 75, 5, 0},
        {10, L"나무부시기", L"grass", 55, 15, 0},

        {11, L"물대포", L"water", 30, 10, 0},
        {12, L"회오리세례", L"water", 50, 8, 0},
        {13, L"물기", L"water", 20, 20, 0},
        {14, L"해일파도", L"water", 40, 15, 0},
        {15, L"물갈퀴", L"water", 60, 7, 0},
        {16, L"파도타기", L"water", 35, 12, 0},
        {17, L"물의파동", L"water", 55, 9, 0},
        {18, L"거품광선", L"water", 70, 5, 0},
        {19, L"소용돌이", L"water", 45, 11, 0},
        {20, L"강류", L"water", 80, 4, 0},

        {21, L"불꽃펀치", L"fire", 30, 15, 0},
        {22, L"불대문자", L"fire", 35, 12, 0},
        {23, L"화염세례", L"fire", 40, 10, 0},
        {24, L"화염폭발", L"fire", 45, 14, 0},
        {25, L"불의마법", L"fire", 50, 9, 0},
        {26, L"화염의댄스", L"fire", 50, 11, 0},
        {27, L"불덩이폭발", L"fire", 55, 8, 0},
        {28, L"화염폭풍", L"fire", 60, 7, 0},
        {29, L"화염분출", L"fire", 65, 6, 0},
        {30, L"화염탄환", L"fire", 70, 5, 0},

        {31, L"돌뿌리기", L"rock", 30, 10, 0},
        {32, L"땅뒤집기", L"rock", 30, 10, 0},
        {33, L"산사태", L"rock", 30, 10, 0},
        {34, L"암바위", L"rock", 40, 15, 0},
        {35, L"강석광", L"rock", 50, 12, 0},
        {36, L"바위포화", L"rock", 35, 14, 0},
        {37, L"바위날림", L"rock", 55, 9, 0},
        {38, L"바위무덤", L"rock", 60, 8, 0},
        {39, L"바위강타", L"rock", 65, 7, 0},
        {40, L"바위망치", L"rock", 70, 6, 0},

        {41, L"번개", L"electric", 35, 8, 0},
        {42, L"백만볼트", L"electric", 40, 10, 0},
        {43, L"전기충격", L"electric", 45, 12, 0},
        {44, L"전기폭발", L"electric", 50, 9, 0},
        {45, L"전기빔", L"electric", 55, 7, 0},
        {46, L"전기쇼크", L"electric", 30, 15, 0},
        {47, L"번개펀치", L"electric", 60, 6, 0},
        {48, L"번개찌르기", L"electric", 65, 5, 0},
        {49, L"전기충전", L"electric", 70, 4, 0},
        {50, L"전기자석", L"electric", 75, 3, 0},

        {51, L"막치기", L"normal", 40, 5, 0},
        {52, L"몸통박치기", L"normal", 20, 15, 0},
        {53, L"베어클로", L"normal", 70, 3, 0}, 
        {54, L"연속뺨치기", L"normal", 55, 10, 0},
        {55, L"머리박기", L"normal", 45, 12, 0},
        {56, L"햘퀴기", L"normal", 50, 15, 0},
        {57, L"뒷축", L"normal", 70, 6, 0},
        {58, L"털치기", L"normal", 60, 10, 0},
        {59, L"전광석화", L"normal", 55, 15, 0},
        {60, L"회전뒷축", L"normal", 70, 10, 0},
    };
    int SkillCount = sizeof(skills) / sizeof(skills[0]);

    // 데이터 저장

    saveSkills1(skills, SkillCount);
    printf("%d 개의 스킬 구조체 데이터를 파일에 저장했습니다.\n",SkillCount);

    // 데이터 읽기
    // Skill *readSkillsArray = readSkills();
    // if (readSkillsArray != NULL) {
    //     // 읽은 데이터 출력
    //     for (int i = 0; i < 10; i++) {
    //         printf("%d %s %s %d %d\n", readSkillsArray[i].idenNum, readSkillsArray[i].skillName, readSkillsArray[i].type, readSkillsArray[i].skillAttack, readSkillsArray[i].skillAvail);
    //     }
    //     free(readSkillsArray); // 동적 할당된 메

    // }
    return 0;
}