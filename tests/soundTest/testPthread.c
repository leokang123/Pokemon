#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *background_task(void *arg) {
    printf("Background thread started.\n");

    // 백그라운드에서 실행되는 작업 수행
    sleep(3); // 예시로 3초 동안 대기

    printf("Background thread finished.\n");

    // 백그라운드 스레드 종료
    pthread_detach(pthread_self()); // 현재 스레드를 분리하여 종료
    return NULL;
}

int main() {
    pthread_t bg_thread, main_thread;

    // 백그라운드 스레드 생성
    pthread_create(&bg_thread, NULL, background_task, NULL);

    printf("Main thread started.\n");

    // 메인 스레드에서 실행되는 작업 수행
    sleep(1); // 예시로 1초 동안 대기

    printf("Main thread finished.\n");

    // 메인 스레드 종료
    pthread_exit(NULL);

    return 0;
}
