#include "TimeCounter.h"
#include <iostream>

TimeCounter::TimeCounter()
{
    seconds = 0;
    gameRunning = false;
}

TimeCounter::~TimeCounter()
{
    printf("TimeCounter destructor called\n");//WYWAL TO
    gameRunning = false;
}

void TimeCounter::start()
{
    gameRunning = true;
    const auto oneSecond = std::chrono::milliseconds(1000);

    while(gameRunning && this->seconds > 0)
    {
        auto start = std::chrono::steady_clock::now();
        this->seconds -= 1;
        std::cout << "sekundnik " << seconds << std::endl;
        auto end = std::chrono::steady_clock::now();
        auto elapsed = end - start;

        auto sleepTime = oneSecond - elapsed;
        if(sleepTime > std::chrono::milliseconds::zero())
        {
            std::this_thread::sleep_for(sleepTime);
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

int TimeCounter::getTimeLeft()
{
    return seconds;
}

void TimeCounter::setTime(int seconds)
{
    this->seconds = seconds;
}