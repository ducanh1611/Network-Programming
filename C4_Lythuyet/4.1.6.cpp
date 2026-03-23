#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&addr, &addr_len);

        if (fork() == 0) {
            close(server_fd);
            write(client_fd, "Hello Client\n", 13);
            close(client_fd);
            exit(0);
        }
        close(client_fd);
    }

    return 0;
}
