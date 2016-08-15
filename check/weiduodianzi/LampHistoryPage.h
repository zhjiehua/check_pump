#ifndef LAMPHISTORYPAGE_H
#define LAMPHISTORYPAGE_H

#include "BasePage.h"
#include "ui_LampHistoryPage.h"
#include "baseMainPage.h"

class LampHistoryPage: public CBasePage
{
	Q_OBJECT
public:
	LampHistoryPage(QWidget *parent = 0, quint8 index = 0, quint8 previndex = 0, quint32 add = 0);
	~LampHistoryPage(void);
	static CBasePage* getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add);

protected:
	void initFocusList();


private:
	Ui::LampHistoryPageClass ui;

	void initDisplay();

private slots:
	void on_firstBtn_clicked();
	void on_prevBtn_clicked();
	void on_lastBtn_clicked();
	void on_nextBtn_clicked();

};


#endif // LAMPHISTORYPAGE_H
