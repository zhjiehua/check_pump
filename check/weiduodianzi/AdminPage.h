#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include "BasePage.h"
#include "ui_AdminPage.h"
#include "msgbox.h"
#include "baseMainPage.h"

class AdminPage: public CBasePage
{
	Q_OBJECT
public:
	AdminPage(QWidget *parent = 0, quint8 index = 0, quint8 previndex = 0, quint32 add = 0);
	~AdminPage(void);
	static CBasePage* getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add);

protected:
	virtual void initFocusList();
	//virtual bool eventFilter(QObject *o, QEvent *e);

private:
	Ui::AdminPage ui;

private slots:
	void on_activeBtn_clicked();
	void on_utcBtn_clicked();
	void on_xtcBtn_clicked();
	void on_ttcBtn_clicked();
	void on_lpcBtn_clicked();
	void changePcPro(int idx);
	void changeConnectPort(int idx);
	void tryDayChanged(QString val);

	void on_rstBtn_clicked();//回复出厂设置

	void on_saveDataBtn_clicked();
	void on_updateDataBtn_clicked();
};

#endif //ADMINPAGE_H
