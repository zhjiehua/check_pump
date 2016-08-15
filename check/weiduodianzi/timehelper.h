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
	static void begin();						//测试程序运行时间开始;
	static quint32 end();						//测试程序运行时间结束;
	static quint32 getRandom();					//获取随机数;

private:
	static QTime m_testRunTime;
	
};

#endif // TIMEHELPER_H
