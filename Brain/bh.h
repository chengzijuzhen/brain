#ifndef BH_H
#define BH_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <String>
//#include <QSqlDatabase>
//#include <QSqlQuery>
#include <QtCore/QDebug>
#include "ui_bh.h"

class bh : public QWidget
{
	Q_OBJECT
public:
	bh(QWidget *parent=0);
	~bh();

	QLineEdit * bili;
	
private:
	Ui::bh ui;
	
};
#endif

