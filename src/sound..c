// #include "../../src/everyheader.h"
#include "../src/everyheader.h"


/* 아마 소리를 첨에 넣는다면 
    soundinit같은 함수로 데이터를 
    배열에다 다 저장해 놓고 할듯?
*/
void * loopSound(void * arg) {
    ALuint buffer, source;
    ALint state;

    // OpenAL 초기화
    ((struct foo*)arg)->x = 0;
    // 오디오 파일 로드
    FILE *file;
    // push1 은 속도 3.5f가 최고
    file = fopen(((struct foo*)arg)->file,"rb");
    // FILE* file = fopen("push3.wav", "rb");
    if (!file) {
        fprintf(stdout,"Failed to open WAV file\n");
        pthread_exit(NULL);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(size);
    if (!data) {
        printf("Failed to allocate memory for WAV data\n");
        fclose(file);
        pthread_exit(NULL);
    }

    fread(data, 1, size, file);
    fclose(file);

    // 오디오 소스 생성 및 속성 설정
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, data, size, 44100);
    free(data);
    // double speed = randomInRange(1,7);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source,AL_PITCH,((struct foo*)arg)->speed); // 속도 (높낮이))
    // 반복 시킬떄 
    alSourcei(source, AL_LOOPING, AL_TRUE);
    // 오디오 재생
    alSourcePlay(source);
    (*(struct foo*)arg).x  = 1;
    // 재생이 완료될 때까지 대기
    do {
        if(((struct foo*)arg)->x == 10) goto EXIT;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    } while (state == AL_PLAYING);
EXIT:
    ((struct foo*)arg)->x = 10;
    // 해제
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    // OpenAL 정리

    // 아마 exit을 다 해주고 쓰래드 결과값정보가 필요없어서 join이 필요없을듯.. 아마.. 
    pthread_exit(NULL);
}

void * singleSound(void * arg) {
    ALuint buffer, source;
    ALint state;

    // OpenAL 초기화
    ((struct foo*)arg)->x = 0;
    // 오디오 파일 로드
    FILE *file;
    // push1 은 속도 3.5f가 최고
    file = fopen(((struct foo*)arg)->file,"rb");
    // FILE* file = fopen("push3.wav", "rb");
    if (!file) {
        fprintf(stdout,"Failed to open WAV file\n");
        pthread_exit(NULL);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(size);
    if (!data) {
        printf("Failed to allocate memory for WAV data\n");
        fclose(file);
        pthread_exit(NULL);
    }

    fread(data, 1, size, file);
    fclose(file);

    // 오디오 소스 생성 및 속성 설정
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, data, size, 44100);
    free(data);
    // double speed = randomInRange(1,7);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source,AL_PITCH,((struct foo*)arg)->speed); // 속도 (높낮이))
    // 오디오 재생
    alSourcePlay(source);
    (*(struct foo*)arg).x  = 1;
    // 재생이 완료될 때까지 대기
    do {
        if(((struct foo*)arg)->x == 10) goto EXIT;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    } while (state == AL_PLAYING);
EXIT:
    ((struct foo*)arg)->x = 10;
    // 해제
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    // OpenAL 정리



    // 아마 exit을 다 해주고 쓰래드 결과값정보가 필요없어서 join이 필요없을듯.. 아마.. 
    pthread_exit(NULL);
}

// 이전 노래랑 똑같은 arg를 쓰는데 arg->x 만 냅두고 나머지 구성요소를 바꿔끼움 
// 일단 만들어놓긴했는데 쓸일이 없지않을까 싶다( 음원 구하기 귀찮음 .. ) 
void * nextSound(void * arg) {
    ALuint buffer, source;
    ALint state;

    // OpenAL 초기화
    ((struct foo*)arg)->x = 0;
    // 오디오 파일 로드
    FILE *file;
    // push1 은 속도 3.5f가 최고
    file = fopen(((struct foo*)arg)->file,"rb");
    // FILE* file = fopen("push3.wav", "rb");
    if (!file) {
        fprintf(stdout,"Failed to open WAV file\n");
        pthread_exit(NULL);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(size);
    if (!data) {
        printf("Failed to allocate memory for WAV data\n");
        fclose(file);
        pthread_exit(NULL);
    }

    fread(data, 1, size, file);
    fclose(file);
    while(((struct foo*)arg)->x != 10) {}   // 이전 노래 끝날때까지 대기 
    // 오디오 소스 생성 및 속성 설정
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, data, size, 44100);
    free(data);
    // double speed = randomInRange(1,7);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source,AL_PITCH,((struct foo*)arg)->speed); // 속도 (높낮이))
    // 반복 시킬떄 
    alSourcei(source, AL_LOOPING, AL_TRUE);
    // 오디오 재생
    alSourcePlay(source);
    (*(struct foo*)arg).x  = 1;
    // 재생이 완료될 때까지 대기
    do {
        if(((struct foo*)arg)->x == 10) goto EXIT;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    } while (state == AL_PLAYING);
EXIT:
    // 해제
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    ((struct foo*)arg)->x = 10;
    // OpenAL 정리

    // 아마 exit을 다 해주고 쓰래드 결과값정보가 필요없어서 join이 필요없을듯.. 아마.. 
    pthread_exit(NULL);
}
