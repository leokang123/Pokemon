#include <stdio.h>

int main(void) {
    FILE * file = fopen("test.bin","ab");
    int count = 2; 
    fwrite(&count,sizeof(int),1,file);
    fclose(file);
    file = fopen("test.bin","ab");
    count = 3; 
    fwrite(&count,sizeof(int),1,file);
    fclose(file);
    return 0;
}