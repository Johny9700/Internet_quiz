#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <fstream>
#include <string>


class Configuration
{
private:
    std::string port;
    int numOfQuestionsPerGame;
    int timePerQuestion;
    int timeBetweenEachGame;
    int timeBeforeFirstGame;

public:
    Configuration(const char* filename);
    int getNumOfQuestionsPerGame();
    int getTimePerQuestion();
    int getTimeBetweenEachGame();
    int getTimeBeforeFirstGame();
    std::string getPort();
};


#endif // CONFIGURATION_H