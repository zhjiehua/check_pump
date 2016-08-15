#ifndef IOMODULE_H
#define IOMODULE_H

#include <QObject>
#include <QTimer>
#include <QStateMachine>

#ifdef linux
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <asm-generic/ioctl.h>
#include <fcntl.h>

//IOCTL������
#define IOC_MAGIC  'A'
#define PWM_IOCTL_WHICH_EDGE	_IO(IOC_MAGIC, 10)//�����Ǽ���½��ػ���������;
#define PWM_IOCTL_SET_FALLING	_IO(IOC_MAGIC, 9)//�����½���;
#define PWM_IOCTL_GET_EDG		_IO(IOC_MAGIC, 8)
#define PWM_IOCTL_GET_IO		_IO(IOC_MAGIC, 7)
#define PWM_IOCTL_CLS_IO		_IO(IOC_MAGIC, 6)
#define PWM_IOCTL_SET_IO		_IO(IOC_MAGIC, 5)
#define PWM_IOCTL_GET_STA		_IO(IOC_MAGIC, 4)
#define PWM_IOCTL_SET_CNT		_IO(IOC_MAGIC, 3)
#define PWM_IOCTL_SET_FREQ		_IO(IOC_MAGIC, 2)
#define PWM_IOCTL_START			_IO(IOC_MAGIC, 1)
#define PWM_IOCTL_STOP			_IO(IOC_MAGIC, 0)
#endif

//IO����
#define IO_PUL_MASK				((unsigned long)1<<0)
#define IO_DIR_MASK				((unsigned long)1<<1)
#define IO_RST_MASK				((unsigned long)1<<2)
#define IO_COIL_MASK			((unsigned long)1<<3)
#define IO_CTL0_MASK			((unsigned long)1<<4)
#define IO_CTL1_MASK			((unsigned long)1<<5)

#define IO_DIN1_MASK			((unsigned long)1<<6)
#define IO_DIN2_MASK			((unsigned long)1<<7)
#define IO_DIN3_MASK			((unsigned long)1<<8)
#define IO_DIN4_MASK			((unsigned long)1<<9)
#define IO_DIN5_MASK			((unsigned long)1<<10)
#define IO_DIN6_MASK			((unsigned long)1<<11)

#define IO_MOTORSTOP_MASK		((unsigned long)1<<12)
#define IO_BULGE_MASK			((unsigned long)1<<13)



class IoModule : public QObject
{
	Q_OBJECT

public:
	~IoModule();
	static IoModule *getInstance();

	void logic_set_io(quint32 io, bool val);
	bool logic_get_io(quint32 io);

	void lightOn(quint8 on, quint8 which = 0);	//���ƹصƣ�1���ƣ�0�ص�;
	void initLamp(quint8 which);				//뮵ơ��ٵƳ�ʼ��;
	void magnitOn(bool on);						//��������ϱպ�;

private:
	QTimer *m_pTimer;
	QTimer *m_pReadIoTimer;
	QStateMachine *pMachine;
	quint8 whichLamp;

	IoModule(QObject *parent = 0);
	void initIO();

//뮵Ƴ�ʼ����;
	void ctl1Out(quint8 x);		//CTL1��ƽ���;
	void ctl0Out(quint8 x);		//CTL0��ƽ���;
	quint8 getDin4();			//��ȡDin4���ŵ�ֵ;
	void logic_init_lamp_machinestat();

signals:
	void initLampSuccess(bool success);
	void bulge();//͹���źų���;
	void resetMachine();//���»ص���ʼ��״̬;

private slots:
	void init_s1();//CTL1���0��ƽ��CTL0���1��ƽ
	void init_s2();//CTL0���0��ƽ;
	void init_s3();//CTL1���1��ƽ����ʱ뮵�Ӧ����;
	void init_s4();//DIN4Ϊ0��ƽ��뮵���������Ϊ1��ƽ��뮵ƴ���
	void operation_s();//����ģʽ;

	void readingIO();
	
};

#endif // IOMODULE_H
