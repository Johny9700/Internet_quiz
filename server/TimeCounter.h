#ifndef TIMECOUNTER_H
#define TIMECOUNTER_H

#include <thread>
#include <vector>
#include <string>
#include "Player.h"
#include "NetworkUtils.h"

class TimeCounter
{
private:
    std::vector<Player*>& players;
    bool gameRunning;
    int seconds;
    void sendTimeToPlayers();
public:
    TimeCounter(std::vector<Player*>& players);
    ~TimeCounter();
    void start(int seconds);
    void stop();
    int getTimeLeft();
};

#endif // TIMECOUNTER_H