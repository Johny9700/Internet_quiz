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
    if(argc != 3) error(1, 0, "Need config file and questions file paths");
    
    // prevent dead sockets from raising pipe signals on write
    signal(SIGPIPE, SIG_IGN);

    GameServer gameServer(argv[1], argv[2]);
    gameServer.run();
}
