#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 100

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <IP> <port>\n", argv[0]);
        exit(-1);
    }

    int clientfd, port;
    char *host, *port_str, buf[MAXLINE];

    host = argv[1];
    port_str = argv[2];
    port = atoi(port_str);

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0)
    {
        perror("Error 'socket'\n");
        exit(-1);
    }

    // struct addrinfo *p, *listp, hints;

    struct sockaddr_in server_addr;
    socklen_t addr_size;
    int n;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(host);
    server_addr.sin_port = htons(port);

    if (connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error 'connect'\n");
        close(clientfd);
        exit(-1);
    }

    ssize_t nread = recv(clientfd, buf, sizeof(buf), 0);
    if (nread < 0)
    {
        perror("Error 'recv'\n");
        close(clientfd);
        exit(-1);
    }

    buf[nread] = '\0';
    printf("Message received from server: %s\n", buf);
    close(clientfd);
    return 1;
}