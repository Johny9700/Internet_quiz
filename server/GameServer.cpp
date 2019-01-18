#include "GameServer.h"

// #include <unistd.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <errno.h>
// #include <error.h>
// #include <netdb.h>
#include <sstream>
#include <algorithm>


GameServer::GameServer(const char* configPath, const char* questionsFilePath): questionDatabase(questionsFilePath), configuration(configPath), timeCounter()
{
    gameIsRunning = false;
    timeForAnswering = false;
}

GameServer::~GameServer()
{
    std::unique_lock<std::mutex> lock(playersVectorLock);
    for(auto p : players)
    {
        NetworkUtils::sendOnSocket(!p->deadSocket && p->clientFd, std::string("99Sorry,\nServer has been turned off"));
        shutdownAndClose(p->clientFd);
        delete p;
    }
    players.clear();
    printf("server object destroyed\n");
}

void GameServer::clientThread(int clientFd)
{
    printf("Started thread for clientfd: %i\n", clientFd);
    Player* player;
    bool end = false;

    // get nick from client and save to vector
    while(!end)
    {
        std::string message;
        if(NetworkUtils::readFromSocket(clientFd, message) == false)
        {
            printf("removing %d\n", clientFd);
            shutdown(clientFd, SHUT_RDWR);
            close(clientFd);
            end = true;
            break;
        } else
        {
            if(nicknameUnique(message))
            {
                if(sendNickCorrect(clientFd, true) == false)
                {
                    shutdownAndClose(clientFd);
                    end = true;
                    break;
                }
                player = new Player();
                player->clientFd = clientFd;
                player->name = message;
                player->score = 0;
                player->answeared = false;
                player->currentPoints = 0;
                player->deadSocket = false;
                std::unique_lock<std::mutex> lock(playersVectorLock);
                players.push_back(player);
                cv.notify_one();
                if(gameIsRunning && timeForAnswering)
                {
                    sendInfoToNewPlayer(player);
                }
                break;
            }
            else
            {
                if(sendNickCorrect(clientFd, false) == false)
                {
                    shutdownAndClose(clientFd);
                    end = true;
                }
            }
        }
    }
    
    //getting answers from players here
    while(!end)
    {
        if(player == nullptr)
        {
            printf("NULL PLAYER!!!!");
            break;
        }
        std::string answer;
        if(NetworkUtils::readFromSocket(clientFd, answer) == false)
        {
            printf("removing %d\n", clientFd);
            std::unique_lock<std::mutex> lock(playersVectorLock);
            removePlayerFromGame(clientFd);
            countAnswers();
            end = true;
        } else
        {
            int currentQuestionScore = timeCounter.getTimeLeft();
            printf("dostalem odpowiedz %s\n", answer.c_str());
            if(timeForAnswering == true)
            {
                std::unique_lock<std::mutex> lock(playersVectorLock);
                if(player->answeared == false && answer[0] == currentQuestion.correct[0])
                {
                    player->currentPoints = currentQuestionScore;
                    player->score += currentQuestionScore;
                    printf("%s udzielił dobrej odpowiedzi, dostaje +%d punktow\n", player->name.c_str(), currentQuestionScore);
                }
                player->answeared = true;
                currentQuestionStats[(int)(answer[0]-'A')] += 1;
                broadcastAnswerCount();
            }
            else
            {
                printf("ale to nie czas na odpowidź wiec ignoruje\n");
            }
        }
    }
    printf("removing clientFd: %i thread\n", clientFd);
}

