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
    QString qport;

    qport = ui->addressLineEdit->text();
    QMessageBox::warning(this, "WARNING", qport);

    ui->APushButton->setEnabled(true);
    ui->BPushButton->setEnabled(true);
    ui->CPushButton->setEnabled(true);
    ui->DPushButton->setEnabled(true);
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
