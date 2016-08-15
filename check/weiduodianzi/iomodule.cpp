#include "iomodule.h"
#include <QSignalTransition>
#include <QDebug>



#ifdef linux
#include <sys/ioctl.h>
static int fd = -1;
static unsigned long temp_read = 0;
#endif




IoModule::IoModule(QObject *parent)
	: QObject(parent)
	, whichLamp(0)
{
	initIO();
	logic_init_lamp_machinestat();
}

IoModule::~IoModule()
{

}

IoModule * IoModule::getInstance()
{
	static IoModule *pIo = new IoModule();
	return pIo;
}


void IoModule::initIO()
{
#ifdef linux
	fd = open("/dev/pwm", 0);
	if (fd < 0) {
		perror("open pwm device");
		exit(1);
	}
	ioctl(fd, PWM_IOCTL_WHICH_EDGE, 1);//ÕÅ½Ü»ªÌí¼Ó@2016-06-15£¬1±íÊ¾ÉÏÉýÑØ¼ì²â
#endif

	m_pReadIoTimer = new QTimer(this);
	m_pReadIoTimer->start(100);
	connect(m_pReadIoTimer, SIGNAL(timeout()), this, SLOT(readingIO()) );
	logic_init_lamp_machinestat();
}


void IoModule::logic_set_io(quint32 io, bool val)
{
#ifdef linux
	if(val)
		ioctl(fd, PWM_IOCTL_SET_IO, io);
	else
		ioctl(fd, PWM_IOCTL_CLS_IO, io);
#endif
}


bool IoModule::logic_get_io(quint32 io)
{
	unsigned long ret = 1;
#ifdef linux
	temp_read = io;
	ioctl(fd, PWM_IOCTL_GET_IO, (unsigned long*)(&temp_read));
	ret = temp_read&io;
#endif
	if(ret)
		return true;
	else
		return false;
}

void IoModule::logic_init_lamp_machinestat()
{
	pMachine = new QStateMachine(this);
	m_pTimer = new QTimer(this);
	m_pTimer->setSingleShot(true);
	QState *pInitS = new QState();
	QState *pInitS1 = new QState(pInitS);
	QState *pInitS2 = new QState(pInitS);
	QState *pInitS3 = new QState(pInitS);
	QState *pInitS4 = new QState(pInitS);
	pInitS->setInitialState(pInitS1);
	pInitS1->addTransition(m_pTimer, SIGNAL(timeout()), pInitS2);
	pInitS2->addTransition(m_pTimer, SIGNAL(timeout()), pInitS3);
	pInitS3->addTransition(m_pTimer, SIGNAL(timeout()), pInitS4);
	pInitS4->addTransition(this, SIGNAL(resetMachine()), pInitS1);

	QState *pOperationS = new QState();
	//pInitS->addTransition(this, SIGNAL(initLampSuccess()),pOperationS);
	pMachine->addState(pInitS);//³õÊ¼»¯×´Ì¬;
	pMachine->addState(pOperationS);//²Ù×÷×´Ì¬;
	pMachine->setInitialState(pInitS);

	connect(pInitS1, SIGNAL(entered()), this, SLOT(init_s1()));
	connect(pInitS2, SIGNAL(entered()), this, SLOT(init_s2()));
	connect(pInitS3, SIGNAL(entered()), this, SLOT(init_s3()));
	connect(pInitS4, SIGNAL(entered()), this, SLOT(init_s4()));
	connect(pOperationS, SIGNAL(entered()), this, SLOT(operation_s()));
	
}

void IoModule::init_s1()
{
	qDebug()<<"s11";
	ctl0Out(1);
	ctl1Out(0);
	m_pTimer->start(5000);
}

void IoModule::init_s2()
{
	qDebug()<<"s12";
	if(whichLamp == 0)//ë®µÆ;
		ctl0Out(0);
	else
		ctl1Out(1);//ÎÙµÆ;

	m_pTimer->start(1000);
}

void IoModule::init_s3()
{
	qDebug()<<"s13";
	if(whichLamp == 0)
	{
		ctl1Out(1);
		m_pTimer->start(1000);
	}
	else
		m_pTimer->start(0);
}

void IoModule::init_s4()
{
	quint8 flag = getDin4();
	if(flag == 0)
	{
		qDebug()<<"light success!!!!!!";
		emit(initLampSuccess(true));
	}
	else
	{
		qDebug()<<"light failed!!!!!!!";
		emit(initLampSuccess(false));
	}
}

void IoModule::operation_s()
{
	qDebug()<<"operation mode";
}

void IoModule::readingIO()
{
	unsigned long ret = 0;
#ifdef linux
	temp_read = IO_BULGE_MASK;
	ioctl(fd, PWM_IOCTL_GET_EDG, (unsigned long*)(&temp_read));
	ret = temp_read&IO_BULGE_MASK;

#else
	static quint32 cnt = 0;
	if(++cnt == 3)
	{
		ret = 1;
		cnt = 0;
	}
#endif
	if(ret)
	{
		emit(bulge());
	}
	

	
}

void IoModule::ctl1Out(quint8 x)
{
	qDebug()<<"CTL1="<<x;
#ifdef linux
		logic_set_io(IO_CTL1_MASK, x);
#endif
}

void IoModule::ctl0Out(quint8 x)
{
	qDebug()<<"CTL0="<<x;
#ifdef linux
	logic_set_io(IO_CTL0_MASK, x);
#endif
}

quint8 IoModule::getDin4()
{
	qDebug()<<"Din4=0";
	bool ret = false;
#ifdef linux
	ret = logic_get_io(IO_DIN4_MASK);
#endif
	if(ret)
		return 1;
	else
		return 0;
}

void IoModule::lightOn(quint8 on, quint8 which)
{
	if(which == 0)//ë®µÆ
	{
		if(on == 1)//¿ªµÆ;
		{
			ctl1Out(1);
			ctl0Out(0);
		}
		else//¹ØµÆ;
		{
			ctl1Out(0);
			ctl0Out(1);
		}
	}
	else//ÎÙµÆ;
	{
		if(on == 1)//¿ªµÆ;
		{
			ctl1Out(1);
		}
		else//¹ØµÆ;
		{
			ctl1Out(0);
		}
	}
	
}

void IoModule::initLamp( quint8 which )
{
	whichLamp = which;
	if(!pMachine->isRunning())
		pMachine->start();
	else
		emit(resetMachine());
}

void IoModule::magnitOn(bool on)
{
	/*if(on)
	ioctl(fd, PWM_IOCTL_SET_IO, io);
	else
	ioctl(fd, PWM_IOCTL_CLS_IO, io);*/
}	
