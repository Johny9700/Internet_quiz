#include "TimeCounter.h"





#include <iostream>
void sendTimeToPlayers(int seconds) //WYWAL TO
{
    std::cout << seconds << std::endl;
}

TimeCounter::TimeCounter(std::vector<Player*>& players) : myThread(), players(players) {}

TimeCounter::~TimeCounter()
{
    std::cout << "TimeCounter destructor called\n";//WYWAL TO
    gameRunning = false;
    if(myThread.joinable())
        myThread.join();
}

void TimeCounter::start(int seconds)
{
    this->seconds = seconds;
    gameRunning = true;
    myThread = std::thread(&TimeCounter::threadMain, this);
}

void TimeCounter::stop()
{
    gameRunning = false;
    std::cout << "TimeCounter stop called\n";//WYWAL TO
    if(myThread.joinable())
        myThread.join();
}

int TimeCounter::getTimeLeft()
{
    return seconds;
}

void TimeCounter::threadMain()
{
    sendTimeToPlayers(seconds);
    std::chrono::system_clock systemClock;
    std::chrono::system_clock::time_point lastRun = systemClock.now();
    while(gameRunning && seconds > 0)
    {
        if (systemClock.now() - lastRun >= std::chrono::seconds(1))
        {
            lastRun += std::chrono::seconds(1);
            seconds -= 1;
            sendTimeToPlayers(seconds);
        }
    }
    gameRunning = false;
    std::cout << "Time's up\n";//WYWAL TO
    return;
}