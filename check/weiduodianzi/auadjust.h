#ifndef AUADJUST_H
#define AUADJUST_H

#include <QObject>
#include <QList>

typedef struct _auNode
{
	int which;			//代表是波长1还是波长2;
	double dAuVal;		//au值;
	int msec;			//时间轴坐标;
}AuNode;

typedef struct _doubleAu
{
	double dAu1;
	double dAu2;
}DoubleAu;

class AuAdjust : public QObject
{
	Q_OBJECT

public:
	~AuAdjust();
	static AuAdjust *getInstance();

	//双波长模式;
	void updateAuVal(int which, double auVal);	//更新au值,which 代表波长1还是波长2;
	void generateAuVal();						//生成中间AU值;
	bool getdoubleAuVal(double *pAu1, double *pAu2);//读取au值;

	//单波长模式;
	void updateAuValSingle(double auVal);
	void generateAuValSingle();
	bool getAuValSingle(double *pAu1);

	void clear();

private:
	QList<AuNode>m_timeLine;					//一条时间轴，将au值串起来;
	QList<DoubleAu>m_doubleAuList;				//波长1波长2的序列;
	bool m_bUpdateDoubleAuList;

	AuAdjust(QObject *parent = 0);

	bool checkValidity(int which);				//检查波长有效性;
	void insertIntoTimeLine(int which, double dAuVal);

	//单波长模式;
	QList<AuNode>m_timeLineSingle;
	QList<double>m_singleAulist;
	bool m_bUpdateSingleAuList;
	void insertIntoTimeLineSingle(double dAuVal);		
};

#endif // AUADJUST_H
