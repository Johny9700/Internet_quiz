#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <thread>
#include <mutex>
#include <unordered_set>
#include <signal.h>

#include "GameServer.h"


// converts cstring to port
uint16_t readPort(char * txt);



int main(int argc, char ** argv)
{
    // get and validate port number
    if(argc != 2) error(1, 0, "Need 1 arg (port)");
    auto port = readPort(argv[1]);

    // // graceful ctrl+c exit
    // signal(SIGINT, ctrl_c); //TODO
    // prevent dead sockets from raising pipe signals on write
    signal(SIGPIPE, SIG_IGN);

    //TODO wczytanie parametrów z pliku albo argv
    GameServer gameServer(5,30);
    gameServer.run(port);
}

uint16_t readPort(char * txt)
{
    char * ptr;
    auto port = strtol(txt, &ptr, 10);
    if(*ptr!=0 || port<1 || (port>((1<<16)-1))) error(1,0,"illegal argument %s", txt);
    return port;
}