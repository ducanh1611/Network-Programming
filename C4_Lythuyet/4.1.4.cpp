#include <stdio.h>
#include <unistd.h>

int main() {
    if (fork() == 0) {
        printf("Tien trinh con ket thuc\n");
        _exit(0);
    } else {
        sleep(10); // cha khong wait -> zombie
    }
    return 0;
}
