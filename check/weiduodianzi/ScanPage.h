#ifndef SCANPAGE_H
#define SCANPAGE_H

#include "BasePage.h"
#include "ui_ScanPage.h"

class ScanPage : public CBasePage
{
	Q_OBJECT

public:
	ScanPage(QWidget *parent = 0, quint8 index = 0, quint8 previndex = 0, quint32 add = 0);
	~ScanPage();

	static CBasePage* getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add);

	bool eventFilter(QObject *obj, QEvent *event);

protected:
	virtual void initFocusList();
	

private:
	Ui::ScanPage ui;
	static bool flag;

	bool checkScanRange();					//检测扫描范围，起始波长必须大于扫描波长;
	
private slots:
	void on_scanBtn_clicked();
	void updateWlenDisp(QString str);
	void updateAuValue(quint32 s, quint32 r, double au, quint8 which);
	void scanDone();

};

#endif // SCANPAGE_H
