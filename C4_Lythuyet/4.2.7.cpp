#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void *handle_client(void *arg) {
    int client = *(int *)arg;

    char msg[] = "Hello Client\n";
    write(client, msg, strlen(msg));

    close(client);
    free(arg);
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    while (1) {
        int *client = malloc(sizeof(int));
        socklen_t len = sizeof(addr);

        *client = accept(server_fd, (struct sockaddr*)&addr, &len);

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client);
        pthread_detach(tid); // tránh leak thread
    }

    return 0;
}
