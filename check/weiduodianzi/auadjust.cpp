#include "auadjust.h"
#include <QTime>
#include <QDebug>

AuAdjust::AuAdjust(QObject *parent)
	: QObject(parent)
	, m_bUpdateDoubleAuList(false)
	, m_bUpdateSingleAuList(false)
{
	/*for (int i = 0; i < 100; i++)
	{
	m_singleAulist.append(0);
	}*/
}

AuAdjust::~AuAdjust()
{

}

AuAdjust* AuAdjust::getInstance()
{
	static AuAdjust *pAuAdjust = NULL;
	if(!pAuAdjust)
		pAuAdjust = new AuAdjust;
	return pAuAdjust;
}

void AuAdjust::updateAuVal( int which, double auVal )
{
	//判断which是否有效波长标识;
	if(which > 1)//0波长1，1波长2;
		return;

	//查看当前列表，是否有效波长
	if(!checkValidity(which))
		return;

	//qDebug()<<"add au"<<which<<":"<<auVal;
	//插入时间轴;
	insertIntoTimeLine(which, auVal);
}

void AuAdjust::generateAuVal()
{
#if 1
	//检查队列有效性;
	if(!m_doubleAuList.isEmpty())
	{
		//qDebug()<<"empty...";
		return;
	}
	if(!m_bUpdateDoubleAuList)
	{
		//qDebug()<<"m_bUpdateDoubleAuList";
		return;
	}
	if(m_timeLine.count() < 4)
	{
		//qDebug()<<".........<4";
		return;
	}
	
	//qDebug()<<".....................generate";

	//复位更新标志位;
	m_bUpdateDoubleAuList = false;

	//计算生成存入队列;
	AuNode node1 = m_timeLine.at(0);
	AuNode node2 = m_timeLine.at(1);
	AuNode node3 = m_timeLine.at(2);
	AuNode node4 = m_timeLine.at(3);

	if(node1.which != node3.which)
		return;

	if(node2.which != node4.which)
		return;

	double k1 = (node3.dAuVal - node1.dAuVal)/(node3.msec - node1.msec);
	double k2 = (node4.dAuVal - node2.dAuVal)/(node4.msec - node2.msec);

	int begin = node2.msec;
	int end = node3.msec;

	int which = node1.which;
	for (int i = begin; i < end; i+=50 )
	{
		DoubleAu doubleAu;
		double au1 = k1*(i-node1.msec) + node1.dAuVal;
		double au2 = k2*(i-begin) + node2.dAuVal;

		if( which != 0 )
			qSwap(au1, au2);

		doubleAu.dAu1 = au1;
		doubleAu.dAu2 = au2;
		m_doubleAuList.append(doubleAu);
		if(m_doubleAuList.count() > 30 )
			m_doubleAuList.removeFirst();
	}

#else

	if(!m_bUpdateDoubleAuList)
	{
		return;
	}
	//复位更新标志位;
	m_bUpdateDoubleAuList = false;

	//张杰华修改@2016-07-04
	if(m_timeLine.count() >= 2)
	{
		DoubleAu doubleAu;
		doubleAu.dAu1 = m_timeLine.at(0).dAuVal;
		doubleAu.dAu2 = m_timeLine.at(1).dAuVal;
		m_doubleAuList.append(doubleAu);
		m_timeLine.removeFirst();
		m_timeLine.removeFirst();
	}
#endif
}

bool AuAdjust::getdoubleAuVal( double *pAu1, double *pAu2 )
{
	static double last_au1 = 0; //张杰华修改@2016-06-16，不返回false，在没数据的时候返回上一次的数据
	static double last_au2 = 0;

	//查看timeline，计算新的数据;
	generateAuVal();

	//检查au值队列是否有数据;
	if(m_doubleAuList.isEmpty())
	{
		*pAu1 = last_au1;
		*pAu2 = last_au2;
		//return true;
		return false;
	}

	//从队列删除已经读取的au值;
	DoubleAu doubleAu = m_doubleAuList.takeFirst();

	last_au1 = doubleAu.dAu1;
	last_au2 = doubleAu.dAu2;

	//填写参数;
	*pAu1 = doubleAu.dAu1;
	*pAu2 = doubleAu.dAu2;

	return true;
}

void AuAdjust::updateAuValSingle( double auVal )
{
	//插入时间轴;
	insertIntoTimeLineSingle(auVal);
}

