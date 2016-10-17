#include "machinestat.h"
#include <QTimer>
#include <QList>
#include <QtAlgorithms>
#include "lineuint.h"
#include "Communication/LogicThread.h"
#include "iomodule.h"
#include "baseMainPage.h"
#include "auadjust.h"

#ifdef linux
#include<sys/time.h>
#include <signal.h>
#include <pthread.h>
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
#endif

extern BaseMainPage *g_pMainWindow;

bool wlen_chang = true;

#define _USE_MATH_DEFINES
#include <math.h>
#include <QTime>

#define LOWSAMPLEVAL  50
#define LOWREFERENCEVAL  50

#define UPLOAD_AU_INTERVAL_MS			50

#define TIMEOUT		UPLOAD_AU_INTERVAL_MS
//#define TIMEOUT		100
#define TIMEOUT100MS (100/TIMEOUT)
#define TIMEOUT1S	(1000/TIMEOUT)
#define TIMEOUT2S	(2000/TIMEOUT)
#define TIMEOUT3S	(3000/TIMEOUT)
#define TIMEOUT60S	(60000/TIMEOUT)

//au值数据池大小;
#define FILTER_LIST_MAX			6  //6
#define AU_LIST_MAX				12  //12
#define AU_LIST_MAX_DOUBLE		AU_LIST_MAX

#define SERIAL_MAX		9999999999
#define SERIAL_NUM_KEY	19900208
#define SERIAL_NUM_VAL	345192069
#define ACTIVE_CODE_TRY	9000000000
#define ACTIVE_CODE_MAX 999999999
#define ACTIVE_MASK		0x12345678

//波长补偿问题;
//前后补偿变化小于1nm时候需要的补偿;
#define MINI_COMPEN_VAL	0.03        //单机扫描补偿参数
#define MINI_COMPEN_VAL1 0.05       //上位机扫描补偿参数

/////////////////////////////////////////////////////////
//
//功能：十进制转BCD码
//
//输入：int Dec                      待转换的十进制数据
//      int length                   BCD码数据长度
//
//输出：unsigned char *Bcd           转换后的BCD码
//
//返回：0  success
//
//思路：原理同BCD码转十进制
//
//////////////////////////////////////////////////////////
int DectoBCD(int Dec,int length)
{
	int ret = 0;
	for(int i = 0; i < length/2; i++)
	{
		int temp = Dec % 100;
		temp = ((temp/10)<<4) | ((temp%10)&0xff);
		temp = temp << i*8;
		ret |= temp;
		Dec/=100;
	}
	return ret;
}




MachineStat::MachineStat(QObject *parent)
	: QObject(parent)
	,m_bHomeInitSuccess(false)
	,m_nTimerId(0)
	,m_nAuUploadTime(1)
	,m_nAuUploadTimeCnt(0)
	,m_nReSendWlenChangeCnt(0)
	,m_nReadAuCnt(0)
	,m_nDouleWaveEqualReadAuCnt(0)
	,m_bSetWaveAfterHome(false)
	,pwdOK(false)
	,pwdNeed(false)
	,noRTCBattery(false)
{
	pDb = DataBase::getInstance();	//数据库初始化;
	initMachineStat();				//机器状态标识和变量初始化;
	initIO();						//IO模块初始化;
	initTimer();					//定时器任务初始化;
	initCommunication();			//通讯模块初始化;

	//参数同步和初始化;
	updateTimeInte();				//更新灯源、时间积分到mcu;
	initAulist();					//清波1au
	initAulist(1);					//清波2au

	initStartupTime();				//开机计时;

	serialNumberGenerate();			//生成序列号;

	initMACAddr();
	initIPAddr();//张杰华添加@2016-06-26

	//resetWaveAndAngle();
	//setWaveCtrlWordAndHome();//归原点;
}

MachineStat::~MachineStat()
{
	releaseTimeoutList();
}

MachineStat * MachineStat::getInstance()
{
	static MachineStat *pStat = new MachineStat();
	return pStat;
}


void MachineStat::timeoutFunc()
{
	for (QList<LPTimeOutStruct>::iterator it = m_timeoutList.begin(); it!=m_timeoutList.end(); it++)
	{
		LPTimeOutStruct pTimeout = *it;
		if(++pTimeout->cnt >= pTimeout->timeout)
		{
			pTimeout->cnt = 0;
			(this->*pTimeout->timeoutFunc)();
		}
	}

	if(!m_bHomeInitSuccess)
	{
		static int initTime = 0;
		initTime++;
		if(initTime >= (60*1000/TIMEOUT))
		{
			stopMotorInit();
			initStartup();
			initTime = 0;
		}
		/*else if(initTime%10 == 0)
		qDebug()<<initTime;*/
	}
}


void MachineStat::initIO()
{
	IoModule *pIO = IoModule::getInstance();
	connect(pIO, SIGNAL(initLampSuccess(bool)), this, SLOT(lightIniSuccess(bool)));

	if(!noRTCBattery)
		initLamp();

	connect(IoModule::getInstance(), SIGNAL(bulge()), this, SLOT(dealBulge()));
}


void MachineStat::initTimer()
{
	initTimeoutList();//定时器任务初始化;				

	QTimer *pTimer = new QTimer(this);
	connect(pTimer, SIGNAL(timeout()), this, SLOT(timeoutFunc()));
	pTimer->start(TIMEOUT);

	if(DataBase::getInstance()->queryData("pcProtocol").toInt() == 0)
		setUploadAuFreq(1);

	//setUploadAuFreq(1);   //张杰华屏蔽@2016-06-20，等到界面完全启动后才上传au值，所以这个函数放在baseMainPage的构造函数末尾

#if 0
//使用linux下的定时器;
#ifdef linux
	if(DataBase::getInstance()->queryData("pcProtocol").toInt() == 0)
		setupUploadTask();
#endif
#endif
}

void MachineStat::initMachineStat()
{
	m_machineStat.machineStat = STARTUP;									//初始化;
	m_machineStat.oldMachineStat = STARTUP;									//旧的机器状态;
	m_machineStat.machineMode = CMDMODE;									//工作模式：扫描模式，命令模式;
	m_machineStat.scanmodePrevStep = 0;										//扫描模式下的前一步;
	m_machineStat.m_nStartupTime = 0;											//开机时间
	m_machineStat.m_nSysUsedTime = pDb->queryData("usedTime").toInt();			//系统累计时间;
	m_machineStat.m_nXeStartupTime = pDb->queryData("xeUsedTime").toInt();		//氘灯累计使用时间;
	m_machineStat.m_nTunStartupTime = pDb->queryData("tunUsedTime").toInt();	//钨灯累计使用时间;
	m_machineStat.lampStat = OFF;											//灯源状态;
	m_machineStat.m_nSampleVal = 0;											//样本值;
	m_machineStat.m_nRefVal = 0;											//参比值;
	m_machineStat.m_nSampleVal2 = 0;											//样本值;
	m_machineStat.m_nRefVal2 = 0;											//参比值;
	m_machineStat.m_dAu1 = 0;												//波长1习惯度;
	m_machineStat.m_dAu2 = 0;												//波长2吸光度;
	m_machineStat.m_nCurrentWave = 0;										//当前波长是波长1/2;
	m_machineStat.m_dCurrentWlen = 0;										//当前波长值;
	m_machineStat.m_dCurrentAngle = 0;										//当前角度;
	m_machineStat.m_dPercentOfRandS = pDb->queryData("percentRofS").toDouble();									//K = R/S;
	m_machineStat.m_dPercentOfRandS2 = pDb->queryData("percentRofS2").toDouble();								//K = R/S;
	m_machineStat.m_nUploadWhich = 0;//默认上传AU;
	m_machineStat.bTryDone = false;											//试用完毕;

	m_machineStat.m_dPrevWlen = 0;
	m_machineStat.m_dScanOffset = 0;

	m_machineStat.m_nUploadInterval = 0;

	m_machineStat.m_bLocateWaveSuccess = true;

	//读取试用的当天日期;
	m_machineStat.m_firstTryDateTime = pDb->queryData("firstTryDateTime").toUInt();//记录开始试用的当天日期时间;
	if(m_machineStat.m_firstTryDateTime == 0)
	{
		clearUsedTime();
	}

	//推后修改波长定时器;
	m_pLatterTimer = new QTimer(this);
	m_pLatterTimer->setSingleShot(true);
	connect(m_pLatterTimer, SIGNAL(timeout()), this, SLOT(changeWlenLater()) ); 

	/*double a = waveToAngle(255);
	double b = waveToAngle(256);
	double c = waveToAngle(300);
	double d = waveToAngle(301);
	qDebug()<<"b="<<(b-=a);
	qDebug()<<"d="<<(d-=c);*/

#ifdef linux
    //! 读取rtc时间;
    time_t now = time(NULL);

    //! 读取数据库标志;
    long last_time = DataBase::getInstance()->queryData("last_time").toLong();

	qDebug() << "!!!!!!now = " << now;
	qDebug() << "!!!!!!last_time = " << last_time;

    if(last_time == 0)
    {
        //写入last_time;
        //DataBase::getInstance()->updateDate("last_time", QString::number(now));

		qDebug() << "last_time == 0";
    }
    else
    {
        //! 比较;
        if( now <= last_time )
		{
			//while(1)
				qDebug() << "--------now <= last_time";
            //exit;
				//while(1);
				//system(QString("exit").toLatin1().data());
				noRTCBattery = true;
		}
		else
		{
			//while(1)
				qDebug() << "=======now > last_time";
				//DataBase::getInstance()->updateDate("last_time", QString::number(now));

				noRTCBattery = false;
		}
    }
	
	noRTCBattery = false;//

	DataBase::getInstance()->updateDate("last_time", QString::number(now));
	system(QString("hwclock -s").toLatin1().data());
#endif
}

void MachineStat::clearTime(MachineTime time)
{
	if(time == SYSTIME)
		clearUsedTime();
	else if(time == STARTUPTIME)
	{
		clearStartupTime();


		//张杰华添加@2016-06-23
		g_pMainWindow->navigatorPageAt(0);
	}
	else if(time == XEUSEDTIME)
		clearXeUsedTime();
	else if(time == TUNUSEDTIME)
		clearTunUsedTime();
}





void MachineStat::clearStartupTime()
{
	//setStartupTime(0);
	initStartupTime();
}




