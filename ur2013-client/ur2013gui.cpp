#include "ur2013gui.h"
#include "ui_ur2013gui.h"
#include <qte

ur2013gui::ur2013gui(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ur2013gui)
{
	ui->setupUi(this);
	ui->hints->removeTab(6);
	ui->hints->removeTab(5);
	ui->hints->removeTab(4);
	ui->hints->removeTab(3);
	ui->hints->removeTab(2);
	ui->hints->removeTab(1);
	QTest::qWait(5000);
	ui->hints->addTab(ui->tab_2);
}
ur2013gui::~ur2013gui()
{
	delete ui;
}
