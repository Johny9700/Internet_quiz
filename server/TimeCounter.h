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
    bool gameRunning;
    int seconds;
public:
    TimeCounter();
    ~TimeCounter();
    void start();
    void stop();
    int getTimeLeft();
    void setTime(int seconds);
};

#endif // TIMECOUNTER_H