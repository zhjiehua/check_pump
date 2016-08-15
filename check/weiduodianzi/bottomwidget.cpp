#include "bottomwidget.h"
#include <QDebug>
#include "baseMainPage.h"
#include <QShortcut>

#define BTNNORMALSTYLE "QPushButton{border-image:url(:/weiduodianzi/ui/normalNavigator.png);}""QPushButton{border: 2px solid green;outline: 0px;}"
#define BTNFOCUSSTYLE "QPushButton:focus{border-image:url(:/weiduodianzi/ui/focusNavigator.png);border: 2px solid green;outline: 0px;}""QPushButton{border-image:url(:/weiduodianzi/ui/activeNavigator.png);border: 2px solid green;outline: 0px;}"

#define LAMPONSTYLE  "QLabel{border-image:url(:/weiduodianzi/ui/light_on.png);}"
#define LAMPOFFSTYLE  "QLabel{border-image:url(:/weiduodianzi/ui/light_off.png);}"
#define LAMPERRSTYLE  "QLabel{border-image:url(:/weiduodianzi/ui/light_err.png);}"

#define CONNECTSTYLE  "QLabel{border-image:url(:/weiduodianzi/ui/connect_established.png);}"
#define DISCONNECTSTYLE  "QLabel{border-image:url(:/weiduodianzi/ui/disconnect.png);}"

BottomWidget::BottomWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initNavigator();
	connect(MachineStat::getInstance(), SIGNAL(systemError(int, QString)), this, SLOT(updateWarning(int, QString)));

	connect(MachineStat::getInstance(), SIGNAL(sampleLow(bool)), this, SLOT(sampleLow(bool)));
	connect(MachineStat::getInstance(), SIGNAL(referenceLow(bool)), this, SLOT(referenceLow(bool)));
	connect(MachineStat::getInstance(), SIGNAL(lampState(quint8)), this, SLOT(lampState(quint8)));

	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::red);
	ui.lowRLabel->setPalette(pa);
	ui.lowSLabel->setPalette(pa);
	ui.lowRLabel->setText("");
	ui.lowSLabel->setText("");

	//ui.label->setText("");
	//updateWarning(0, tr("No Warn"));
	//ui.lampLabel->setStyleSheet(LAMPOFFSTYLE);
}



BottomWidget::~BottomWidget()
{

}


void BottomWidget::initNavigator()
{
	m_btnList.append(ui.runBtn);
	m_btnList.append(ui.paramBtn);
	m_btnList.append(ui.setBtn);
#ifndef linux
	//m_btnList.append(ui.dbgBtn);
	ui.dbgBtn->hide();
#else
	ui.dbgBtn->hide();
#endif
}





void BottomWidget::on_runBtn_clicked()
{
	g_pMainWindow->navigatorPageAt(0);
}



void BottomWidget::on_paramBtn_clicked()
{
	g_pMainWindow->navigatorPageAt(1);
}



void BottomWidget::on_setBtn_clicked()
{
	g_pMainWindow->navigatorPageAt(2);
}



void BottomWidget::on_dbgBtn_clicked()
{
	g_pMainWindow->navigatorPageAt(3);
}




void BottomWidget::changeNavigatorDisp(quint8 index)
{
	for(int i = 0; i < m_btnList.count(); i++)
	{
		if(i != index)
			m_btnList.at(i)->setStyleSheet(BTNNORMALSTYLE);
		else
		{
			m_btnList.at(i)->setStyleSheet(BTNFOCUSSTYLE);
			m_btnList.at(i)->setFocus();
		}
	}

}

void BottomWidget::updateWarning(int err, QString str)
{
	QPalette pa;
	//if(err == 0)
	//	pa.setColor(QPalette::WindowText, Qt::blue);
	//else
	//	pa.setColor(QPalette::WindowText, Qt::red);
	//ui.label->setPalette(pa);
	//ui.label->setText(str);

	if(err)
		ui.label->setStyleSheet(DISCONNECTSTYLE);
	else
		ui.label->setStyleSheet(CONNECTSTYLE);
}

void BottomWidget::updateLanguage()
{
	ui.runBtn->setText(tr("Run"));
	ui.paramBtn->setText(tr("Param"));
	ui.setBtn->setText(tr("Setup"));
	ui.dbgBtn->setText(tr("Debug"));
	MachineStat::getInstance()->updateWarning();//���������@2016-06-18
}



void BottomWidget::sampleLow(bool low)
{
	if(low)
		ui.lowSLabel->setText("Ls");
	else
		ui.lowSLabel->setText("");
}

void BottomWidget::referenceLow(bool low)
{
	if(low)
		ui.lowRLabel->setText("Lr");
	else
		ui.lowRLabel->setText("");
}

void BottomWidget::lampState(quint8 state)
{
	if(state == 1)
		ui.lampLabel->setStyleSheet(LAMPONSTYLE);
		//ui.lampLabel->setStyleSheet(LAMPERRSTYLE);
	else if(state == 2)
		ui.lampLabel->setStyleSheet(LAMPOFFSTYLE);
	else
		ui.lampLabel->setStyleSheet(LAMPERRSTYLE);
}
