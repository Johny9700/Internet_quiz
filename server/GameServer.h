#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <vector>
#include <thread>
#include <mutex>
#include "Question.h"
#include "QuestionDatabase.h"
#include "Player.h"
#include "TimeCounter.h"
#include "NetworkUtils.h"

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
    int currentQuestionStats[4];
    bool gameIsRunning;
    TimeCounter timeCounter;
    void clientThread(int clientFd);
    void gameThread();
    void sendEndOfGameInfo();
    bool nicknameUnique(std::string nickname);
    void removePlayerFromGame(int clientFd);
    void sendInfoToNewPlayer(int clientFd);
    void broadcastQuestion();
    void broadcastAnswerCount(); // how many players answered question
    void cleanUpBeforeQuestion();
    std::string prepareTop3message();
    void broadcastStats();
    void sendNickCorrect(int clientFD, bool correct);
public:
    GameServer(int num, int time);
    ~GameServer();
    void run(uint16_t port);
};

#endif // GAMESERVER_H