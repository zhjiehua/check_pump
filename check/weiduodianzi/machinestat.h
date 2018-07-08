#ifndef MACHINESTAT_H
#define MACHINESTAT_H

#include <QObject>
#include "database.h"
#include <QList>
#include <QVector>
#include <QTime>
#include <QTimerEvent>
#include "lineuint.h"
#include "communicationcoupling.h"
#include "iomodule.h"


#define COMUNICATION_ERR 1//通讯出错
#define LAMPINI_ERR		 2//灯源初始化失败






class MachineStat;
typedef void (MachineStat::*pTimeoutFunc)();

int DectoBCD(int Dec,int length);




#include <QMutex>
class MachineStat : public QObject
{
	Q_OBJECT

public:
	QMutex m_mutex;

	enum USRTYPE
	{
		ADMIN,
		USER,
		LAMP,
	};

	enum MachineTime
	{
		SYSTIME,		//系统累计时间,开机不清零;
		STARTUPTIME,	//开机时间,开机清零;
		XEUSEDTIME,		//氘灯累计运行时间,开机不清零;
		TUNUSEDTIME,	//钨灯累计运行时间,开机不清零;
	};

	//状态机: startup->ready->initializing->ready;
	enum MachineStatment
	{
		STARTUP = -1,	//初始状态,开机时候处于该状态;
		WAITRDY = 0,	//等待就绪状态;
		READY = 1,		//就绪状态;
		LOCATINGWAVE,	//定位波长中;
		INITIALIZING,	//初始化状态;
	};

	enum MachineMode
	{
		SCANMODE,
		CMDMODE,
	};

	enum LampStatment
	{
		ON = 0,//打开;
		OFF,//关闭;
	};

	enum EStatException
	{
		EStat_Busy,
		EStat_Success,
	};

	enum EWLEN
	{
		EWLEN1,
		EWLEN2,
	};


    enum E_IPConfig
    {
        E_LOCALIP,
        E_LOCALPORT,
        E_REMOTEIP,
        E_REMOTEPORT,
    };

	struct MachineRunningStat{
		MachineStatment machineStat;
		MachineStatment oldMachineStat;
		MachineMode machineMode;							//扫描模式;
		quint32 scanmodePrevStep;					//扫描模式下的
		double sWlen;								//开始波长;
		double eWlen;								//结束波长;
		quint32 m_nStartupTime;						//开机时间,自动清零;
		uint m_firstTryDateTime;					//记录试用当日的日期时间，不清零;
		quint32 m_nSysUsedTime;						//系统累计时间,开机不清零;
		quint32 m_nXeStartupTime;					//氘灯灯使用时间;
		quint32 m_nTunStartupTime;					//氘灯灯使用时间;
		LampStatment lampStat;						//灯状态;
		quint32 m_nSampleVal;						//最新的样本值(1);
		quint32 m_nRefVal;							//最新的参比值(1);
		quint32 m_nSampleVal2;						//最新的样本值(2);
		quint32 m_nRefVal2;							//最新的参比值(2);
		double  m_dAu1;								//对应波长1吸光度;
		double  m_dAu2;								//对应波长2吸光度;
		quint32 m_nCurrentWave;						//标志是哪个波长（1/2）
		double m_dCurrentWlen;						//当前波长值;
		double m_dCurrentAngle;						//当前角度;
		double m_dPercentOfRandS;					//K = R/S,对应波长1;
		double m_dPercentOfRandS2;					//K = R/S,对应波长2;
		quint8 m_nUploadWhich;						//Au, S, R;
		bool bTryDone;								//试用完毕标志;
		quint32 m_nSerialId;						//序列号的随机ID;

		double m_dPrevWlen;	
		double m_dScanOffset;						//扫描偏移量,叠加;
		double saowLen1;                             //上位机扫描补偿使用

		quint32 m_nUploadInterval;					//上传au值间隔;


		bool m_bLocateWaveSuccess;					//标志MCU已定位到波长;

	};

	~MachineStat();
	static MachineStat *getInstance();
	void setPcProtocol(int idx);
	void setConnectPort(int idx);
	void delay_ms(int msec);															//延时;
	void mcuLocateWaveSuccess(bool bSuccess);

	int checkProbation();																//检查使用剩余时间;
	QString getStartupTime();															//获取开机时间;
	quint32 getTime(MachineTime time);													//获取时间;
	void clearTime(MachineTime time);													//清除时间;
	bool activeMachine(quint64 activeNum, bool bActive = true);						//通过激活码激活机器状态;	
	bool isTryDone(){return m_machineStat.bTryDone;}									//检查是否过了试用期;
	//void activeMachine(int active){pDb->updateDate("bActive", QString::number(active)); }//激活机器状态;
	void setWaveCtrlWord();																//设置波长控制字;
	void setWaveCtrlWord(QString wlen1, QString wlen2);								//设置波长控制字;
	void initMotor();																	//初始化电机,重新回原点;
	void setPercentOfRandS(quint32 waveType = 0);
	
