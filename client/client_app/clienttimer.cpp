#include "clienttimer.h"
#include <QtCore>

clientTimer::clientTimer()
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(modifyTime()));
}

int clientTimer::getTime(){
    return time;
}

void clientTimer::setTime(int t){
    time = t;
    startTime();
    emit changeTime();
}

void clientTimer::startTime(){
    timer->start(1000);
}

void clientTimer::stopTime(){
    timer->stop();
    time = 0;
    emit changeTime();
}

void clientTimer::modifyTime(){
    time = time - 1;
    if(time == 0){
        stopTime();
    }
    emit changeTime();
}

