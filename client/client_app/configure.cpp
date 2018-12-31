#include "configure.h"

configure::configure()
{
    setConfiguration();
}

void configure::setConfiguration(){
    configfile.open("files/config.txt");
    if(configfile.is_open()){
        std::getline(configfile, addr);
        std::getline(configfile, port);
        configfile.close();
    }
    else{
        addr = "123";
        port = "888000";
    }
}

std::string configure::getAddr(){
    return addr;
}

std::string configure::getPort(){
    return port;
}
