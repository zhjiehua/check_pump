#include "AdminPage.h"
#include <QKeyEvent>
#include "ui_AdminPage.h"
#include <QDebug>
#include <QMessageBox>
#include "baseMainPage.h"
#include "machinestat.h"

#include "msgbox.h"
#include <QFile>

#ifdef WIN32
#define SRCFILE			"E:/weiduodianzi.txt"
#define TARGETFILE		"F:/weiduodianzi.txt"

#define SRCDBFILE		"E:/wda.txt"
#define TARGETDBFILE	"F:/wda.txt"
#else
#define SRCFILE			"/sdcard/sepuyi"
#define TARGETFILE		"/bin/weiduodianzi"

#define SRCDBFILE		"/sdcard/wda.db"
#define TARGETDBFILE	"/bin/wda.db"
#endif

AdminPage::AdminPage(QWidget *parent /*= 0*/, quint8 index, quint8 previndex, quint32 add)
	: CBasePage(tr("AdminPage"), index, previndex, add, parent )
{
	ui.setupUi(this);
	m_strTitle = tr("Admin");
}


AdminPage::~AdminPage(void)
{
}



void AdminPage::initFocusList()
{
	setStyleSheet(BTNGLOBALSTYLE);

	xList.append(ui.activeBtn);
	xList.append(ui.utcBtn);
	xList.append(ui.xtcBtn);
	xList.append(ui.ttcBtn);
	xList.append(ui.lpcBtn);
	xList.append(ui.rstBtn);
	xList.append(ui.saveDataBtn);
	xList.append(ui.updateDataBtn);
	xList.append(ui.manufYearEdit);
	xList.append(ui.manufMonthEdit);
	xList.append(ui.manufDayEdit);
	xList.append(ui.instYearEdit);
	xList.append(ui.instMonthEdit);
	xList.append(ui.instDayEdit);
	xList.append(ui.repairYearEdit);
	xList.append(ui.repairMonthEdit);
	xList.append(ui.repairDayEdit);
	xList.append(ui.licenseEdit);
	xList.append(ui.proCombo);
	xList.append(ui.serialEdit);
    xList.append(ui.connectCombo);

	yList.append(ui.activeBtn);
	yList.append(ui.utcBtn);
	yList.append(ui.xtcBtn);
	yList.append(ui.ttcBtn);
	yList.append(ui.lpcBtn);
	yList.append(ui.rstBtn);
	yList.append(ui.saveDataBtn);
	yList.append(ui.updateDataBtn);
	yList.append(ui.manufYearEdit);
	yList.append(ui.instYearEdit);
	yList.append(ui.repairYearEdit);
	yList.append(ui.manufMonthEdit);
	yList.append(ui.instMonthEdit);
	yList.append(ui.repairMonthEdit);
	yList.append(ui.manufDayEdit);
	yList.append(ui.instDayEdit);
	yList.append(ui.repairDayEdit);
	yList.append(ui.licenseEdit);
	yList.append(ui.serialEdit);
	yList.append(ui.proCombo);
    yList.append(ui.connectCombo);

	ui.repairYearEdit->setValRange("repairYear", 1990, 2050, 0);
	ui.repairMonthEdit->setValRange("repairMonth", 1, 12, 0);
	ui.repairDayEdit->setValRange("repairDay", 0, 31, 0);

	ui.manufYearEdit->setValRange("manufYear", 1990, 2050, 0);
	ui.manufMonthEdit->setValRange("manufMonth", 1, 12, 0);
	ui.manufDayEdit->setValRange("manufDay", 0, 31, 0);

	ui.instYearEdit->setValRange("instYear", 1990, 2050, 0);
	ui.instMonthEdit->setValRange("instMonth", 1, 12, 0);
	ui.instDayEdit->setValRange("instDay", 0, 31, 0);
	//ui.licenseEdit->setValRange("license", 0, 9999999999, 0, 10);
	ui.licenseEdit->setValRange("license", 0, 9999999999);//������޸�@2016-06-08
	ui.serialEdit->setValRange("serial", 0, 9999999999, 0, 10);
	//ui.dayEdit->setValRange("tryDay", 1, 1000, 0);
	ui.proCombo->setVar("pcProtocol");
    ui.connectCombo->setVar("connect_port");
	connect(ui.proCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(changePcPro(int)));
	connect(ui.connectCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(changeConnectPort(int)));
	//connect(ui.dayEdit, SIGNAL(dataChanging(QString)), this, SLOT(tryDayChanged(QString)) );

	//ui.activeBtn->setFocus();
	//ui.dayEdit->setEnabled(false);
	ui.licenseEdit->setTextMode();
	ui.serialEdit->setTextMode();
	ui.licenseEdit->setReadOnly(true);
	ui.instYearEdit->setReadOnly(true);
}


