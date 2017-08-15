#include "database.h"
#include "sqlite3.h"
#include <QDebug>
#include <QMap>
#include "lineuint.h"
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QList>
#include "timehelper.h"

DataBase::DataBase(QObject *parent)
	: QObject(parent)
	, endTime(1)
	, m_zErrMsg(0)
	, m_db(0)
	,m_ncolumn(0)
	,m_nrow(0)
	,m_azResult(0)
{
	initDb();
	createCompensationTable();
	initLampUsedHistoryTable();
	connect(this, SIGNAL(save()), this, SLOT(saveToDataBase()));
	connect(this, SIGNAL(dateChanged(QString, QString)), this, SLOT(saveData(QString, QString)) );
	moveToThread(&m_thread);
	m_thread.start();
}

DataBase::~DataBase()
{
	saveDb();
	sqlite3_free_table( m_azResult );
	sqlite3_free(m_zErrMsg);
	sqlite3_close(m_db);
}

DataBase * DataBase::getInstance()
{
	static DataBase *pDb = new DataBase();
	return pDb;
}

void DataBase::updateDate(QString name, QString data)
{
	dataBase.insert(name, data);
	emit(dateChanged(name, data));
	//保存到数据库文件;
}

void DataBase::saveData(QString name, QString val)
{
	//TimeHelper::begin();
	QString sql = QString("UPDATE WDA SET VALUE = '%1' WHERE NAME = '%2';").arg(val).arg(name);
	sqlite3_exec( m_db , sql.toLatin1().data() , 0 , 0 , &m_zErrMsg );
	//TimeHelper::end();
}

QString DataBase::queryData(QString name)
{
	QString val = dataBase.value(name);
	return val;
}


void DataBase::insertBaseData(QString var, QString val)
{
	QString sql = QString("INSERT INTO WDA VALUES('%1' , '%2');").arg(var).arg(val);
#if QT_VERSION >= 0x050000
	sqlite3_exec(m_db, sql.toLatin1().data(), 0, 0, &m_zErrMsg);
#else
	sqlite3_exec( m_db , sql.toAscii().data() , 0 , 0 , &m_zErrMsg );
#endif
	
}



