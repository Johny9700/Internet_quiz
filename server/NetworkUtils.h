#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <error.h>
#include <string>

namespace NetworkUtils
{
    // converts cstring to port
    uint16_t readPort(char * txt);
    // sets SO_REUSEADDR
    void setReuseAddr(int sock);
    // sends message on socket and returns 0 for success, -1 for failure
    bool sendOnSocket(int sockFd, std::string message);
    bool readFromSocket(int sockFd, std::string &message);
}

#endif // NETWORKUTILS_H