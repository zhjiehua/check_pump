#ifndef AUADJUST_H
#define AUADJUST_H

#include <QObject>
#include <QList>

typedef struct _auNode
{
	int which;			//�����ǲ���1���ǲ���2;
	double dAuVal;		//auֵ;
	int msec;			//ʱ��������;
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

	//˫����ģʽ;
	void updateAuVal(int which, double auVal);	//����auֵ,which ������1���ǲ���2;
	void generateAuVal();						//�����м�AUֵ;
	bool getdoubleAuVal(double *pAu1, double *pAu2);//��ȡauֵ;

	//������ģʽ;
	void updateAuValSingle(double auVal);
	void generateAuValSingle();
	bool getAuValSingle(double *pAu1);

	void clear();

private:
	QList<AuNode>m_timeLine;					//һ��ʱ���ᣬ��auֵ������;
	QList<DoubleAu>m_doubleAuList;				//����1����2������;
	bool m_bUpdateDoubleAuList;

	AuAdjust(QObject *parent = 0);

	bool checkValidity(int which);				//��鲨����Ч��;
	void insertIntoTimeLine(int which, double dAuVal);

	//������ģʽ;
	QList<AuNode>m_timeLineSingle;
	QList<double>m_singleAulist;
	bool m_bUpdateSingleAuList;
	void insertIntoTimeLineSingle(double dAuVal);		
};

#endif // AUADJUST_H
