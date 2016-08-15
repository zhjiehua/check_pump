#include "DebugMcuProtoPage.h"
#include "baseMainPage.h"
#include "editordelegate.h"
#include "database.h"
#include "iomodule.h"

DebugMcuProtoPage::DebugMcuProtoPage(QWidget *parent /*= 0*/, quint8 index, quint8 previndex, quint32 add)
	: CBasePage(tr("DebugMcuProtoPage"), index, previndex, add, parent )
	, m_bCollectFlag(false)
	, m_bStartFlag(false)
	, m_nBulgeFlag(0)
{
	ui.setupUi(this);
	m_strTitle = tr("DebugPressPage");
	initDisplay();
}


DebugMcuProtoPage::~DebugMcuProtoPage(void)
{
	if(timer)
		delete timer;

	if(m_bStartFlag)
	{
		//MachineStat::getInstance()->updateFlow("0", true);//停止;
		//MachineStat::getInstance()->endUpdateFlow();
	}
}

void DebugMcuProtoPage::initFocusList()
{
	xList.append(ui.tableView);
	xList.append(ui.flowEdit);
	xList.append(ui.startBtn);
	xList.append(ui.clearBtn);
	xList.append(ui.collectBtn);

	yList.append(ui.tableView);
	yList.append(ui.flowEdit);
	yList.append(ui.startBtn);
	yList.append(ui.clearBtn);
	yList.append(ui.collectBtn);

	setStyleSheet(BTNGLOBALSTYLE);
}



CBasePage* DebugMcuProtoPage::getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add)
{
	return new DebugMcuProtoPage(parent, index, previndex, add);
}

void DebugMcuProtoPage::initDisplay()
{
	gradient_model = new MyTableModel(this, 2);
	ui.tableView->setModel(gradient_model);
	ui.tableView->setColumnWidth(0,85);    
	ui.tableView->setColumnWidth(1,85);    
	ui.tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed);

	//为每一列设置代理;
	ui.tableView->setItemDelegateForColumn(0, new EditorDelegate("000.0000"));//压力;
	ui.tableView->setItemDelegateForColumn(1, new EditorDelegate("000.0000"));//校准;
	ui.tableView->initIndex();


	int array[7]={42, 25 , 20, 20, 15, 10, 10};
	int pumpType = DataBase::getInstance()->queryData("pumptype").toInt();
	if(pumpType > 6)
		pumpType = 0;
	double maxFlow = array[pumpType];
	ui.flowEdit->setValRange("flowRate", 0, maxFlow, 3);

	connect(IoModule::getInstance(), SIGNAL(bulge()), this, SLOT(dealBulge()));
	connect(ui.tableView, SIGNAL(getOutFocus(int)), this, SLOT(getOutTableFocus(int)));
	connect(MachineStat::getInstance(), SIGNAL(updatePressDisplay(QString, quint8)), this, SLOT(updatePressVal(QString, quint8)));
	timer = new QTime();
}

void DebugMcuProtoPage::getOutTableFocus(int dir)
{
	if(dir == 0)
		ui.collectBtn->setFocus();
	else if(dir == 1)
		ui.flowEdit->setFocus();
	else if(dir == 2)
		ui.flowEdit->setFocus();
	else if(dir == 3)
		ui.flowEdit->setFocus();
}

void DebugMcuProtoPage::updatePressVal(QString press, quint8 add)
{
	if(m_bCollectFlag)
	{
		QStringList list;
		list.append(QString::number(((double)timer->elapsed()/1000.0)));
		list.append(press);
		list.append(QString::number(getBulge()));
		int row = gradient_model->rowCount();
		gradient_model->insertRow(row, MyTableModel::USERDATA, list);
		if(row >= 1000)
		{
			gradient_model->removeRow(0);
		}
			
		ui.tableView->scrollToBottom();
	}
	
}

void DebugMcuProtoPage::on_collectBtn_clicked()
{
	m_bCollectFlag = !m_bCollectFlag;
	if(m_bCollectFlag)
	{
		timer->restart();
	}
	else
	{
		//保存文件;
		DataBase::getInstance()->saveTableToFile(QString("/sdcard/press.txt"), gradient_model->getTableData());
	}
}

void DebugMcuProtoPage::on_clearBtn_clicked()
{
	//MachineStat::getInstance()->clearPress();
}

void DebugMcuProtoPage::on_startBtn_clicked()
{
	m_bStartFlag = !m_bStartFlag;
	if(m_bStartFlag)
	{
		//MachineStat::getInstance()->updateFlow(ui.flowEdit->text(), true);//开始
		//MachineStat::getInstance()->beginUpdateFlow();
	}
	else
	{
		//MachineStat::getInstance()->endUpdateFlow();
	}
}

void DebugMcuProtoPage::dealBulge()
{
	m_nBulgeFlag = 1;
}

int DebugMcuProtoPage::getBulge()
{
	if(m_nBulgeFlag)
	{
		m_nBulgeFlag = 0;
		return 1;
	}
	else
		return 0;
}



