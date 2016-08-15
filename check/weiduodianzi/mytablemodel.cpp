#include "mytablemodel.h"
#include <QDebug>
#include <QTableView>
#include "baseMainPage.h"

MyTableModel::MyTableModel(QObject *parent, int nColumnCnt/* = 0*/)
	: QAbstractTableModel(parent)
	, m_insertMode(COPYLASTROW)
	, m_nColumnCnt(nColumnCnt)
{

}


MyTableModel::~MyTableModel()
{

}


QVariant MyTableModel::data( const QModelIndex &index, int role ) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::TextAlignmentRole) {
		return int(Qt::AlignLeft | Qt::AlignVCenter);
	}
	else if(role == Qt::DisplayRole)//显示内容;
	{
		return tableData.at(index.row()+1).at(index.column());
	}
	else if(role == Qt::BackgroundRole)
	{
		if(tableData.at(index.row()).count() > m_nColumnCnt)
		{
			if(tableData.at(index.row()).at(m_nColumnCnt).toInt())
				return QBrush(QColor(64, 128, 0));
		}
		
		return QBrush(QColor(255, 255, 255));
	}
	else
		return QVariant();
		//return QAbstractTableModel::data(index, role);
}


int MyTableModel::rowCount( const QModelIndex &parent ) const
{
	return tableData.count()-1;
}


int MyTableModel::columnCount( const QModelIndex &parent ) const
{
	return m_nColumnCnt;
}


bool MyTableModel::insertRows( int row, int count, const QModelIndex & parent /*= QModelIndex()*/ )
{
	beginInsertRows(QModelIndex(), row, row+count-1);
	
	if(m_insertMode == COPYLASTROW)
		insertRowsWithCopyMode(row, count);
	else
		insertRowsWithUsrMode(row, count);
	
	endInsertRows();
	return true;
}


bool MyTableModel::removeRows( int row, int count, const QModelIndex &parent /*= QModelIndex() */ )
{
	beginRemoveRows(QModelIndex(), row, row+count-1);
	for(int i = 0; i < count; i++)
		tableData.removeAt(row+1);
	endRemoveRows();
	return true;
}


bool MyTableModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
	if (index.isValid() && role == Qt::EditRole)
	{
		QString temp = value.toString();
		double dData = temp.toDouble();
		temp = QString::number(dData);
		QStringList list = tableData.at(index.row()+1);
		list.replace(index.column(), temp);
		tableData.replace(index.row()+1, list);
		emit(dataChanged(index, index));
		return true;
	}
	return false;
}


Qt::ItemFlags MyTableModel::flags( const QModelIndex & index ) const
{
	Qt::ItemFlags flags = QAbstractItemModel::flags(index);
	flags |= Qt::ItemIsEditable;
	return flags;
}


void MyTableModel::readDataFromTable(int which)
{
	if(which == TABLE_WAVE)//读取波长补偿表;
	{
		tableData = DataBase::getInstance()->readCompensationTable();
	}
	else if(which == TABLE_LAMPHISTORY)//读取灯源使用记录表格;
	{
		tableData = DataBase::getInstance()->readLampHistoryRecordTable();
	}
}



void MyTableModel::insertRow(int row, TableInsertMode mode, const QStringList &data)
{
	m_insertMode = mode;
	tempData = data;
	QAbstractTableModel::insertRow(row);
}

void MyTableModel::insertRowsWithCopyMode(int row, int count)
{
	if( tableData.count() > 1 )
	{
		QStringList list = tableData.at(row);
		QString temp = tableData.at(row).at(0);
		for(int i = 0; i < count; i++)
		{
			double time = temp.toDouble();
			time += 0.1;
			temp = QString::number(time, 'f', 1);
			list.replace(0, temp);
			tableData.insert(row+1+i, list);
		}
	}
	else//插入新的行;
	{
		QStringList list;
		for (int i = 0; i < m_nColumnCnt; i++)
		{
			list.append("0");
		}
		tableData.insert(row+1, list);
	}
}

void MyTableModel::insertRowsWithUsrMode(int row, int count)
{
	for(int i = 0; i < count; i++)
	{
		tableData.insert(row+i, tempData);
	}
}

MyTableModel * MyTableModel::createModelAndConnectToView(QTableView *parent, int column, int *pWidthArray, int tableIndex, bool bEdit)
{
	MyTableModel *gradient_model = new MyTableModel(parent, column);
	gradient_model->readDataFromTable(tableIndex);
	parent->setModel(gradient_model);
	for ( int i = 0; i < column; i++ )
	{
		parent->setColumnWidth(i,pWidthArray[i]); 
	}
	parent->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	parent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	if(bEdit)
		parent->setEditTriggers(QAbstractItemView::AnyKeyPressed);

    return gradient_model;

}



QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */) const //另外封装的函数
{
	if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
        if(section >= strTitleList.count() )
            return "";
        else
            return strTitleList.at(section);
        
	}
	return QAbstractTableModel::headerData(section, orientation, role);
}

void MyTableModel::setTitle(QStringList list)
{
    strTitleList = list;
}
