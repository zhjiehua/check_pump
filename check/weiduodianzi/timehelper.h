#ifndef TIMEHELPER_H
#define TIMEHELPER_H

#include <QObject>
#include <QTime>

class TimeHelper : public QObject
{
	Q_OBJECT

public:
	TimeHelper(QObject *parent = 0);
	~TimeHelper();

	static void mDelay(const quint32 mSec);
	static void begin();						//���Գ�������ʱ�俪ʼ;
	static quint32 end();						//���Գ�������ʱ�����;
	static quint32 getRandom();					//��ȡ�����;

private:
	static QTime m_testRunTime;
	
};

#endif // TIMEHELPER_H
