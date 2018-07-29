#include <string.h>
#include <arpa/inet.h>

#include "client.h"

Client::Client(const char *server, uint16_t port) :
    SERVER(server), PORT(port)
{
    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, server, &server_address.sin_addr);
    server_address.sin_port = htons(port);
}

const char * Client::getResponse()
{
    return buffer;
}