void GameServer::gameThread()
{
    sleep(configuration.getTimeBeforeFirstGame());
    while(true)
    {
        int questionsLeft = configuration.getNumOfQuestionsPerGame();

        printf("waiting for first player...\n");
        std::unique_lock<std::mutex> lock(playersVectorLock);
        cv.wait(lock, [this]{return players.size()>0;});
        lock.unlock();
        
        sleep(configuration.getTimeBetweenEachGame());

        //or wait if there is only one player
        lock.lock();
        cv.wait(lock, [this]{return players.size()>1;});
        printf("OK, have enough players\n");
        resetPlayersScores();
        lock.unlock();

        printf("Starting game in 2 seconds...\n");
        sleep(2); //give last player time after choosing nickname
        timeCounter.setTime(configuration.getTimePerQuestion());
        gameIsRunning = true;
        while(questionsLeft > 0)
        {
            cleanUpBeforeQuestion();
            printf("1 getNextQuestion\n");
            currentQuestion = questionDatabase.getNextQuestion();
            questionsLeft -= 1;
            timeCounter.setTime(configuration.getTimePerQuestion());
            printf("2 broadcastQuestion\n");
            broadcastQuestion();
            printf("3 startTimer\n");
            timeForAnswering = true;
            timeCounter.start();
            timeForAnswering = false;
            printf("4 end of question, send stats\n");
            broadcastStats();
            printf("<<<<<<waiting 5 seconds>>>>>>\n");
            sleep(5);
        }
        gameIsRunning = false;
        sendEndOfGameInfo();
    }
}

void GameServer::sendEndOfGameInfo()
{
    std::string message("24");
    std::unique_lock<std::mutex> lock(playersVectorLock);
    broadcastMessage(message);
}

std::string GameServer::prepareMessageWithQuestionAndChoices()
{
    std::string temp;
    std::stringstream ss;
    //"`" is delimiter to split in client
    ss << "20" << currentQuestion.question << "`";
    for(int i=0; i<4; i++)
        ss << currentQuestion.choices[i] << "`";
    temp = ss.str();

    return temp;
}

void GameServer::sendInfoToNewPlayer(Player* player) // mutex locked when this method is called
{  
    std::string temp = prepareMessageWithQuestionAndChoices();
    int clientFd = player->clientFd;

    if(!player->deadSocket && NetworkUtils::sendOnSocket(clientFd, temp) == false)
    {
        shutdownAndClose(clientFd);
        player->deadSocket = true;
        return;
    }


    temp = std::string("21") + std::to_string(timeCounter.getTimeLeft());
    if(!player->deadSocket && NetworkUtils::sendOnSocket(clientFd, temp) == false)
    {
        shutdownAndClose(clientFd);
        player->deadSocket = true;
        return;
    }

    std::string prefix("25");
    temp = prefix + countAnswers();
    if(!player->deadSocket && NetworkUtils::sendOnSocket(clientFd, temp) == false)
    {
        shutdownAndClose(clientFd);
        player->deadSocket = true;
        return;
    }
}

void GameServer::broadcastMessage(std::string const& message)
{
    for(auto p : players)
    {
        if(!p->deadSocket && NetworkUtils::sendOnSocket(p->clientFd, message) == false)
        {
            shutdownAndClose(p->clientFd);
            p->deadSocket = true;
        }
    }
}

void GameServer::broadcastQuestion()
{
    std::string temp = prepareMessageWithQuestionAndChoices();
    int time = timeCounter.getTimeLeft();
    std::string prefix("21"); //prefix for client app
    std::string timeMessage = prefix + std::to_string(time);

    std::unique_lock<std::mutex> lock(playersVectorLock);
    broadcastMessage(temp);
    broadcastMessage(timeMessage);
}

std::string GameServer::countAnswers()
{
    unsigned int count = 0;
    for(auto p : players)
    {
        if(p->answeared == true)
            count += 1;
    }
    if(count == players.size())
    {
        timeCounter.stop();
        timeForAnswering = false;
    }
    return std::to_string(count);
}

void GameServer::broadcastAnswerCount()
{
    std::string prefix("25");
    std::string message = prefix + countAnswers();
    broadcastMessage(message);
}

void GameServer::resetPlayersScores()
{
    for(auto p : players)
    {
        p->score = 0;
    }
}

void GameServer::cleanUpBeforeQuestion()
{
    for(int i=0; i<4; i++)
        currentQuestionStats[i] = 0;
    std::unique_lock<std::mutex> lock(playersVectorLock);
    for(auto p : players)
    {
        p->answeared = false;
        p->currentPoints = 0;
    }
}

