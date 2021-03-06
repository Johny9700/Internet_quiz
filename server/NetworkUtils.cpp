#include "NetworkUtils.h"

namespace NetworkUtils
{
    uint16_t readPort(std::string txt)
    {
        char * ptr;
        auto port = strtol(txt.c_str(), &ptr, 10);
        if(*ptr!=0 || port<1 || (port>((1<<16)-1))) error(1,0,"illegal argument %s", txt.c_str());
        return port;
    }

    void setReuseAddr(int sock)
    {
        const int one = 1;
        int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
        if(res) error(1,errno, "setsockopt failed");
    }

    bool sendOnSocket(int sockFd, std::string const& message)
    {
        std::string messageWithDelimiter = message + std::string("%^&"); ///%^& - end of message
        int count = messageWithDelimiter.length();
        int res = send(sockFd, messageWithDelimiter.c_str(), count, MSG_DONTWAIT);
        if(res == count)
            return true;
        else
        {
            printf("Wysylanie nie powiodlo sie\n");
            return false;
        }
            
    }
    
    bool readFromSocket(int sockFd, std::string &message)
    {
        char buffer[255];
        std::string temp("");
        printf("NetworkUtlils reading...\n");
        do
        {
            int count = read(sockFd, buffer, 255);
            printf("NetworkUtils get some message\n");
            if(count < 1)
            {
                message = "";
                printf("NetworkUtils read return false\n");
                return false;
            }
            
            std::string receivedData(buffer);
            receivedData = receivedData.substr(0, count);
            temp += receivedData;
        } while(temp.substr(temp.size()-3) != std::string("%^&"));
        

        if(!temp.empty() && temp[temp.length()-1] == '\n')
        {
            //get rid of endline, useful when testing with socat
            temp.erase(temp.length()-1);
        }
        message = temp.substr(0, temp.size()-3);
        return true;
    }
}