#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/progress.h"

void saveUserData1(Userdata *userData) {
    const char *filename = "./userdata.bin";
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    int count = 0;
    fread(&count, sizeof(int),1,file);
    count += 1;
    // printf("%d\n", count);
    rewind(file);
    fwrite(&count,sizeof(int),1,file);
    fclose(file);
    file = fopen(filename,"ab"); // 파일 포인터가 맨뒤에서 시작 
    // 구조체 데이터를 파일에 저장
    fwrite(userData, sizeof(Userdata), 1, file);

    fclose(file);
}

Userdata *readUserData1(char * userName) {
    const char * filename = "./userdata.bin";
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }
    int count;
    // 구조체의 총 개수를 파일로부터 읽어옴
    fread(&count, sizeof(int), 1, file);
    // 구조체 데이터를 저장할 메모리 동적 할당
    Userdata *userData = (Userdata *)malloc(sizeof(Userdata));
    if (userData == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // 파일로부터 구조체 데이터를 읽어옴
    for (int i = 0; i < count; i++) {
        fread(userData, sizeof(Userdata), 1, file);
        if (strcmp(userData->username, userName) == 0) {
            fclose(file);
            return userData;
        }
    }

    fclose(file);

    return userData;
}

int main() {

    FILE * file =  fopen("userdata.bin","wb");
    rewind(file);
    int a = 0;
    int count = a;
    fwrite(&count,sizeof(int),1,file);
    fclose(file);

Userdata userDataArray1 = {"user1", 0, 1, 10000, {{"Mypretty", 12, 2, {{1}, {3}}, {"Pikachu", "electronic", 1, 5, 150, 6, {1,3,5,7,10,11,}}}}, {3,2,0,0,1}};
saveUserData1(&userDataArray1);

Userdata userDataArray2 = {"user2", 1, 2, 20000, {{"Mypretty2", 15, 3, {{2}, {4}, {6}}, {"Charmander", "fire", 5, 6, 200, 5, {2,4,6,8,10,12,}},}, {"Mypretty3", 10, 1, {{5}}, {"Squirtle", "water", 3, 7, 180, 4, {5,7,9,11,13,15,}},}}, {3, 2, 1, 0, 2}};
saveUserData1(&userDataArray2);

Userdata userDataArray3 = {"user3", 3, 4, 40000, {{"Mypretty7", 25, 4, {{24}, {26}, {28}, {30}}, {"Dragonite", "dragon", 12, 30, 300, 10, {20,22,24,26,28,30,}},}, {"Mypretty8", 22, 3, {{25}, {27}, {29}}, {"Blastoise", "water", 15, 25, 280, 8, {25,27,29,31,33,35,}},}, {"Mypretty9", 14, 2, {{32}, {34}}, {"Venusaur", "grass", 18, 20, 320, 9, {32,34,36,38,40,42,}},}}, {5, 2, 3, 2, 4}};
saveUserData1(&userDataArray3);


    //         // 나머지 사용자 데이xw터 추가
    //     // 샘플 사용자 데이터의 개수

    // // bin 파일로부터 사용자 데이터 읽기
    Userdata *readUserDataArray1 = readUserData1("user1");
    // printf("skill Num: %d\n", readUserDataArray1->own[0].skillarr[0].idenNum);
    Userdata *readUserDataArray2 = readUserData1("user2");
    Userdata *readUserDataArray3 = readUserData1("user3");
    if (readUserDataArray1 != NULL) {
        // 읽어온 사용자 데이터 출력
        printf("User %d\n", 1);
        printf("Username: %s\n", readUserDataArray1->username);
        printf("Pokenum: %u\n", readUserDataArray1->pokenum);
        printf("Balance: %u\n", readUserDataArray1->balance);
        printf("Progress: %u\n", readUserDataArray1->progress);
        for (int j = 0; j < readUserDataArray1->pokenum; j++) {
            printf("Pokemon %d %s: %s\n", readUserDataArray1->own[j].pokedata.idenNum, readUserDataArray1->own[j].pokedata.pokename, readUserDataArray1->own[j].pokename);
        }
        printf("\n");
        printf("%d\n", (int)sizeof(PokeList));
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
            printf("Pokemon %d %s: %s\n", readUserDataArray2->own[j].pokedata.idenNum, readUserDataArray2->own[j].pokedata.pokename, readUserDataArray2->own[j].pokename);
        }
        printf("\n");
        printf("%d\n", (int)sizeof(PokeList));
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
            printf("Pokemon %d %s: %s\n", readUserDataArray3->own[j].pokedata.idenNum, readUserDataArray3->own[j].pokedata.pokename, readUserDataArray3->own[j].pokename);
        }
        printf("\n");
        printf("%d\n", (int)sizeof(PokeList));
        // 메모리 해제
        free(readUserDataArray3);
    }

    return 0;
}
