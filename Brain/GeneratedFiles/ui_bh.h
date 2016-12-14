/********************************************************************************
** Form generated from reading UI file 'bh.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BH_H
#define UI_BH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bh
{
public:
    QLineEdit *bh_lineEdit;
    QLabel *bh_label;

    void setupUi(QWidget *bh)
    {
        if (bh->objectName().isEmpty())
            bh->setObjectName(QStringLiteral("bh"));
        bh->resize(361, 122);
        bh_lineEdit = new QLineEdit(bh);
        bh_lineEdit->setObjectName(QStringLiteral("bh_lineEdit"));
        bh_lineEdit->setGeometry(QRect(110, 40, 113, 20));
        bh_label = new QLabel(bh);
        bh_label->setObjectName(QStringLiteral("bh_label"));
        bh_label->setGeometry(QRect(53, 40, 71, 21));

        retranslateUi(bh);

        QMetaObject::connectSlotsByName(bh);
    } // setupUi

    void retranslateUi(QWidget *bh)
    {
        bh->setWindowTitle(QApplication::translate("bh", "Form", 0));
        bh_label->setText(QApplication::translate("bh", "\350\204\221\345\256\271\347\247\257\346\257\224\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class bh: public Ui_bh {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BH_H
