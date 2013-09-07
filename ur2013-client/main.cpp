#include "ur2013gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ur2013gui w;
	w.show();

	return a.exec();
}
