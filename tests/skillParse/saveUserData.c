#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/progress.h"


int main() {

    FILE * file =  fopen("userdata.bin","wb");
    rewind(file);
    int a = 0;
    int count = a;
    fwrite(&count,sizeof(int),1,file);
    fclose(file);
    for(int i = 0 ; i < 3; i++) {
        Userdata userDataArray1[] = {
            {"leokang", 10000, 0, 3, {
                {1, "Pikachu", "Electric", 5, 150, 3, {{1,0,0,0,0},{3,0,0,0,0},{11,0,0,0,0}}},
                {2, "Bulbasaur", "Grass", 5, 120, 4, {{2,0,0,0,0},{4,0,0,0,0},{6,0,0,0,0},{12,0,0,0,0}}},
                {3, "Charmander", "Fire", 5, 130, 4, {{1,0,0,0,0},{3,0,0,0,0},{5,0,0,0,0},{9,0,0,0,0}}},
                // 나머지 사용자 데이터 추가
            }, {3, 3, 5, 2, 2}},
            {"ashketchum", 15000, 1, 2, {
                {4, "Squirtle", "Water", 5, 140, 2, {{2,0,0,0,0},{8,0,0,0,0}}},
                {5, "Pidgey", "Normal", 5, 110, 3, {{1,0,0,0,0},{3,0,0,0,0},{5,0,0,0,0}}},
                // 추가 사용자 데이터 추가
            }, {2, 1, 3, 4, 0}},
            {"misty", 8000, 2, 1, {
                {6, "Geodude", "Rock", 5, 160, 2, {{2,0,0,0,0},{12,0,0,0,0}}},
                // 추가 사용자 데이터 추가
            }, {1, 0, 0, 0, 3}},
            // 더 많은 사용자 데이터 추가
        };
        saveUserData("userdata.bin", &userDataArray1[i]);
            // 나머지 사용자 데이터 추가
        // 샘플 사용자 데이터의 개수
    }


    // bin 파일로부터 사용자 데이터 읽기
    Userdata *readUserDataArray1 = readUserData("userdata.bin", "leokang");
    printf("skill Num: %d\n", readUserDataArray1->own[0].skillarr[0].idenNum);
    Userdata *readUserDataArray2 = readUserData("userdata.bin", "ashketchum");
    Userdata *readUserDataArray3 = readUserData("userdata.bin", "misty");
    if (readUserDataArray1 != NULL) {
        // 읽어온 사용자 데이터 출력
        printf("User %d\n", 1);
        printf("Username: %s\n", readUserDataArray1->username);
        printf("Pokenum: %u\n", readUserDataArray1->pokenum);
        printf("Balance: %u\n", readUserDataArray1->balance);
        printf("Progress: %u\n", readUserDataArray1->progress);
        for (int j = 0; j < readUserDataArray1->pokenum; j++) {
            printf("Pokemon %d: %d\n", j + 1, readUserDataArray1->own[j].skillarr[1].idenNum);
        }
            printf("\n");
        // 메모리 해제
        free(readUserDataArray1);
    }
    if (readUserDataArray2 != NULL) {
        // 읽어온 사용자 데이터 출력
        printf("User %d\n", 2);
        printf("Username: %s\n", readUserDataArray2->username);
        printf("Pokenum: %u\n", readUserDataArray2->pokenum);
        printf("Balance: %u\n", readUserDataArray2->balance);
        printf("Progress: %u\n", readUserDataArray2->progress);
        for (int j = 0; j < readUserDataArray2->pokenum; j++) {
            printf("Pokemon %d: %s\n", j + 1, readUserDataArray2->own[j].pokename);
        }
            printf("\n");
        // 메모리 해제
        free(readUserDataArray2);
    }
    if (readUserDataArray3 != NULL) {
        // 읽어온 사용자 데이터 출력
        printf("User %d\n", 3);
        printf("Username: %s\n", readUserDataArray3->username);
        printf("Pokenum: %u\n", readUserDataArray3->pokenum);
        printf("Balance: %u\n", readUserDataArray3->balance);
        printf("Progress: %u\n", readUserDataArray3->progress);
        for (int j = 0; j < readUserDataArray3->pokenum; j++) {
            printf("Pokemon %d: %s\n", j + 1, readUserDataArray3->own[j].pokename);
        }
            printf("\n");
        // 메모리 해제
        free(readUserDataArray3);
    }

    return 0;
}