CBasePage* AdminPage::getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add)
{
	return new AdminPage(parent, index, previndex, add);
}

void AdminPage::on_activeBtn_clicked()
{
	MsgBox msgBox(this, tr("Tips"), tr("Comfirm to Cancel Active!!!"));
	if(msgBox.exec() == QMessageBox::Ok)
	{
		MachineStat::getInstance()->activeMachine(0, 0);				//ȡ������;
		MachineStat::getInstance()->clearTime(MachineStat::SYSTIME);	//�������������¼���;
	}
}

void AdminPage::on_utcBtn_clicked()
{
	MsgBox msgBox(this, tr("Tips"), tr("Comfirm to Clear!!!"));
	if(msgBox.exec() == QMessageBox::Ok)
		MachineStat::getInstance()->clearTime(MachineStat::SYSTIME);
}

void AdminPage::on_xtcBtn_clicked()
{
	MsgBox msgBox(this, tr("Tips"), tr("Comfirm to Clear!!!"));
	if(msgBox.exec() == QMessageBox::Ok)
		MachineStat::getInstance()->clearTime(MachineStat::XEUSEDTIME);
}

void AdminPage::on_ttcBtn_clicked()
{
	MsgBox msgBox(this, tr("Tips"), tr("Comfirm to Clear!!!"));
	if(msgBox.exec() == QMessageBox::Ok)
		MachineStat::getInstance()->clearTime(MachineStat::TUNUSEDTIME);
}

void AdminPage::changePcPro(int idx)
{
	MachineStat::getInstance()->setPcProtocol(idx);
}

void AdminPage::changeConnectPort(int idx)
{
	MachineStat::getInstance()->setConnectPort(idx);
}

void AdminPage::on_lpcBtn_clicked()
{
	MsgBox msgBox(this, tr("Tips"), tr("Comfirm to Clear!!!"));
	if(msgBox.exec() == QMessageBox::Ok)
	{
		//����л���Դ����;
		DataBase::getInstance()->updateDate("lampcha", "0");

		//�����Դ��ʷ��¼;
		DataBase::getInstance()->clearLampHistoryRecord();
	}
}

void AdminPage::tryDayChanged(QString val)
{
	MachineStat::getInstance()->clearTime(MachineStat::SYSTIME);
}

void AdminPage::on_rstBtn_clicked()
{
	MsgBox msgBox(this, tr("Tips"), tr("Comfirm to Restore!!!"));
	if(msgBox.exec() == QMessageBox::Ok)
	{
		DataBase::getInstance()->restoreDatabase();
	}
}

//��������
void AdminPage::on_saveDataBtn_clicked()
{
	QFile file(TARGETDBFILE);
	if(!file.exists())
	{
		MsgBox msgBox(this,tr("Tips"), tr("file not found!"));
		msgBox.exec();
		return;
	}

	QFile target(SRCDBFILE);
	if(target.exists())
		qDebug()<<target.remove();
	if(QFile::copy(TARGETDBFILE, SRCDBFILE) )
	{
		MsgBox msgBox(this,tr("Tips"), tr("success!"));
		msgBox.exec();
	}
	else
	{
		MsgBox msgBox(this,tr("Tips"), tr("failed!"));
		msgBox.exec();
	}

}

//��������
void AdminPage::on_updateDataBtn_clicked()
{
	MsgBox msgBox(this, tr("Tips"), tr("Comfirm to update data?"));
	if(msgBox.exec() != QMessageBox::Ok)
		return;

	QFile file(SRCDBFILE);
	if(!file.exists())
	{
		MsgBox msgBox(this,tr("Tips"), tr("file not found!"));
		msgBox.exec();
		return;
	}

	QFile target(TARGETDBFILE);
	if(target.exists())
		qDebug()<<target.remove();
	if(QFile::copy(SRCDBFILE, TARGETDBFILE) )
	{
		MsgBox msgBox(this,tr("Tips"), tr("success!"));
		msgBox.exec();
	}
	else
	{
		MsgBox msgBox(this,tr("Tips"), tr("failed!"));
		msgBox.exec();
	}

}
