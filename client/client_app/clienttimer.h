#ifndef CLIENTTIMER_H
#define CLIENTTIMER_H
#include <QTimer>
#include <QRunnable>


class clientTimer : public QObject
{

Q_OBJECT

public:
    clientTimer();
    int getTime();
    void setTime(int t);
    void stopTime();
signals:
    void changeTime();
private:
    QTimer *timer;
    int time;
    void startTime();

private slots:
    void modifyTime();
};

#endif // CLIENTTIMER_H
