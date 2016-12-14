/********************************************************************************
** Form generated from reading UI file 'brain.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRAIN_H
#define UI_BRAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BrainClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BrainClass)
    {
        if (BrainClass->objectName().isEmpty())
            BrainClass->setObjectName(QStringLiteral("BrainClass"));
        BrainClass->resize(600, 400);
        menuBar = new QMenuBar(BrainClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BrainClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BrainClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BrainClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BrainClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BrainClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BrainClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BrainClass->setStatusBar(statusBar);

        retranslateUi(BrainClass);

        QMetaObject::connectSlotsByName(BrainClass);
    } // setupUi

    void retranslateUi(QMainWindow *BrainClass)
    {
        BrainClass->setWindowTitle(QApplication::translate("BrainClass", "Brain", 0));
    } // retranslateUi

};

namespace Ui {
    class BrainClass: public Ui_BrainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRAIN_H