	MachineStatment getCurrentStat(){
		return m_machineStat.machineStat;
	}
	//获取当前机器状态;
	LampStatment getLampStat()
	{
		return m_machineStat.lampStat;
	}

	quint32 getSamleVal(){return m_machineStat.m_nSampleVal;}
	quint32 getRefVal(){return m_machineStat.m_nRefVal;}


	void setLampStat(LampStatment stat);	//设置开关灯;

	/*00XXXX：氘灯关状态
	01XXXX：氘灯关状态
	10XXXX：乌灯关状态
	11XXXX：乌灯关状态
	XXXX为当前检测器波长，190～700nm*/
	quint32 getMachineStat1();				//获取状态1; 

	/*0XX0YY
	XX为时间常数（1，2，5，10，50，固定1位小数）
	YY输出范围0～17*/
	quint32 getMachineStat2();				//获取状态2;
	

//波长操作!!!!!!!!!
	void setWlen(quint32 wlen, quint8 which);
	void resetWaveAndAngle();
	void setWaveCtrlWordAndHome();								//原点定位;
	void locateToWaveLen1(double wLen, quint8 which);			//定位delta角度到指定波长1;
	void locateToWaveLen2(double wLen);							//定位delta角度到指定波长1;
	inline double waveToAngle(double wave);						//波长转换成角度;
	void updateSampleVal(quint32 val);							//更新sample值;
	void updateRefVal(quint32 val);								//更新reference值;
	void setCurrentWave(quint32 which);							//分控告知当前是波长1还是波长2的值;
	double compensationForWave(double wave);
	void setWaveScanMode(bool on, double sWave = 0, double eWave = 0, quint32 time = 0);//设置扫描模式;
	void stepToWave(double wave);								//步进到指定波长;
	void setWlenStep(quint32 step, quint8 dir, quint8 which);							//设置波长1或2的步进控制字;
	void setStepTo(quint32 step, quint8 dir);					//设置波长1步进到指定位置;
	void motorInitSuccess();									//电机回原点成功;
	void stopMotorInit();										//停止初始化，进入待机模式;
	double getAverageOfAu(double au, quint8 waveType = 0);							//取au平均值;

	void updateTimeInte();
	void uploadTimeToPc(MachineTime time, quint32 add);		//更新时间值到上位机;
	void sysError(int reSend, bool insert);					//插入报警;
	uint getUsedTime();										//获取系统使用时间;



	MachineStat::EStatException changeWaveLengthClarity(double wlen1, double wlen2);//张杰华添加@2016-06-30

	MachineStat::EStatException changeWaveLength(double wlen, MachineStat::EWLEN which);			//改变波长;
	void chanelChanged(int ch);//通道发生改变;
	void initIPAddr();//初始化ip地址;
	void initMACAddr();
    void setNetWorkConfig(MachineStat::E_IPConfig eConfig);//配置本地和远程IP/PORT

	qint32 uploadAuToPc();									//更新AU值到上位机;
	void updateSerialId(quint32 id);						//更新序列号的随机ID;

	/*clarity协议下;*/
	//设置上传au值频率
	void setUploadAuFreq(quint32 interval);

	void updateWarning();		//更新报警;//吴杰能添加@2016-06-18，将该私有方法改为公有

	//张杰华添加@2016-07-04
	quint32 m_nReSendWlenChangeCnt;

	quint32 m_nReadAuCnt;
	quint32 m_nDouleWaveEqualReadAuCnt;

	bool m_bSetWaveAfterHome;

	bool m_bClaritySetFreq;

	EWLEN whichLen;
	quint32 getWeightedAverage(QVector<quint32> &myVector);
	double getWeightedAverage(QVector<double> &myVector);
	quint32 getAverage(QList<quint32> &myList);
	quint32 orderFilter(QList<quint32> &myList, quint32 order);
	double orderFilter(QList<double> &myList, quint32 order);


	MachineRunningStat getMachineState();

	bool pwdOK;
	bool pwdNeed;
	USRTYPE usrType;
	int whichPage;  //如果密码正确将跳到的页面

	bool noRTCBattery;

private:
	typedef struct tagTimeOutStruct
	{
		quint32 timeout;
		quint32 cnt;
		pTimeoutFunc timeoutFunc;
	}TimeOutStruct,*LPTimeOutStruct;


	MachineStat(QObject *parent = 0);
	quint32 m_nStartupTimeMsec;									//开机时间;
	QTime m_startupTime;										//开机时间;
	struct MachineRunningStat m_machineStat;				//机器状态;
	DataBase *pDb;
	CommunicationCoupling *m_pCommunicationCoupling;		//通讯胶合层;
	QList<LPTimeOutStruct> m_timeoutList;					//定时任务列表;
	QList<int>warningList;									//报警队列;
	QList<double>auList;									//au列表对应波1;
	QList<double>auList2;									//au列表对应波2;
	bool m_bHomeInitSuccess;								//原点初始化成功标志		

