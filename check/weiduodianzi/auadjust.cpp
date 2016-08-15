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
	//�ж�which�Ƿ���Ч������ʶ;
	if(which > 1)//0����1��1����2;
		return;

	//�鿴��ǰ�б��Ƿ���Ч����
	if(!checkValidity(which))
		return;

	//qDebug()<<"add au"<<which<<":"<<auVal;
	//����ʱ����;
	insertIntoTimeLine(which, auVal);
}

void AuAdjust::generateAuVal()
{
#if 1
	//��������Ч��;
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

	//��λ���±�־λ;
	m_bUpdateDoubleAuList = false;

	//�������ɴ������;
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
	//��λ���±�־λ;
	m_bUpdateDoubleAuList = false;

	//�Žܻ��޸�@2016-07-04
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
	static double last_au1 = 0; //�Žܻ��޸�@2016-06-16��������false����û���ݵ�ʱ�򷵻���һ�ε�����
	static double last_au2 = 0;

	//�鿴timeline�������µ�����;
	generateAuVal();

	//���auֵ�����Ƿ�������;
	if(m_doubleAuList.isEmpty())
	{
		*pAu1 = last_au1;
		*pAu2 = last_au2;
		//return true;
		return false;
	}

	//�Ӷ���ɾ���Ѿ���ȡ��auֵ;
	DoubleAu doubleAu = m_doubleAuList.takeFirst();

	last_au1 = doubleAu.dAu1;
	last_au2 = doubleAu.dAu2;

	//��д����;
	*pAu1 = doubleAu.dAu1;
	*pAu2 = doubleAu.dAu2;

	return true;
}

void AuAdjust::updateAuValSingle( double auVal )
{
	//����ʱ����;
	insertIntoTimeLineSingle(auVal);
}

void AuAdjust::generateAuValSingle()
{
#if 1

	//��������Ч��;
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

	//��λ���±�־λ;
	m_bUpdateSingleAuList = false;

	//�������ɴ������;
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
	//��λ���±�־λ;
	m_bUpdateSingleAuList = false;
	//�Žܻ��޸�@2016-07-04
	if(m_timeLineSingle.count() >= 1)
	{
		m_singleAulist.append(m_timeLineSingle.at(0).dAuVal);
		m_timeLineSingle.removeFirst();
	}
#endif
}

bool AuAdjust::getAuValSingle( double *pAu1 )
{
	static double last_au = 0; //�Žܻ��޸�@2016-06-16��������false����û���ݵ�ʱ�򷵻���һ�ε�����

	//�鿴timeline�������µ�����;
	generateAuValSingle();
	//���auֵ�����Ƿ�������;
	if( m_singleAulist.isEmpty())
	{
		*pAu1 = last_au;
		//return true;
		return false;
	}

	//�Ӷ���ɾ���Ѿ���ȡ��auֵ;
	//double au = m_singleAulist.takeAt(0);
	double au = 0;
	if(m_singleAulist.count() > 0)
	{
		au = m_singleAulist.takeFirst();
		last_au = au;
	}

	//��д����;
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
	//����ڵ�;
	AuNode node;
	node.which = which;
	node.dAuVal = dAuVal;
	node.msec = QTime(0,0).msecsTo(QTime::currentTime());
	m_timeLine.append(node);

	//���±�ʶλ;
	m_bUpdateDoubleAuList = true;

	//�����еĳ��ȣ�����4����ɾ�����һ����
	if( m_timeLine.count() > 4 )
		m_timeLine.removeFirst();
}

void AuAdjust::insertIntoTimeLineSingle( double dAuVal )
{
	//����ڵ�;
	AuNode node;
	node.which = 0;
	node.dAuVal = dAuVal;
	node.msec = QTime(0,0).msecsTo(QTime::currentTime());
	m_timeLineSingle.append(node);

	//���±�ʶλ;
	m_bUpdateSingleAuList = true;

	//�����еĳ��ȣ�����2����ɾ�����һ��
	if( m_timeLineSingle.count() > 2 )
	{
		m_timeLineSingle.removeFirst();
		
		// /*for(int i = 0; i < m_timelinesingle.count(); i++)
		// {
			// qdebug()<<"time:"<<m_timelinesingle.at(i).msec<<"---"<<"val:"<<m_timelinesingle.at(i).dauval;
		// }*/
	}
	
}