void DataBase::restoreWDADataBase(bool restore /*= false*/)
{
	//创建全局参数表格!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;
	char *sql = "DROP TABLE WDA;" ;
	if(restore)
		sqlite3_exec( m_db , sql , 0 , 0 , &m_zErrMsg );

	sql = "CREATE TABLE WDA(NAME TEXT PRIMARY KEY,VALUE TEXT);" ;
	m_ret = sqlite3_exec( m_db , sql , 0 , 0 , &m_zErrMsg );
	//插入数据; 

	QMap<QString, QString>dbData;
    dbData["last_time"] = "0";      //上一次时间;
	dbData["language"] = "0";		//语言;
	dbData["pcProtocol"] = "0";		//协议;
	dbData["wavelen1"] = "254";		//波长1;
	dbData["wavelen2"] = "256";		//波长2;
	dbData["chanel"] = "0";			//通道;
	dbData["xe_tun"] = "0";			//灯源;
	dbData["lampcha"] = "0";		//灯源次数;
	dbData["sample"] = "0";			//采样值;
	dbData["base"] = "0";			//参考值;
	dbData["range"] = "13";			//量程常量;
	dbData["timeconst"] = "0";		//时间常量;
	dbData["state"] = "0";			//状态;
	dbData["lampstate"] = "0";		//灯状态;
	dbData["coefficient"] = "1";	//系数;
	dbData["timeInte"] = "0";		//时间积分;
	dbData["percentRofS"] = "1";	//R与S的比值;
	dbData["percentRofS2"] = "1";	//R与S的比值;
	dbData["sampleDisp"] = "1";		//采样值;
	dbData["refDisp"] = "1";		//参考值;

	dbData["ausample1"] = "1";		//波长1参比;
	dbData["auref1"] = "1";			//波长1样比;
	dbData["au1"] = "0";			//波长1吸光度;
	dbData["ausample2"] = "1";		//波长2参比;
	dbData["auref2"] = "1";			//波长2样比;
	dbData["au2"] = "0";			//波长2吸光度;


	//扫描页面;
	dbData["sWlen"] = "0";			//起始波长;
	dbData["eWlen"] = "600";		//结束波长;
	dbData["sTime"] = "30";			//扫描时间;


	//年月日时分秒;
	dbData["year"] = "2015";
	dbData["month"] = "10";
	dbData["day"] = "1";
	dbData["hour"] = "5";
	dbData["minute"] = "5";
	dbData["second"] = "5";
	dbData["datetimeoffset"] = "0";//日期偏移量;

	//上次维修日期
	dbData["repairYear"] = "0000";
	dbData["repairMonth"] = "00";
	dbData["repairDay"] = "0";

	//生产日期
	dbData["manufYear"] = "2015";
	dbData["manufMonth"] = "10";
	dbData["manufDay"] = "1";

	//安装日期
	dbData["instYear"] = "2015";
	dbData["instMonth"] = "10";
	dbData["instDay"] = "1";

	//许可证序列号;
	dbData["lic"] = "123456";
	dbData["license"] = "1111111111";
	dbData["serial"] = "0000000000";
	dbData["tryDay"] = "15";
	dataBase["activeCode"]="0000000000";

	//用户密码;
	dbData["pwd"] = "173895";
	dbData["usrpwd"] = "222222";
	dbData["lamppwd"] = "333333";

	//时间页面;
	dbData["usedTime"] = "0";//累计开机时间;
	dbData["xeUsedTime"] = "0";//氘灯累计使用时间;
	dbData["tunUsedTime"] = "0";//钨灯累计使用时间;
	dbData["firstTryDateTime"] = "0";//记录开始试用的当天日期时间;

	//激活状态;
	dbData["bActive"] = "0";//设备是否永久激活;
	dbData["bTryDay"] = "0";//设备是否到达试用时间;

	//张杰华添加@2016-06-26
	//本地IP和端口
	dbData["ip1"] = "192";
	dbData["ip2"] = "168";
	dbData["ip3"] = "1";
	dbData["ip4"] = "110";
	dbData["port"] = "6666";
	//远端IP和端口
	dbData["remote_ip1"] = "192";
	dbData["remote_ip2"] = "168";
	dbData["remote_ip3"] = "1";
	dbData["remote_ip4"] = "105";
	dbData["remote_port"] = "6665";

    //! 端口(网口或串口)
    dbData["connect_port"] = "0";

	QMap<QString, QString>::const_iterator it;
	for (it = dbData.constBegin(); it != dbData.constEnd(); ++it) {
		insertBaseData(it.key(), it.value());
	}

	//TimeHelper::begin();
	sql = "SELECT * FROM WDA ";
	sqlite3_get_table( m_db , sql , &m_azResult , &m_nrow , &m_ncolumn , &m_zErrMsg );
	qDebug("row:%d column=%d \n" , m_nrow , m_ncolumn );
	qDebug()<<( "The result of querying is :" );
	dataBase.clear();
	for(int i=2 ; i<( m_nrow + 1 ) * m_ncolumn ; )
	{
		QString key = QString(m_azResult[i]);
		QString val = QString(m_azResult[i+1]);
		dataBase.insert(key, val);
		i = i+2;
	}
	//qDebug()<<"------------------elapse:"<<TimeHelper::end();

	//打印内存数据库;
#if 0
	QMap<QString, QString>::const_iterator i;
	for (i = dataBase.constBegin(); i != dataBase.constEnd(); ++i) {
		qDebug() << i.key() << ":" << i.value();
	}
#endif
}

