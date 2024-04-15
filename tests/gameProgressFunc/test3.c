#include "../../src/everyheader.h"
#include <stdlib.h>
#include <wchar.h>
// #include <ncursesw/curses.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

int main(void ){
    // user2의 정보를 읽고 바꿔보자 
    Item item2= {5,4,3,2,1};
    Userdata * readData = readUserData(L"user1");
    printf("Before: %d\n", readData->item.ball1);
    readData->item = item2;
    saveUserData(readData,EDIT);
    free(readData);

    readData = readUserData(L"user1");
    printf("After: %d\n", readData->item.ball1);
    free(readData);

    return 0;
}