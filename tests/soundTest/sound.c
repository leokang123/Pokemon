#include <stdio.h>
#include <unistd.h>
/*
    콘솔에서만 소리가 남 
*/
int main(void) {
    fprintf(stdout, "\aB!\n" );
    usleep(100000);
    fprintf(stdout, "\aBe!\n" );
    usleep(100000);
    fprintf(stdout, "\aBee!\n" );
    usleep(100000);
    fprintf(stdout, "\aBeep!\n" );
    usleep(100000);
    fprintf(stdout, "\aBeep!!\n" );
    usleep(100000);
    return 0;
}