int MachineStat::checkProbation()
{
	quint32 probationDay = pDb->queryData("tryDay").toInt();			//试用天数;
	//quint32 usedDay = getUsedTime()/60/60/24;
	quint32 usedDay = getTime(SYSTIME)/60/60/24;
	//qDebug()<<getUsedTime();
	//qDebug()<<"..."<<probationDay;
	qint32 temp = probationDay - usedDay;
	//qDebug()<<"try Day:"<<probationDay;
	//qDebug()<<"used Day:"<<usedDay;

	//temp = 100;//屏蔽先;

	if(temp <= 0)
	{
		m_machineStat.bTryDone = true;
		temp = 0;
	}
	else
		m_machineStat.bTryDone = false;

	//return 0;
	return temp;
}

void MachineStat::saveUsedTime()
{
	//使用时间记录;机器累计
	quint32 usedTime = m_machineStat.m_nSysUsedTime;
	QString temp = QString::number(usedTime);
	pDb->updateDate("usedTime", temp);

	usedTime = m_machineStat.m_nXeStartupTime;
	temp = QString::number(usedTime);
	pDb->updateDate("xeUsedTime",temp);

	usedTime = m_machineStat.m_nTunStartupTime;
	temp = QString::number(usedTime);
	pDb->updateDate("tunUsedTime",temp);
}



quint32 MachineStat::getTime(MachineTime time)
{
	if(time == SYSTIME)
		//return getUsedTime();
		return m_machineStat.m_nSysUsedTime;
	else if(time == STARTUPTIME)
		return m_machineStat.m_nStartupTime;
	else if(time == XEUSEDTIME)
		return m_machineStat.m_nXeStartupTime;
	else if(time == TUNUSEDTIME)
		return m_machineStat.m_nTunStartupTime;
	else
		return 0;
}

void MachineStat::initTimeoutList()
{
	m_timeoutList.clear();
	registerTimeoutFunc(TIMEOUT2S, &MachineStat::saveUsedTime);			//保存各种使用时间;//3s
	registerTimeoutFunc(TIMEOUT2S, &MachineStat::checkTryOut);			//检查是否试用超时;//3s
	//registerTimeoutFunc(TIMEOUT60S, &MachineStat::saveDataBase);		//保存数据库;//60s
	registerTimeoutFunc(TIMEOUT1S, &MachineStat::updateStartupTime);	//更新使用时间;//1s

	//registerTimeoutFunc(TIMEOUT100MS, &MachineStat::uploadAuToPc);		//更新Au值到PC;//1s

	registerTimeoutFunc(1, &MachineStat::auUploadTimeOut);		//更新Au值到PC;//50ms
}

void MachineStat::releaseTimeoutList()
{
	qDeleteAll(m_timeoutList.begin(), m_timeoutList.end() );
	m_timeoutList.clear();
}

void MachineStat::registerTimeoutFunc(const quint32 time, pTimeoutFunc pFunc)
{
	LPTimeOutStruct pTimeout= new TimeOutStruct;
	pTimeout->timeout = time;
	pTimeout->timeoutFunc = pFunc;
	pTimeout->cnt = 0;
	m_timeoutList.append(pTimeout);
}

void MachineStat::deRegisterTimeoutFunc( pTimeoutFunc pFunc )
{
	for (int i = 0; i < m_timeoutList.count(); i++)
	{
		if(m_timeoutList.at(i)->timeoutFunc == pFunc)
			delete(m_timeoutList.takeAt(i));
	}
}

QString g_sTime;

void MachineStat::auUploadTimeOut()
{
	if(!m_bHomeInitSuccess)//未完成原点前不能下发命令给MCU，否则导致找原点不准
	{
		return;
	}

	m_nAuUploadTimeCnt++;
	if(m_nAuUploadTime > 0 && m_nAuUploadTimeCnt >= m_nAuUploadTime)
	{
		m_nAuUploadTimeCnt = 0;

		if(uploadAuToPc() != -1)
			m_nStartupTimeMsec++;
	}

	quint32 ch = DataBase::getInstance()->queryData("chanel").toInt();
#if 1
	if(m_machineStat.m_bLocateWaveSuccess == true)
	{
		//张杰华添加@2016-07-06,主动读取S R
		if(ch == 0) 
			//|| (ch == 1 && DataBase::getInstance()->queryData("wavelen1").toInt() == DataBase::getInstance()->queryData("wavelen2").toInt()))
		{
			if(m_nReadAuCnt++ >= 4)//200ms读一次，太快会出问题,MCU会发送一些乱的 S R!!!!!!!!!!!!!!!!!!!!!!!!!
			{
				m_nReadAuCnt = 0;
				m_pCommunicationCoupling->sendMcuCmd(1, MCU_READ_AU_VAL_1, 0);
			}
		}
		else if(DataBase::getInstance()->queryData("wavelen1").toInt() == DataBase::getInstance()->queryData("wavelen2").toInt())
		{
			if(m_nDouleWaveEqualReadAuCnt++ >= 4)//200ms读一次，太快会出问题,MCU会发送一些乱的 S R!!!!!!!!!!!!!!!!!!!!!!!!!
			{
				m_nDouleWaveEqualReadAuCnt = 0;
				m_pCommunicationCoupling->sendMcuCmd(1, MCU_READ_AU_VAL_1, 0);
			}
		}
	}
	else
	{
		m_nReadAuCnt = 0;
		m_nDouleWaveEqualReadAuCnt = 0;
	}
#endif

	//张杰华添加@2016-07-04,波长修改重发=======================================
	if(m_machineStat.machineStat == LOCATINGWAVE
		&& m_machineStat.m_bLocateWaveSuccess == false)
	{
		m_nReSendWlenChangeCnt++;
		if(m_nReSendWlenChangeCnt >=  10)//50ms*15还没接收到8400000000重发
		{
			qDebug() << "\nwlen = " << DataBase::getInstance()->queryData("wavelen1") << "change timeout***************** ";
			m_nReSendWlenChangeCnt = 0;
			//quint8 chanel = DataBase::getInstance()->queryData("chanel").toInt();
			if(ch == 0)// && whichLen == EWLEN1
			{
				MachineStat::getInstance()->setWaveCtrlWord();
			}
			else
			{
				MachineStat::getInstance()->resetWaveAndAngle();
				MachineStat::getInstance()->setWaveCtrlWord();
			}
		}
	}
	else
	{
		m_nReSendWlenChangeCnt = 0;
	}
}

void MachineStat::timerEvent( QTimerEvent *event )
{
	/*QTime newCurrentTime = QTime::currentTime();
	qDebug()<<m_currentTime.msecsTo(newCurrentTime);
	m_currentTime = newCurrentTime;*/

	if(uploadAuToPc() != -1)
		m_nStartupTimeMsec++;

#if 1
	//张杰华添加@2016-07-06,主动读取S R
	static int cnt = 0;
	if(DataBase::getInstance()->queryData("chanel").toInt() == 0)
	{
		if(cnt++ >= 3)//150ms读一次，太快会出问题
		{
			cnt = 0;
			m_pCommunicationCoupling->sendMcuCmd(1, MCU_READ_AU_VAL_1, 0);
		}
	}
#endif

	//张杰华添加@2016-07-04,波长修改重发=======================================
	if(m_machineStat.machineStat == LOCATINGWAVE
		&& m_machineStat.m_bLocateWaveSuccess == false)
	{
		m_nReSendWlenChangeCnt++;
		if(m_nReSendWlenChangeCnt >=  15)//50ms*15还没接收到8400000000重发
		{
			qDebug() << "\nwlen = " << DataBase::getInstance()->queryData("wavelen1") << "change timeout***************** ";
			m_nReSendWlenChangeCnt = 0;
			quint8 chanel = DataBase::getInstance()->queryData("chanel").toInt();
			if(chanel == 0 && whichLen == EWLEN1)
			{
				MachineStat::getInstance()->setWaveCtrlWord();
			}
			else
			{
				MachineStat::getInstance()->resetWaveAndAngle();
				MachineStat::getInstance()->setWaveCtrlWord();
			}
		}
	}
	else
		m_nReSendWlenChangeCnt = 0;

}

void MachineStat::checkTryOut()
{
	int active = pDb->queryData("bActive").toInt();
	if(active == 0)//如果未激活，需要定时检测试用时间;
	{
		if( checkProbation() == 0)
		{
			//g_pMainWindow->changePage(PWDPAGE_INDEX);
			m_machineStat.bTryDone = true;
			g_pMainWindow->changePage(PERMITPAGE_INDEX);
		}
		else//试用期未到;
		{
			m_machineStat.bTryDone = false;
		}
	}
	else
		m_machineStat.bTryDone = false;
}



void MachineStat::updateStartupTime()
{
#if 1
	if(getLampStat() == ON)//灯源正在工作;
	{
		emit(lampState(1));
		if(DataBase::getInstance()->queryData("xe_tun").toInt() == 0)//氘灯;
			m_machineStat.m_nXeStartupTime++;
		else
			m_machineStat.m_nTunStartupTime++;
	}
	else
		emit(lampState(2));
#endif
	m_machineStat.m_nSysUsedTime++;//系统使用时间;
	//qDebug()<<m_machineStat.m_nSysUsedTime;
}



void MachineStat::setStartupTime(quint32 time)
{
	m_machineStat.m_nStartupTime = time;
	emit(updateStartupTimeDisplay( time) );
}

void MachineStat::initCommunication()
{
	m_pCommunicationCoupling = new CommunicationCoupling(this);
}



void MachineStat::lightIniSuccess(bool success)
{
	if(success)//开机时候
	{
		emit(changeLightStat(ON));
		m_machineStat.lampStat = ON;
		if(m_machineStat.machineStat == STARTUP)
		{
			QTimer::singleShot(500, this, SLOT(initStartup()));//延时500ms
		}
	}
	else
	{
		emit(changeLightStat(OFF));
		//sysError(LAMPINI_ERR, true);//灯源初始化失败;
		emit(lampState(0));
	}
	
}

void MachineStat::setLampStat(LampStatment stat)
{
	if(stat == m_machineStat.lampStat)
		return;

	m_machineStat.lampStat = stat;
	int whichLamp = DataBase::getInstance()->queryData("xe_tun").toInt();
	if(stat == ON)//开灯;
	{
		IoModule::getInstance()->lightOn(1, whichLamp);
	}
	else//关灯;
	{
		IoModule::getInstance()->lightOn(0, whichLamp);
	}
	emit(changeLightStat(stat));

}



//波长操作;
#define KK (0.8589598*2.0/1200.0*1000000.0)
double MachineStat::waveToAngle(double wave)
{
	double val = wave/KK;
	val = asin((double)val);
	return val;
}


