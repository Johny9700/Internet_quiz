#include "quizwindow.h"
#include "ui_quizwindow.h"
#include <QtGui>
#include <QtCore>
#include <QMessageBox>
#include <string>
#include <sstream>


QuizWindow::QuizWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuizWindow)
{
    ui->setupUi(this);
    conf = new configure();
    tcpSocket = new QTcpSocket(this);
    cTimer = new clientTimer();

    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()));
    connect(cTimer, SIGNAL(changeTime()), this, SLOT(setNewTime()));

}

QuizWindow::~QuizWindow()
{
    delete ui;
}

void QuizWindow::connectedToServer(){
    sendNick(ui->nickLineEdit->text());
}

void QuizWindow::disconnectedFromServer(){
    gameMode(false);
    connectionMode(false);
    cTimer->stopTime();
    ui->timeLabel->setText("0");

}

void QuizWindow::displayError(QAbstractSocket::SocketError socketError){
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::warning(this, "Error", "Server was closed.");
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::warning(this, "Error", "The host was not found.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::warning(this, "Error","The connection was refused by the peer.\n Make sure the server is running.");
        break;
    default:
        QMessageBox::warning(this,"Error", "Socket error, check your internet connection.");
    }
}

void QuizWindow::read(){
     QString messageFromServer = tcpSocket->readAll();
     QStringList  messagesFromServer;
     if(messageFromServer.right(3) == "%^&"){
         messageBuffer.append(messageFromServer);
         messageFromServer = messageBuffer;
         messageBuffer = "";
         messagesFromServer= messageFromServer.split( "%^&" );
         int howManyMessages = messagesFromServer.length();

         for(int i = 0; i < howManyMessages; i++){
             messageFromServer = messagesFromServer[i];
             QString typeOfMessage = messageFromServer.left(2);
             int lengthMessage = messageFromServer.length();
             messageFromServer = messageFromServer.right(lengthMessage - 2);

             switch(typeOfMessage.toInt()){
             case 10:
                 connectionMode(true);
                 ui->questionLabel->setText("Waiting for players.");
                 break;
             case 11:
                 connectionMode(false);
                 ui->connectButton->setText("Set new nick");
                 QMessageBox::information(this,"Forbidden nick", "Please change your nick and try again.");
                 break;
             case 20:
                 setQuestionAndAnswers(messageFromServer);
                 break;
             case 21:
                 if(messageFromServer == '0'){
                     gameMode(false);
                 }
                 else{
                    cTimer->setTime(messageFromServer.toInt());
                 }
                 break;
             case 22:
                 ui->scoreLabel->setText(messageFromServer);
                 break;
             case 23:
                 ui->questionLabel->setText(messageFromServer);
                 cTimer->stopTime();
                 break;
             case 24:
                 gameFinished(messageFromServer);
                 cTimer->stopTime();
                 break;
             case 25:
                 ui->amountOfAnswersLabel->setText(messageFromServer);
                 break;
             case 30:
                 setTop3(messageFromServer);
                 break;
             default:
                 break;
             }
        }

     }
     else{
         messageBuffer.append(messageFromServer);
     }

}

void QuizWindow::gameMode(bool mode){
    if(mode == true){
        ui->APushButton->setEnabled(true);
        ui->BPushButton->setEnabled(true);
        ui->CPushButton->setEnabled(true);
        ui->DPushButton->setEnabled(true);
    }
    else{
        ui->APushButton->setEnabled(false);
        ui->BPushButton->setEnabled(false);
        ui->CPushButton->setEnabled(false);
        ui->DPushButton->setEnabled(false);
    }
}

void QuizWindow::connectionMode(bool mode){
    if(mode == true){
        ui->connectButton->setText("Disconnect");
        ui->nickLineEdit->setEnabled(false);
    }
    else{
        ui->connectButton->setText("Connect");
        ui->nickLineEdit->setEnabled(true);
        resetGame();
    }
}

