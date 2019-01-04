#include "TimeCounter.h"

TimeCounter::TimeCounter(std::vector<Player*>& players) : players(players) {}

TimeCounter::~TimeCounter()
{
    printf("TimeCounter destructor called\n");//WYWAL TO
    gameRunning = false;
}

void TimeCounter::start(int seconds)
{
    this->seconds = seconds;
    gameRunning = true;
    
    sendTimeToPlayers();
    std::chrono::system_clock systemClock;
    std::chrono::system_clock::time_point lastRun = systemClock.now();
    while(gameRunning && this->seconds > 0)
    {
        if (systemClock.now() - lastRun >= std::chrono::seconds(1))
        {
            lastRun += std::chrono::seconds(1);
            this->seconds -= 1;
            sendTimeToPlayers();
        }
    }
    gameRunning = false;
    return;
}

void TimeCounter::stop()
{
    gameRunning = false;
    printf("TimeCounter stop called\n");//WYWAL TO
}

void TimeCounter::sendTimeToPlayers()
{
    std::string prefix("21"); //prefiz for client app
    std::string message = prefix + std::to_string(seconds);
    for(auto p : players)
    { 
        NetworkUtils::sendOnSocket(p->clientFd, message);
    }
}

int TimeCounter::getTimeLeft()
{
    return seconds;
}