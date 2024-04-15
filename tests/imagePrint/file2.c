#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, ""); // 현재 로케일을 설정하여 멀티바이트 문자열을 wchar_t로 변환할 수 있도록 함

    char buffer[2048] ={0,};
    wchar_t buffer2[2048] = {0,};
    wchar_t str[2048] = {0,};
    char real_buffer[2048] = {0,};
    int teminal_len = 103;
    int image_len = 0;
    FILE * filep = fopen("file.txt","r");
    while(fgets(buffer,sizeof(buffer),filep) != NULL) {
        mbstowcs(buffer2, buffer, 200); // 멀티바이트 문자열을 wchar_t로 변환
        image_len = wcslen(buffer2);
        if(image_len <= 110) {
            memset(str,0,sizeof(str));
            wchar_t space[2] = L" "; // 공백을 나타내는 wchar_t 배열
            for (int i = 0; i < 50; i++) wcscat(str, space); // 공백 추가
            wcscat(str,buffer2);
        }
        // printf("%d\n",image_len);
        wprintf(L"%ls",str);
        usleep(8888);
    }
    fclose(filep);
    // for(int i = 0 ; i < 10;i++) printf("\n");
    return 0;
}