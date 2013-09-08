/*
	ur2013-client - an app for my birthday in 2013
	Copyright (C) 2013 Łukasz "Cyber Killer" Korpalski

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ur2013gui.h"
#include "ui_ur2013gui.h"
//#include <QDebug>

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
	ui->label->setText(trUtf8(QByteArray::fromBase64("SmVzdCA4IGhpbnTDs3cgaSBuaWUga2HFvGR5IHogbmljaCBqZXN0IHJlYWxuxIUgcG9kcG93aWVkemnEhSA6LSkuPGJyIC8+PGJyIC8+QsSZZMSFIHNpxJkgb2RzxYJhbmlhxIcgeiBjemFzZW0gKG5hIMW8eXdvIHBvZGN6YXMgZHppYcWCYW5pYSBwcm9ncmFtaWt1KS4=")));
	ui->label_2->setText(trUtf8(QByteArray::fromBase64("PGh0bWw+PGhlYWQvPjxib2R5PjxwPkl0J3MgZGFuZ2Vyb3VzIHRvIGdvIGFsb25lLCB0YWtlIDxhIGhyZWY9Imh0dHA6Ly96eGluZy5vcmcvdy9kZWNvZGUuanNweCI+PHNwYW4gc3R5bGU9IiB0ZXh0LWRlY29yYXRpb246IHVuZGVybGluZTsgY29sb3I6IzAwNTdhZTsiPnRoaXM8L3NwYW4+PC9hPi48L3A+PHA+KEx1YiBtaWVqIHBvZCByxJlrxIUgY3p5dG5payBRUkNvZGUgbmEga29tw7NyY2UpPC9wPjwvYm9keT48L2h0bWw+")));
	ui->label_3->setText(trUtf8(QByteArray::fromBase64("THVkemllIG5pZ2R5IG5pZSBjenl0YWrEhSByYW5kb20gY29tbWVudMOzdyA6LVAuPGJyIC8+PGJyIC8+QSBwcnplc3Rhd2lhbmllIHplZ2Fya2EgdyBzeXN0ZW1pZSBuaWUgcG9tYWdhLg==")));
	ui->label_4->setText(trUtf8(QByteArray::fromBase64("PGh0bWw+PGhlYWQvPjxib2R5PjxwPlRlcmF6IGJ5IHNpxJkgcHJ6eWRhxYJvIHRvIG1pZcSHIGNvIG5pZT88L3A+PHA+PGltZyBzcmM9IjovaW1nL3Jlcy90LnBuZyIvPjwvcD48L2JvZHk+PC9odG1sPg==")));
	ui->label_5->setText(trUtf8(QByteArray::fromBase64("Q2Flc2FyIGNoY2UgcHJ6ZWthemHEhywgxbxlIHRvIHBvd3nFvGVqIHRvIG5pZSBqZXN0IHdwcm9zdCBiYXNlNjQuPGJyIC8+PGJyIC8+Li4uaSBwb3RyemVibnkgamVzdCBkb3N0xJlwIGRvIHNpZWNpLCBiZXogdGVnbyBsaWN6bmlrIG5pZSBkemlhxYJhIHBvcHJhd25pZS4=")));
	ui->label_6->setText(trUtf8(QByteArray::fromBase64("PGh0bWw+PGhlYWQvPjxib2R5PjxwPk1vxbxlIHRlZ28gc3p1a2Fzej88L3A+PHA+PGltZyBzcmM9IjovaW1nL3Jlcy9jLnBuZyIvPjwvcD48L2JvZHk+PC9odG1sPg==")));
	ui->label_7->setText(trUtf8(QByteArray::fromBase64("PGh0bWw+PGhlYWQvPjxib2R5PjxwPk9LLCBiZXogxZtjaWVteSwgdHUgamVzdCBvZHBvd2llZMW6OjwvcD48cD48aW1nIHNyYz0iOi9pbWcvcmVzL3IucG5nIi8+PC9wPjwvYm9keT48L2h0bWw+")));
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
	text=text.toUtf8().toBase64(); //zegarek w base64
	//qDebug() << "base64" << text;
	std::reverse(text.begin(),text.end()); //i od końca
	//qDebug() << "odwrócony" << text;
	std::string original = text.toAscii().data();
	//qDebug() << "data" << text;

	std::string result = original; //mega brzydka implementacja rot13 znaleziona w necie, ale przynajmniej działa w przeciwieństwie do wielu ładniejszych i krótszych :-P
	for (unsigned int a = 0; a<result.length(); ++a)
	{
		switch (result[a])
		{
			case 'a':
				result[a] = 'n';
				break;
			case 'A':
				result[a] = 'N';
				break;
			case 'b':
				result[a] = 'o';
				break;
			case 'B':
				result[a] = 'O';
				break;
			case 'c':
				result[a] = 'p';
				break;
			case 'C':
				result[a] = 'P';
				break;
			case 'd':
				result[a] = 'q';
				break;
			case 'D':
				result[a] = 'Q';
				break;
			case 'e':
				result[a] = 'r';
				break;
			case 'E':
				result[a] = 'R';
				break;
			case 'f':
				result[a] = 's';
				break;
			case 'F':
				result[a] = 'S';
				break;
			case 'g':
				result[a] = 't';
				break;
			case 'G':
				result[a] = 'T';
				break;
			case 'h':
				result[a] = 'u';
				break;
			case 'H':
				result[a] = 'U';
				break;
			case 'i':
				result[a] = 'v';
				break;
			case 'I':
				result[a] = 'V';
				break;
			case 'j':
				result[a] = 'w';
				break;
			case 'J':
				result[a] = 'W';
				break;
			case 'k':
				result[a] = 'x';
				break;
			case 'K':
				result[a] = 'X';
				break;
			case 'l':
				result[a] = 'y';
				break;
			case 'L':
				result[a] = 'Y';
				break;
			case 'm':
				result[a] = 'z';
				break;
			case 'M':
				result[a] = 'Z';
				break;
			case 'n':
				result[a] = 'a';
				break;
			case 'N':
				result[a] = 'A';
				break;
			case 'o':
				result[a] = 'b';
				break;
			case 'O':
				result[a] = 'B';
				break;
			case 'p':
				result[a] = 'c';
				break;
			case 'P':
				result[a] = 'C';
				break;
			case 'q':
				result[a] = 'd';
				break;
			case 'Q':
				result[a] = 'D';
				break;
			case 'r':
				result[a] = 'e';
				break;
			case 'R':
				result[a] = 'E';
				break;
			case 's':
				result[a] = 'f';
				break;
			case 'S':
				result[a] = 'F';
				break;
			case 't':
				result[a] = 'g';
				break;
			case 'T':
				result[a] = 'G';
				break;
			case 'u':
				result[a] = 'h';
				break;
			case 'U':
				result[a] = 'H';
				break;
			case 'v':
				result[a] = 'i';
				break;
			case 'V':
				result[a] = 'I';
				break;
			case 'w':
				result[a] = 'j';
				break;
			case 'W':
				result[a] = 'J';
				break;
			case 'x':
				result[a] = 'k';
				break;
			case 'X':
				result[a] = 'K';
				break;
			case 'y':
				result[a] = 'l';
				break;
			case 'Y':
				result[a] = 'L';
				break;
			case 'z':
				result[a] = 'm';
				break;
			case 'Z':
				result[a] = 'M';
				break;
		}
	}


	text = QString::fromStdString(result); //i pojechany rot13!!! muahahahaha!!! :-D
	//qDebug() << "rot13" << text;
	if(InSeconds>0) ui->timerlabel->setText(text);
	else ui->timerlabel->setText(trUtf8(QByteArray::fromBase64("Q2lhc3RvIGplc3QhPGJyIC8+KGx1YiBqdcW8IGJ5xYJvKQ==")));

	if(InSeconds<5300 && hint2show==false)
	{
		ui->hints->addTab(ui->tab_2,"Hint 2");
		hint2show=true;
	}
	if(InSeconds<4300 && hint3show==false)
	{
		ui->hints->addTab(ui->tab_3,"Hint 3");
		hint3show=true;
	}
	if(InSeconds<3900 && hint4show==false)
	{
		ui->hints->addTab(ui->tab_4,"Hint 4");
		hint4show=true;
	}
	if(InSeconds<2200 && hint5show==false)
	{
		ui->hints->addTab(ui->tab_5,"Hint 5");
		hint5show=true;
	}
	if(InSeconds<1950 && hint6show==false)
	{
		ui->hints->addTab(ui->tab_6,"Hint 6");
		hint6show=true;
	}
	if(InSeconds<500 && hint7show==false)
	{
		ui->hints->addTab(ui->tab_7,"Ostatni hint");
		hint7show=true;
	}
	InSeconds--;
	//qDebug()<< InSeconds;
}
