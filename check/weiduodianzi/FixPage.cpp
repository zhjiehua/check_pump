#include "FixPage.h"
#include <QKeyEvent>
#include "baseMainPage.h"

static quint32 curCoef;
static quint32 curTimeInte;

FixPage::FixPage(QWidget *parent /*= 0*/, quint8 index, quint8 previndex, quint32 add)
	: CBasePage(tr("Calibration"), index, previndex, add, parent )
{
	ui.setupUi(this);
	m_strTitle = tr("Calibration");
	//setStyleSheet("QPushButton:focus{border:2px solid rgb(155,200,33);outline:0px;}");
	setStyleSheet("QPushButton:focus{border:2px solid blue;outline:0px;}");
}

FixPage::~FixPage(void)
{

}

void FixPage::initFocusList()
{
	xList.append(ui.coefficient);
	xList.append(ui.timeInteCombo);
	xList.append(ui.wavCalBtn);

	yList.append(ui.coefficient);
	yList.append(ui.timeInteCombo);
	yList.append(ui.wavCalBtn);

	//ui.timeInteBtn->setFocus();

	ui.coefficient->setValRange(QString("coefficient"),0,100, 3);
	ui.timeInteCombo->setVar(QString("timeInte"));
	connect(ui.timeInteCombo, SIGNAL(currentIndexChanged(int )), this, SLOT(timeInteChanged(int)));

	//connect(ui.coefficient, SIGNAL(textChanged(const QString &)), this, SLOT(coefficientChanged(const QString &)));
	if(MachineStat::getInstance()->pwdOK)
		MachineStat::getInstance()->pwdNeed = false;
	else
		MachineStat::getInstance()->pwdNeed = true;
	MachineStat::getInstance()->pwdOK = false;
	curCoef = DataBase::getInstance()->queryData("coefficient").toInt();
	curTimeInte = DataBase::getInstance()->queryData("timeInte").toInt(); 

    //! added by wjf 20160803
    ui.timeInteCombo->installEventFilter(this);
    ui.coefficient->installEventFilter(this);
}



CBasePage* FixPage::getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add)
{
	return new FixPage(parent, index, previndex, add);
}




void FixPage::on_wavCalBtn_clicked()
{
	//MachineStat::getInstance()->whichPage = FLOWFIXPAGE_INDEX;
	//MachineStat::getInstance()->usrType = MachineStat::USER;
	//g_pMainWindow->changePage(PWDPAGE_INDEX);

	g_pMainWindow->changePage(FLOWFIXPAGE_INDEX);
}

void FixPage::timeInteChanged( int timeInte)
{
	//if(MachineStat::getInstance()->pwdNeed)
	//{
	//	ui.timeInteCombo->setCurrentIndex(curTimeInte);
	//	//DataBase::getInstance()->updateDate("timeInte", QString::number(curTimeInte));
	//	MachineStat::getInstance()->whichPage = g_pMainWindow->GetPageIndex();
	//	//qDebug() << "timeInteChanged() whichPage = " << MachineStat::getInstance()->whichPage;
	//	MachineStat::getInstance()->usrType = MachineStat::USER;
	//	g_pMainWindow->changePage(PWDPAGE_INDEX);
	//}
	//else
		MachineStat::getInstance()->updateTimeInte();
}

void FixPage::coefficientChanged(const QString &s)
{
	if(MachineStat::getInstance()->pwdNeed)
	{
		ui.coefficient->setText(QString::number(curCoef));
		//DataBase::getInstance()->updateDate("coefficient", QString::number(curCoef));
		MachineStat::getInstance()->whichPage = g_pMainWindow->GetPageIndex();
		MachineStat::getInstance()->usrType = MachineStat::USER;
		g_pMainWindow->changePage(PWDPAGE_INDEX);
	}
}

bool FixPage::eventFilter(QObject *obj, QEvent *event)
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
