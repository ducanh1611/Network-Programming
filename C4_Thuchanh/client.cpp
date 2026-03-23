#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[256];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    for (int i = 0; i < 10; i++) {
        recv(sock, buffer, sizeof(buffer), 0);
        printf("\n%s\n", buffer);

        for (int j = 0; j < 4; j++) {
            recv(sock, buffer, sizeof(buffer), 0);
            printf("%d. %s\n", j, buffer);
        }

        int answer;
        printf("Nhap dap an (0-3): ");
        scanf("%d", &answer);

        send(sock, &answer, sizeof(answer), 0);
    }

    int score;
    recv(sock, &score, sizeof(score), 0);

    printf("Diem cua ban: %d/10\n", score);

    close(sock);
    return 0;
}
