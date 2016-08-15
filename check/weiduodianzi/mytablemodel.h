#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>


#define TABLE_WAVE			20
#define TABLE_LAMPHISTORY	21

class QTableView;

class MyTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	enum TableInsertMode
	{
		COPYLASTROW,
		USERDATA,
	};


	MyTableModel(QObject *parent, int nColumnCnt = 0);
	~MyTableModel();
	static MyTableModel * createModelAndConnectToView(QTableView *parent, int column, int *pWidthArray, int tableIndex, bool bEdit = false);

    void setTitle(QStringList list);

	void readDataFromTable(int which);//从数据库读入数据;
	void updateDataToTable();//更新数据到数据库;
	QList<QStringList>& getTableData(){return tableData;}

	void insertRow(int row, TableInsertMode mode = COPYLASTROW, const QStringList &data = QStringList());
	int rowCount(const QModelIndex &parent  = QModelIndex()) const;//!!!!!!
	int columnCount(const QModelIndex &parent = QModelIndex()) const;//!!!!

	QList<QStringList> tableData;
	QStringList tempData;

    QStringList strTitleList;

private:
	int m_nColumnCnt;//表格列数;
	TableInsertMode m_insertMode;

/*******************************必须实现的虚函数****************************************/
	QVariant data(const QModelIndex &index, int role) const;//!!!!
	bool setData(const QModelIndex &index, const QVariant &value, int role);//!!!!
	bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());//!!!!
	bool removeRows(int row, int count, const QModelIndex &parent  = QModelIndex() );//!!!!
	Qt::ItemFlags flags ( const QModelIndex & index ) const;
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	

//另外封装的函数;
	void insertRowsWithCopyMode(int row, int count);
	void insertRowsWithUsrMode(int row, int count);

signals:

	
};

#endif // MYTABLEMODEL_H
