#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include "configure.h"

namespace Ui {
class QuizWindow;
}

class QuizWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuizWindow(QWidget *parent = 0);
    ~QuizWindow();

private slots:
    void on_connectButton_clicked();

    void on_APushButton_clicked();

    void on_BPushButton_clicked();

    void on_CPushButton_clicked();

    void on_DPushButton_clicked();

    void on_exitPushButton_clicked();

    void connectedToServer();

    void read();

    void displayError(QAbstractSocket::SocketError socketError);

    void disconnectedFromServer();

private:
    Ui::QuizWindow *ui;
    QTcpSocket *tcpSocket;
    configure *conf;
    void gameMode(bool);
    void connectionMode(bool);
    void setQuestionAndAnswers(QString);
    void gameFinished(QString);
    void setTop3(QString);
    bool verifyNick(QString);
    void sendNick(QString);
    void resetGame();
};

#endif // QUIZWINDOW_H
