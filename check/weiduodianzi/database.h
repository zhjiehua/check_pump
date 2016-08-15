#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QThread>
#include "lineuint.h"
#include "sqlite3.h"

class DataBase : public QObject
{
	Q_OBJECT

public:
	~DataBase();
	static DataBase *getInstance();

	void saveDb();														//保存数据库文件;
	void updateDate(QString name, QString data);						//更新数据;
	QString queryData(QString name);									//查询数据;
	QList<LineUint> &getWaveCompensationList(){return waveCompensationList;}//获取流量补偿表;


	QList<QStringList> readCompensationTable(int which = 0);			//读取补偿表(流量或梯度补偿);
	void updateCompensationTable(int which, QList<QStringList>data);	//更新补偿表;
	void updateWaveCompensationTable(QList<QStringList>data);			

	void readWaveCompensationTableIntoList();							//读出流量补偿表，进行必要的转换;
	void readWaveCompensationTableIntoList(QList<QStringList>&data);	//读出流量补偿表，进行必要的转换;
	void reOrderList(QList<QStringList> &list);							//排序;

	void saveTableToFile(QString fileName, QList<QStringList>&data);//保存表格到文件;

	double getConstVal();

	//灯源历史记录接口;
	void insertLampHistoryRecord(QString name, QString time, QString date);	//插入灯源使用记录;
	QList<QStringList> readLampHistoryRecordTable();							//读取补偿表(流量或梯度补偿);
	void clearLampHistoryRecord();												//清除灯源历史记录;

	//数据库恢复出厂操作;
	void restoreDatabase();

private:
	DataBase(QObject *parent = 0);
	QThread m_thread;
	QMap<QString, QString>dataBase;										//数据库内容;
	quint32 endTime;
	QList<LineUint> waveCompensationList;


	char *m_zErrMsg;
	sqlite3 *m_db;
	int m_ret;
	int m_nrow;
	int m_ncolumn;
	char **m_azResult;									//二维数组存放结果;




//method
	void initDb();										//初始化数据库;
	void createCompensationTable();						//创建流量补偿表和压力补偿表;
	void initLampUsedHistoryTable();					//创建灯源使用记录表;
	void insertBaseData(QString var, QString val);		//插入到数据库;
	
	void restoreDefWaveCompenTable(int arg = 0);		//创建出厂默认波长校正表格;
	void restoreWDADataBase(bool restore = false);		//恢复WDA数据库出厂设置;

signals:
	void dateChanged(QString, QString);
	void save();

private slots:
	void saveToDataBase();//保存数据库文件;
	void saveData(QString name, QString val);			//保存数据到数据库文件;
	
};

#endif // DATABASE_H
