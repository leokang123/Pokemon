#include <stdio.h>

void story1(){
    printf("STORY1\n");
}
void story2(){
    printf("STORY2\n");
}
void story3(){
    printf("STORY3\n");
}

int main(void) {
    int a;
    scanf("%d", &a);
    switch(a){
        case 1:
            goto S1;
            break;
        case 2:
            goto S2;
            break;
        case 3:
            goto S3;
            break;
        default:
            break;
    }
S1:
    story1();
S2:
    story2();
S3:
    story3();

}