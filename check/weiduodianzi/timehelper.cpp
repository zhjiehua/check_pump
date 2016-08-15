#include "timehelper.h"
#include <QTime>
#include <QDebug>

QTime TimeHelper::m_testRunTime;

TimeHelper::TimeHelper(QObject *parent)
	: QObject(parent)
{

}

TimeHelper::~TimeHelper()
{

}

void TimeHelper::mDelay(const quint32 mSec)
{
	QTime n=QTime::currentTime();
	QTime now;
	do{
		now=QTime::currentTime();
	}   while (n.msecsTo(now)<=mSec);
}

void TimeHelper::begin()
{
	m_testRunTime = QTime::currentTime();
}


quint32 TimeHelper::end()
{
	QTime tempTime = QTime::currentTime();
	quint32 elapse = m_testRunTime.msecsTo(tempTime);
	//qDebug()<<"elapse:"<<elapse;
	return elapse;
}

quint32 TimeHelper::getRandom()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	qsrand(currentTime.time().msec());
	int randNum = qrand()%99999999;
	return randNum;
}