#define PULSE_PER_ROUND 102400
void MachineStat::locateToWaveLen1(double wLen, quint8 which)
{
	//qDebug() << "\n";
	//qDebug() << "before compensation wLen = " << wLen;

	wLen = compensationForWave(wLen);

	m_machineStat.saowLen1 = wLen;        //补偿使用参数

	if(qAbs(wLen-m_machineStat.m_dPrevWlen) <= 3)
	{
		if(wLen > m_machineStat.m_dPrevWlen)
			m_machineStat.saowLen1+=MINI_COMPEN_VAL1;
		else
			m_machineStat.saowLen1-=MINI_COMPEN_VAL1;
	}
	double tAngle = waveToAngle(m_machineStat.saowLen1);//目标波长转换成角度;
	/*qDebug()<<(tAngle/2/M_PI*360);
	qDebug()<<(m_machineStat.m_dCurrentAngle/2/M_PI*360);*/
	//int dir = 0;
	//if(wLen > m_machineStat.m_dCurrentWlen)
	//	dir = 0x00;//逆时针;
	//else
	//	dir = 0x10;//顺时针;

	//qDebug() << "locateToWaveLen1()";
	//qDebug() << "wLen = " << wLen;

		//Debug() << "m_machineStat.m_dCurrentWlen = " << m_machineStat.m_dCurrentWlen;

	/*qDebug() << "tAngle = " << tAngle;
	qDebug() << "dir = " << dir;*/
	

	////角度差;
	//double delta = tAngle - m_machineStat.m_dCurrentAngle;
	////角度差转换成脉冲数;
	////delta = abs(delta);
	//if(delta < 0)
	//	delta = m_machineStat.m_dCurrentAngle-tAngle;
	////qDebug()<<(delta/2/M_PI*360);
	//quint32 nStep = (delta/(2*M_PI))*PULSE_PER_ROUND;
	////顺时针逆时针??????
	//quint32 arg =( (dir|0x1&0xff)<<21 |(nStep&0x1fffff) );

	//张杰华修改@2016-06-29，改为发送绝对坐标
	quint32 nStep = (tAngle/(2*M_PI))*PULSE_PER_ROUND;
	//顺时针逆时针??????
	quint32 arg = (0x01<<21)|(nStep&0x1fffff);

	//qDebug() << "nStep = " << nStep;

	//张杰华调试添加@2016-07-03
	if(nStep)
		wlen_chang = true;
	else
		qDebug() << "wlen change error, maybe not change!!!!";

	//qDebug() << "\n";

	m_pCommunicationCoupling->sendMcuCmd(1,MCU_SETWAV_TO,arg);

	m_machineStat.m_dCurrentWlen = wLen;
	m_machineStat.m_dCurrentAngle = waveToAngle(wLen);

}


void MachineStat::setWaveCtrlWordAndHome()
{
	//setWaveCtrlWord();		//下发MCU波长值; //张杰华屏蔽@2016-07-03

	m_bSetWaveAfterHome = true;

	//delay_ms(10000);			
	initMotor();			//下发MCU初始化命令;

}

#define USE_FILTER 1

void MachineStat::updateSampleVal(quint32 val)
{
	static bool sampleLowState = false;

	static quint32 lastSampleVal;
	static quint32 lastSampleVal2;

	////张杰华添加@2016-07-07
	//if(m_machineStat.machineStat == LOCATINGWAVE && m_machineStat.m_bLocateWaveSuccess)
	//{
	//	delayAfterUpdateWave();
	//	qDebug() << "updateSampleVal()";
	//}

	int timeInte = 1;
	quint32 temp = val*timeInte;

	quint32 average = 0;
	quint32 outSampleAverage = 0;

	if(m_machineStat.m_nCurrentWave == 0)//波长1
	{
		if(m_machineStat.m_nUploadWhich == 2)//只上传r
		{
			m_machineStat.m_nSampleVal = lastSampleVal;
		}
		else
		{

#if USE_FILTER
			//数据池未满采用平均滤波
			if(sampleValList.count() < AU_LIST_MAX)
			{
				sampleValList << temp;
				average = getAverage(sampleValList);
			}
			else//加权平均
			{
				sampleValList.removeFirst();
				sampleValList.append(temp);
				QVector<quint32> myVector = sampleValList.toVector();
				average = getWeightedAverage(myVector);
				//average = getAverage(sampleValList);
			}

			//最大4阶滤波
			if(sampleValOutList.count() > FILTER_LIST_MAX)
				sampleValOutList.removeFirst();
			sampleValOutList << average;
			outSampleAverage = orderFilter(sampleValOutList, sampleValOutList.count());
			sampleValOutList.removeLast();
			sampleValOutList << outSampleAverage;

			//最终输出数据
			m_machineStat.m_nSampleVal = outSampleAverage;
#else
			m_machineStat.m_nSampleVal = temp;
#endif
			lastSampleVal = m_machineStat.m_nSampleVal;
		}

		if(m_machineStat.m_nSampleVal < LOWSAMPLEVAL)
		{
			if(!sampleLowState)
			{
				sampleLowState = true;
				emit(sampleLow(true));
			}
		}
		else
		{
			if(sampleLowState)
			{
				sampleLowState = false;
				emit(sampleLow(false));
			}
		}
		
#if 0
		//static qint32 last_m_nSampleVal = 0;
		//if(abs(last_m_nSampleVal - (qint32)m_machineStat.m_nSampleVal) > 30)
		//{
		//	qDebug() << "m_nSampleVal = " << m_machineStat.m_nSampleVal;
		//	qDebug() << "last_m_nSampleVal = " << last_m_nSampleVal;
		//}
		//last_m_nSampleVal = m_machineStat.m_nSampleVal;
#endif

	}
	else//波长2
	{
		if(m_machineStat.m_nUploadWhich == 2)//只上传r
		{
			m_machineStat.m_nSampleVal2 = lastSampleVal2;;
		}
		else
		{

#if USE_FILTER
			//数据池未满采用平均滤波
			if(sampleVal2List.count() < AU_LIST_MAX)
			{
				sampleVal2List << temp;
				average = getAverage(sampleVal2List);
			}
			else//加权平均
			{
				sampleVal2List.removeFirst();
				sampleVal2List.append(temp);
				QVector<quint32> myVector = sampleVal2List.toVector();
				average = getWeightedAverage(myVector);
			}

			//最大4阶滤波
			if(sampleVal2OutList.count() > FILTER_LIST_MAX)
				sampleVal2OutList.removeFirst();
			sampleVal2OutList << average;
			outSampleAverage = orderFilter(sampleVal2OutList, sampleVal2OutList.count());
			sampleVal2OutList.removeLast();
			sampleVal2OutList << outSampleAverage;

			//最终输出数据
			m_machineStat.m_nSampleVal2 = outSampleAverage;
#else
			m_machineStat.m_nSampleVal2 = temp;
#endif
			lastSampleVal2 = m_machineStat.m_nSampleVal2;
		}

		if(m_machineStat.m_nSampleVal2 < LOWSAMPLEVAL)
		{
			if(!sampleLowState)
			{
				sampleLowState = true;
				emit(sampleLow(true));
			}
		}
		else
		{
			if(sampleLowState)
			{
				sampleLowState = false;
				emit(sampleLow(false));
			}
		}
		
	}
}

