#include "Configuration.h"

Configuration::Configuration(const char* filename)
{
    std::ifstream input (filename);
    if(input.is_open())
    {
        input >> port;
        input >> numOfQuestionsPerGame;
        input >> timePerQuestion;
        input >> timeBeforeFirstGame;
        input >> timeBetweenEachGame;
    }
    else
    {
        printf("cannot open %s, using default values", filename);
        port = "8000";
        numOfQuestionsPerGame = 7;
        timePerQuestion = 30;
        timeBeforeFirstGame = 20;
        timeBetweenEachGame = 15;
    }
}

int Configuration::getNumOfQuestionsPerGame()
{
    return numOfQuestionsPerGame;
}

int Configuration::getTimePerQuestion()
{
    return timePerQuestion;
}

int Configuration::getTimeBetweenEachGame()
{
    return timeBetweenEachGame;
}

int Configuration::getTimeBeforeFirstGame()
{
    return timeBeforeFirstGame;
}

std::string Configuration::getPort()
{
    return port;
}