#include <stdio.h>
#include <unistd.h>

int main() {
    if (fork() == 0) {
        printf("Child process exit\n");
        _exit(0);
    } else {
        sleep(30); // không wait ? zombie
    }
    return 0;
}
