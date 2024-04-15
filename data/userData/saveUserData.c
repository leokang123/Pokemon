#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
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
    rewind(file);
    fwrite(&count,sizeof(int),1,file);
    fclose(file);
    file = fopen(filename,"ab"); // 파일 포인터가 맨뒤에서 시작 
    // 구조체 데이터를 파일에 저장
    fwrite(userData, sizeof(Userdata), 1, file);

    fclose(file);
}

Userdata *readUserData1(wchar_t * userName) {
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
        if (wcscmp(userData->username, userName) == 0) {
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

// Userdata userDataArray1 = {L"user1", 0, 1, 10000, {{L"Mypretty", 12, 2, 0, 150, {{1}, {3}}, {L"Pikachu", L"electronic", 1, 5, 150, 6, {1,3,5,7,10,11,}}}}, {3,2,0,0,1}};
// saveUserData1(&userDataArray1);

// Userdata userDataArray2 = {L"user2", 1, 2, 20000, {{L"Mypretty2", 15, 3, 0, 200, {{2}, {4}, {6}}, {L"Charmander", L"fire", 5, 6, 200, 5, {2,4,6,8,10,12,}},}, {L"Mypretty3", 10, 1, 0, 180, {{5}}, {L"Squirtle", L"water", 3, 7, 180, 4, {5,7,9,11,13,15,}},}}, {3, 2, 1, 0, 2}};
// saveUserData1(&userDataArray2);

// Userdata userDataArray3 = {L"user3", 3, 3, 40000, {{L"Mypretty7", 25, 3, 0, 300, {{14, L"바위비", L"rock", 50, 7, 0},{15, L"대지의파동", L"rock", 75, 3, 0},{16, L"울부짖기", L"rock", 40, 10, 0},}, {L"Dragonite", L"dragon", 12, 30, 300, 10, {20,22,24,26,28,30,}},}, {L"Mypretty8", 22, 3, 0, 280, {{25}, {27}, {29}}, {L"Blastoise", L"water", 15, 25, 280, 8, {25,27,29,31,33,35,}},}, {L"Mypretty9", 14, 2, 0, 320, {{32}, {34}}, {L"Venusaur", L"grass", 18, 20, 320, 9, {32,34,36,38,40,42,}},}}, {5, 2, 3, 2, 4}};
// saveUserData1(&userDataArray3);


    //         // 나머지 사용자 데이xw터 추가
    //     // 샘플 사용자 데이터의 개수

    // // bin 파일로부터 사용자 데이터 읽기
    // Userdata *readUserDataArray1 = readUserData1(L"user1");
    // // printf("skill Num: %d\n", readUserDataArray1->own[0].skillarr[0].idenNum);
    // Userdata *readUserDataArray2 = readUserData1(L"user2");
    // Userdata *readUserDataArray3 = readUserData1(L"user3");
    // if (readUserDataArray1 != NULL) {
    //     // 읽어온 사용자 데이터 출력
    //     wprintf(L"User %d\n", 1);
    //     wprintf(L"Username: %ls\n", readUserDataArray1->username);
    //     wprintf(L"Pokenum: %u\n", readUserDataArray1->pokenum);
    //     wprintf(L"Balance: %u\n", readUserDataArray1->balance);
    //     wprintf(L"Progress: %u\n", readUserDataArray1->progress);
    //     for (int j = 0; j < readUserDataArray1->pokenum; j++) {
    //         wprintf(L"Pokemon %d %ls: %ls\n", readUserDataArray1->own[j].pokedata.idenNum, readUserDataArray1->own[j].pokedata.pokename, readUserDataArray1->own[j].pokename);
    //     }
    //     wprintf(L"\n");
    //     wprintf(L"%d\n", (int)sizeof(PokeList));
    //     // 메모리 해제
    //     free(readUserDataArray1);
    // }
    // if (readUserDataArray2 != NULL) {
    //     // 읽어온 사용자 데이터 출력
    //     wprintf(L"User %d\n", 2);
    //     wprintf(L"Username: %ls\n", readUserDataArray2->username);
    //     wprintf(L"Pokenum: %u\n", readUserDataArray2->pokenum);
    //     wprintf(L"Balance: %u\n", readUserDataArray2->balance);
    //     wprintf(L"Progress: %u\n", readUserDataArray2->progress);
    //     for (int j = 0; j < readUserDataArray2->pokenum; j++) {
    //         wprintf(L"Pokemon %d %ls: %ls\n", readUserDataArray2->own[j].pokedata.idenNum, readUserDataArray2->own[j].pokedata.pokename, readUserDataArray2->own[j].pokename);
    //     }
    //     wprintf(L"\n");
    //     wprintf(L"%d\n", (int)sizeof(PokeList));
    //     // 메모리 해제
    //     free(readUserDataArray2);
    // }
    // if (readUserDataArray3 != NULL) {
    //     // 읽어온 사용자 데이터 출력
    //     wprintf(L"User %d\n", 3);
    //     wprintf(L"Username: %ls\n", readUserDataArray3->username);
    //     wprintf(L"Pokenum: %u\n", readUserDataArray3->pokenum);
    //     wprintf(L"Balance: %u\n", readUserDataArray3->balance);
    //     wprintf(L"Progress: %u\n", readUserDataArray3->progress);
    //     for (int j = 0; j < readUserDataArray3->pokenum; j++) {
    //         wprintf(L"Pokemon %d %ls: %ls\n", readUserDataArray3->own[j].pokedata.idenNum, readUserDataArray3->own[j].pokedata.pokename, readUserDataArray3->own[j].pokename);
    //     }
    //     wprintf(L"\n");
    //     wprintf(L"%d\n", (int)sizeof(PokeList));
    //     // 메모리 해제
    //     free(readUserDataArray3);
    // }

    return 0;
}
