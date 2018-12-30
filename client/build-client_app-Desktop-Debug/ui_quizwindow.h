/********************************************************************************
** Form generated from reading UI file 'quizwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZWINDOW_H
#define UI_QUIZWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuizWindow
{
public:
    QWidget *centralWidget;
    QPushButton *connectButton;
    QLabel *nickLabel;
    QLineEdit *nickLineEdit;
    QLabel *questionLabel;
    QPushButton *APushButton;
    QPushButton *BPushButton;
    QPushButton *CPushButton;
    QPushButton *DPushButton;
    QPushButton *exitPushButton;
    QLabel *yourScoreLabel;
    QLabel *scoreLabel;
    QLabel *firstPlayerLabel;
    QLabel *secondPlayerLabel;
    QLabel *thirdPlayerLabel;
    QLabel *firstPlayerScoreLabel;
    QLabel *secondPlayerScoreLabel;
    QLabel *thirdPlayerScoreLabel;
    QLabel *yourTimeLabel;
    QLabel *timeLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QuizWindow)
    {
        if (QuizWindow->objectName().isEmpty())
            QuizWindow->setObjectName(QStringLiteral("QuizWindow"));
        QuizWindow->setEnabled(true);
        QuizWindow->resize(1200, 800);
        QuizWindow->setMinimumSize(QSize(1200, 800));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        QuizWindow->setFont(font);
        centralWidget = new QWidget(QuizWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(50, 90, 231, 31));
        nickLabel = new QLabel(centralWidget);
        nickLabel->setObjectName(QStringLiteral("nickLabel"));
        nickLabel->setGeometry(QRect(50, 30, 41, 51));
        QFont font1;
        font1.setPointSize(14);
        nickLabel->setFont(font1);
        nickLabel->setScaledContents(false);
        nickLineEdit = new QLineEdit(centralWidget);
        nickLineEdit->setObjectName(QStringLiteral("nickLineEdit"));
        nickLineEdit->setGeometry(QRect(100, 40, 181, 31));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        nickLineEdit->setFont(font2);
        nickLineEdit->setClearButtonEnabled(true);
        questionLabel = new QLabel(centralWidget);
        questionLabel->setObjectName(QStringLiteral("questionLabel"));
        questionLabel->setGeometry(QRect(30, 160, 1131, 91));
        QFont font3;
        font3.setPointSize(16);
        questionLabel->setFont(font3);
        questionLabel->setLayoutDirection(Qt::RightToLeft);
        questionLabel->setAlignment(Qt::AlignCenter);
        APushButton = new QPushButton(centralWidget);
        APushButton->setObjectName(QStringLiteral("APushButton"));
        APushButton->setEnabled(false);
        APushButton->setGeometry(QRect(180, 300, 351, 131));
        QFont font4;
        font4.setPointSize(40);
        font4.setBold(false);
        font4.setWeight(50);
        APushButton->setFont(font4);
        BPushButton = new QPushButton(centralWidget);
        BPushButton->setObjectName(QStringLiteral("BPushButton"));
        BPushButton->setEnabled(false);
        BPushButton->setGeometry(QRect(670, 300, 351, 131));
        BPushButton->setFont(font4);
        CPushButton = new QPushButton(centralWidget);
        CPushButton->setObjectName(QStringLiteral("CPushButton"));
        CPushButton->setEnabled(false);
        CPushButton->setGeometry(QRect(180, 450, 351, 131));
        CPushButton->setFont(font4);
        DPushButton = new QPushButton(centralWidget);
        DPushButton->setObjectName(QStringLiteral("DPushButton"));
        DPushButton->setEnabled(false);
        DPushButton->setGeometry(QRect(670, 450, 351, 131));
        DPushButton->setFont(font4);
        exitPushButton = new QPushButton(centralWidget);
        exitPushButton->setObjectName(QStringLiteral("exitPushButton"));
        exitPushButton->setGeometry(QRect(490, 650, 221, 41));
        yourScoreLabel = new QLabel(centralWidget);
        yourScoreLabel->setObjectName(QStringLiteral("yourScoreLabel"));
        yourScoreLabel->setGeometry(QRect(520, 20, 101, 51));
        yourScoreLabel->setFont(font1);
        yourScoreLabel->setScaledContents(false);
        scoreLabel = new QLabel(centralWidget);
        scoreLabel->setObjectName(QStringLiteral("scoreLabel"));
        scoreLabel->setGeometry(QRect(620, 20, 61, 51));
        scoreLabel->setFont(font1);
        scoreLabel->setScaledContents(false);
        scoreLabel->setAlignment(Qt::AlignCenter);
        firstPlayerLabel = new QLabel(centralWidget);
        firstPlayerLabel->setObjectName(QStringLiteral("firstPlayerLabel"));
        firstPlayerLabel->setGeometry(QRect(990, 30, 101, 17));
        secondPlayerLabel = new QLabel(centralWidget);
        secondPlayerLabel->setObjectName(QStringLiteral("secondPlayerLabel"));
        secondPlayerLabel->setGeometry(QRect(990, 60, 101, 17));
        thirdPlayerLabel = new QLabel(centralWidget);
        thirdPlayerLabel->setObjectName(QStringLiteral("thirdPlayerLabel"));
        thirdPlayerLabel->setGeometry(QRect(990, 90, 101, 17));
        firstPlayerScoreLabel = new QLabel(centralWidget);
        firstPlayerScoreLabel->setObjectName(QStringLiteral("firstPlayerScoreLabel"));
        firstPlayerScoreLabel->setGeometry(QRect(1110, 30, 61, 20));
        firstPlayerScoreLabel->setAlignment(Qt::AlignCenter);
        secondPlayerScoreLabel = new QLabel(centralWidget);
        secondPlayerScoreLabel->setObjectName(QStringLiteral("secondPlayerScoreLabel"));
        secondPlayerScoreLabel->setGeometry(QRect(1110, 60, 61, 20));
        secondPlayerScoreLabel->setAlignment(Qt::AlignCenter);
        thirdPlayerScoreLabel = new QLabel(centralWidget);
        thirdPlayerScoreLabel->setObjectName(QStringLiteral("thirdPlayerScoreLabel"));
        thirdPlayerScoreLabel->setGeometry(QRect(1110, 90, 61, 20));
        thirdPlayerScoreLabel->setAlignment(Qt::AlignCenter);
        yourTimeLabel = new QLabel(centralWidget);
        yourTimeLabel->setObjectName(QStringLiteral("yourTimeLabel"));
        yourTimeLabel->setGeometry(QRect(520, 70, 101, 51));
        yourTimeLabel->setFont(font1);
        yourTimeLabel->setScaledContents(false);
        yourTimeLabel->setAlignment(Qt::AlignCenter);
        timeLabel = new QLabel(centralWidget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setGeometry(QRect(620, 70, 61, 51));
        timeLabel->setFont(font1);
        timeLabel->setScaledContents(false);
        timeLabel->setAlignment(Qt::AlignCenter);
        QuizWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QuizWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 22));
        QuizWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QuizWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QuizWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QuizWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QuizWindow->setStatusBar(statusBar);

        retranslateUi(QuizWindow);

        QMetaObject::connectSlotsByName(QuizWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QuizWindow)
    {
        QuizWindow->setWindowTitle(QApplication::translate("QuizWindow", "QuizWindow", Q_NULLPTR));
        connectButton->setText(QApplication::translate("QuizWindow", "Connect", Q_NULLPTR));
        nickLabel->setText(QApplication::translate("QuizWindow", "Nick:", Q_NULLPTR));
        nickLineEdit->setText(QApplication::translate("QuizWindow", "Enter your nick here", Q_NULLPTR));
        questionLabel->setText(QApplication::translate("QuizWindow", "Questions appear here", Q_NULLPTR));
        APushButton->setText(QApplication::translate("QuizWindow", "A", Q_NULLPTR));
        BPushButton->setText(QApplication::translate("QuizWindow", "B", Q_NULLPTR));
        CPushButton->setText(QApplication::translate("QuizWindow", "C", Q_NULLPTR));
        DPushButton->setText(QApplication::translate("QuizWindow", "D", Q_NULLPTR));
        exitPushButton->setText(QApplication::translate("QuizWindow", "Exit", Q_NULLPTR));
        yourScoreLabel->setText(QApplication::translate("QuizWindow", "Your score:", Q_NULLPTR));
        scoreLabel->setText(QApplication::translate("QuizWindow", "0", Q_NULLPTR));
        firstPlayerLabel->setText(QApplication::translate("QuizWindow", "First player", Q_NULLPTR));
        secondPlayerLabel->setText(QApplication::translate("QuizWindow", "Second player", Q_NULLPTR));
        thirdPlayerLabel->setText(QApplication::translate("QuizWindow", "Third player", Q_NULLPTR));
        firstPlayerScoreLabel->setText(QApplication::translate("QuizWindow", "0", Q_NULLPTR));
        secondPlayerScoreLabel->setText(QApplication::translate("QuizWindow", "0", Q_NULLPTR));
        thirdPlayerScoreLabel->setText(QApplication::translate("QuizWindow", "0", Q_NULLPTR));
        yourTimeLabel->setText(QApplication::translate("QuizWindow", "Time:", Q_NULLPTR));
        timeLabel->setText(QApplication::translate("QuizWindow", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QuizWindow: public Ui_QuizWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZWINDOW_H
