#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_func(void *arg) {
    printf("Thread running\n");
    return NULL;
}

int main() {
    pthread_t tid;

    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_detach(tid);

    sleep(1); // d?i thread ch?y xong
    return 0;
}
