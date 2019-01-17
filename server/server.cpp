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
#include "NetworkUtils.h"


int main(int argc, char ** argv)
{
    // get and validate port number
    if(argc != 3) error(1, 0, "Need config file and questions file paths");
    
    // // graceful ctrl+c exit
    // signal(SIGINT, ctrl_c); //TODO
    // prevent dead sockets from raising pipe signals on write
    signal(SIGPIPE, SIG_IGN);

    //TODO wczytanie parametrów z pliku albo argv
    GameServer gameServer(argv[1], argv[2]); //num of questions and time per question
    gameServer.run();
}