#ifndef TIMECOUNTER_H
#define TIMECOUNTER_H

#include <thread>
#include <vector>
#include "Player.h"

class TimeCounter
{
private:
    std::thread myThread;
    std::vector<Player*>& players;
    bool gameRunning;
    int seconds;
    void threadMain();
public:
    TimeCounter(std::vector<Player*>& players);
    ~TimeCounter();
    void start(int seconds);
    void stop();
    int getTimeLeft();
};

#endif // TIMECOUNTER_H