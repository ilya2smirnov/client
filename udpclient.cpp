#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "udpclient.h"

ssize_t UdpClient::send(const char * msg)
{
    ssize_t len =
        sendto(server_fd, msg, strlen(msg), 0,
               (struct sockaddr*)&server_address, sizeof(server_address));

    printf("sent to %s:%d\n", SERVER, PORT);
    return len;
}

ssize_t UdpClient::recv(size_t len)
{
    struct sockaddr_in recv_from;
    socklen_t recv_len = 0;
    ssize_t msglen = recvfrom(server_fd, buffer, len,
                               0, (struct sockaddr *)&recv_from, &recv_len);

    if (msglen > 0) buffer[msglen] = '\0';
    return msglen;
}

UdpClient::UdpClient(const char *server, const uint16_t port) :
    Client(server, port)
{
        server_fd = socket(PF_INET, SOCK_DGRAM, 0);
        if (server_fd < 0) {
            printf("could not create socket\n");
            exit(1);
        }
        struct timeval tv;
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        if (setsockopt(server_fd, SOL_SOCKET, SO_RCVTIMEO, &tv,sizeof(tv)) < 0) {
            perror("setsockopt error");
        }
}

UdpClient::~UdpClient()
{
    close(server_fd);
}

