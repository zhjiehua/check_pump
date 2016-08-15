#ifndef SETUPLISTPAGE_H
#define SETUPLISTPAGE_H

#include "BasePage.h"
#include "ui_DebugMcuProtoPage.h"
#include "baseMainPage.h"
#include "mytablemodel.h"
#include <QTimer>
#include <QTime>


class DebugMcuProtoPage: public CBasePage
{
	Q_OBJECT
public:
	DebugMcuProtoPage(QWidget *parent = 0, quint8 index = 0, quint8 previndex = 0, quint32 add = 0);
	~DebugMcuProtoPage(void);

	static CBasePage* getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add);

protected:
	void initFocusList();

private:
	Ui::DebugMcuProtoPageClass ui;
	bool m_bStartFlag;
	bool m_bCollectFlag;
	int m_nBulgeFlag;
	MyTableModel *gradient_model;
	QTime *timer;

	void initDisplay();
	int getBulge();

private slots:
	void on_startBtn_clicked();
	void on_collectBtn_clicked();
	void on_clearBtn_clicked();
	void getOutTableFocus(int dir);
	void updatePressVal(QString, quint8);
	void dealBulge();//´¦ÀíÍ¹ÂÖÐÅºÅ;

};

#endif // SETUPLISTPAGE_H