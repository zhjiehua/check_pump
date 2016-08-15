#include "ScanPage.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include "baseMainPage.h"
#include "Common.h"
#include "msgbox.h"

bool ScanPage::flag = false;

ScanPage::ScanPage(QWidget *parent /*= 0*/, quint8 index, quint8 previndex, quint32 add)
	: CBasePage(tr("Scan"), index, previndex, add, parent )
	//, flag(false)
{
	ui.setupUi(this);
	m_strTitle = tr("Scan");
}

ScanPage::~ScanPage()
{
	//if(flag)
	//	MachineStat::getInstance()->setWaveScanMode(false);

	//MachineStat::getInstance()->setUploadPcValChanel(0);//ÕÅ½Ü»ªµ÷ÊÔÆÁ±Î@2016-07-26
}

void ScanPage::initFocusList()
{
	xList.append(ui.sWlen);
	xList.append(ui.eWlen);
	xList.append(ui.sTime);
	xList.append(ui.scanBtn);
	xList.append(ui.uploadWhichCombo);

	yList.append(ui.sWlen);
	yList.append(ui.eWlen);
	yList.append(ui.sTime);
	yList.append(ui.scanBtn);
	yList.append(ui.uploadWhichCombo);

	ui.sWlen->setValRange(QString("sWlen"),190,800, 0);
	ui.eWlen->setValRange(QString("eWlen"),190,800, 0);
	ui.sTime->setValRange(QString("sTime"),0,1000, 0);
	ui.uploadWhichCombo->setVar("uploadWhich");
	ui.uploadWhichCombo->setCurrentIndex(DataBase::getInstance()->queryData("uploadWhich").toInt());
	if(flag)
		ui.scanBtn->setText(tr("Stop"));
	else
		ui.scanBtn->setText(tr("Scan"));

	setStyleSheet(BTNGLOBALSTYLE);

	updateWlenDisp(DataBase::getInstance()->queryData("wavelen1"));
	updateAuValue(MachineStat::getInstance()->getMachineState().m_nSampleVal,
					MachineStat::getInstance()->getMachineState().m_nRefVal,
					MachineStat::getInstance()->getMachineState().m_dAu1,0);

	connect(MachineStat::getInstance(), SIGNAL(wLenChanged(QString, quint8)), this, SLOT(updateWlenDisp( QString)));
	connect(MachineStat::getInstance(), SIGNAL(updateAuValue(quint32, quint32, double, quint8)), this, SLOT(updateAuValue(quint32, quint32, double, quint8)));
	connect(ui.uploadWhichCombo, SIGNAL(currentIndexChanged(int)), MachineStat::getInstance(), SLOT(setUploadPcValChanel(int)) );
	connect(MachineStat::getInstance(), SIGNAL(wLenScanDone()), this, SLOT(scanDone()) );


	if(MachineStat::getInstance()->pwdOK)
		MachineStat::getInstance()->pwdNeed = false;
	else
		MachineStat::getInstance()->pwdNeed = true;
	MachineStat::getInstance()->pwdOK = false;
	ui.uploadWhichCombo->installEventFilter(this);
}

bool ScanPage::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::KeyPress )
	{
		QKeyEvent *ke = (QKeyEvent *)(event);
		if( ke->key() == Qt::Key_Return && MachineStat::getInstance()->pwdNeed)
		{
			MachineStat::getInstance()->whichPage = g_pMainWindow->GetPageIndex();
			MachineStat::getInstance()->usrType = MachineStat::USER;
			g_pMainWindow->changePage(PWDPAGE_INDEX);
			return true;
		}
	}

	return false;
}

void ScanPage::on_scanBtn_clicked()
{
	flag = !flag;
	
	if(flag)
	{
		if( !checkScanRange() )
		{
			MsgBox msgBox(this, tr("Tips"), tr("End wave must larger than begin wave!"));
			msgBox.exec();
			flag = !flag;
			return;
		}
		ui.scanBtn->setText(tr("Stop"));
	}
	else
	{
		ui.scanBtn->setText(tr("Scan"));
	}
	MachineStat::getInstance()->setWaveScanMode(flag, ui.sWlen->text().toDouble(), ui.eWlen->text().toDouble(), ui.sTime->text().toInt());
}

CBasePage* ScanPage::getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add)
{
	return new ScanPage(parent, index, previndex, add);
}

void ScanPage::updateWlenDisp( QString str )
{
	ui.wLenLbl->setText(str);
}

void ScanPage::updateAuValue( quint32 s, quint32 r, double au, quint8 which )
{
	ui.sLbl->setText(QString::number(s).rightJustified(7,'0'));
	ui.rLbl->setText(QString::number(r).rightJustified(7,'0'));
	ui.auLbl->setText(QString::number(au, 'f', 4));
}

void ScanPage::scanDone()
{
	if(flag)
		on_scanBtn_clicked();
}

bool ScanPage::checkScanRange()
{
	return (ui.sWlen->text().toDouble() < ui.eWlen->text().toDouble() );
}





