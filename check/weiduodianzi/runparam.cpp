#include "runparam.h"
#include <QDebug>
#include "Common.h"
#include "database.h"
#include "machinestat.h"
#include "msgbox.h"

RunParamPage::RunParamPage(QWidget *parent /*= 0*/, quint8 index, quint8 previndex, quint32 add)
	: CBasePage(tr("Parameters"), index, previndex, add, parent )
{
	ui.setupUi(this);
	m_strTitle = tr("Parameters");
}

RunParamPage::~RunParamPage()
{

}


void RunParamPage::initFocusList()
{
	quint32 channel = DataBase::getInstance()->queryData("chanel").toInt();

	xList.append(ui.wLen1Edit);
	if(channel == 1)
		xList.append(ui.wLen2Edit);
	else
		ui.wLen2Edit->setEnabled(false);
	xList.append(ui.rangeCombo);
	xList.append(ui.timeCombo);
	xList.append(ui.chlCombo);
	xList.append(ui.lhtCombo);
	xList.append(ui.sDispCombo);
	xList.append(ui.rDispCombo);

	yList.append(ui.wLen1Edit);
	yList.append(ui.rangeCombo);
	yList.append(ui.chlCombo);
	yList.append(ui.sDispCombo);
	if(channel == 1)
		yList.append(ui.wLen2Edit);
	yList.append(ui.timeCombo);
	yList.append(ui.lhtCombo);
	yList.append(ui.rDispCombo);

	ui.wLen1Edit->setValRange(QString("wavelen1"),190,800, 0);
	ui.wLen2Edit->setValRange(QString("wavelen2"),190,800, 0);
	
	ui.wLen1Edit->disableAutoSave();
	ui.wLen2Edit->disableAutoSave();

	ui.chlCombo->setVar(QString("chanel"));
	ui.lhtCombo->setVar(QString("xe_tun"));
	ui.rangeCombo->setVar(QString("range"));
	ui.timeCombo->setVar(QString("timeconst"));
	ui.sDispCombo->setVar(QString("sampleDisp"));
	ui.rDispCombo->setVar(QString("refDisp"));

	connect(ui.wLen1Edit, SIGNAL(dataChanging(QString)), this, SLOT(waveLen1Changed(QString)));
	connect(ui.wLen2Edit, SIGNAL(dataChanging(QString)), this, SLOT(waveLen2Changed(QString)));
	connect(ui.chlCombo, SIGNAL(currentIndexChanged(int )), this, SLOT(chanelChnaged(int)));
	connect(ui.lhtCombo, SIGNAL(currentIndexChanged(int)), MachineStat::getInstance(), SLOT(changeLampSrc(int)));

	setStyleSheet(BTNGLOBALSTYLE);
}



CBasePage* RunParamPage::getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add)
{
	return new RunParamPage(parent, index, previndex, add);
}

void RunParamPage::waveLen1Changed(QString str)
{
	//quint8 chanel = DataBase::getInstance()->queryData("chanel").toInt();
	//if(chanel == 1)
	//{
	//	quint32 wave = QString(ui.wLen1Edit->text()).toInt();
	//	quint32 wave2 = DataBase::getInstance()->queryData("wavelen2").toInt();
	//	if(wave2 == wave)
	//	{
	//		MsgBox msgBox(this,tr("Tips"), tr("The wave shouldn't equal to wave2!"));
	//		msgBox.exec();
	//		ui.wLen1Edit->restoreData();
	//		return;
	//	}
	//}

	if( MachineStat::EStat_Busy == MachineStat::getInstance()->changeWaveLength(ui.wLen1Edit->text().toDouble(), MachineStat::EWLEN1 ) )
		ui.wLen1Edit->restoreData();
	else //伍剑飞添加@2016-06-29
		ui.wLen1Edit->saveData(ui.wLen1Edit->text());
}

void RunParamPage::chanelChnaged( int ch)
{
	//quint32 wave = DataBase::getInstance()->queryData("wavelen1").toInt();
	//quint32 wave2 = DataBase::getInstance()->queryData("wavelen2").toInt();
	//if(ch == 1 && wave2 == wave)
	//{
	//	ui.chlCombo->setCurrentIndex(0);
	//	MsgBox msgBox(this,tr("Tips"), tr("The two waves shouldn't be equal!"));
	//	msgBox.exec();
	//	return;
	//}

	MachineStat::getInstance()->chanelChanged(ch);
	
	if(ch == 0)
		ui.wLen2Edit->setEnabled(false);
	else
		ui.wLen2Edit->setEnabled(true);

	//更新光标列表
	xList.clear();
	yList.clear();

	xList.append(ui.wLen1Edit);
	if(ch == 1)
		xList.append(ui.wLen2Edit);
	xList.append(ui.rangeCombo);
	xList.append(ui.timeCombo);
	xList.append(ui.chlCombo);
	xList.append(ui.lhtCombo);
	xList.append(ui.sDispCombo);
	xList.append(ui.rDispCombo);

	yList.append(ui.wLen1Edit);
	yList.append(ui.rangeCombo);
	yList.append(ui.chlCombo);
	yList.append(ui.sDispCombo);
	if(ch == 1)
		yList.append(ui.wLen2Edit);
	yList.append(ui.timeCombo);
	yList.append(ui.lhtCombo);
	yList.append(ui.rDispCombo);
}

void RunParamPage::waveLen2Changed(QString str)
{
	quint8 chanel = DataBase::getInstance()->queryData("chanel").toInt();
	//if(chanel == 1)
	//{
	//	quint32 wave = DataBase::getInstance()->queryData("wavelen1").toInt();
	//	quint32 wave2 = QString(ui.wLen2Edit->text()).toInt();
	//	if(wave2 == wave)
	//	{
	//		MsgBox msgBox(this,tr("Tips"), tr("The wave2 shouldn't equal to wave!"));
	//		msgBox.exec();
	//		ui.wLen2Edit->restoreData();
	//		return;
	//	}
	//}

	if(chanel == 0)//单波长;
	{
		ui.wLen2Edit->saveData(ui.wLen2Edit->text());
	}
	else
	{
		if( MachineStat::EStat_Busy == MachineStat::getInstance()->changeWaveLength(ui.wLen2Edit->text().toDouble(), MachineStat::EWLEN2 ) )
		{
			ui.wLen2Edit->restoreData();
		}
		else //伍剑飞添加@2016-06-29
			ui.wLen2Edit->saveData(ui.wLen2Edit->text());
	}
}



