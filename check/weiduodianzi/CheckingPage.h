#ifndef	CHECKINGPAGE_H
#define CHECKINGPAGE_H

#include "BasePage.h"
#include "ui_CheckingPage.h"
//#include "baseMainPage.h"

class CheckingPage: public CBasePage
{
	Q_OBJECT
public:
	CheckingPage(QWidget *parent = 0, quint8 index = 0, quint8 previndex = 0, quint32 add = 0);
	~CheckingPage(void);
	static CBasePage* getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add);

protected:
	void initFocusList();

private slots:
	void lampSuccess(bool success);
	void motorInitSuccess();
    void updateTimer();

private:
	Ui::CheckingPageClass ui;

	

};


#endif // GRADIENTPAGE_H
