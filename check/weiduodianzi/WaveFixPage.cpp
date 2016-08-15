#include "WaveFixPage.h"
#include "mytablemodel.h"
#include "editordelegate.h"
#include "msgbox.h"
#include "baseMainPage.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!Ŀǰ���ļ�δʹ��


WaveFixPage::WaveFixPage(QWidget *parent /*= 0*/, quint8 index, quint8 previndex, quint32 add)
	: CBasePage(tr("PressFix"), index, previndex, add, parent )
{
	ui.setupUi(this);
	m_strTitle = tr("PressFix");
	initDisplay();
}


WaveFixPage::~WaveFixPage(void)
{

	//DataBase::getInstance()->readPressCompensationTableIntoList();
}

void WaveFixPage::initFocusList()
{
	xList.append(ui.tableView);
	xList.append(ui.saveBtn);
	xList.append(ui.backBtn);
	xList.append(ui.wlenEdit);

	yList.append(ui.tableView);
	yList.append(ui.saveBtn);
	yList.append(ui.backBtn);
	yList.append(ui.wlenEdit);
}


void WaveFixPage::initDisplay()
{
	MyTableModel *gradient_model = new MyTableModel(this, 2);
	gradient_model->readDataFromTable(21);
	ui.tableView->setModel(gradient_model);
	ui.tableView->setColumnWidth(0,200);    
	ui.tableView->setColumnWidth(1,150);    
	ui.tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed);

	//Ϊÿһ�����ô���;
	ui.tableView->setItemDelegateForColumn(0, new EditorDelegate("000.0000"));//����;
	ui.tableView->setItemDelegateForColumn(1, new EditorDelegate("000.0000"));//����У׼;
	ui.tableView->initIndex();

	connect(ui.tableView, SIGNAL(getOutFocus(int)), this, SLOT(getOutTableFocus(int)));
	setStyleSheet( BTNGLOBALSTYLE);

}

void WaveFixPage::getOutTableFocus(int dir)
{
	if(dir == 0)//��
		ui.saveBtn->setFocus();
	else if(dir == 1)//��;
		ui.saveBtn->setFocus();
	else if(dir == 2)//��
		ui.wlenEdit->setFocus();
	else if(dir == 3)//��
		ui.saveBtn->setFocus();

	updateWlenCompenList();
}

void WaveFixPage::on_saveBtn_clicked()
{
	MyTableModel *mod = static_cast<MyTableModel *>(ui.tableView->model());
	//DataBase::getInstance()->updatePressCompensationTable(mod->tableData);
	MsgBox msgBox(this,tr("Tips"), tr("save success!"), QMessageBox::Ok);
	msgBox.exec();
}

void WaveFixPage::on_backBtn_clicked()
{
	g_pMainWindow->backToPage();
}






void WaveFixPage::updateWlenCompenList()
{
	MyTableModel *mod = static_cast<MyTableModel *>(ui.tableView->model());
	//DataBase::getInstance()->readPressCompensationTableIntoList(mod->tableData);
}



CBasePage* WaveFixPage::getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add)
{
	return new WaveFixPage(parent, index, previndex, add);
}



