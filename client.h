#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <netinet/in.h>
#include <stdint.h>

class Client
{
public:
    static constexpr int MAX_MESSAGE = 65536;

    Client(const char *, uint16_t);
    virtual ~Client() = default;

    virtual ssize_t send(const char *) = 0;
    virtual ssize_t recv(size_t) = 0;
    const char * getResponse();

private:
    Client();
    Client & operator= (Client&);
    Client(Client&);

protected:
    const char *   SERVER;
    const uint16_t PORT;
    char buffer[MAX_MESSAGE];
    sockaddr_in server_address;
    int server_fd;

};

#endif // CLIENT_H
