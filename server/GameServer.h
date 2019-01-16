#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
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
    std::condition_variable cv;
    QuestionDatabase questionDatabase;
    Question currentQuestion;
    int currentQuestionStats[4];
    std::atomic<bool> gameIsRunning;
    std::atomic<bool> timeForAnswering;
    TimeCounter timeCounter;
    void clientThread(int clientFd);
    void gameThread();
    void sendEndOfGameInfo();
    bool nicknameUnique(std::string nickname);
    void shutdownAndClose(int clientFd);
    void removePlayerFromGame(int clientFd);
    std::string prepareMessageWithQuestionAndChoices();
    void sendInfoToNewPlayer(Player* player);
    void broadcastMessage(std::string const& message);
    void broadcastQuestion();
    std::string countAnswers();// how many players answered question
    void broadcastAnswerCount(); 
    void resetPlayersScores();
    void cleanUpBeforeQuestion();
    std::string prepareTop3message();
    void broadcastStats();
    bool sendNickCorrect(int clientFD, bool correct);
public:
    GameServer(int num, int time);
    ~GameServer();
    void run(uint16_t port);
};

#endif // GAMESERVER_H