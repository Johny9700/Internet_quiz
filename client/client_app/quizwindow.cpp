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
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()));
}

QuizWindow::~QuizWindow()
{
    delete ui;
}

void QuizWindow::connectedToServer(){
    QString qnick;
    QByteArray nick;
    qnick = "10";
    qnick.append(ui->nickLineEdit->text());
    nick = qnick.toUtf8();
    tcpSocket->write(nick);
    gameMode(true);

}

void QuizWindow::disconnectedFromServer(){
    gameMode(false);
    connectionMode(false);
}

void QuizWindow::displayError(QAbstractSocket::SocketError socketError){
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
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
     QString typeOfMessage = messageFromServer.left(2);
     int lengthMessage = messageFromServer.length();
     messageFromServer = messageFromServer.right(lengthMessage - 2);

     switch(typeOfMessage.toInt()){
     case 10:
         connectionMode(true);
         break;
     case 11:
         connectionMode(false);
         QMessageBox::information(this,"Forbidden nick", "Please change your nick and try again.");
         tcpSocket->abort();
         break;
     case 20:
         setQuestionAndAnswers(messageFromServer);
         break;
     case 21:
         if(messageFromServer == '0'){
             gameMode(false);
         }
         ui->timeLabel->setText(messageFromServer);
         break;
     case 22:
         ui->scoreLabel->setText(messageFromServer);
         break;
     case 23:
         ui->questionLabel->setText(messageFromServer);
         break;
     case 24:
         gameFinished(messageFromServer);
         break;
     case 30:
         setTop3(messageFromServer);
         break;
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
    }
}

void QuizWindow::setQuestionAndAnswers(QString message){
    QStringList questionsAndAnswers = message.split( "`" );
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
    tcpSocket->abort();
    reply = QMessageBox::question(this, "Game finished", message, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QString addr = "127.0.0.1";
        quint16 port = 8000;
        tcpSocket->connectToHost(addr,port);
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

void QuizWindow::on_connectButton_clicked()
{
    if((ui->connectButton->text()).toStdString() == "Connect"){
        QString addr = "127.0.0.1";
        quint16 port = 8000;
        QString nick;
        nick = ui->nickLineEdit->text();
        if(nick == ""){
            QMessageBox::information(this, "Warning", "Your nick has to be longer.");
        }
        else if(nick.contains(" ")){
           QMessageBox::information(this, "Warning", "Your nick can't contain whitespace.");
        }
        else{
            tcpSocket->connectToHost(addr,port);
        }
    }
    else{
        tcpSocket->abort();
    }
}

void QuizWindow::on_APushButton_clicked()
{
    QString answer = "20A";
    tcpSocket->write(answer.toUtf8());
    gameMode(false);
}

void QuizWindow::on_BPushButton_clicked()
{
    QString answer = "20B";
    tcpSocket->write(answer.toUtf8());
    gameMode(false);
}

void QuizWindow::on_CPushButton_clicked()
{
    QString answer = "20C";
    tcpSocket->write(answer.toUtf8());
    gameMode(false);
}

void QuizWindow::on_DPushButton_clicked()
{
    QString answer = "20D";
    tcpSocket->write(answer.toUtf8());
    gameMode(false);
}

void QuizWindow::on_exitPushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure?", "Quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close();
    }
}

