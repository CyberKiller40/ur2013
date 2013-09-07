#include "ur2013gui.h"
#include "ui_ur2013gui.h"

ur2013gui::ur2013gui(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ur2013gui)
{
	ui->setupUi(this);
}

ur2013gui::~ur2013gui()
{
	delete ui;
}