void DataBase::initDb()
{
	m_ret = sqlite3_open("wda.db", &m_db);//打开指定的数据库文件,如果不存在将创建一个同名的数据库文件;
	if( m_ret )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_db));
		sqlite3_close(m_db);
		return;
	}
	else 
		qDebug()<<"You have opened a sqlite3 database ";

	
	restoreWDADataBase();
}

void DataBase::saveDb()
{
	emit(save());
}



void DataBase::createCompensationTable()
{
	char *sql = 0;
	int ret = 0;

	//创建流量补偿表,当烧录程序到核心板，第一次创建表格时候,ret返回SQLITE_OK,否则返回错误;
	//当第一次创建该表格时候，需要设为出厂默认参数;
	sql = "DROP TABLE COMPENSATIONTABLE0";
	//ret = sqlite3_exec( m_db , sql , 0 , 0 , &m_zErrMsg );
	sql = "CREATE TABLE COMPENSATIONTABLE0(WAVE TEXT PRIMARY KEY, VALUE TEXT);";
	ret = sqlite3_exec( m_db , sql , 0 , 0 , &m_zErrMsg );
	if(ret == SQLITE_OK)//恢复默认数据;
		restoreDefWaveCompenTable();

	readWaveCompensationTableIntoList();
}


QList<QStringList> DataBase::readCompensationTable(int which /*= 0*/)
{
	QString temp;
	QString tableName = QString("COMPENSATIONTABLE%1").arg(which);
	temp = QString("SELECT * FROM %1").arg(tableName);
	sqlite3_get_table( m_db , temp.toLatin1().data() , &m_azResult , &m_nrow , &m_ncolumn , &m_zErrMsg );

	//读取数据库表格;
	QList<QStringList>ret;
	for(int i=0 ; i<( m_nrow + 1 ) ; i++ )
	{
		QStringList list;
		for(int j = 0; j < m_ncolumn; j++)
		{
			int index = i*m_ncolumn+j;
			QString data = QString(m_azResult[index]);
			list.append(data);
		}
		ret.append(list);
	}

	return ret;
}

void DataBase::updateWaveCompensationTable(QList<QStringList>data)
{
	int row = data.count();

	//清空表格;
	QString temp;
	temp = QString("DELETE FROM COMPENSATIONTABLE0;");
	sqlite3_exec( m_db , temp.toLatin1().data() , 0 , 0 , &m_zErrMsg );

	//插入数据;
	for ( int i = 1; i < row; i++)
	{
		temp = QString("INSERT INTO COMPENSATIONTABLE0 VALUES('%1' , '%2');")
			.arg(data.at(i).at(0))
			.arg(data.at(i).at(1));
		sqlite3_exec( m_db , temp.toLatin1().data() , 0 , 0 , &m_zErrMsg );
	}
	readWaveCompensationTableIntoList();

}



void DataBase::readWaveCompensationTableIntoList()
{
	QString temp;
	temp = QString("SELECT * FROM COMPENSATIONTABLE0 ");
	sqlite3_get_table( m_db , temp.toLatin1().data() , &m_azResult , &m_nrow , &m_ncolumn , &m_zErrMsg );
	//qDebug()<<( "The result of querying is :" );
	QList<QStringList>list;
	for(int i=2 ; i<( m_nrow + 1 ) * m_ncolumn ; )//0、1个是标题;
	{
		//qDebug( "azResult[%d] = %s", i , m_azResult[i] );
		QString flow(m_azResult[i]);
		QString value(m_azResult[i+1]);
		QStringList record;
		record.append(flow);
		record.append(value);
		list.append(record);
		i= i+2;
	}
	readWaveCompensationTableIntoList(list);
}

