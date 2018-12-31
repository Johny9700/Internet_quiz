#ifndef CONFIGURE_H
#define CONFIGURE_H
#include <fstream>
#include <iostream>
#include <string>

class configure
{
private:
    std::string addr;
    std::string port;
    std::ifstream configfile;

public:
    configure();
    std::string getAddr();
    std::string getPort();
    void setConfiguration();
};

#endif // CONFIGURE_H
