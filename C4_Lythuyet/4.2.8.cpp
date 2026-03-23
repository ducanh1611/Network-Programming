#include <pthread.h>
#include <stdio.h>

int global = 100;

void *test(void *arg) {
    int local = 10;

    printf("Global: %d, dia chi: %p\n", global, &global);
    printf("Local: %d, dia chi: %p\n", local, &local);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, test, NULL);
    pthread_create(&t2, NULL, test, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
