#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAXLINE 1024
int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    char ip[50];
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    printf("Nhap IP cua server: ");
    scanf("%s", ip);
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Nhap vao message: ");
    getchar();
    fgets(sendline, MAXLINE, stdin);
    write(sockfd, sendline, strlen(sendline));
    n = read(sockfd, recvline, MAXLINE);
    recvline[n] = '\0';
    printf("Server reply: %s\n", recvline);
    close(sockfd);
    return 0;
}