	QList<double> auOutList;			//滤波输出后的数据池，3阶滤波用
	QList<double> au2OutList;

	QList<quint32> sampleValOutList;			//滤波输出后的数据池，3阶滤波用
	QList<quint32> sampleVal2OutList;
	QList<quint32> refValOutList;
	QList<quint32> refVal2OutList;

	QList<quint32> sampleValList;				//MCU上传的数据的数据池，数据中值加权滤波用
	QList<quint32> sampleVal2List;
	QList<quint32> refValList;
	QList<quint32> refVal2List;


	//退后修改波长，目前修改波长正处于忙状态;
	double m_dTempWlen;
	EWLEN m_eWhich;
	QTimer *m_pLatterTimer;

	//定时器;
	int m_nTimerId;
	QTime m_currentTime;

	quint32 m_nAuUploadTime;
	quint32 m_nAuUploadTimeCnt;

//methods:
//初始化;
	void initDb();
	void initIO();
	void initTimer();
	void initMachineStat();
	void initLogicThread();									//初始化后台通讯处理线程;
	void initTimeoutList();									//初始化定时器列表;
	void initCommunication();								//通讯初始化;
	inline void initLamp();									//灯源初始化;
	void initAulist(quint8 wavetype = 0);										//参数初始化;
//释放;
	void releaseTimeoutList();								//释放定时器列表;
//机器状态控制;
	
//时间相关;
	void registerTimeoutFunc(const quint32 time, pTimeoutFunc pFunc);//注册定时函数;
	void deRegisterTimeoutFunc(pTimeoutFunc pFunc);					//注销定时函数;
	void timerEvent(QTimerEvent *event);							//定时上传;
	void auUploadTimeOut();									
	
	//周期性执行;
	void saveUsedTime();									//使用时间记录保存;
	void saveDataBase(){pDb->saveDb();}						//保存数据库;
	void checkTryOut();										//检查试用期是否超时;
	void updateStartupTime();								//更新启动时间;
	
	void readSandRval();									//读取S和R值;
	//void waveScanUpdate();									//扫描模式时候更新波长;
	//void updateWarning();									//更新报警;
	int timeConstToAuListCnt();								//读取时间常数，获取aulist 的最大值;

	//设置以及清除时间;
	void initStartupTime();										//初始化开机时间;
	void setStartupTime(quint32 time);							//设置开机时间;				
	inline void clearStartupTime();								//清除开机时间;
	inline void clearUsedTime();								//清除系统累计使用时间;
	inline void clearXeUsedTime();								//清除氘灯累计使用时间;
	inline void clearTunUsedTime();								//清除钨灯累计试用时间;
	
	QString getUsedTimeStr();									//获取系统使用时间;

	//权限相关;
	void serialNumberGenerate();								//随机生成序列号;
	quint64 generateActiveCode(quint64 sertialNum, quint8 which);					//生成激活码;
	quint32 getTryDayFromActiveCode(quint64 activeNum, quint32 serialId);		//根据激活码和随机码反推试用日期;

	//波长操作;
	bool checkWaveLenChanged(double wlen, MachineStat::EWLEN which);	//判断设定波长和已设置波长是否相等;
		
	void setupUploadTask();										//后台上传工作准备;

	//转换操作;
	//clarity下的au值转换;
	quint32 changeAuValtoClarity(double au);								

public slots:
	void changeLampSrc(int src);							//灯源切换;
	void setUploadPcValChanel(int which);					//设置上存通道;(Au, S, R)


private slots:
	void timeoutFunc();
	void lightIniSuccess(bool success);
	void waveScanUpdate();									//扫描模式时候更新波长;
	void initStartup();										//开机时候初始化;
	void delayAfterUpdateWave();							//更新波长后当收到第一个S/R值时候延时1s;

	void clearWave1();										//清波长1
	void clearWave2();										//清波长2

	void dealBulge();			//检测器GPE0_4(XciYDATA1)状态从0变1时，触发上传命令58 0D 7F（16进制）使上位机软件自动进入采集图谱

	void changeWlenLater();

#if INIT_SUCCESS_SIMULATE
	void motorInitSuccessSimulate();
#endif

signals:
	void machineStatChanged(MachineStat::MachineStatment stat);		//机器状态变化;
	void updateStartupTimeDisplay(quint32);							//更新运行时间显示;	
	void changeLightStat(MachineStat::LampStatment stat);			//灯源状态;
	void updateAuValue(quint32 s, quint32 r, double au, quint8 which);//更新AU值得;

	void wLenChanged(QString str, quint8 which);
	void wLenScanDone();											//扫描结束;

	void systemError(int num, QString str);
	void motorInitSuccessSignal();									//电机初始化成功;
	

	void sampleLow(bool);
	void referenceLow(bool);
	void lampState(quint8 state);

	void testSignal(double);
};

#endif // MACHINESTAT_H
