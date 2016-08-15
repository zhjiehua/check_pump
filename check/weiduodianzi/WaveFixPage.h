#ifndef WAVEFIXPAGE_H
#define WAVEFIXPAGE_H

#include "BasePage.h"
#include "ui_waveFixPage.h"

class WaveFixPage: public CBasePage
{
	Q_OBJECT
public:
	WaveFixPage(QWidget *parent = 0, quint8 index = 0, quint8 previndex = 0, quint32 add = 0);
	~WaveFixPage(void);
	static CBasePage* getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add);

protected:
	void initFocusList();

private:
	Ui::WaveFixPageClass ui;


	void initDisplay();



private slots:
	void getOutTableFocus(int dir);
	void on_saveBtn_clicked();
	void on_backBtn_clicked();

	void updateWlenCompenList();
	
};

#endif // WAVEFIXPAGE_H
