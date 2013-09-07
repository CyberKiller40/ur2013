#include "ur2013gui.h"
#include "ui_ur2013gui.h"
#include <QDebug>


ur2013gui::ur2013gui(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ur2013gui)
{
	ui->setupUi(this);
	ui->alabel_8->hide();
	ui->hints->removeTab(6);
	ui->hints->removeTab(5);
	ui->hints->removeTab(4);
	ui->hints->removeTab(3);
	ui->hints->removeTab(2);
	ui->hints->removeTab(1);

	//ui->hints->addTab(ui->tab_2,"Hint 2");

	//czas z netu
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
	manager->get(QNetworkRequest(QUrl("http://212.83.63.218/ck/time.php")));

	//timer
	timer = new QTimer();
	timeValue = new QTime(0,0,1000);
	//this->setParent(parentWidget);
	//this->display(timeValue->toString());
	QObject::connect(timer,SIGNAL(timeout()),this,SLOT(setDisplay()));
	timer->start(2000);

}
ur2013gui::~ur2013gui()
{
	delete ui;
}
void ur2013gui::replyFinished(QNetworkReply *reply) //odpowiedź z neta i timer
{
	QByteArray data=reply->readAll();
	QString str(data);
	qDebug() << str;
}

void ur2013gui::setDisplay()
{
	this->timeValue->setHMS(0,this->timeValue->addSecs(-1).minute(),this->timeValue->addSecs(-1).second());
	ui->timerlabel->setText(timeValue->toString());

}
