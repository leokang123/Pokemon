#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POKEMON 4

typedef struct {
    unsigned int idenNum;
    char pokename[20];
    char type[10];
    unsigned int level;
    unsigned int health;
    unsigned int skillNum;
    int skillarr[10];
} PokeData;

typedef struct {
    char username[20]; // 유저 이름 추가
    unsigned int balance;
    unsigned int progress;
    unsigned int pokenum;
    PokeData own[MAX_POKEMON];
    struct {
        unsigned int heal;
        unsigned int drug;
        unsigned int ball1;
        unsigned int ball2;
        unsigned int ball3;
    } item;
} Userdata;

Userdata *getUserData(const char *filename, const char *username) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    // 구조체의 총 개수를 파일로부터 읽어옴
    int count;
    fread(&count, sizeof(int), 1, file);
    printf("%d\n",count);
    Userdata *userData = (Userdata*)malloc(sizeof(Userdata));
    // 파일로부터 구조체 데이터를 읽어옴
    for (int i = 0; i < count; i++) {
        fread(userData, sizeof(Userdata), 1, file);
        if (strcmp(userData->username, username) == 0) {
            fclose(file);
            return userData;
        }
    }
    fclose(file);
    return NULL;
}

int main() {
    const char *filename = "userdata.bin";
    const char *username = "leokang"; // 찾고자 하는 사용자 이름

    Userdata *userData = getUserData(filename, username);
    
    if (userData != NULL) {
        printf("User found!\n");
        printf("Username: %s\n", userData->username);
        printf("Pokenum: %u\n", userData->pokenum);
        printf("Balance: %u\n", userData->balance);
        printf("Progress: %u\n", userData->progress);
        // 포켓몬 데이터 출력
        for (int i = 0; i < userData->pokenum; i++) {
            printf("Pokemon %d: %s\n", i + 1, userData->own[i].pokename);
        }
    } else {
        printf("User '%s' not found.\n", username);
    }

    return 0;
}
