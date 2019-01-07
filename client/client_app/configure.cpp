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
        addr = "127.0.0.1";
        port = "8000";
    }
}

std::string configure::getAddr(){
    return addr;
}

std::string configure::getPort(){
    return port;
}
