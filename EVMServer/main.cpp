#include "evmserver.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	EVMServer w;
	w.show();
	return a.exec();
}
