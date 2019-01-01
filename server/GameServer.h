#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <vector>
#include <thread>
#include <mutex>
#include "Question.h"
#include "QuestionDatabase.h"
#include "Player.h"
#include "TimeCounter.h"

class GameServer
{
private:
    int servFd;
    int numOfQuestionsPerGame;
    int timePerQuestion;
    std::vector<Player*> players;
    std::mutex playersVectorLock;
    QuestionDatabase questionDatabase;
    Question currentQuestion;
    TimeCounter timeCounter;
    void clientThread(int clientFd);
    void gameThread();
    bool nicknameUnique(std::string nickname);
    void removePlayerFromGame(int clientFd);
    void broadcastQuestion();
    void sendNickCorrect(int clientFD, bool correct);
public:
    GameServer(int num, int time);
    ~GameServer();
    void run(uint16_t port);
};

#endif // GAMESERVER_H