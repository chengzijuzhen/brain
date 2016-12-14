#include "bh.h"
bh::bh(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	bili=ui.bh_lineEdit;
	this->setFixedSize(this->width(),this->height());
}

bh::~bh()
{

}