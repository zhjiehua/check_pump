#ifndef RUNPAGE_H
#define RUNPAGE_H

#include "ui_RunPage.h"
#include "BasePage.h"
#include "machinestat.h"


class RunPage : public CBasePage
{
	Q_OBJECT

public:
	RunPage(QWidget *parent = 0, quint8 index = 0, quint8 previndex = 0, quint32 add = 0);
	~RunPage();

	static CBasePage* getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add);

protected:
	virtual void initFocusList();


private:
	Ui::RunPageClass ui;
	void initDisplay();
	

private slots:
	void updateAuValue(quint32 s, quint32 r, double au, quint8 which);
	void changeLampStat(MachineStat::LampStatment stat);
	void lampComboChanged(int index);
	void updateWlenDisp(QString str, quint8 which);

	void waveLen1Changed(QString str);
	void waveLen2Changed(QString str);

	void updateStartupTime();

	void updateTestSignal(double wlen);
	/*void on_pushButton_clicked();
	void fuck();*/
};

#endif // RUNPAGE_H
