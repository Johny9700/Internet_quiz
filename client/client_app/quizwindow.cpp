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
}

QuizWindow::~QuizWindow()
{
    delete ui;
}

void QuizWindow::on_connectButton_clicked()
{
    QString qaddress;
    QString qport;
    int port;

    try{
        qaddress = ui->addressLineEdit->text();
        qport = ui->portLineEdit->text();
        QMessageBox::warning(this, "Error", "Udało się połączyć z grą.");
        port = qport.toInt();

        ui->questionLabel->setText("Nowe pytanie");
        ui->APushButton->setEnabled(true);
        ui->BPushButton->setEnabled(true);
        ui->CPushButton->setEnabled(true);
        ui->DPushButton->setEnabled(true);
    }
    catch(...){
        QMessageBox::warning(this, "Error", "Nie udało się połączyć z grą, spróbuj ponownie.");
    }
}

void QuizWindow::on_APushButton_clicked()
{

}

void QuizWindow::on_BPushButton_clicked()
{

}

void QuizWindow::on_CPushButton_clicked()
{

}

void QuizWindow::on_DPushButton_clicked()
{

}

void QuizWindow::on_exitPushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure?", "Quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close();
    }
}

