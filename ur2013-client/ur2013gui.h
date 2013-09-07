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
	QTime finishtime = QTime(10,26);
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
