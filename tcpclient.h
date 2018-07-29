#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "client.h"


class TcpClient : public Client
{
public:
    TcpClient(const char *, uint16_t);
    ~TcpClient();

    ssize_t send(const char *);
    ssize_t recv(size_t);

private:

};

#endif // TCPCLIENT_H