void MachineStat::updateRefVal(quint32 val)
{
	static bool refLowState = false;

	static quint32 lastRefVal;
	static quint32 lastRefVal2;

	if(m_machineStat.machineMode == SCANMODE && m_machineStat.machineStat == WAITRDY)
	{
		quint32 nIntervalTime = DataBase::getInstance()->queryData("sTime").toInt();
		nIntervalTime*=1000;
		nIntervalTime/=TIMEOUT;
		//registerTimeoutFunc(TIMEOUT3S,&MachineStat::waveScanUpdate);
		registerTimeoutFunc(nIntervalTime,&MachineStat::waveScanUpdate);
		m_machineStat.machineStat = READY;
		//sysError(5, 1);
	}

	//张杰华屏蔽@2016-07-07，接收到定位成功命令立即设置为可以修改波长，可能没能接收到au数据
	if(m_machineStat.machineStat == LOCATINGWAVE && m_machineStat.m_bLocateWaveSuccess)
	{
		delayAfterUpdateWave();
		qDebug() << "updateRefVal";
	}

	int timeInte = 1;
	quint32 temp = val*timeInte;

	quint32 average = 0;
	quint32 outRefAverage = 0;
	double cofficient = DataBase::getInstance()->queryData("coefficient").toDouble();
	double au = 0;
	
	if(m_machineStat.m_nCurrentWave == 0)//波长1;
	{
		if(m_machineStat.m_nUploadWhich == 1)//只上传s
		{
			m_machineStat.m_nRefVal = lastRefVal;
		}
		else
		{

#if USE_FILTER
			//数据池未满采用平均滤波
			if(refValList.count() < AU_LIST_MAX)
			{
				refValList << temp;
				average = getAverage(refValList);
			}
			else//加权平均
			{
				refValList.removeFirst();
				refValList.append(temp);
				QVector<quint32> myVector = refValList.toVector();
				average = getWeightedAverage(myVector);
				//average = getAverage(refValList);
			}

			//最大4阶滤波
			if(refValOutList.count() > FILTER_LIST_MAX)
				refValOutList.removeFirst();
			refValOutList << average;
			outRefAverage = orderFilter(refValOutList, refValOutList.count());
			refValOutList.removeLast();
			refValOutList << outRefAverage;

			//最终输出数据
			m_machineStat.m_nRefVal = outRefAverage;
#else
			m_machineStat.m_nRefVal = temp;
#endif
			lastRefVal = m_machineStat.m_nRefVal;
		}

		if(m_machineStat.m_nRefVal < LOWSAMPLEVAL)
		{
			if(!refLowState)
			{
				refLowState = true;
				emit(referenceLow(true));
			}
		}
		else
		{
			if(refLowState)
			{
				refLowState = false;
				emit(referenceLow(false));
			}
		}

#if 0
		static qint32 last_m_nRefVal = 0;
		if(abs(last_m_nRefVal - (qint32)m_machineStat.m_nRefVal) > 30)
		{
			qDebug() << "m_nRefVal = " << m_machineStat.m_nRefVal;
			qDebug() << "last_m_nRefVal = " << last_m_nRefVal;
		}
		last_m_nRefVal = m_machineStat.m_nRefVal;
#endif

//========================================================================================
		if(m_machineStat.m_nRefVal == 0 || m_machineStat.m_nSampleVal == 0)
		{
			au = 0;
		}
		else
		{
			//AU值计算公式;
			au = cofficient*log10(m_machineStat.m_dPercentOfRandS *(double)m_machineStat.m_nRefVal/(double)m_machineStat.m_nSampleVal);
			//au = au/log10((double)2);//张杰华添加@2016-07-02

			double constVal = DataBase::getInstance()->getConstVal();
			au = au*2.0/constVal;

			//平滑处理;
			au = getAverageOfAu(au);
		}

		DataBase::getInstance()->updateDate("ausample1", QString::number(m_machineStat.m_nSampleVal));
		DataBase::getInstance()->updateDate("auref1", QString::number(m_machineStat.m_nRefVal));
		//double constVal = DataBase::getInstance()->getConstVal();
		//au = au*2.0/constVal;
		DataBase::getInstance()->updateDate("au1", QString::number(au, 'f', 4));
		m_machineStat.m_dAu1 = au;

		//qDebug() << "au = " << au;
		
		emit(updateAuValue(m_machineStat.m_nSampleVal, m_machineStat.m_nRefVal, au, m_machineStat.m_nCurrentWave));
	}
	else
	{
		if(m_machineStat.m_nUploadWhich == 1)//只上传s
		{
			m_machineStat.m_nRefVal2 = lastRefVal2;
		}
		else
		{

#if USE_FILTER
			//数据池未满采用平均滤波
			if(refVal2List.count() < AU_LIST_MAX)
			{
				refVal2List << temp;
				average = getAverage(refVal2List);
			}
			else//加权平均
			{
				refVal2List.removeFirst();
				refVal2List.append(temp);
				QVector<quint32> myVector = refVal2List.toVector();
				average = getWeightedAverage(myVector);
			}

			//最大4阶滤波
			if(refVal2OutList.count() > FILTER_LIST_MAX)
				refVal2OutList.removeFirst();
			refVal2OutList << average;
			outRefAverage = orderFilter(refVal2OutList, refVal2OutList.count());
			refVal2OutList.removeLast();
			refVal2OutList << outRefAverage;

			//最终输出数据
			m_machineStat.m_nRefVal2 = outRefAverage;
#else
			m_machineStat.m_nRefVal2 = temp;
#endif
			lastRefVal2 = m_machineStat.m_nRefVal2;
		}

		if(m_machineStat.m_nRefVal2 < LOWSAMPLEVAL)
		{
			if(!refLowState)
			{
				refLowState = true;
				emit(referenceLow(true));
			}
		}
		else
		{
			if(refLowState)
			{
				refLowState = false;
				emit(referenceLow(false));
			}
		}

//========================================================================================
		if(m_machineStat.m_nRefVal2 == 0 || m_machineStat.m_nSampleVal2 == 0)
		{
			au = 0;
		}
		else
		{
			//AU值计算公式;
			au = cofficient*log10(m_machineStat.m_dPercentOfRandS2 *(double)m_machineStat.m_nRefVal2/(double)m_machineStat.m_nSampleVal2);
			//au = au/log10((double)2);//张杰华添加@2016-07-02

			double constVal = DataBase::getInstance()->getConstVal();
			au = au*2.0/constVal;

			//平滑处理;
			au = getAverageOfAu(au, 1);
		}

		DataBase::getInstance()->updateDate("ausample2", QString::number(m_machineStat.m_nSampleVal2));
		DataBase::getInstance()->updateDate("auref2", QString::number(m_machineStat.m_nRefVal2));
		DataBase::getInstance()->updateDate("au2", QString::number(au, 'f', 4));
		m_machineStat.m_dAu2 = au;

		emit(updateAuValue(m_machineStat.m_nSampleVal2, m_machineStat.m_nRefVal2, au, m_machineStat.m_nCurrentWave));
	}
}


double MachineStat::getAverageOfAu(double au, quint8 waveType)
{
#if 1  //张杰华屏蔽@2016-07-02
	double auAverage = au;
#else  
	//au值平滑处理;
	double auAverage = 0;
	int maxLen = AU_LIST_MAX;//单波长数据池;
	if(DataBase::getInstance()->queryData("chanel").toInt() == 1)//双波长数据池长度;
		maxLen = AU_LIST_MAX_DOUBLE;
	
	if(waveType == 0)//波1
	{
		QList<double>& list = auList;
		if( list.count() > maxLen && maxLen != 0 )
		{
			list.removeFirst();
			list<<au;

#if 1        //张杰华修改@2016-07-05

			for (int i = 0; i < maxLen; i++)
			{
				auAverage += list.at(i);
			}
			auAverage /= (double)maxLen;

#else
			
			QVector<double> auVector = list.toVector();

			qDebug() << "before order";
			for(int i = 0; i < maxLen; i++)
			{
				qDebug() << "auVector[" << i << "] = " << auVector[i];
			}

			for(int i = 0; i < maxLen-1; i++)
			{
				for(int j = i+1; j < maxLen; j++)
				{
					if(auVector[i] < auVector[j])
					{
						double temp = auVector[i];
						auVector[i] = auVector[j];
						auVector[j] = temp;
					}
				}
			}

			/*qDebug() << "after order";
			for(int i = 0; i < maxLen; i++)
			{
				qDebug() << "auVector[" << i << "] = " << auVector[i];
			}*/

			int average_cnt = 0;
			for(int i = maxLen/3; i < maxLen - maxLen/3; i++)
			{
				if(i <= maxLen/2)
				{
					auAverage += auVector[i]*(i - maxLen/3 + 1);
					average_cnt += (i - maxLen/3 + 1);
				}
				else
				{
					auAverage += auVector[i]*(maxLen - maxLen/3 - i);
					average_cnt += (maxLen - maxLen/3 - i);
				}
			}
			auAverage /= (maxLen - maxLen/3*2);
			auAverage /= average_cnt;

			qDebug() << "auAverage = " << auAverage;

#endif
		}
		else
		{
			list<<au;
			for (int i = 0; i < list.count(); i++)
			{
				auAverage += list.at(i);
			}
			auAverage /= (double)list.count();
		}

		////3阶滤波
		//static QList<double> auAverageFilter;
		//if(auAverageFilter.count() < 3)
		//	auAverageFilter<<auAverage;
		//else
		//{
		//	auAverage = (auAverageFilter.at(0) + 2*auAverageFilter.at(1) + 3*auAverageFilter.at(2) + 4*auAverage)/(1+2+3+4);
		//	auAverageFilter.removeFirst();
		//	auAverageFilter<<auAverage;
		//}
	}
	else//波2;
	{
		QList<double>& list = auList2;
		if( list.count() > maxLen && maxLen != 0 )
		{
			list.removeFirst();
			list<<au;

#if 1        //张杰华修改@2016-07-05

			for (int i = 0; i < maxLen; i++)
			{
				auAverage += list.at(i);
			}
			auAverage /= (double)maxLen;

#else

			QVector<double> auVector = list.toVector();
			for(int i = 0; i < maxLen-1; i++)
			{
				for(int j = i+1; j < maxLen; j++)
				{
					if(auVector[i] < auVector[j])
					{
						double temp = auVector[i];
						auVector[i] = auVector[j];
						auVector[j] = temp;
					}
				}
			}

			for(int i = maxLen/4; i < maxLen - maxLen/4; i++)
			{
				auAverage += auVector[i];
			}
			auAverage /= (maxLen - maxLen/2);
#endif

		}
		else
		{
			list<<au;
			for (int i = 0; i < list.count(); i++)
			{
				auAverage += list.at(i);
			}
			auAverage /= (double)list.count();
		}
	}
#endif
	
	//double auAverage = au;

	if(pDb->queryData("chanel").toInt() != 0)//双波长;
		AuAdjust::getInstance()->updateAuVal(waveType, auAverage);
	else if(waveType == 0)//单波长并且为波长1;
		AuAdjust::getInstance()->updateAuValSingle(auAverage);

	return auAverage;
}





void MachineStat::setCurrentWave(quint32 which)
{
		m_machineStat.m_nCurrentWave = which;//当前波长是波长1/2;
		//m_machineStat.m_nCurrentWave = 1;//当前波长是波长2;
}

void MachineStat::setWaveCtrlWord()
{
	setWaveCtrlWord(DataBase::getInstance()->queryData("wavelen1"), DataBase::getInstance()->queryData("wavelen2"));
}

void MachineStat::setWaveCtrlWord( QString wlen1, QString wlen2 )
{
	//delay_ms(100); //张杰华屏蔽@2016-06-28
	locateToWaveLen1(wlen1.toDouble(), 0);

	//quint8 chanel = DataBase::getInstance()->queryData("chanel").toInt();
	//if(chanel == 1)
	{
		//delay_ms(20); //张杰华修改@2016-06-28
		locateToWaveLen2(wlen2.toDouble());
	}

	//切换到定位波长状态;
	m_machineStat.machineStat = LOCATINGWAVE;
	mcuLocateWaveSuccess(false);//置位标志位，等待MCU定位波长成功;

	m_nReSendWlenChangeCnt = 0;//清重发计数器

	initAulist();
	initAulist(1);
}

void MachineStat::locateToWaveLen2(double wLen)
{
	wLen = compensationForWave(wLen);
	double tAngle = waveToAngle(wLen);//目标波长转换成角度;

	//qDebug()<<(tAngle/2/M_PI*360);
	int dir = 0;
	if(wLen > m_machineStat.m_dCurrentWlen)
		dir = 0;//逆时针;
	else
		dir = 0x10;//顺时针;
	//角度差;
	double delta = tAngle - m_machineStat.m_dCurrentAngle;
	//角度差转换成脉冲数;
	//delta = abs(delta);
	if(delta < 0)
		delta = m_machineStat.m_dCurrentAngle-tAngle;
	quint32 nStep = (delta/(2*M_PI))*PULSE_PER_ROUND;
	//顺时针逆时针??????
	quint8 chanel = DataBase::getInstance()->queryData("chanel").toInt();
	if(chanel == 0)
		nStep = 0;
	quint32 arg =( (dir|0x2&0xff)<<21 |(nStep&0x1fffff) );

	
	////张杰华修改@2016-06-29，改为发送绝对坐标
	//quint32 nStep = (tAngle/(2*M_PI))*PULSE_PER_ROUND;
	////顺时针逆时针??????
	//quint32 arg = (0x02<<21)|(nStep&0x1fffff);

	m_pCommunicationCoupling->sendMcuCmd(1,MCU_SETWAV_TO,arg);

	//m_machineStat.m_dCurrentWlen = wLen;
	//m_machineStat.m_dCurrentAngle = tAngle;
}

