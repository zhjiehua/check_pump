#include "glpinfopage.h"
#include <QDebug>
#include "baseMainPage.h"
#include <QApplication>
#include <QKeyEvent>

//#define TIME_UNIT_BASE 1//单位是s，测试用;
#define TIME_UNIT_BASE 3600//单位小时，真正用;


GlpInfoPage::GlpInfoPage(QWidget *parent /*= 0*/, quint8 index, quint8 previndex, quint32 add)
	: CBasePage(tr("GLP Information"), index, previndex, add, parent )
{
	ui.setupUi(this);
	m_strTitle = tr("GLP Information");
    setStyleSheet(BTNGLOBALSTYLE);

	QTimer *pTimer = new QTimer(this);
	connect(pTimer, SIGNAL(timeout()), this, SLOT(updateUsedTime()));
	pTimer->start(1000);
}

//系统累计使用时间显示;
//updateUsedTime();

GlpInfoPage::~GlpInfoPage()
{

}


void GlpInfoPage::initFocusList()
{
	//xList.append(ui.lpBtn);
	//xList.append(ui.lampEdit);
	//xList.append(ui.historyBtn);

	//yList.append(ui.lpBtn);
	//yList.append(ui.historyBtn);
	//yList.append(ui.lampEdit);

	ui.lampEdit->setValRange(QString("lampcha"),0,1000,0);

	int whichLamp = DataBase::getInstance()->queryData("xe_tun").toInt();
	if(whichLamp == 0)
	{
		int usedTime = DataBase::getInstance()->queryData("xeUsedTime").toInt();
		usedTime /= TIME_UNIT_BASE;
		ui.dLpUsedLbl->setText(QString::number(usedTime)+QString("h"));

		ui.tLampLable->hide();
		ui.tLpUsedLbl->hide();
	}
	else
	{
		int usedTime = DataBase::getInstance()->queryData("tunUsedTime").toInt();
		usedTime /= TIME_UNIT_BASE;
		ui.tLpUsedLbl->setText(QString::number(usedTime)+QString("h"));
		ui.dLampLable->hide();
		ui.dLpUsedLbl->hide();
	}

	if(MachineStat::getInstance()->pwdOK)
	{
		MachineStat::getInstance()->pwdNeed = false;
		
		//xList.append(ui.lampEdit);
		xList.append(ui.lpBtn);
		xList.append(ui.historyBtn);

		//yList.append(ui.lampEdit);
		yList.append(ui.lpBtn);
		yList.append(ui.historyBtn);
		

		ui.lampEdit->setEnabled(false);
	}
	else
	{
		MachineStat::getInstance()->pwdNeed = true;

		//xList.append(ui.lampEdit);
		xList.append(ui.lpBtn);
		xList.append(ui.historyBtn);

		//yList.append(ui.lampEdit);
		yList.append(ui.lpBtn);
		yList.append(ui.historyBtn);
	
		ui.lampEdit->setEnabled(false);
	}
	MachineStat::getInstance()->pwdOK = false;
	ui.lpBtn->installEventFilter(this);

	QString temp = DataBase::getInstance()->queryData("manufYear");
	temp += "-";
	temp += DataBase::getInstance()->queryData("manufMonth");
	temp += "-";
	temp += DataBase::getInstance()->queryData("manufDay");
	ui.manufLabel->setText(temp);

	temp = DataBase::getInstance()->queryData("instYear");
	temp += "-";
	temp += DataBase::getInstance()->queryData("instMonth");
	temp += "-";
	temp += DataBase::getInstance()->queryData("instDay");
	ui.instLabel->setText(temp);

	temp = DataBase::getInstance()->queryData("repairYear");
	temp += "-";
	temp += DataBase::getInstance()->queryData("repairMonth");
	temp += "-";
	temp += DataBase::getInstance()->queryData("repairDay");
	ui.repairLabel->setText(temp);

	updateUsedTime();
}

bool GlpInfoPage::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::KeyPress )
	{
		QKeyEvent *ke = (QKeyEvent *)(event);
		if( ke->key() == Qt::Key_Return && MachineStat::getInstance()->pwdNeed)
		{
			MachineStat::getInstance()->whichPage = g_pMainWindow->GetPageIndex();
			MachineStat::getInstance()->usrType = MachineStat::LAMP;
			g_pMainWindow->changePage(PWDPAGE_INDEX);
			return true;
		}
	}

	return false;
}

CBasePage* GlpInfoPage::getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add)
{
	return new GlpInfoPage(parent, index, previndex, add);
}


void GlpInfoPage::on_historyBtn_clicked()
{
	//qDebug()<<"history";
	g_pMainWindow->changePage(GRADIENTPAGE_INDEX);
}

void GlpInfoPage::on_lpBtn_clicked()
{
	int cnt = DataBase::getInstance()->queryData("lampcha").toInt();
	cnt++;
	DataBase::getInstance()->updateDate("lampcha", QString::number(cnt));
	int nLampWhich = DataBase::getInstance()->queryData("xe_tun").toInt();

	//记录灯的使用记录(灯的类型、灯的结束使用日期、灯的时间)
	QString strLamp;
	QString strTime;
	QString strEndDate = QDate::currentDate().toString(Qt::ISODate);
	if( nLampWhich == 0 )
	{
		//strLamp = QString(tr("Deuterium Lamp"));
		strLamp = QString(tr("D Lamp"));
		strTime = QString("%1h").arg(MachineStat::getInstance()->getTime(MachineStat::XEUSEDTIME)/3600);
		MachineStat::getInstance()->clearTime(MachineStat::XEUSEDTIME);
	}
	else
	{
		//strLamp = QString(tr("Tungsten Lamp"));
		strLamp = QString(tr("T Lamp"));
		strTime = QString("%1h").arg(MachineStat::getInstance()->getTime(MachineStat::TUNUSEDTIME)/3600);
		MachineStat::getInstance()->clearTime(MachineStat::TUNUSEDTIME);
	}

	//插入到数据库中
	DataBase::getInstance()->insertLampHistoryRecord(strLamp, strTime, strEndDate);
}

#define YEAR_SECOND	(60×60×24×365)
void GlpInfoPage::updateUsedTime()
{
	int totalSec = MachineStat::getInstance()->getTime(MachineStat::SYSTIME);
	int totalHour = totalSec/TIME_UNIT_BASE;
	int totalDay = totalHour/24;
	totalHour%=24;
	int totalMin = totalSec % TIME_UNIT_BASE / 60 ;
	totalSec = totalSec % TIME_UNIT_BASE % 60 ;

	QString strDisp = QString::number(totalDay)+tr("Day")+"  "+QString::number(totalHour)+tr("Hour")+"  "+QString::number(totalMin)+tr("Min")+"  "+QString::number(totalSec)+tr("Sec");
	ui.usedTimeLbl->setText(strDisp);
}

