#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "client.h"
#include <stdint.h>

class UdpClient : public Client
{
public:    
    UdpClient(const char *, uint16_t);
    ~UdpClient();

    ssize_t send(const char *);
    ssize_t recv(size_t);

private:

};

#endif // UDPCLIENT_H
