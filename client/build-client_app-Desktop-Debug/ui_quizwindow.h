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
    QLabel *addressIPLabel;
    QLineEdit *addressLineEdit;
    QLineEdit *portLineEdit;
    QLabel *portLabel;
    QLabel *questionLabel;
    QPushButton *APushButton;
    QPushButton *BPushButton;
    QPushButton *CPushButton;
    QPushButton *DPushButton;
    QPushButton *exitPushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QuizWindow)
    {
        if (QuizWindow->objectName().isEmpty())
            QuizWindow->setObjectName(QStringLiteral("QuizWindow"));
        QuizWindow->setEnabled(true);
        QuizWindow->setMinimumSize(QSize(1200, 800));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        QuizWindow->setFont(font);
        centralWidget = new QWidget(QuizWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(930, 40, 211, 31));
        addressIPLabel = new QLabel(centralWidget);
        addressIPLabel->setObjectName(QStringLiteral("addressIPLabel"));
        addressIPLabel->setGeometry(QRect(50, 30, 91, 51));
        QFont font1;
        font1.setPointSize(14);
        addressIPLabel->setFont(font1);
        addressIPLabel->setScaledContents(false);
        addressLineEdit = new QLineEdit(centralWidget);
        addressLineEdit->setObjectName(QStringLiteral("addressLineEdit"));
        addressLineEdit->setGeometry(QRect(150, 40, 391, 31));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        addressLineEdit->setFont(font2);
        addressLineEdit->setClearButtonEnabled(true);
        portLineEdit = new QLineEdit(centralWidget);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));
        portLineEdit->setGeometry(QRect(670, 40, 201, 31));
        portLineEdit->setClearButtonEnabled(true);
        portLabel = new QLabel(centralWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));
        portLabel->setGeometry(QRect(600, 40, 51, 31));
        portLabel->setFont(font1);
        questionLabel = new QLabel(centralWidget);
        questionLabel->setObjectName(QStringLiteral("questionLabel"));
        questionLabel->setGeometry(QRect(30, 140, 1131, 91));
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
        addressIPLabel->setText(QApplication::translate("QuizWindow", "Adress IP:", Q_NULLPTR));
        addressLineEdit->setText(QApplication::translate("QuizWindow", "Enter IP address here", Q_NULLPTR));
        portLineEdit->setText(QApplication::translate("QuizWindow", "Enter port number here", Q_NULLPTR));
        portLabel->setText(QApplication::translate("QuizWindow", "Port:", Q_NULLPTR));
        questionLabel->setText(QApplication::translate("QuizWindow", "Questions appear here", Q_NULLPTR));
        APushButton->setText(QApplication::translate("QuizWindow", "A", Q_NULLPTR));
        BPushButton->setText(QApplication::translate("QuizWindow", "B", Q_NULLPTR));
        CPushButton->setText(QApplication::translate("QuizWindow", "C", Q_NULLPTR));
        DPushButton->setText(QApplication::translate("QuizWindow", "D", Q_NULLPTR));
        exitPushButton->setText(QApplication::translate("QuizWindow", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QuizWindow: public Ui_QuizWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZWINDOW_H
