#include "GameServer.h"

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sstream>


void setReuseAddr(int sock)//WYWAL TO, znaczy gdzie indziej zaimplementuj
{
    const int one = 1;
    int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(res) error(1,errno, "setsockopt failed");
}


GameServer::GameServer(int num, int time) : questionDatabase("questions.txt"), timeCounter(players)
{
    numOfQuestionsPerGame = num;
    timePerQuestion = time;
}

GameServer::~GameServer()
{
    std::unique_lock<std::mutex> lock(playersVectorLock);
    for(auto player : players)
    {
        //TODO send message server has been turned off
        //shutdown and close
        shutdown(player->clientFd, SHUT_RDWR);
        close(player->clientFd);
        delete player;
    }
    players.clear();
    printf("server object destroyed\n"); //WYWAL TO
}

void GameServer::clientThread(int clientFd)
{
    printf("odpalono watek dla clientfd: %i\n", clientFd);
    Player* player;
    char buffer[255];
    bool end = false;

    // get nick from client and save to vector
    while(!end)
    {
        int count = read(clientFd, buffer, 255);
        if(count < 1)
        {
            printf("removing %d\n", clientFd);
            shutdown(clientFd, SHUT_RDWR);
            close(clientFd);
            end = true;
            break;
        } else
        {
            std::string temp = buffer;
            temp = temp.substr(0, count);
            if(nicknameUnique(temp))
            {
                sendNickCorrect(clientFd, true);
                player = new Player();
                player->clientFd = clientFd;
                player->name = temp;
                player->score = 0;
                std::unique_lock<std::mutex> lock(playersVectorLock);
                players.push_back(player);
                break;
            }
            else
            {
                sendNickCorrect(clientFd, false);
            }
        }
    }
    
    //communication during game
    while(!end){
        int count = read(clientFd, buffer, 255);
        
        if(count < 1) {
            printf("removing %d\n", clientFd);
            removePlayerFromGame(clientFd);
            shutdown(clientFd, SHUT_RDWR);
            close(clientFd);
            break;
        } else {
            //TODO check if answer correct and add points to score
            printf("dostalem odpowiedz %s\n", buffer);
            //czytaj tylko jeden znak
        }
    }
    printf("wywalamy watek\n");
}

void GameServer::gameThread()
{
    while(players.size() < 2)
    {
        sleep(1);
        //TODO rozpoczynamy po minucie od pierwszego albo czekamy aż będzie dwóch
    }
    printf("Rozpoczynamy gre\n");
    while(true)
    {
        currentQuestion = questionDatabase.getNextQuestion();
        broadcastQuestion();
        timeCounter.start(timePerQuestion);
        sleep(100);
    }

}

void GameServer::broadcastQuestion()
{
        int res;
        std::stringstream ss;
        //"`" is delimiter to split in client
        ss << "20" << currentQuestion.question << "`";
        for(int i=0; i<4; i++)
            ss << currentQuestion.choices[i] << "`";
        std::string temp = ss.str();

        const char *questionText = temp.c_str();
        const int questionTextLen = temp.length();

        std::vector<int> bad;
        std::unique_lock<std::mutex> lock(playersVectorLock);
        //TODO send to new players, who joined during answering time
        for(auto p : players)
        {
            res = send(p->clientFd, questionText, questionTextLen, MSG_DONTWAIT);
            if(res!=questionTextLen)
                bad.push_back(p->clientFd);
        }
        //TODO usuwanie graczy ktorym padlo polaczenie
}

void GameServer::sendNickCorrect(int clientFD, bool correct)
{
    std::string message;
    if(correct)
        message = "10";
    else
        message = "11";
    send(clientFD, message.c_str(), 2, MSG_DONTWAIT);
    return;
}

bool GameServer::nicknameUnique(std::string nickname)
{
    printf("sprawdzam imie: %s\n", nickname.c_str());
    std::unique_lock<std::mutex> lock(playersVectorLock);
    for(auto p : players)
    {
        if(p->name == nickname)
        {
            printf("imie: %s jest zajete\n", nickname.c_str());
            return false;
        }
    }
    printf("imie: %s jest ok\n", nickname.c_str());
    return true;
}

void GameServer::removePlayerFromGame(int clientFd)
{
    std::unique_lock<std::mutex> lock(playersVectorLock);
    printf("wywalam gracza z vectora\n");
    // for (int i = 0; i<players.size(); i++) 
    // {       
    //     delete players[i];    
    // }    
    // a.clear();
    //TODO
}

void GameServer::run(uint16_t port)
{
    printf("server started\n");//WYWAL TO
    // create socket
    servFd = socket(AF_INET, SOCK_STREAM, 0);
    if(servFd == -1) error(1, errno, "socket failed");
    setReuseAddr(servFd);

    // bind to any address and port provided in arguments
    sockaddr_in serverAddr{.sin_family=AF_INET, .sin_port=htons((short)port), .sin_addr={INADDR_ANY}};
    int res = bind(servFd, (sockaddr*) &serverAddr, sizeof(serverAddr));
    if(res) error(1, errno, "bind failed");
    
    // enter listening mode
    res = listen(servFd, 1);
    if(res) error(1, errno, "listen failed");

    std::thread(&GameServer::gameThread, this).detach();

    while(true)
    {
        // prepare placeholders for client address
        sockaddr_in clientAddr{};
        socklen_t clientAddrSize = sizeof(clientAddr);
        
        // accept new connection
        auto clientFd = accept(servFd, (sockaddr*) &clientAddr, &clientAddrSize);
        if(clientFd == -1) error(1, errno, "accept failed");
        
        // tell who has connected
        printf("new connection from: %s:%hu (fd: %d)\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);

        std::thread(&GameServer::clientThread, this, clientFd).detach();
    }
    printf("server stopped\n");//WYWAL TO
}