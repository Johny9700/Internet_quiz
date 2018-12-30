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
     QString messageFromServer = tcp_socket->readAll();
     QString typeOfMessage = messageFromServer.left(2);
     int lengthMessage = len(messageFromServer);
     messageFromServer = messageFromServer.right(lengthMessage - 2);

     switch(typeOfMessage){
     case 10:

         breaak;
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

void QuizWindow::on_connectButton_clicked()
{
    if((ui->connectButton->text()).toStdString() == "Connect"){
        try{
            QString addr = "127.0.0.1";
            quint16 port = 8000;

            tcpSocket->connectToHost(addr,port);

            ui->questionLabel->setText("Nowe pytanie");
//            gameMode(true);

        }
        catch(...){
            QMessageBox::warning(this, "Error", "Nie udało się połączyć z grą, spróbuj ponownie.");
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
}

void QuizWindow::on_BPushButton_clicked()
{
    QString answer = "20B";
    tcpSocket->write(answer.toUtf8());
}

void QuizWindow::on_CPushButton_clicked()
{
    QString answer = "20C";
    tcpSocket->write(answer.toUtf8());
}

void QuizWindow::on_DPushButton_clicked()
{
    QString answer = "20D";
    tcpSocket->write(answer.toUtf8());
}

void QuizWindow::on_exitPushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure?", "Quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close();
    }
}