void MachineStat::resetWaveAndAngle()
{
	m_machineStat.m_dCurrentWlen = 0;//656.1;
	m_machineStat.m_dCurrentAngle = 0;//(27.2774/360.0)*2*M_PI;
}


double MachineStat::compensationForWave(double wave)
{
#if 0
	return wave;
#endif
	QList<LineUint> &waveCompensationList = pDb->getWaveCompensationList();
	int cnt = waveCompensationList.count();
	if( cnt > 0 )
	{
		//判断是否小于最小值;
		if( waveCompensationList.first().bOutOfStep(wave, LineUint::LEFT) )
		{
			wave = waveCompensationList.first().getValueByXAndK(wave, LineUint::LEFT);
		}
		//判断是否大于最大值;
		else if( waveCompensationList.last().bOutOfStep(wave, LineUint::RIGHT) )
		{
			wave = waveCompensationList.last().getValueByXAndK(wave, LineUint::RIGHT);
		}
		//判断是否处于某个区间;
		else
		{
			for (int i = 0; i<cnt; i++)
			{
				const LineUint &line = waveCompensationList.at(i);
				if(line.inRange(wave))
				{
					wave = line.getValueByXAndK(wave);//根据公式返回对应的流量值;
					return wave;
				}
			}
		}
	}
	
	return wave;
}

void MachineStat::setPercentOfRandS(quint32 waveType)
{
	//waveType = m_machineStat.m_nCurrentWave;

	//if(waveType == 0)//波长1
	//{
		initAulist();

		if(m_machineStat.m_nSampleVal == 0)
			return;

		if(m_machineStat.m_nRefVal == 0 )
			return;

		m_machineStat.m_dPercentOfRandS = (double)m_machineStat.m_nSampleVal/(double)m_machineStat.m_nRefVal;
		DataBase::getInstance()->updateDate("percentRofS", QString::number(m_machineStat.m_dPercentOfRandS));
	//}
	//else//波长2;
	//{
		initAulist(1);

		if(m_machineStat.m_nSampleVal2 == 0)
			return;

		if(m_machineStat.m_nRefVal2 == 0 )
			return;

		m_machineStat.m_dPercentOfRandS2 = (double)m_machineStat.m_nSampleVal2/(double)m_machineStat.m_nRefVal2;
		DataBase::getInstance()->updateDate("percentRofS2", QString::number(m_machineStat.m_dPercentOfRandS2));
	//}
}

void MachineStat::clearXeUsedTime()
{
	m_machineStat.m_nXeStartupTime = 0;
	saveUsedTime();
}

void MachineStat::clearTunUsedTime()
{
	m_machineStat.m_nTunStartupTime = 0;
	saveUsedTime();
}

qint32 MachineStat::uploadAuToPc()
{
//#ifdef WIN32
	if(m_machineStat.machineStat!= READY && m_machineStat.machineStat != LOCATINGWAVE) //张杰华修改@2016-06-24
		return -1;
//#endif

	quint32 pcProtocol = DataBase::getInstance()->queryData("pcProtocol").toInt();
	/*double au = 0.132081;
	double au = -0.080012;
	m_pCommunicationCoupling->sendCmdClarity(0, PFCC_SEND_AU, changeAuValtoClarity(au));
	return;*/

	//switch(m_machineStat.m_nUploadWhich)
	quint8 which = 0;
	switch(which)
	{
		//上传Au
		case 0:
		{
			double au = QString::number(m_machineStat.m_dAu1,'f', 8).toDouble();
			double au2 = QString::number(m_machineStat.m_dAu2,'f', 8).toDouble();
			int chanel = DataBase::getInstance()->queryData("chanel").toInt();
			double constVal = DataBase::getInstance()->getConstVal();
			if(chanel != 0)//双波长时候;
			{
				if( !AuAdjust::getInstance()->getdoubleAuVal(&au, &au2) )
				{
					//qDebug()<<"error.......................double wlen get au upload";
					return -1;
				}

				//4阶滤波
				if(auOutList.count() > FILTER_LIST_MAX)
					auOutList.removeFirst();
				auOutList << au;
				au = orderFilter(auOutList, auOutList.count());
				auOutList.removeLast();
				auOutList << au;

				//4阶滤波
				if(au2OutList.count() > FILTER_LIST_MAX)
					au2OutList.removeFirst();
				au2OutList << au2;
				au2 = orderFilter(au2OutList, au2OutList.count());
				au2OutList.removeLast();
				au2OutList << au2;

				//au = au*2/constVal;
				qint32 nUploadAu1Temp = ((au+2.0)/4.0*0xffffff); //张杰华修改@2016-06-15
				if(nUploadAu1Temp < 0)
					nUploadAu1Temp = 0;
				quint32 nUploadAu1 = nUploadAu1Temp;
				if(nUploadAu1 >= 0xffffff)
					nUploadAu1 = 0xffffff;

				//au2 = au2*2/constVal;
				qint32 nUploadAu2Temp = ((au2+2.0)/4.0*0xffffff); //张杰华修改@2016-06-15
				if(nUploadAu2Temp < 0)
					nUploadAu2Temp = 0;
				quint32 nUploadAu2 = nUploadAu2Temp;
				if(nUploadAu2 >= 0xffffff)
					nUploadAu2 = 0xffffff;

				if(pcProtocol == 0)
					m_pCommunicationCoupling->sendCmd(CMD_ASCII_DOUBLEWAV, nUploadAu1, nUploadAu2);
				else
				{
					m_pCommunicationCoupling->sendCmdClarity(0, PFCC_SEND_AU, changeAuValtoClarity(au));
					m_pCommunicationCoupling->sendCmdClarity(1, PFCC_SEND_AU, changeAuValtoClarity(au2));
				}
			}
			else//单波长时候;
			{
				if( !AuAdjust::getInstance()->getAuValSingle(&au) )
				{
					//qDebug()<<"error.......................single wlen get au upload";
					return -1;
				}
				//qDebug() << "au = "<< au;

				//4阶滤波
				if(auOutList.count() > FILTER_LIST_MAX)
					auOutList.removeFirst();
				auOutList << au;
				au = orderFilter(auOutList, auOutList.count());
				auOutList.removeLast();
				auOutList << au;

				//au = 1;
				//qDebug() << "au = " << au;
				//au = au*2/constVal;
				qint32 nUploadAu1Temp = ((au+2.0)/4.0*0xffffff); //张杰华修改@2016-06-15
				if(nUploadAu1Temp < 0)
					nUploadAu1Temp = 0;
				quint32 nUploadAu1 = nUploadAu1Temp;
				if(nUploadAu1 >= 0xffffff)
					nUploadAu1 = 0xffffff;

				if(pcProtocol == 0)
				{
					//nUploadAu1 = 0xffffff;
					//nUploadAu1 = 0;
					//qDebug() << "nUploadAu1 = " << nUploadAu1;

					m_pCommunicationCoupling->sendCmd(CMD_ASCII_SINGLEWAV, nUploadAu1, 0);
				}
				else
				{
					m_pCommunicationCoupling->sendCmdClarity(0, PFCC_SEND_AU, changeAuValtoClarity(au));
				}
			}			
		}
		break;
		//上传S值;
		case 1:
		{
			quint32 sVal = 0;
			if(m_machineStat.m_nCurrentWave == 0)//波1
				sVal = m_machineStat.m_nSampleVal;
			else//波2;
				sVal = m_machineStat.m_nSampleVal2;
			m_pCommunicationCoupling->sendCmd(CMD_ASCII_SVAL , sVal, 0);
		}
		break;
		//上传R值;
		case 2:
		{
			quint32 rVal = 0;
			if(m_machineStat.m_nCurrentWave == 0)//波1
				rVal = m_machineStat.m_nRefVal;
			else
				rVal = m_machineStat.m_nRefVal2;
			m_pCommunicationCoupling->sendCmd(CMD_ASCII_RVAL, rVal, 0);
		}
		break;
		default:
			break;
	}
	return 0;
}

quint32 MachineStat::changeAuValtoClarity( double au )
{
	quint32 ret = 0;
	if( au < 0 )
	{
		ret=((-au)*1000000);
		ret= 0xffffff-ret;
	}
	else
	{
		ret = 1000000*au;
	}
	return ret;
}

void MachineStat::updateSerialId( quint32 id )
{
	m_machineStat.m_nSerialId = id;
}



void MachineStat::initMotor()
{
	/*m_pCommunicationCoupling->sendMcuCmd(1,MCU_MOTOR_INI,0);
	return;*/

	if(m_machineStat.machineStat != READY && m_machineStat.machineStat != LOCATINGWAVE)
		return;

	m_bHomeInitSuccess = false;

	//delay_ms(100);
	m_pCommunicationCoupling->sendMcuCmd(1,MCU_MOTOR_INI_STOP,0);
	m_pCommunicationCoupling->sendMcuCmd(1,MCU_MOTOR_INI,0);
	IoModule::getInstance()->magnitOn(true);
	m_machineStat.machineStat = INITIALIZING;
}

void MachineStat::setWaveScanMode( bool on, double sWave /*= 0*/, double eWave /*= 0*/, quint32 time /*= 0*/ )
{
	static int chanel = DataBase::getInstance()->queryData("chanel").toInt();
	if(!on)//取消了扫描模式，则回复之前状态;
	{
		//清零与恢复命令模式;
		m_machineStat.machineMode = CMDMODE;		//命令模式;
		m_machineStat.scanmodePrevStep = 0;
		m_machineStat.machineStat = READY;			//就绪状态;

		//返回之前状态;
		DataBase::getInstance()->updateDate("chanel", QString::number(chanel));//恢复之前的波长通道;
		resetWaveAndAngle();
		setWaveCtrlWordAndHome();					//设置波长字并归原点;		

		deRegisterTimeoutFunc(&MachineStat::waveScanUpdate);
	}
	else//开启扫描模式;
	{
		//保存上一模式;
		chanel = DataBase::getInstance()->queryData("chanel").toInt();

		//切换到单波长;
		DataBase::getInstance()->updateDate("chanel", "0");
		resetWaveAndAngle();
		//setWlenStep(0,0, 1);//清空波长1控制字;
		//delay_ms(100);
		//setWlenStep(0,0, 2);//清空波长2控制字;

		//进入扫描模式;
		m_machineStat.machineMode = SCANMODE;
		m_machineStat.sWlen = sWave;//开始扫描波长;
		m_machineStat.eWlen = eWave;//结束扫描波长;

		m_machineStat.m_dPrevWlen = 0;
		m_machineStat.m_dScanOffset = 0;

		//如果目前正处于初始化怎么办??????????m_machineStat.machineState = INITIALIZING?????????

		//初始化;
		initMotor();

#if 0//上位机调试打印扫描间隔需要用到这段代码
		//quint32 nIntervalTime = DataBase::getInstance()->queryData("sTime").toInt();
		quint32 nIntervalTime = time;
		nIntervalTime*=1000;
		nIntervalTime/=TIMEOUT;
		registerTimeoutFunc(nIntervalTime,&MachineStat::waveScanUpdate);
#endif
	}
}