void AuAdjust::generateAuValSingle()
{
#if 1

	//检查队列有效性;
	if( !m_singleAulist.isEmpty() )
	{
		return;
	}
	if(!m_bUpdateSingleAuList)
	{
		return;
	}
	if(m_timeLineSingle.count() < 2)
	{
		return;
	}

	//复位更新标志位;
	m_bUpdateSingleAuList = false;

	//计算生成存入队列;
	AuNode node1 = m_timeLineSingle.at(0);
	AuNode node2 = m_timeLineSingle.at(1);

#if 1
	quint32 msecDelta = node2.msec - node1.msec;

	if(msecDelta > 100 && msecDelta < 300)
	{
		double k1 = (node2.dAuVal - node1.dAuVal)/(node2.msec - node1.msec);
		int begin = node1.msec;
		int end = node2.msec;
		for (int i = begin; i < end; i+=50 )
		{
			double au = k1*(i-node1.msec) + node1.dAuVal;
			m_singleAulist.append(au);
			if( m_singleAulist.count() > 30 )
				m_singleAulist.removeFirst();
		}
	}
	else
	{
		int begin = 0;
		int end = 200;//150ms
		double k1 = (node2.dAuVal - node1.dAuVal)/(end-begin);

		for (int i = begin; i < end; i+=50 )
		{
			double au = k1*i + node1.dAuVal;
			m_singleAulist.append(au);
			if( m_singleAulist.count() > 30 )
				m_singleAulist.removeFirst();
		}
	}

#else
#endif

#else

	if(!m_bUpdateSingleAuList)
	{
		return;
	}
	//复位更新标志位;
	m_bUpdateSingleAuList = false;
	//张杰华修改@2016-07-04
	if(m_timeLineSingle.count() >= 1)
	{
		m_singleAulist.append(m_timeLineSingle.at(0).dAuVal);
		m_timeLineSingle.removeFirst();
	}
#endif
}

bool AuAdjust::getAuValSingle( double *pAu1 )
{
	static double last_au = 0; //张杰华修改@2016-06-16，不返回false，在没数据的时候返回上一次的数据

	//查看timeline，计算新的数据;
	generateAuValSingle();
	//检查au值队列是否有数据;
	if( m_singleAulist.isEmpty())
	{
		*pAu1 = last_au;
		//return true;
		return false;
	}

	//从队列删除已经读取的au值;
	//double au = m_singleAulist.takeAt(0);
	double au = 0;
	if(m_singleAulist.count() > 0)
	{
		au = m_singleAulist.takeFirst();
		last_au = au;
	}

	//填写参数;
	*pAu1 = au;

	return true;
}

void AuAdjust::clear()
{
	m_timeLine.clear();
	m_timeLineSingle.clear();
}

bool AuAdjust::checkValidity( int which )
{
	int cnt = m_timeLine.count();
	if(cnt == 0)
	{
		return true;
	}
	else
	{
		if( m_timeLine.last().which != which )
			return true;
		else
			return false;
	}
}

void AuAdjust::insertIntoTimeLine( int which, double dAuVal )
{
	//插入节点;
	AuNode node;
	node.which = which;
	node.dAuVal = dAuVal;
	node.msec = QTime(0,0).msecsTo(QTime::currentTime());
	m_timeLine.append(node);

	//更新标识位;
	m_bUpdateDoubleAuList = true;

	//检查队列的长度，保持4个，删除最后一个。
	if( m_timeLine.count() > 4 )
		m_timeLine.removeFirst();
}

void AuAdjust::insertIntoTimeLineSingle( double dAuVal )
{
	//插入节点;
	AuNode node;
	node.which = 0;
	node.dAuVal = dAuVal;
	node.msec = QTime(0,0).msecsTo(QTime::currentTime());
	m_timeLineSingle.append(node);

	//更新标识位;
	m_bUpdateSingleAuList = true;

	//检查队列的长度，保持2个，删除最后一个
	if( m_timeLineSingle.count() > 2 )
	{
		m_timeLineSingle.removeFirst();
		
		// /*for(int i = 0; i < m_timelinesingle.count(); i++)
		// {
			// qdebug()<<"time:"<<m_timelinesingle.at(i).msec<<"---"<<"val:"<<m_timelinesingle.at(i).dauval;
		// }*/
	}
	
}
