#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct Player
{
    int clientFd;
    std::string name;
    int score;
    bool answeared;
};

#endif // PLAYER_H