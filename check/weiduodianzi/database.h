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

	void saveDb();														//�������ݿ��ļ�;
	void updateDate(QString name, QString data);						//��������;
	QString queryData(QString name);									//��ѯ����;
	QList<LineUint> &getWaveCompensationList(){return waveCompensationList;}//��ȡ����������;


	QList<QStringList> readCompensationTable(int which = 0);			//��ȡ������(�������ݶȲ���);
	void updateCompensationTable(int which, QList<QStringList>data);	//���²�����;
	void updateWaveCompensationTable(QList<QStringList>data);			

	void readWaveCompensationTableIntoList();							//�����������������б�Ҫ��ת��;
	void readWaveCompensationTableIntoList(QList<QStringList>&data);	//�����������������б�Ҫ��ת��;
	void reOrderList(QList<QStringList> &list);							//����;

	void saveTableToFile(QString fileName, QList<QStringList>&data);//�������ļ�;

	double getConstVal();

	//��Դ��ʷ��¼�ӿ�;
	void insertLampHistoryRecord(QString name, QString time, QString date);	//�����Դʹ�ü�¼;
	QList<QStringList> readLampHistoryRecordTable();							//��ȡ������(�������ݶȲ���);
	void clearLampHistoryRecord();												//�����Դ��ʷ��¼;

	//���ݿ�ָ���������;
	void restoreDatabase();

private:
	DataBase(QObject *parent = 0);
	QThread m_thread;
	QMap<QString, QString>dataBase;										//���ݿ�����;
	quint32 endTime;
	QList<LineUint> waveCompensationList;


	char *m_zErrMsg;
	sqlite3 *m_db;
	int m_ret;
	int m_nrow;
	int m_ncolumn;
	char **m_azResult;									//��ά�����Ž��;




//method
	void initDb();										//��ʼ�����ݿ�;
	void createCompensationTable();						//���������������ѹ��������;
	void initLampUsedHistoryTable();					//������Դʹ�ü�¼��;
	void insertBaseData(QString var, QString val);		//���뵽���ݿ�;
	
	void restoreDefWaveCompenTable(int arg = 0);		//��������Ĭ�ϲ���У�����;
	void restoreWDADataBase(bool restore = false);		//�ָ�WDA���ݿ��������;

signals:
	void dateChanged(QString, QString);
	void save();

private slots:
	void saveToDataBase();//�������ݿ��ļ�;
	void saveData(QString name, QString val);			//�������ݵ����ݿ��ļ�;
	
};

#endif // DATABASE_H