void DataBase::readWaveCompensationTableIntoList(QList<QStringList> &list)
{
	reOrderList(list);
	QList<QStringList> &data = list;

	QList<QStringList>myList;
	for (int i = 0; i < data.count(); i++)
	{
		QStringList list = data.at(i);
		QStringList temp;
		double percent = list.at(1).toDouble();
		percent = 2 - percent;
		temp.append( QString::number( percent*list.at(0).toDouble() ) );
		temp.append(list.at(0));
		myList.append(temp);
	}
	/*qDebug()<<data;
	qDebug()<<"---------------";
	qDebug()<<myList;
	qDebug()<<"---------------";*/
	reOrderList(myList);
	/*qDebug()<<myList;*/
	
#if 1
	//判断点的个数;
	int len = myList.count();
	
	if(len >= 2 )
	{
		//清空gradientList
		waveCompensationList.clear();
		for(int i = 0; i < len-1; i++)
		{
			QStringList temp = myList.at(i);
			QStringList nextTemp = myList.at(i+1);
			LineUint line(0);
			double x1 = temp.at(0).toDouble();
			double x2 = nextTemp.at(0).toDouble();
			double y1 = temp.at(1).toDouble();
			double y2 = nextTemp.at(1).toDouble();
			line.setRange(x1, y1, x2, y2, QString(""));
			waveCompensationList.append(line);
		}
	}
	else
		return;

#endif
}



bool compareForList(const QStringList &s1, const QStringList &s2)
{
	if(s1.count() <=0 || s2.count() <=0 )
		return false;

	if(s1.at(0).toDouble() < s2.at(0).toDouble() )
		return true;
	else
		return false;
}

void DataBase::reOrderList(QList<QStringList> &list)
{
	qSort(list.begin(), list.end(), compareForList);
}

void DataBase::saveTableToFile(QString fileName, QList<QStringList>&data)
{
	QFile file(fileName);

	if (!file.open(QFile::WriteOnly | QFile::Truncate))
		return;
	QTextStream out(&file);
	for(int i = 0; i < data.count(); i++)
	{
		for(int j = 0; j < data.at(i).count(); j++)
		{
			out<<qSetFieldWidth(10)<<left<<data.at(i).at(j);
		}
		out<<qSetFieldWidth(0)<<endl;
	}
}

void DataBase::saveToDataBase()
{
	QString temp;
	for (QMap<QString, QString>::ConstIterator i = dataBase.constBegin(); i != dataBase.constEnd(); ++i)
	{
		temp = QString("UPDATE WDA SET VALUE = '%1' WHERE NAME='%2';")
			.arg(i.value())
			.arg(i.key());
		//qDebug()<<temp;
		sqlite3_exec( m_db , temp.toLatin1().data() , 0 , 0 , &m_zErrMsg );
	}
}

double DataBase::getConstVal()
{
	QList<double>list;
	list<<0.0001<<0.0002<<0.0005<<0.001<<0.002<<0.005<<0.01<<0.02<<0.05<<0.1<<0.2<<0.5<<1<<2<<5<<10;
	int index = DataBase::getInstance()->queryData("range").toInt();
	return list.at(index);
}

void DataBase::initLampUsedHistoryTable()
{
	QString tableName;
	QString temp;
	char *sql;

	//创建灯源使用记录表格;
	tableName = QString("LAMPHISTORY");
	temp = QString("CREATE TABLE IF NOT EXISTS %1(ID INT PRIMARY KEY, NAME TEXT, TIME TEXT, CHDATE TEXT);").arg(tableName);
	sqlite3_exec( m_db , temp.toLatin1().data() , 0 , 0 , &m_zErrMsg );

//test:
#if 0
	sql = "DELETE FROM LAMPHISTORY";//删除表格数据;
	sqlite3_exec( m_db , sql , 0 , 0 , &m_zErrMsg );
	insertLampHistoryRecord("Deu", "14", "2016.03.06");
#endif

#if 0
	sql = "SELECT * FROM LAMPHISTORY";
	sqlite3_get_table( m_db , sql , &m_azResult , &m_nrow , &m_ncolumn , &m_zErrMsg );
	qDebug("row:%d column=%d \n" , m_nrow , m_ncolumn );
	for(int i=0 ; i<( m_nrow + 1 ) * m_ncolumn ; i++)
	{
		qDebug()<<m_azResult[i];
	}
#endif
}