std::string GameServer::prepareTop3message()
{
    std::stringstream ss;
    ss << "30";
    int numOfPlayers = players.size();

    if(numOfPlayers < 1)
    {
        ss << " --" << " --" << " --" << " --" << " --" << " --";
    }
    else if(numOfPlayers < 2)
    {
        ss << players[0]->name << ": " << players[0]->score << " --" << " --" << " --" << " --";
    }
    else
    {
        std::sort(players.begin(), players.end(), [](Player *a, Player *b) {return a->score > b->score; });
        if(numOfPlayers < 3)
        {
            ss << players[0]->name << ": " << players[0]->score << " ";
            ss << players[1]->name << ": " << players[1]->score << " ";
            ss << "--" << " --";
        }
        else
        {
            ss << players[0]->name << ": " << players[0]->score << " ";
            ss << players[1]->name << ": " << players[1]->score << " ";
            ss << players[2]->name << ": " << players[2]->score;
        }
    }
    //Formatting nick1: score1 nick2: score2 nick3: score3
    //or --: -- if less than 3 players
    std::string message = ss.str();
    return message;
}

void GameServer::broadcastStats()
{
    //Prepate common message for all players
    std::stringstream ss;
    ss << "23";
    for(int i=0; i<4; i++)
        ss << (char)('A'+i) << ": " << currentQuestionStats[i] << "        ";
    std::string forAllPlayers = ss.str();

    std::unique_lock<std::mutex> lock(playersVectorLock);
    std::string messageTop3 = prepareTop3message();
    for(auto p : players)
    {
        //Send Answer stats and points for this question
        std::string forThisPlayer = forAllPlayers;
        forThisPlayer += std::string("\nCorrect answer was: ");
        forThisPlayer += currentQuestion.correct;
        forThisPlayer += std::string("\nYou got ");
        forThisPlayer += std::to_string(p->currentPoints);
        forThisPlayer += std::string(" for this question\n");
        
        if(!p->deadSocket && NetworkUtils::sendOnSocket(p->clientFd, forThisPlayer) == false)
        {
            shutdownAndClose(p->clientFd);
            p->deadSocket = true;
        }
        
        //Send total score
        forThisPlayer = std::string("22") + std::to_string(p->score);
        if(!p->deadSocket && NetworkUtils::sendOnSocket(p->clientFd, forThisPlayer) == false)
        {
            shutdownAndClose(p->clientFd);
            p->deadSocket = true;
        }

        //Send top3
        if(!p->deadSocket && NetworkUtils::sendOnSocket(p->clientFd, messageTop3) == false)
        {
            shutdownAndClose(p->clientFd);
            p->deadSocket = true;
        }
    }
}

bool GameServer::sendNickCorrect(int clientFD, bool correct)
{
    std::string message;
    if(correct)
        message = "10";
    else
        message = "11";
    if(NetworkUtils::sendOnSocket(clientFD, message) == false)
    {
        return false;
    }
     return true;   
}

bool GameServer::nicknameUnique(std::string nickname)
{
    printf("checking if name is unique: '%s'\n", nickname.c_str());
    std::unique_lock<std::mutex> lock(playersVectorLock);
    for(auto p : players)
    {
        if(p->name == nickname)
        {
            printf("name: %s is already used by other player\n", nickname.c_str());
            return false;
        }
    }
    printf("name: '%s' is ok\n", nickname.c_str());
    return true;
}

void GameServer::shutdownAndClose(int clientFd)
{
    shutdown(clientFd, SHUT_RDWR);
    close(clientFd);
}

void GameServer::removePlayerFromGame(int clientFd)
{
    for (unsigned int i = 0; i<players.size(); i++)
    {       
        if(players[i]->clientFd == clientFd)
        {
            printf("Removing player clientFd %d, name: %s\n", players[i]->clientFd, players[i]->name.c_str());
            if(!players[i]->deadSocket)
            {
                shutdownAndClose(clientFd);
            }
            delete players[i];
            players[i] = nullptr;
            players.erase(players.begin() + i);
            break;
        }
    }
}

void GameServer::run()
{
    printf("server started\n");
    // read port
    auto port = NetworkUtils::readPort(configuration.getPort());
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
    printf("server stopped\n");
}
