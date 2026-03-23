#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

#define PORT 8080

typedef struct {
    char question[256];
    char options[4][100];
    int correct;
} Quiz;

Quiz quiz[10] = {
    {"2+2=?", {"1","2","3","4"}, 3},
    {"3+3=?", {"5","6","7","8"}, 1},
    {"5-2=?", {"2","3","4","5"}, 1},
    {"10/2=?", {"3","4","5","6"}, 2},
    {"7+1=?", {"6","7","8","9"}, 2},
    {"9-3=?", {"5","6","7","8"}, 1},
    {"6*2=?", {"10","11","12","13"}, 2},
    {"8/2=?", {"2","3","4","5"}, 2},
    {"1+9=?", {"8","9","10","11"}, 2},
    {"5+5=?", {"9","10","11","12"}, 1}
};

void handle_client(int client) {
    int score = 0;
    char buffer[256];

    for (int i = 0; i < 10; i++) {
        send(client, quiz[i].question, strlen(quiz[i].question), 0);

        for (int j = 0; j < 4; j++) {
            send(client, quiz[i].options[j], strlen(quiz[i].options[j]), 0);
        }

        int answer;
        recv(client, &answer, sizeof(answer), 0);

        if (answer == quiz[i].correct) {
            score++;
        }
    }

    send(client, &score, sizeof(score), 0);
    close(client);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    signal(SIGCHLD, SIG_IGN); // tránh zombie

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&addr, &addr_len);

        if (fork() == 0) {
            close(server_fd);
            handle_client(client_fd);
            exit(0);
        }

        close(client_fd);
    }

    return 0;
}
