#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

int main(void) {
    wchar_t str[] = L"123456789ABCDEF";
    // wchar_t temp[100];
    // wcsncpy(temp,str,5);

    wchar_t * temp = str;
    temp += 3;
    wprintf(L"temp: %ls\n",temp);
    return 0;
}