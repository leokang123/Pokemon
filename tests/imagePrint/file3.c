#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>

int main(void) {
    wchar_t str[400] = {0,};
    for (int i = 0; i < 103; i++) {
        wcscat(str, L"⣀"); // 문자열을 L"⣀"으로 변경
    }
    wprintf(L"%s", str); // 출력 형식 지정자를 %ls로 변경
    int a = wcslen(str);
    wprintf(L"\n%d\n", a); // 출력 형식 지정자를 %d로 변경
    char str2[] = "hello";
    int b = strlen(str2);
    printf("%d\n", b);
    return 0;
}