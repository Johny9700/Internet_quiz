#include "GameServer.h"

// #include <unistd.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <errno.h>
// #include <error.h>
// #include <netdb.h>
#include <sstream>


GameServer::GameServer(int num, int time) : questionDatabase("questions.txt"), timeCounter(players)
{
    numOfQuestionsPerGame = num;
    timePerQuestion = time;
}

GameServer::~GameServer()
{
    std::unique_lock<std::mutex> lock(playersVectorLock);
    for(auto p : players)
    {
        NetworkUtils::sendOnSocket(p->clientFd, std::string("99Sorry,\nServer has been turned off"));
        shutdown(p->clientFd, SHUT_RDWR);
        close(p->clientFd);
        delete p;
    }
    players.clear();
    printf("server object destroyed\n"); //WYWAL TO
}

void GameServer::clientThread(int clientFd)
{
    printf("odpalono watek dla clientfd: %i\n", clientFd);
    Player* player;
    bool end = false;

    // get nick from client and save to vector
    while(!end)
    {
        std::string temp = NetworkUtils::readFromSocket(clientFd);
        if(temp.length() < 1)
        {
            printf("removing %d\n", clientFd);
            shutdown(clientFd, SHUT_RDWR);
            close(clientFd);
            end = true;
            break;
        } else
        {
            if(nicknameUnique(temp))
            {
                sendNickCorrect(clientFd, true);
                player = new Player();
                player->clientFd = clientFd;
                player->name = temp;
                player->score = 0;
                player->answeared = false;
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
    while(!end)
    {
        std::string temp = NetworkUtils::readFromSocket(clientFd);
        int currentQuestionScore = timeCounter.getTimeLeft();
        
        if(temp.length() < 1)
        {
            printf("removing %d\n", clientFd);
            removePlayerFromGame(clientFd);
            shutdown(clientFd, SHUT_RDWR);
            close(clientFd);
            end = true;
        } else
        {
            //TODO check if answer correct and add points to score
            printf("dostalem odpowiedz %s\n", temp.c_str());
            if(player->answeared == false && temp[0] == currentQuestion.correct[0])
            {
                player->score += currentQuestionScore;
                player->answeared = true;
                printf("%s udzielił dobrej odpowiedzi, dostaje +%d punktow\n", player->name.c_str(), currentQuestionScore);
            }
            else
            {
                printf("'%c' to nie '%c'", temp[0], currentQuestion.correct[0]);
            }
            
            timeCounter.stop();
            //czytaj tylko jeden znak
        }
    }
    printf("wywalamy watek\n");
}

void GameServer::gameThread()
{
    while(true)
    {
        int questionsLeft = numOfQuestionsPerGame;
        //waiting for first player
        while(players.size() < 1)
        {
            sleep(1);
        }
        //start game after 1 minute
        sleep(10);//TODO set 60, 10 is for testing
        //or wait if there is only one player
        while(players.size() < 2)
        {
            sleep(1);
        }
        sleep(2); //player have same time after choosing nickname
        printf("Rozpoczynamy gre\n");
        while(questionsLeft > 0)
        {
            printf("1\n");
            currentQuestion = questionDatabase.getNextQuestion();
            questionsLeft -= 1;
            printf("2\n");
            broadcastQuestion();
            printf("3\n");
            timeCounter.start(timePerQuestion+10);
            printf("4\n");
            sleep(2);
        }
    }
}

void GameServer::broadcastQuestion()
{
    std::stringstream ss;
    //"`" is delimiter to split in client
    ss << "20" << currentQuestion.question << "`";
    for(int i=0; i<4; i++)
        ss << currentQuestion.choices[i] << "`";
    std::string temp = ss.str();

    printf("broadcastQuestion before mutex\n");
    std::unique_lock<std::mutex> lock(playersVectorLock);
    //TODO send to new players, who joined during answering time
    for(auto p : players)
    {
        printf("broadcastQuestion for loop before send\n");
        int res = NetworkUtils::sendOnSocket(p->clientFd, temp);
        printf("broadcastQuestion for loop after send\n");
        if(res != 0)
        {
            removePlayerFromGame(p->clientFd);
            printf("wywal gracza wewnatrz broadcastQuestion\n");
        }
        printf("broadcastQuestion for loop after if(player socket problem)\n");
    }
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
    printf("imie: '%s' jest ok\n", nickname.c_str());
    return true;
}

void GameServer::removePlayerFromGame(int clientFd)
{
    std::unique_lock<std::mutex> lock(playersVectorLock);
    printf("wywalam gracza z vectora\n");
    for (unsigned int i = 0; i<players.size(); i++) 
    {       
        if(players[i]->clientFd == clientFd)
        {
            printf("Wywalam gracza o fd %d, name: %s\n", players[i]->clientFd, players[i]->name.c_str());
            shutdown(players[i]->clientFd, SHUT_RDWR);
            close(players[i]->clientFd);
            delete players[i];
            players.erase(players.begin() + i);
            break;
        }
    }
}

void GameServer::run(uint16_t port)
{
    printf("server started\n");//WYWAL TO
    // create socket
    servFd = socket(AF_INET, SOCK_STREAM, 0);
    if(servFd == -1) error(1, errno, "socket failed");
    NetworkUtils::setReuseAddr(servFd);

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