void QuizWindow::setQuestionAndAnswers(QString message){
    QStringList questionsAndAnswers = message.split( "`" );
    ui->amountOfAnswersLabel->setText("0");
    ui->questionLabel->setText(questionsAndAnswers[0]);
    ui->APushButton->setText(questionsAndAnswers[1]);
    ui->BPushButton->setText(questionsAndAnswers[2]);
    ui->CPushButton->setText(questionsAndAnswers[3]);
    ui->DPushButton->setText(questionsAndAnswers[4]);
    gameMode(true);
}

void QuizWindow::gameFinished(QString message){
    message.append("\nDo you want to play again?");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Game finished", message, QMessageBox::Yes|QMessageBox::No);
    resetGame();
    if (reply == QMessageBox::No) {
        tcpSocket->close();
    }
}

void QuizWindow::setTop3(QString message){
    QStringList topPlayers = message.split( " " );
    ui->firstPlayerLabel->setText(topPlayers[0]);
    ui->firstPlayerScoreLabel->setText(topPlayers[1]);
    ui->secondPlayerLabel->setText(topPlayers[2]);
    ui->secondPlayerScoreLabel->setText(topPlayers[3]);
    ui->thirdPlayerLabel->setText(topPlayers[4]);
    ui->thirdPlayerScoreLabel->setText(topPlayers[5]);
}

bool QuizWindow::verifyNick(QString nick){
    bool nickOK = true;
    if(nick == ""){
        QMessageBox::information(this, "Warning", "Your nick has to be longer.");
        nickOK = false;
    }
    else if(nick.contains(" ")){
       QMessageBox::information(this, "Warning", "Your nick can't contain whitespace.");
       nickOK = false;
    }
    return nickOK;
}

void QuizWindow::sendNick(QString qnick){
    QByteArray nick;
    qnick = qnick + "%^&";
    nick = qnick.toUtf8();
    tcpSocket->write(nick);
}

void QuizWindow::resetGame(){
    ui->questionLabel->setText("Questions appear here");
    ui->APushButton->setText("A");
    ui->BPushButton->setText("B");
    ui->CPushButton->setText("C");
    ui->DPushButton->setText("D");
    ui->amountOfAnswersLabel->setText("0");
    ui->timeLabel->setText("0");
    ui->scoreLabel->setText("0");
    ui->firstPlayerLabel->setText("First Player");
    ui->firstPlayerScoreLabel->setText("0");
    ui->secondPlayerLabel->setText("Second Player");
    ui->secondPlayerScoreLabel->setText("0");
    ui->thirdPlayerLabel->setText("Third Player");
    ui->thirdPlayerScoreLabel->setText("0");
}

void QuizWindow::setNewTime(){
    ui->timeLabel->setText(QString::number(cTimer->getTime()));
    if(cTimer->getTime() == 0){
        gameMode(false);
    }
}

void QuizWindow::on_connectButton_clicked()
{
    if((ui->connectButton->text()).toStdString() == "Connect"){
        QString addr = (QString::fromStdString((conf->getAddr()))).trimmed();
        int portint = std::stoi(conf->getPort());
        quint16 port = quint16(portint);
        QString nick;
        nick = ui->nickLineEdit->text();
        if(verifyNick(nick) == true){
            tcpSocket->connectToHost(addr,port);
        }
    }
    else if((ui->connectButton->text()).toStdString() == "Set new nick"){
        QString nick;
        nick = ui->nickLineEdit->text();
        if(verifyNick(nick) == true){
          sendNick(nick);
        }
    }
    else{
        tcpSocket->close();
    }
}

void QuizWindow::on_APushButton_clicked()
{
    QString answer = "A%^&";
    tcpSocket->write(answer.toUtf8());
    gameMode(false);
}

void QuizWindow::on_BPushButton_clicked()
{
    QString answer = "B%^&";
    tcpSocket->write(answer.toUtf8());
    gameMode(false);
}

void QuizWindow::on_CPushButton_clicked()
{
    QString answer = "C%^&";
    tcpSocket->write(answer.toUtf8());
    gameMode(false);
}

void QuizWindow::on_DPushButton_clicked()
{
    QString answer = "D%^&";
    tcpSocket->write(answer.toUtf8());
    gameMode(false);
}

void QuizWindow::on_exitPushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure?", "Quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        tcpSocket->close();
        this->close();
    }
}

