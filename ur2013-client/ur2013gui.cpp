#include "ur2013gui.h"
#include "ui_ur2013gui.h"

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

	//czas z netu
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
	manager->get(QNetworkRequest(QUrl("http://212.83.63.218/ck/time.php")));

}
ur2013gui::~ur2013gui()
{
	delete ui;
}
void ur2013gui::replyFinished(QNetworkReply *reply) //odpowiedź z neta
{
	QByteArray data=reply->readAll();
	QString str(data);
	nowtime = QTime::fromString(str);

	//timer
	timer = new QTimer();
	InSeconds=nowtime.secsTo(finishtime);
	int seconds = InSeconds % 60 ;
	int InMinutes = InSeconds / 60 ;
	int minutes = InMinutes % 60 ;
	int InHours = InMinutes / 60 ;
	int hours = InHours % 24 ;
	timeValue = new QTime(hours,minutes,seconds);
	QObject::connect(timer,SIGNAL(timeout()),this,SLOT(setDisplay()));
	timer->start(1000);
}

void ur2013gui::setDisplay()
{
	this->timeValue->setHMS(this->timeValue->addSecs(-1).hour(),this->timeValue->addSecs(-1).minute(),this->timeValue->addSecs(-1).second());
	QString text = timeValue->toString();
	text=text.toUtf8().toBase64();
	std::reverse(text.begin(),text.end());
	if(InSeconds>0) ui->timerlabel->setText(text);
	else ui->timerlabel->setText(trUtf8("Ciasto jest! (lub już było)"));
	if(InSeconds<5400 && hint2show==false)
	{
		ui->hints->addTab(ui->tab_2,"Hint 2");
		hint2show=true;
	}
	if(InSeconds<4500 && hint3show==false)
	{
		ui->hints->addTab(ui->tab_3,"Hint 3");
		hint3show=true;
	}
	if(InSeconds<3600 && hint4show==false)
	{
		ui->hints->addTab(ui->tab_4,"Hint 4");
		hint4show=true;
	}
	if(InSeconds<2800 && hint5show==false)
	{
		ui->hints->addTab(ui->tab_5,"Hint 5");
		hint5show=true;
	}
	if(InSeconds<1800 && hint6show==false)
	{
		ui->hints->addTab(ui->tab_6,"Hint 6");
		hint6show=true;
	}
	if(InSeconds<900 && hint7show==false)
	{
		ui->hints->addTab(ui->tab_7,"Ostatni hint");
		hint7show=true;
	}
	InSeconds--;
}
