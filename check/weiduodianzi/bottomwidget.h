#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QWidget>
#include "ui_bottomwidget.h"

class BottomWidget;
typedef void (BottomWidget::*btnSlots)();

class BottomWidget : public QWidget
{
	Q_OBJECT

public:
	BottomWidget(QWidget *parent = 0);
	~BottomWidget();

	void changeNavigatorDisp(quint8 index);		//�ı䵼������ʾ;
	void updateLanguage();						//����������ʾ;

private:
	Ui::BottomWidget ui;
	QList<QPushButton *>m_btnList;

	void initNavigator();						//������ť��ʼ��;
	

private slots:
	void on_runBtn_clicked();
	void on_paramBtn_clicked();
	void on_setBtn_clicked();
	void on_dbgBtn_clicked();
	void updateWarning(int, QString);
	

	void sampleLow(bool);
	void referenceLow(bool);
	void lampState(quint8 state);
};

#endif // BOTTOMWIDGET_H