void MachineStat::waveScanUpdate()
{
#if 0//打印扫描间隔;
	static QTime eLapseTime = QTime::currentTime();
	qDebug()<<"scan..............................."<<eLapseTime.elapsed();
	eLapseTime.restart();
#endif	

	if(m_machineStat.eWlen >= m_machineStat.sWlen) 
	{
		if(m_machineStat.machineStat == READY || m_machineStat.machineStat == WAITRDY)// m_bHomeInitSuccess
		//if(m_machineStat.machineStat == LOCATINGWAVE && m_machineStat.m_bLocateWaveSuccess == false)
		{
			//stepToWave(m_machineStat.sWlen);
			changeWaveLength(m_machineStat.sWlen, MachineStat::EWLEN1);

			//emit(wLenChanged(QString::number(m_machineStat.sWlen), 0));
			m_machineStat.sWlen++;
		}
	}
	else//scan done...
	{
		QTimer::singleShot(100, this, SIGNAL(wLenScanDone()));//不能马山调用，否则waveScanUpdate函数返回前超时实体被注销掉;
	}
}

void MachineStat::stepToWave( double wLen )
{
	int dir = 0x00;//0x00逆时针;0x10顺时针;
	qDebug()<<"step to wave---------------:"<<wLen;

	//根据波长补偿表，补偿波长;
	double wLenCompen = compensationForWave(wLen);

	//小范围补偿;
	wLenCompen += m_machineStat.m_dScanOffset;
	if(qAbs(wLenCompen-m_machineStat.m_dPrevWlen) <= 3)
	{
		if(wLenCompen > m_machineStat.m_dPrevWlen)
		{
			wLenCompen+=MINI_COMPEN_VAL;
			m_machineStat.m_dScanOffset += MINI_COMPEN_VAL;
		}
		else
		{
			wLenCompen-=MINI_COMPEN_VAL;
			m_machineStat.m_dScanOffset -= MINI_COMPEN_VAL;
		}
	}
	m_machineStat.m_dPrevWlen = wLenCompen;

	double tAngle = waveToAngle(wLenCompen);						//目标波长转换成角度;
		
	double delta = qAbs( tAngle - m_machineStat.m_dCurrentAngle );	//求0度求角度差，m_machineStat.m_dCurrentAngle=0;
	
	quint32 nStep = (delta/(2*M_PI))*PULSE_PER_ROUND;				//角度差转步数;
	int deltaStep = nStep-m_machineStat.scanmodePrevStep;			//求扫描的前后步数差;
	if(deltaStep < 0)
		dir = 0x10;//逆时针;
	deltaStep = qAbs(deltaStep);									//取步数差的绝对值;

	quint32 arg =( (dir|0x6&0xff)<<21 |(deltaStep&0x1fffff) );		//发送给MCU;
	m_machineStat.scanmodePrevStep = nStep;
	m_pCommunicationCoupling->sendMcuCmd(1,MCU_STEP_TO,arg);
	
}


void MachineStat::setWlenStep( quint32 step, quint8 dir, quint8 which )
{
	quint32 arg =( (dir|which&0xff)<<21 |(step&0x1fffff) );
	m_pCommunicationCoupling->sendMcuCmd(1,MCU_SETWAV_TO,arg);
}


void MachineStat::motorInitSuccess()
{
	if( m_machineStat.machineStat == INITIALIZING )//如果正在初始化，则返回就绪状态;
	{
		emit(motorInitSuccessSignal());
		m_bHomeInitSuccess = true;
		if(DataBase::getInstance()->queryData("xe_tun").toInt() == 0)	//氘灯则释放电磁铁;
			IoModule::getInstance()->magnitOn(false);

		if(m_machineStat.machineMode == SCANMODE)
		{
			//stopMotorInit();
			waveScanUpdate();									//定位到第一个起始波长;
			m_machineStat.machineStat = WAITRDY;
		}
		else
			m_machineStat.machineStat = READY;
	}
}


void MachineStat::stopMotorInit()
{
	m_pCommunicationCoupling->sendMcuCmd(1,MCU_MOTOR_INI_STOP,0);
}


void MachineStat::setStepTo( quint32 step, quint8 dir )
{
	quint32 arg =( (dir|0x06&0xff)<<21 |(step&0x1fffff) );
	qDebug()<<"setStepTo---------------:"<<arg;
	m_pCommunicationCoupling->sendMcuCmd(1,MCU_STEP_TO,arg);
}


void MachineStat::uploadTimeToPc( MachineTime time, quint32 add )
{
	if(time == XEUSEDTIME)
	{
		quint32 time = DataBase::getInstance()->queryData("xeUsedTime").toInt();
		
		if(add == 0)//分钟
		{
			time /= 60;
		}
		else if(add == 1)//小时;
		{
			time /= 3600;
		}
		else
			time = 0;
		
		//张杰华修改@2016-06-18，兼容Clarity协议
		if(!DataBase::getInstance()->queryData("pcProtocol").toInt())
			m_pCommunicationCoupling->sendCmd(1, PFC_READ_LGTIME, time);
		else
			m_pCommunicationCoupling->sendCmdClarity(0, PFCC_READ_XEUSEDTIME, time);
	}
	else if(time == SYSTIME)
	{
		//quint32 time = DataBase::getInstance()->queryData("usedTime").toInt();
		quint32 time = getUsedTime();

		if(add == 0)//分钟
		{
			time /= 60;
		}
		else if(add == 1)//小时;
		{
			time /= 3600;
		}
		else
			time = 0;

		m_pCommunicationCoupling->sendCmd(1, PFC_READ_SYSTIME, time);
	}
}


void MachineStat::delay_ms(int msec)
{
	QTime n=QTime::currentTime();
	QTime now;
	do{
		now=QTime::currentTime();
	}   while (n.msecsTo(now)<=msec);
}


void MachineStat::mcuLocateWaveSuccess( bool bSuccess )
{
	m_machineStat.m_bLocateWaveSuccess = bSuccess;

	////张杰华添加@2016-07-07
	//if(m_machineStat.machineStat == LOCATINGWAVE)
	//	m_machineStat.machineStat = READY;
}

void MachineStat::sysError(int number, bool insert)
{
	if(warningList.indexOf(number) != -1 )
	{
		if(!insert)
			warningList.removeOne(number);
	}
	else
	{
		if(insert)
			warningList.append(number);
	}
	updateWarning();
}


void MachineStat::updateWarning()
{
	if(warningList.count() == 0)
		emit(systemError(0, tr("No Warn")));
	else
	{
		int warningId = warningList.at(0);
		switch(warningId)
		{
			case COMUNICATION_ERR:
				emit(systemError(warningId, tr("Com error!")));
				break;
			case LAMPINI_ERR:
				emit(systemError(warningId, tr("Lamp error!")));
				break;
			default:
				break;
		}
	}
}

void MachineStat::readSandRval()
{
	m_pCommunicationCoupling->sendMcuCmd(CMD_NORMAL, MCU_READ_AU_VAL_1, 0);
	delay_ms(10);
	m_pCommunicationCoupling->sendMcuCmd(CMD_NORMAL, MCU_READ_AU_VAL_2, 0);
}

int MachineStat::timeConstToAuListCnt()
{
	int auListLen[]={1,2,5,10,20,50,100};
	int timeConst = DataBase::getInstance()->queryData("timeconst").toInt();
	return auListLen[timeConst%7];
}

void MachineStat::initLamp()
{
	int whichLamp = DataBase::getInstance()->queryData("xe_tun").toInt();
	IoModule::getInstance()->initLamp(whichLamp);
}

void MachineStat::changeLampSrc( int src )
{
	DataBase::getInstance()->updateDate( "xe_tun", QString::number(src) );
	initLamp();
}

void MachineStat::setWlen( quint32 wlen, quint8 which )
{
	if(which == 0)
		DataBase::getInstance()->updateDate("wavelen1", QString::number(wlen));
	else
		DataBase::getInstance()->updateDate("wavelen2", QString::number(wlen));

	emit(wLenChanged(QString::number(wlen), which));
}

void MachineStat::updateTimeInte()
{
#if 1
	int whichLamp = DataBase::getInstance()->queryData("xe_tun").toInt();//灯源
	int timeInte = DataBase::getInstance()->queryData("timeInte").toInt();//时间积分;
	QList<int>timeInteList;
	timeInteList<<0x08<<0x04<<0x02<<0x01;
	if(timeInte > 3)
		return;
	quint32 arg = ((whichLamp&0xff)<<21)|((timeInteList.at(timeInte)&0xff)<<14);
	m_pCommunicationCoupling->sendMcuCmd(CMD_NORMAL, MCU_SET_PARAM, arg);
#endif
}

void MachineStat::setPcProtocol(int idx)
{
	m_pCommunicationCoupling->setPcProtocol(idx);
}

void MachineStat::setConnectPort(int idx)
{
	m_pCommunicationCoupling->setConnectPort(idx);
}

quint32 MachineStat::getMachineStat1()
{
	/*00XXXX：氘灯关状态
	01XXXX：氘灯开状态
	10XXXX：乌灯关状态
	11XXXX：乌灯开状态
	XXXX为当前检测器波长，190～700nm*/
	quint32 ret = 0;
	quint32 lampWhich = DataBase::getInstance()->queryData("xe_tun").toInt();//0氘灯、1钨灯;
	quint32 lampStat = getLampStat();//0开，1关;
	if(lampWhich == 0)
	{
		ret = 0x000000;
	}
	else
	{
		ret = 0x100000;
	}
	if(lampStat == 0)//开状态;
	{
		ret |= 0x10000;
	}
	
	quint32 wLen = DataBase::getInstance()->queryData("wavelen1").toInt();
	quint32 hWlen = DectoBCD(wLen, 4);
	ret|=hWlen;
	qDebug("%x",ret);
	return ret;
}

