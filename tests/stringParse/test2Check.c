#include <stdio.h>

int main(void) {
    FILE * file = fopen("test.bin","rb+");
    rewind(file);
    int count;
    fread(&count,sizeof(int),1,file); // 2 읽음 
    printf("%d\n", count);
    count = 10 ;
    fseek(file,0,SEEK_SET);
    fwrite(&count,sizeof(int),1,file);
    fclose(file);
    FILE * file3 = fopen("test.bin","rb"); 
    // fseek(file3,0,SEEK_END);
    fread(&count,sizeof(int),1,file3);
    fclose(file3);
    printf("%d\n",count);
    return 0;


}