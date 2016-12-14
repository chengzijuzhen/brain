#include "bh.h"
#include "brain.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Brain w;
	w.show();
	return a.exec();

}
