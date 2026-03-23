#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    if (fork() == 0) {
        printf("Child process exit\n");
        _exit(0);
    } else {
        sleep(5);
        wait(NULL);
        printf("Da thu gom zombie\n");
    }
    return 0;
}
