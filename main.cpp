#include <iostream>
#include <string>
#include <stdint.h>
#include <memory>
#include "udpclient.h"
#include "tcpclient.h"

int main(int argc, char **argv)
{
    std::unique_ptr<Client> client;
    char *server, *type;
    uint16_t port;

    if (argc < 4) {
        printf("Usage: %s <ip> <port> <tcp|udp>\n", argv[0]);
        exit(1);
    }

    server = argv[1];
    port = static_cast<uint16_t>(atoi(argv[2]));
    type = argv[3];

    if (std::string(type) == "udp") {
        client.reset(new UdpClient(server, port));
    }
    else {
        client.reset(new TcpClient(server, port));
    }

    while (true) {
        std::string msg;

        std::cout << "Enter message: ";
        std::getline(std::cin, msg);
        client->send(msg.c_str());

        if (client->recv(msg.length()) < 0)
            std::cout << "No response\n\n";
        else
           std::cout << "Recieved: " << client->getResponse() << "\n\n";
    }

    return 0;
}
