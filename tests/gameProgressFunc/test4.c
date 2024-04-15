#include <stdio.h>

// 매크로는 컴파일타임동안 결정되는겨라 매크로 함수매개변수 부분에 지역변수나 다른 변수를 쓸수 없다 
#define I_BASE_CONCAT(x,y) x ## y
#define I_CONCAT(x,y) I_BASE_CONCAT(x,y)

int main(int argc, char *argv[])
{
    int a = 1;
    int b = 2; 
    I_CONCAT(a,b);

}