quint32 MachineStat::getMachineStat2()
{
	/*0XX0YY
	XX为时间常数（1，2，5，10，50，固定1位小数）
	YY输出范围0～17*/
	quint32 ret = 0;
	char buf[7] = {0x01, 0x02, 0x05, 0x10, 0x20, 0x50, 0x0};
	int timeIdx = DataBase::getInstance()->queryData("timeconst").toInt();
	int rangeIdx = DataBase::getInstance()->queryData("range").toInt();
	ret |= buf[timeIdx]<<12;
	ret |= DectoBCD(rangeIdx, 2);
	qDebug("%6x",ret);
	return ret;
}

void MachineStat::setUploadPcValChanel( int which )
{
	if(which >=0 && which <=2)
		m_machineStat.m_nUploadWhich = which;
}

#if 1
MachineStat::EStatException MachineStat::changeWaveLength(double wlen, MachineStat::EWLEN which)
{
	whichLen = which;

	//检查波长是否发生改变，如果没有，返回;
	if( !checkWaveLenChanged(wlen, which) )
		return EStat_Busy;

	//qDebug() << "11111";

	EStatException eStatException = EStat_Success;

	//if(m_machineStat.machineMode == SCANMODE)//扫描模式;
	//{
	//	eStatException = EStat_Busy;
	//	//qDebug() << "22222  SCANMODE";
	//}
	//else									 //自动模式;
	{
		if( m_machineStat.machineStat != READY )
		{
			eStatException = EStat_Busy;
			
			qDebug() << "m_machineStat.machineStat = " << m_machineStat.machineStat;
			qDebug() << "m_machineStat.m_bLocateWaveSuccess = " << m_machineStat.m_bLocateWaveSuccess;
			qDebug() << "===============================================================";
		}
		else//如果机器处于READY状态，代表机器已经归过原点;
		{
			//qDebug() << "44444";
			quint8 chanel = DataBase::getInstance()->queryData("chanel").toInt();

			////解决双波长不能同时相同的问题
			//if(chanel == 1)
			//{
			//	double otherWave = 0;
			//	if(which == EWLEN1)
			//		otherWave = DataBase::getInstance()->queryData("wavelen2").toDouble();
			//	else
			//		otherWave = DataBase::getInstance()->queryData("wavelen1").toDouble();

			//	if(otherWave == wlen)
			//		return EStat_Busy;
			//}


			emit(wLenChanged(QString::number(wlen), which));

			if(which == EWLEN1)
			{
				DataBase::getInstance()->updateDate("wavelen1", QString::number(wlen));
			}
			else
			{
				DataBase::getInstance()->updateDate("wavelen2", QString::number(wlen));
			}
			if(chanel == 0)// && which == EWLEN1
			{
				//MachineStat::getInstance()->resetWaveAndAngle();
				MachineStat::getInstance()->setWaveCtrlWord();
			}
			else
			{
				MachineStat::getInstance()->resetWaveAndAngle();
				//MachineStat::getInstance()->setWaveCtrlWordAndHome();
				MachineStat::getInstance()->setWaveCtrlWord();
			}
		}
	}

	//推后修改波长;
#if 0
	if(eStatException != EStat_Success)
	{
		m_dTempWlen = wlen;
		m_eWhich = which;
		emit(testSignal(m_dTempWlen));
		if(!m_pLatterTimer->isActive())
			m_pLatterTimer->start(800);
	}
#endif

	return eStatException;
}
#endif


//张杰华添加@2016-06-30
MachineStat::EStatException MachineStat::changeWaveLengthClarity(double wlen1, double wlen2)
{
	bool wlen1_change = false;
	bool wlen2_change = false;

	//检查波长是否发生改变，如果没有，返回;
	if( checkWaveLenChanged(wlen1, EWLEN1) )
		wlen1_change = true;
	if( checkWaveLenChanged(wlen2, EWLEN2) )
		wlen2_change = true;

	if(!wlen1_change && !wlen2_change)
		return EStat_Busy;

	//qDebug() << "11111";

	EStatException eStatException = EStat_Success;

	//if(m_machineStat.machineMode == SCANMODE)//扫描模式;
	//{
	//	eStatException = EStat_Busy;
	//	qDebug() << "22222   SCANMODE";
	//}
	//else									 //自动模式;
	{
		if( m_machineStat.machineStat != READY )
		{
			eStatException = EStat_Busy;

			qDebug() << "m_machineStat.machineStat = " << m_machineStat.machineStat;
			qDebug() << "============================================";
		}
		else//如果机器处于READY状态，代表机器已经归过原点;
		{
			qDebug() << "44444";
			quint8 chanel = DataBase::getInstance()->queryData("chanel").toInt();
			if(wlen1_change)
			{
				emit(wLenChanged(QString::number(wlen1), EWLEN1));
				DataBase::getInstance()->updateDate("wavelen1", QString::number(wlen1));
			}
			if(wlen2_change)
			{
				emit(wLenChanged(QString::number(wlen2), EWLEN2));
				DataBase::getInstance()->updateDate("wavelen2", QString::number(wlen2));
			}

			if(chanel == 0)
			{
				MachineStat::getInstance()->setWaveCtrlWord();
			}
			else
			{
				MachineStat::getInstance()->resetWaveAndAngle();
				MachineStat::getInstance()->setWaveCtrlWord();
			}
		}
	}

	return eStatException;
}


void MachineStat::initMACAddr()
{
	QString sMAC = DataBase::getInstance()->queryData("serial");
	if(sMAC.count() < 10)
		sMAC = QString("1234567890");

	sMAC = "ifconfig eth0 hw ether " + QString("AA") + sMAC;//第一个字节的第一位不能是1，1表示广播
	//qDebug() << "sMAC = " << sMAC;

#ifdef linux
	system(QString("ifconfig eth0 down").toLatin1().data());
	system(sMAC.toLatin1().data());   //张杰华删除@2016-06-15，调试用，到时要添加回来
	system(QString("ifconfig eth0 up").toLatin1().data());
#endif
}

void MachineStat::initIPAddr()
{
	QString strCig = QString("ifconfig eth0 %1.%2.%3.%4").arg(DataBase::getInstance()->queryData("ip1")).arg(DataBase::getInstance()->queryData("ip2")).arg(DataBase::getInstance()->queryData("ip3")).arg(DataBase::getInstance()->queryData("ip4"));
#ifdef linux
	system(strCig.toLatin1().data());   //张杰华删除@2016-06-15，调试用，到时要添加回来
#endif
}

void MachineStat::initAulist(quint8 wavetype)
{
	//初始化au队列，用于平均au值，平滑;
	if(wavetype == 0)
	{
		auList.clear();
		auOutList.clear();
		sampleValOutList.clear();
		refValOutList.clear();
		sampleValList.clear();
		refValList.clear();
	}
	else
	{
		auList2.clear();
		au2OutList.clear();
		sampleVal2OutList.clear();
		refVal2OutList.clear();
		sampleVal2List.clear();
		refVal2List.clear();
	}
}

void MachineStat::initStartupTime()
{
	/*m_startupTime = QTime::currentTime();*/
	m_nStartupTimeMsec = 0;
}

QString MachineStat::getStartupTime()
{
	quint32 sec = m_nStartupTimeMsec/20;

	int h = sec/3600;
	int m = sec/60%60;
	int s = sec%60;
	QString strHour = QString("%1:").arg(h).rightJustified(3, '0');
	QString strMin = QString("%1:").arg(m).rightJustified(3, '0');
	QString strSec = QString("%1").arg(s).rightJustified(2, '0');
	return strHour+strMin+strSec;
}

//17位序列号;
void MachineStat::serialNumberGenerate()
{
	if(DataBase::getInstance()->queryData("serial").toULongLong() == 0 )
	{
		QDateTime currentTime = QDateTime::currentDateTime();
		qsrand(currentTime.time().msec());
		int randNum = qrand()%999999;

		quint64 serialNum = currentTime.date().year()*pow(10.0, 13) + currentTime.date().month()*pow(10.0, 11) + currentTime.date().day()*pow(10.0, 9);
		serialNum += currentTime.time().hour()*pow(10.0, 7) + currentTime.time().minute()*pow(10.0, 5) + currentTime.time().second()*pow(10.0, 3);
		serialNum += randNum;

		serialNum %=SERIAL_MAX;
		serialNum ^= SERIAL_NUM_KEY;

		DataBase::getInstance()->updateDate("serial", QString::number(serialNum));
		qDebug()<<"............"<<serialNum;
	}
}

quint64 MachineStat::generateActiveCode( quint64 sertialNum, quint8 which )
{
	quint64 ret=0;
	quint64 date=m_machineStat.m_nSerialId;
	/*QDate today = QDate::currentDate();
	date=today.year()*10000;
	date+=today.month()*100;
	date+=today.day();*/
	if(which == 0)//永久激活;
	{
		ret = (sertialNum+date)%ACTIVE_CODE_MAX;
		ret ^=ACTIVE_MASK;
		ret %=ACTIVE_CODE_MAX;
	}
	else
	{
		ret = (sertialNum+date)%ACTIVE_CODE_MAX;
		ret ^=ACTIVE_MASK;
		ret %=ACTIVE_CODE_MAX;
		ret /=1000;
		ret *=1000;
		ret +=ACTIVE_CODE_TRY;
	}
	return ret;
}

quint32 MachineStat::getTryDayFromActiveCode( quint64 activeNum, quint32 serialId )
{
	quint32 tryday = activeNum%1000;
	serialId %=1000;
	tryday ^=serialId;
	tryday = 999-tryday;
	return tryday;
}

quint64 getActiveNum(quint64 sertialNum)
{
	quint64 serialNum = DataBase::getInstance()->queryData("serial").toULongLong();
	serialNum ^= SERIAL_NUM_KEY;
	return serialNum - SERIAL_NUM_VAL;
}


bool MachineStat::activeMachine(quint64 activeNum, bool bActive/* = true*/)
{
	bool ret = true;
	if( bActive )
	{
		quint64 serialNum = DataBase::getInstance()->queryData("serial").toULongLong();
		if( activeNum >= ACTIVE_CODE_TRY )//试用激活;
		{
			//判断是否相等;
			quint64 tActiveNum = generateActiveCode(serialNum, 1);
			quint64 temp = activeNum/1000*1000;
			if(tActiveNum == temp)
			{
				//获取天数;
				quint64 tryday = getTryDayFromActiveCode(activeNum, m_machineStat.m_nSerialId);
				//quint64 tryday = activeNum%1000;
				//清空序列号随机码;
				m_machineStat.m_nSerialId = 0;
				
				if(tryday == 0)//取消激活;
				{
					//清空试用日期;
					pDb->updateDate("tryDay", QString::number(0));
					clearUsedTime();
				}
				else
				{
					//累加试用日期;
					tryday+=pDb->queryData("tryDay").toUInt();
					pDb->updateDate("tryDay", QString::number(tryday));
					/*qDebug()<<pDb->queryData("tryDay");*/

				}
				DataBase::getInstance()->updateDate("bActive", "0");

			}
			else
				ret = false;
		}
		else//永久激活;
		{
			//判断是否相等;
			quint64 tActiveNum = generateActiveCode(serialNum, 0);
			if(tActiveNum == activeNum)
			{
				//记录激活标志;
				DataBase::getInstance()->updateDate("bActive", "1");
				//清空序列号随机码;
				m_machineStat.m_nSerialId = 0;

				//清空试用日期;
				pDb->updateDate("tryDay", QString::number(0));
				clearUsedTime();
			}
			else
				ret = false;
		}	
	}
	else
	{
		//取消激活标志;
		DataBase::getInstance()->updateDate("bActive", "0");
	}
	return ret;
}

