#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "tcpclient.h"

ssize_t TcpClient::send(const char * msg)
{
    ssize_t len = ::send(server_fd, msg, strlen(msg), 0);
    printf("sent to %s:%d\n", SERVER, PORT);
    return len;
}

ssize_t TcpClient::recv(size_t len)
{
    ssize_t msglen = 0;
    bzero(buffer, sizeof(buffer));
    msglen = ::recv(server_fd, buffer, MAX_MESSAGE, 0);
    if (msglen > 0) buffer[msglen] = '\0';
    return msglen;
}

TcpClient::TcpClient(const char *server, const uint16_t port) :
    Client(server, port)
{
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            printf("could not create socket\n");
            exit(1);
        }
        struct timeval tv;
        tv.tv_sec = 3;
        tv.tv_usec = 0; //
        setsockopt(server_fd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv));
        int optval = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval));

        if (connect(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
            perror("connect error");
            exit(1);
        }
}

TcpClient::~TcpClient()
{
    close(server_fd);
}

