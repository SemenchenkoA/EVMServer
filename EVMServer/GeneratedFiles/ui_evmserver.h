/********************************************************************************
** Form generated from reading UI file 'evmserver.ui'
**
** Created: Wed 23. Sep 14:59:36 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVMSERVER_H
#define UI_EVMSERVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EVMServerClass
{
public:
    QWidget *centralWidget;
    QPushButton *connectBut;
    QPushButton *disconnectBut;
    QLabel *label;
    QSpinBox *spinPort;
    QSpinBox *spinLen;
    QLabel *label_2;
    QPushButton *pushLeft;
    QPushButton *pushRight;

    void setupUi(QMainWindow *EVMServerClass)
    {
        if (EVMServerClass->objectName().isEmpty())
            EVMServerClass->setObjectName(QString::fromUtf8("EVMServerClass"));
        EVMServerClass->resize(850, 650);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EVMServerClass->sizePolicy().hasHeightForWidth());
        EVMServerClass->setSizePolicy(sizePolicy);
        EVMServerClass->setMinimumSize(QSize(850, 650));
        EVMServerClass->setMaximumSize(QSize(850, 650));
        centralWidget = new QWidget(EVMServerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        connectBut = new QPushButton(centralWidget);
        connectBut->setObjectName(QString::fromUtf8("connectBut"));
        connectBut->setGeometry(QRect(10, 10, 75, 23));
        disconnectBut = new QPushButton(centralWidget);
        disconnectBut->setObjectName(QString::fromUtf8("disconnectBut"));
        disconnectBut->setGeometry(QRect(90, 10, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 10, 61, 21));
        spinPort = new QSpinBox(centralWidget);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));
        spinPort->setGeometry(QRect(270, 10, 81, 22));
        spinPort->setMaximum(1000000);
        spinPort->setValue(10001);
        spinLen = new QSpinBox(centralWidget);
        spinLen->setObjectName(QString::fromUtf8("spinLen"));
        spinLen->setGeometry(QRect(450, 10, 91, 22));
        spinLen->setMinimum(1);
        spinLen->setMaximum(1000000);
        spinLen->setValue(32768);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 10, 71, 21));
        pushLeft = new QPushButton(centralWidget);
        pushLeft->setObjectName(QString::fromUtf8("pushLeft"));
        pushLeft->setGeometry(QRect(704, 10, 51, 23));
        pushRight = new QPushButton(centralWidget);
        pushRight->setObjectName(QString::fromUtf8("pushRight"));
        pushRight->setGeometry(QRect(770, 10, 51, 23));
        EVMServerClass->setCentralWidget(centralWidget);

        retranslateUi(EVMServerClass);

        QMetaObject::connectSlotsByName(EVMServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *EVMServerClass)
    {
        EVMServerClass->setWindowTitle(QApplication::translate("EVMServerClass", "EVMServer", 0, QApplication::UnicodeUTF8));
        connectBut->setText(QApplication::translate("EVMServerClass", "Connect", 0, QApplication::UnicodeUTF8));
        disconnectBut->setText(QApplication::translate("EVMServerClass", "Disconnect", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EVMServerClass", "Listen port:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EVMServerClass", "Signal length:", 0, QApplication::UnicodeUTF8));
        pushLeft->setText(QApplication::translate("EVMServerClass", "<<", 0, QApplication::UnicodeUTF8));
        pushRight->setText(QApplication::translate("EVMServerClass", ">>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EVMServerClass: public Ui_EVMServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVMSERVER_H
