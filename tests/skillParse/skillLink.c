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


// void saveSkills(const char *filename, Skill *Skills, int count) {
//     FILE *file = fopen(filename, "wb"); // 이진 쓰기 모드로 파일 열기
//     if (file == NULL) {
//         perror("Failed to open file");
//         return;
//     }

//     // 구조체의 총 개수를 파일에 저장
//     fwrite(&count, sizeof(int), 1, file);

//     // 구조체 데이터를 파일에 저장
//     fwrite(Skills, sizeof(Skill), count, file);

//     fclose(file); // 파일 닫기
// }

// // 데이터 읽기 함수
// // 일단은 전체 스킬을 할당해서불러와서 도감 불러올때 각 포켓몬에 맵핑해주고 
// // 도감 빠져나갈때 할당해제 한다고 생각하자 
// Skill *readSkills(const char *filename) {
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
    PokeList * list = makeLink();
    Userdata * userData = readUserData("userdata.bin","leokang");
    Userdata *readUserDataArray1 = readUserData("userdata.bin", "leokang");

    // 데이터 읽기
    
    int num = userData->pokenum;
    Skill *readSkillsArray = readSkills("skills.bin");
    printf("%s\n",readSkillsArray->skillName);
    if (readSkillsArray != NULL) {
        // 읽은 데이터 출력
        for(int i = 0 ; i < num ; i++ ){
            int skillnum = userData->own[i].skillCurNum;
            printf("skillNum : %d\n", skillnum);
            for(int j = 0 ; j < skillnum ; j++) {
                int idenNum = userData->own[i].skillarr[j].idenNum;
                userData->own[i].skillarr[j].skillAttack = readSkillsArray[idenNum].skillAttack;
                userData->own[i].skillarr[j].skillAvail = readSkillsArray[idenNum].skillAvail;
                strcpy(userData->own[i].skillarr[j].skillName,readSkillsArray[idenNum].skillName);
                strcpy(userData->own[i].skillarr[j].type,readSkillsArray[idenNum].type);
                printf("%s\n", readSkillsArray[idenNum].skillName);
            }
        }
        free(readSkillsArray); 
        for(int i = 0 ; i < 3 ; i++)
        printf("name: %s, type: %s, skilname: %s %s %s",userData->own[i].pokename,userData->own[i].type, userData->own[i].skillarr[0].skillName,userData->own[i].skillarr[1].skillName,userData->own[i].skillarr[2].skillName);

    }
    freePokeList(list,userData);
    return 0;
}