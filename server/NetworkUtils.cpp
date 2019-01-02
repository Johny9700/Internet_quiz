#include "NetworkUtils.h"

namespace NetworkUtils
{
    uint16_t readPort(char * txt)
    {
        char * ptr;
        auto port = strtol(txt, &ptr, 10);
        if(*ptr!=0 || port<1 || (port>((1<<16)-1))) error(1,0,"illegal argument %s", txt);
        return port;
    }

    void setReuseAddr(int sock)
    {
        const int one = 1;
        int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
        if(res) error(1,errno, "setsockopt failed");
    }

    int sendOnSocket(int sockFd, std::string message)
    {
        int count = message.length();
        int res = send(sockFd, message.c_str(), count, MSG_DONTWAIT);
        if(res == count)
            return 0;
        else
            return -1;
    }
    
    std::string readFromSocket(int sockFd)
    {
        char buffer[255];
        int count = read(sockFd, buffer, 255);
        if(count < 1)
            return std::string("");
        std::string temp(buffer);
        temp = temp.substr(0, count);

        if(!temp.empty() && temp[temp.length()-1] == '\n')
        {
            //get rid of endline, useful when testing with socat
            temp.erase(temp.length()-1);
        }
        return temp;
    }
}