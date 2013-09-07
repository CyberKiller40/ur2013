#ifndef UR2013GUI_H
#define UR2013GUI_H

#include <QWidget>

namespace Ui {
	class ur2013gui;
}

class ur2013gui : public QWidget
{
	Q_OBJECT
	
public:
	explicit ur2013gui(QWidget *parent = 0);
	~ur2013gui();
	
private:
	Ui::ur2013gui *ui;
};

#endif // UR2013GUI_H
