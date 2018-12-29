#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QMainWindow>

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

private:
    Ui::QuizWindow *ui;
};

#endif // QUIZWINDOW_H