void MachineStat::initStartup()
{
	m_machineStat.machineStat = READY;
	resetWaveAndAngle();				//复位波长计算参考值;
	setWaveCtrlWordAndHome();			//设置波长并归原点;
}

void MachineStat::delayAfterUpdateWave()
{
	if(m_machineStat.machineStat == LOCATINGWAVE)
		m_machineStat.machineStat = READY;
}

void MachineStat::clearWave1()
{

}

void MachineStat::clearWave2()
{

}

 void MachineStat::dealBulge()
{
#ifdef linux
	if( DataBase::getInstance()->queryData("pcProtocol").toInt() == 0 )
	{
		qDebug() << "----dealBulge()----";
		m_pCommunicationCoupling->sendCmd(CMD_SYNC_COLLECT,0,0);
	}
	else
	{
		m_pCommunicationCoupling->sendCmdClarity(0, PFCC_INPUT_EVENT, 0);
	}
#endif
}

 void MachineStat::changeWlenLater()
 {
	 changeWaveLength(m_dTempWlen, m_eWhich);
 }

 bool MachineStat::checkWaveLenChanged(double wlen, EWLEN which)
{
	QString wlenVar = QString("wavelen1");
	if(which == EWLEN2)
		wlenVar = QString("wavelen2");

	double oldWlen = DataBase::getInstance()->queryData(wlenVar).toDouble();

	return (oldWlen != wlen);
}

void MachineStat::chanelChanged(int ch)
{
	initAulist(0);
	initAulist(1);
	resetWaveAndAngle();
	//setWaveCtrlWordAndHome();
	setWaveCtrlWord();

	AuAdjust::getInstance()->clear();
}

void MachineStat::clearUsedTime()
{
	//m_machineStat.m_firstTryDateTime = QDateTime::currentDateTime().toTime_t();//记录当前日期时间;
	//pDb->updateDate("firstTryDateTime", QString::number(m_machineStat.m_firstTryDateTime));
	m_machineStat.m_nSysUsedTime = 0;
	QString temp = QString::number(m_machineStat.m_nSysUsedTime);
	pDb->updateDate("usedTime", temp);
}

uint MachineStat::getUsedTime()
{
#if 1
	QDateTime startTime = QDateTime::fromTime_t(m_machineStat.m_firstTryDateTime);
	QDateTime currentTime = QDateTime::currentDateTime();

	if(currentTime.toTime_t() > startTime.toTime_t())
		return (currentTime.toTime_t() - startTime.toTime_t() );
	else
		return 345600;
#endif

}




QString MachineStat::getUsedTimeStr()
{
	/*quint32 time = getUsedTime();
	QString str;
	QString str*/
	return "";
}

//定时上传;
struct timeval startTime,endTime;
int flag =0;
void uploadRoutine(int signo)
{
	
#ifdef linux
	if(signo == SIGALRM)
	{ 

		struct itimerval value, ovalue;
		value.it_value.tv_sec = 0;
		value.it_value.tv_usec = (0);
		value.it_interval.tv_sec = 0;
		value.it_interval.tv_usec = (0);
		setitimer(ITIMER_REAL, &value, &ovalue); 




		float elapse;
		gettimeofday(&endTime,NULL);

		//计算时间;
		elapse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);  
		elapse /= 1000;
		//printf("!!!!!!!!!elapse!!!!!!!!!!!!!!! = %f\n",elapse);  

		MachineStat::getInstance()->uploadAuToPc();
		//signal(SIGALRM, uploadRoutine);
		gettimeofday(&startTime,NULL);  

		value.it_value.tv_sec = 0;
		value.it_value.tv_usec = (UPLOAD_AU_INTERVAL_MS*1000*1);
		value.it_interval.tv_sec = 0;
		value.it_interval.tv_usec = (UPLOAD_AU_INTERVAL_MS*1000*1);
		setitimer(ITIMER_REAL, &value, &ovalue); 
		signal(SIGALRM, uploadRoutine);

		


	}



#endif
	
}


//linux定时功能;
void MachineStat::setupUploadTask()
{
#ifdef linux
	setUploadAuFreq(1);
#endif
}



void MachineStat::setUploadAuFreq( quint32 interval )
{
	m_nAuUploadTime = interval;
	m_nAuUploadTimeCnt = 0;

	//if(m_nTimerId !=0 )
	//	killTimer(m_nTimerId);

	////开启定时器;
	////m_nTimerId = startTimer(UPLOAD_AU_INTERVAL_MS*interval);
	//if(interval)
	//	m_nTimerId = startTimer(UPLOAD_AU_INTERVAL_MS);  //张杰华修改@2016-06-18，新协议，只在0和50ms之间选择
#if 0
#ifdef linux
	struct itimerval value, ovalue;

	signal(SIGALRM, uploadRoutine);

	value.it_value.tv_sec = 0;

	value.it_value.tv_usec = (UPLOAD_AU_INTERVAL_MS*1000*interval);

	value.it_interval.tv_sec = 0;

	value.it_interval.tv_usec = (UPLOAD_AU_INTERVAL_MS*1000*interval);

	setitimer(ITIMER_REAL, &value, &ovalue); 
#endif
#endif
}

void MachineStat::setNetWorkConfig(E_IPConfig eConfig)
{
    switch(eConfig)
    {
    case E_LOCALIP:
        {
            initIPAddr();
        }
        break;
    case E_LOCALPORT:
        {
            qDebug()<<"change port:"<<DataBase::getInstance()->queryData("port");

			quint32 connectPort = DataBase::getInstance()->queryData("connect_port").toUInt();
			if(connectPort == 1)//PC_COMMUNICATION_PORT_NET
			{
				m_pCommunicationCoupling->localPortChange();
			}
        }
        break;
    case E_REMOTEIP:
        {
            QString strCig = QString("%1.%2.%3.%4").arg(DataBase::getInstance()->queryData("remote_ip1")).arg(DataBase::getInstance()->queryData("remote_ip2")).arg(DataBase::getInstance()->queryData("remote_ip3")).arg(DataBase::getInstance()->queryData("remote_ip4"));
            qDebug()<<"!!!!!!!!!!!!!!!!remote ip change"<<"  "<<strCig;

			quint32 connectPort = DataBase::getInstance()->queryData("connect_port").toUInt();
			if(connectPort == 1)//PC_COMMUNICATION_PORT_NET
			{
				m_pCommunicationCoupling->remoteIPChange();
			}
        }
        break;
    case E_REMOTEPORT:
        {
            qDebug()<<"change remoteport:"<<DataBase::getInstance()->queryData("remote_port");

			quint32 connectPort = DataBase::getInstance()->queryData("connect_port").toUInt();
			if(connectPort == 1)//PC_COMMUNICATION_PORT_NET
			{
				m_pCommunicationCoupling->remotePortChange();
			}
        }
        break;
    }
}


quint32 MachineStat::getWeightedAverage(QVector<quint32> &myVector)
{
	quint32 average = 0;
	quint32 averageCnt = 0;
	quint32 len = myVector.count();
	quint32 startIndex = len/4;
	//quint32 startIndex = 0;

	//排序 降序
	for(int i = 0; i < len-1; i++)
	{
		for(int j = i+1; j < len; j++)
		{
			if(myVector[i] < myVector[j])
			{
				quint32 temp = myVector[i];
				myVector[i] = myVector[j];
				myVector[j] = temp;
			}
		}
	}

	//加权平均
	for(int i = startIndex; i < len - startIndex; i++)
	{
		if(i <= len/2)
		{
			average += myVector[i]*(i - startIndex + 1);
			averageCnt += (i - startIndex + 1);
		}
		else
		{
			average += myVector[i]*(len - startIndex - i);
			averageCnt += (len - startIndex - i);
		}
	}
	average /= averageCnt;

	return average;
}

double MachineStat::getWeightedAverage(QVector<double> &myVector)
{
	double average = 0;
	qint32 averageCnt = 0;
	quint32 len = myVector.count();
	quint32 startIndex = len/4;
	//quint32 startIndex = 0;

	//排序
	for(int i = 0; i < len-1; i++)
	{
		for(int j = i+1; j < len; j++)
		{
			if(myVector[i] < myVector[j])
			{
				double temp = myVector[i];
				myVector[i] = myVector[j];
				myVector[j] = temp;
			}
		}
	}

	//加权平均
	for(int i = startIndex; i < len - startIndex; i++)
	{
		if(i <= len/2)
		{
			average += myVector[i]*(i - startIndex + 1);
			averageCnt += (i - startIndex + 1);
		}
		else
		{
			average += myVector[i]*(len - startIndex - i);
			averageCnt += (len - startIndex - i);
		}
	}
	average /= averageCnt;

	return average;
}

quint32 MachineStat::getAverage(QList<quint32> &myList)
{
	quint32 average = 0;
	quint32 len = myList.count();
	for(int i=0;i<len;i++)
		average += myList.at(i);
	average /= len;
	return average;
}

quint32 MachineStat::orderFilter(QList<quint32> &myList, quint32 order)
{
	quint32 average = 0;
	quint32 averageCnt = 0;
	quint32 len = myList.count();
	for(int i=0;i<len;i++)
	{
		average += (myList.at(i) * (i + 1));
		averageCnt += (i + 1);
	}
	average /= averageCnt;
	return average;
}


double MachineStat::orderFilter(QList<double> &myList, quint32 order)
{
	double average = 0;
	quint32 averageCnt = 0;
	quint32 len = myList.count();
	for(int i=0;i<len;i++)
	{
		average += (myList.at(i) * (i + 1));
		averageCnt += (i + 1);
	}
	average /= averageCnt;
	return average;
}

MachineStat::MachineRunningStat MachineStat::getMachineState()
{
	return m_machineStat;
}