void DataBase::insertLampHistoryRecord(QString name, QString time, QString date)
{
	char *sql = "SELECT * FROM LAMPHISTORY";
	sqlite3_get_table( m_db , sql , &m_azResult , &m_nrow , &m_ncolumn , &m_zErrMsg );

	QString temp = QString("INSERT INTO LAMPHISTORY (ID,NAME,TIME,CHDATE) VALUES (%1, '%2', '%3', '%4')").arg(m_nrow+1).arg(name).arg(time).arg(date);
	sqlite3_exec( m_db , temp.toLatin1().data() , 0 , 0 , &m_zErrMsg );

//打印;
#if 0
	sql = "SELECT * FROM LAMPHISTORY";
	sqlite3_get_table( m_db , sql , &m_azResult , &m_nrow , &m_ncolumn , &m_zErrMsg );
	qDebug("row:%d column=%d \n" , m_nrow , m_ncolumn );
	for(int i=0 ; i<( m_nrow + 1 ) * m_ncolumn ; i++)
	{
		if( i%4 == 0 )
			qDebug("\n");
		qDebug( "%s", m_azResult[i]);
		
	}
#endif
}

QList<QStringList> DataBase::readLampHistoryRecordTable()
{
	QList<QStringList>ret;
	char *sql = "SELECT * FROM LAMPHISTORY";
	m_ret = sqlite3_get_table( m_db , sql , &m_azResult , &m_nrow , &m_ncolumn , &m_zErrMsg );

	//读取数据库表格;
	if(m_ncolumn == 0)//表格为空
	{
		QStringList list;
		list<<tr("ID")<<tr("Lamp")<<tr("Used Time")<<tr("Change Date");
		ret.append(list);
	}
	else
	{
		for(int i=0 ; i<( m_nrow + 1 ) ; i++ )
		{
			QStringList list;
			for(int j = 0; j < m_ncolumn; j++)
			{
				int index = i*m_ncolumn+j;
				QString data = QString(m_azResult[index]);
				list.append(data);
			}
			ret.append(list);
		}
	}
	
	return ret;
}

void DataBase::clearLampHistoryRecord()
{
	char *sql = "DELETE FROM LAMPHISTORY";
	sqlite3_get_table( m_db , sql , &m_azResult , &m_nrow , &m_ncolumn , &m_zErrMsg );
}

void DataBase::restoreDefWaveCompenTable(int arg /*= 0*/)
{
	//泵的压力校正表;
	QMap<double, double>tbl;
	tbl.clear();

	tbl[195]=1;
	tbl[205]=1;
	tbl[213]=1;
	tbl[220]=1;
	tbl[235]=1;
	tbl[254]=1;
	tbl[257]=1;
	tbl[265]=1;
	tbl[280]=1;
	tbl[313]=1;
	tbl[350]=1;
	tbl[450]=1;
	tbl[600]=1;
	tbl[800]=1;

	//先删除之前的表格
	char *sql = "DELETE FROM COMPENSATIONTABLE0";
	sqlite3_exec( m_db , sql , 0 , 0 , &m_zErrMsg );

	//插入出厂默认值;
	QMap<double, double>::const_iterator it;
	for (it = tbl.constBegin(); it != tbl.constEnd(); ++it) {
		QString temp = QString("INSERT INTO COMPENSATIONTABLE0 VALUES('%1', '%2');").arg(it.key()).arg(it.value());
		sqlite3_exec( m_db , temp.toLatin1().data() , 0 , 0 , &m_zErrMsg );
	}
}

void DataBase::restoreDatabase()
{
	restoreDefWaveCompenTable();
}





