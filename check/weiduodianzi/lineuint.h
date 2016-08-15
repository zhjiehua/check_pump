#ifndef LINEUINT_H
#define LINEUINT_H

#include <QObject>

//线性单元
class LineUint : public QObject
{
	Q_OBJECT
public:
	enum DIR
	{
		LEFT,
		MIDDLE,
		RIGHT,
	};

	LineUint(QObject *parent = 0);
	explicit LineUint(const LineUint &line);
	~LineUint();

	void setRange(double x1, double y1, double x2, double y2, QString disp = QString("") );
	bool inStep(double x) const;
	bool inRange(double x) const;
	void printOut() const;
	double getStepValueByX(double x)const;
	double getValueByXAndK(double x, LineUint::DIR = MIDDLE)const;
	bool bOutOfStep(double x, LineUint::DIR) const;
	QString getFlowStr()const;

private:
	double x1;
	double y1;
	double x2;
	double y2;
	double k;//斜率;
	QString str;
	
};

#endif // LINEUINT_H
