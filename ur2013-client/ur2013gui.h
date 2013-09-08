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

#ifndef UR2013GUI_H
#define UR2013GUI_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QTime>
#include <algorithm>
#include <string>


namespace Ui {
	class ur2013gui;
}

class ur2013gui : public QWidget
{
	Q_OBJECT
	
public:
	explicit ur2013gui(QWidget *parent = 0);
	~ur2013gui();
	QTimer* timer;
	QTime* timeValue;
	QTime nowtime;
	QTime finishtime = QTime(10,47); //godzina do której odlicza
	int InSeconds;
	bool hint2show = false;
	bool hint3show = false;
	bool hint4show = false;
	bool hint5show = false;
	bool hint6show = false;
	bool hint7show = false;


private:
	Ui::ur2013gui *ui;
public slots:
	void replyFinished(QNetworkReply*);
	void setDisplay();

};

#endif // UR2013GUI_H
