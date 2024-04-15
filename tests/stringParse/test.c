#include <stdio.h>
#include <string.h>

int main(void) {
    char str[] = "hello world";
    char str2[] = "world";
    char *point;
    point = strstr(str,str2);
    printf("%d", (int)(str - point));
    return 0;
}