#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "192.168.1.1", &addr.sin_addr) <= 0) {
        printf("Invalid IP address\n");
        return -1;
    }
    printf("Sockaddr_in initialized successfully\n");
    printf("Address Family : AF_INET (IPv4)\n");
    printf("Port           : %d\n", ntohs(addr.sin_port));
    printf("IP Address     : 192.168.1.1\n");
    return 0;
}
