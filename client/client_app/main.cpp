#include "quizwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuizWindow w;
    w.show();

    return a.exec();
}
