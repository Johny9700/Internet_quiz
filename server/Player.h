#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct Player
{
    int clientFd;
    std::string name;
    int score;
    bool answeared;
    int currentPoints;
    bool deadSocket;
};

#endif // PLAYER_H