#include "CheckingPage.h"
#include <QMessageBox>
#include <QKeyEvent>
#include "msgbox.h"
#include "iomodule.h"
#include "machinestat.h"
#include "baseMainPage.h"



CheckingPage::CheckingPage(QWidget *parent /*= 0*/, quint8 index, quint8 previndex, quint32 add)
	: CBasePage(tr("Checking"), index, previndex, add, parent )
{
	ui.setupUi(this);
	m_strTitle = tr("Checking");
	setStyleSheet( BTNGLOBALSTYLE);

    QTimer *pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(updateTimer()) );
    pTimer->start(1000);

	if(MachineStat::getInstance()->noRTCBattery)
	{
		QPalette pa;
		pa.setColor(QPalette::WindowText, Qt::red);
		ui.batteryWarnLbl->setPalette(pa);
		ui.batteryWarnLbl->setText(tr("no battery!"));
	}
}



CheckingPage::~CheckingPage(void)
{
	
}

void CheckingPage::initFocusList()
{
	connect( IoModule::getInstance(), SIGNAL(initLampSuccess(bool)), this, SLOT(lampSuccess(bool)) );
	connect( MachineStat::getInstance(), SIGNAL(motorInitSuccessSignal()), this, SLOT(motorInitSuccess()) );
	
	//CHECKGLOBALSTYLE
	ui.lampCheck->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/weiduodianzi/ui/signalflag0.png);}""QCheckBox::indicator:checked {image: url(:/weiduodianzi/ui/signalflag1.png);}");
	ui.motorCheck->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/weiduodianzi/ui/signalflag0.png);}""QCheckBox::indicator:checked {image: url(:/weiduodianzi/ui/signalflag1.png);}");
}

CBasePage* CheckingPage::getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add)
{
	return new CheckingPage(parent, index, previndex, add);
}

void CheckingPage::lampSuccess(bool success)
{
	ui.lampCheck->setChecked(success);
}

void CheckingPage::motorInitSuccess()
{
	ui.motorCheck->setChecked(true);
	g_pMainWindow->checkingSuccess();
}

void CheckingPage::updateTimer()
{
    static int sec = 0;
    sec++;
	ui.startupTime->setText(QString::number(sec) + "s");
}



