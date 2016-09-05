#include "LampHistoryPage.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>
#include "msgbox.h"
#include "mytablemodel.h"
#include <QScrollBar>

#define RECORD_CNT_PERPAGE 3

extern int g_nActScreenX;
extern int g_nActScreenY;

LampHistoryPage::LampHistoryPage(QWidget *parent /*= 0*/, quint8 index, quint8 previndex, quint32 add)
	: CBasePage(tr("Lamp History"), index, previndex, add, parent )
{
	ui.setupUi(this);
	m_strTitle = tr("Lamp History");
	setStyleSheet( BTNGLOBALSTYLE);
	initDisplay();

	//QString temp = tr("Deu.Lamp");
	//temp = tr("Tung.Lamp");
}



LampHistoryPage::~LampHistoryPage(void)
{
	
}

void LampHistoryPage::initFocusList()
{
	xList.append(ui.firstBtn);
	xList.append(ui.prevBtn);
	xList.append(ui.nextBtn);
	xList.append(ui.lastBtn);

	yList.append(ui.firstBtn);
	yList.append(ui.prevBtn);
	yList.append(ui.nextBtn);
	yList.append(ui.lastBtn);
}



CBasePage* LampHistoryPage::getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add)
{
	return new LampHistoryPage(parent, index, previndex, add);
}

void LampHistoryPage::on_firstBtn_clicked()
{
	ui.tableView->scrollToTop();
}

void LampHistoryPage::on_prevBtn_clicked()
{
	int maxValue = ui.tableView->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值25
	int nCurScroller = ui.tableView->verticalScrollBar()->value(); //获得当前scroller值
	if(nCurScroller > 0)
	{
		if(nCurScroller >= RECORD_CNT_PERPAGE)
			nCurScroller -= RECORD_CNT_PERPAGE;
		else
			nCurScroller = 0;
		ui.tableView->verticalScrollBar()->setSliderPosition(nCurScroller);
	}
	else
		ui.tableView->scrollToBottom();
}

void LampHistoryPage::on_lastBtn_clicked()
{
	ui.tableView->scrollToBottom();
}

void LampHistoryPage::on_nextBtn_clicked()
{
	int maxValue = ui.tableView->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值25
	int nCurScroller = ui.tableView->verticalScrollBar()->value(); //获得当前scroller值
	if(nCurScroller<maxValue)
		ui.tableView->verticalScrollBar()->setSliderPosition(RECORD_CNT_PERPAGE+nCurScroller);
	else
		ui.tableView->verticalScrollBar()->setSliderPosition(0);
}

void LampHistoryPage::initDisplay()
{
	int width[4];
	if(g_nActScreenX < 420)
	{
		width[0] = 30;
		width[1] = 70;
		width[2] = 80;
		width[3] = 100;
	}
	else
	{
		width[0] = 30*2;
		width[1] = 70*2;
		width[2] = 80*2;
		width[3] = 100*2;
	}
	
	MyTableModel *gradient_model = MyTableModel::createModelAndConnectToView(ui.tableView, 4, width, TABLE_LAMPHISTORY);

    QStringList titleList;
    titleList<<tr("ID")<<tr("Lamp")<<tr("Used Time")<<tr("Change Date");
    gradient_model->setTitle(titleList);
	
	ui.tableView->verticalHeader()->setVisible(false);
}



