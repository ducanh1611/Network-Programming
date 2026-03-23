#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 5; i++) {
        if (fork() == 0) {
            printf("Tien trinh con %d, PID = %d\n", i, getpid());
            _exit(0);
        }
    }

    for (int i = 0; i < 5; i++) {
        wait(NULL);
    }

    return 0;
}
