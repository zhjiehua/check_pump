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


#define COMUNICATION_ERR 1//ͨѶ����
#define LAMPINI_ERR		 2//��Դ��ʼ��ʧ��






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
		SYSTIME,		//ϵͳ�ۼ�ʱ��,����������;
		STARTUPTIME,	//����ʱ��,��������;
		XEUSEDTIME,		//뮵��ۼ�����ʱ��,����������;
		TUNUSEDTIME,	//�ٵ��ۼ�����ʱ��,����������;
	};

	//״̬��: startup->ready->initializing->ready;
	enum MachineStatment
	{
		STARTUP = -1,	//��ʼ״̬,����ʱ���ڸ�״̬;
		WAITRDY = 0,	//�ȴ�����״̬;
		READY = 1,		//����״̬;
		LOCATINGWAVE,	//��λ������;
		INITIALIZING,	//��ʼ��״̬;
	};

	enum MachineMode
	{
		SCANMODE,
		CMDMODE,
	};

	enum LampStatment
	{
		ON = 0,//��;
		OFF,//�ر�;
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
		MachineMode machineMode;							//ɨ��ģʽ;
		quint32 scanmodePrevStep;					//ɨ��ģʽ�µ�
		double sWlen;								//��ʼ����;
		double eWlen;								//��������;
		quint32 m_nStartupTime;						//����ʱ��,�Զ�����;
		uint m_firstTryDateTime;					//��¼���õ��յ�����ʱ�䣬������;
		quint32 m_nSysUsedTime;						//ϵͳ�ۼ�ʱ��,����������;
		quint32 m_nXeStartupTime;					//뮵Ƶ�ʹ��ʱ��;
		quint32 m_nTunStartupTime;					//뮵Ƶ�ʹ��ʱ��;
		LampStatment lampStat;						//��״̬;
		quint32 m_nSampleVal;						//���µ�����ֵ(1);
		quint32 m_nRefVal;							//���µĲα�ֵ(1);
		quint32 m_nSampleVal2;						//���µ�����ֵ(2);
		quint32 m_nRefVal2;							//���µĲα�ֵ(2);
		double  m_dAu1;								//��Ӧ����1�����;
		double  m_dAu2;								//��Ӧ����2�����;
		quint32 m_nCurrentWave;						//��־���ĸ�������1/2��
		double m_dCurrentWlen;						//��ǰ����ֵ;
		double m_dCurrentAngle;						//��ǰ�Ƕ�;
		double m_dPercentOfRandS;					//K = R/S,��Ӧ����1;
		double m_dPercentOfRandS2;					//K = R/S,��Ӧ����2;
		quint8 m_nUploadWhich;						//Au, S, R;
		bool bTryDone;								//������ϱ�־;
		quint32 m_nSerialId;						//���кŵ����ID;

		double m_dPrevWlen;	
		double m_dScanOffset;						//ɨ��ƫ����,����;
		double saowLen1;                             //��λ��ɨ�貹��ʹ��

		quint32 m_nUploadInterval;					//�ϴ�auֵ���;


		bool m_bLocateWaveSuccess;					//��־MCU�Ѷ�λ������;

	};

	~MachineStat();
	static MachineStat *getInstance();
	void setPcProtocol(int idx);
	void setConnectPort(int idx);
	void delay_ms(int msec);															//��ʱ;
	void mcuLocateWaveSuccess(bool bSuccess);

	int checkProbation();																//���ʹ��ʣ��ʱ��;
	QString getStartupTime();															//��ȡ����ʱ��;
	quint32 getTime(MachineTime time);													//��ȡʱ��;
	void clearTime(MachineTime time);													//���ʱ��;
	bool activeMachine(quint64 activeNum, bool bActive = true);						//ͨ�������뼤�����״̬;	
	bool isTryDone(){return m_machineStat.bTryDone;}									//����Ƿ����������;
	//void activeMachine(int active){pDb->updateDate("bActive", QString::number(active)); }//�������״̬;
	void setWaveCtrlWord();																//���ò���������;
	void setWaveCtrlWord(QString wlen1, QString wlen2);								//���ò���������;
	void initMotor();																	//��ʼ�����,���»�ԭ��;
	void setPercentOfRandS(quint32 waveType = 0);
	
	MachineStatment getCurrentStat(){
		return m_machineStat.machineStat;
	}
	//��ȡ��ǰ����״̬;
	LampStatment getLampStat()
	{
		return m_machineStat.lampStat;
	}

	quint32 getSamleVal(){return m_machineStat.m_nSampleVal;}
	quint32 getRefVal(){return m_machineStat.m_nRefVal;}


	void setLampStat(LampStatment stat);	//���ÿ��ص�;

	/*00XXXX��뮵ƹ�״̬
	01XXXX��뮵ƹ�״̬
	10XXXX���ڵƹ�״̬
	11XXXX���ڵƹ�״̬
	XXXXΪ��ǰ�����������190��700nm*/
	quint32 getMachineStat1();				//��ȡ״̬1; 

	/*0XX0YY
	XXΪʱ�䳣����1��2��5��10��50���̶�1λС����
	YY�����Χ0��17*/
	quint32 getMachineStat2();				//��ȡ״̬2;
	

//��������!!!!!!!!!
	void setWlen(quint32 wlen, quint8 which);
	void resetWaveAndAngle();
	void setWaveCtrlWordAndHome();								//ԭ�㶨λ;
	void locateToWaveLen1(double wLen, quint8 which);			//��λdelta�Ƕȵ�ָ������1;
	void locateToWaveLen2(double wLen);							//��λdelta�Ƕȵ�ָ������1;
	inline double waveToAngle(double wave);						//����ת���ɽǶ�;
	void updateSampleVal(quint32 val);							//����sampleֵ;
	void updateRefVal(quint32 val);								//����referenceֵ;
	void setCurrentWave(quint32 which);							//�ֿظ�֪��ǰ�ǲ���1���ǲ���2��ֵ;
	double compensationForWave(double wave);
	void setWaveScanMode(bool on, double sWave = 0, double eWave = 0, quint32 time = 0);//����ɨ��ģʽ;
	void stepToWave(double wave);								//������ָ������;
	void setWlenStep(quint32 step, quint8 dir, quint8 which);							//���ò���1��2�Ĳ���������;
	void setStepTo(quint32 step, quint8 dir);					//���ò���1������ָ��λ��;
	void motorInitSuccess();									//�����ԭ��ɹ�;
	void stopMotorInit();										//ֹͣ��ʼ�����������ģʽ;
	double getAverageOfAu(double au, quint8 waveType = 0);							//ȡauƽ��ֵ;

	void updateTimeInte();
	void uploadTimeToPc(MachineTime time, quint32 add);		//����ʱ��ֵ����λ��;
	void sysError(int reSend, bool insert);					//���뱨��;
	uint getUsedTime();										//��ȡϵͳʹ��ʱ��;



	MachineStat::EStatException changeWaveLengthClarity(double wlen1, double wlen2);//�Žܻ����@2016-06-30

	MachineStat::EStatException changeWaveLength(double wlen, MachineStat::EWLEN which);			//�ı䲨��;
	void chanelChanged(int ch);//ͨ�������ı�;
	void initIPAddr();//��ʼ��ip��ַ;
	void initMACAddr();
    void setNetWorkConfig(MachineStat::E_IPConfig eConfig);//���ñ��غ�Զ��IP/PORT

	qint32 uploadAuToPc();									//����AUֵ����λ��;
	void updateSerialId(quint32 id);						//�������кŵ����ID;

	/*clarityЭ����;*/
	//�����ϴ�auֵƵ��
	void setUploadAuFreq(quint32 interval);

	void updateWarning();		//���±���;//��������@2016-06-18������˽�з�����Ϊ����

	//�Žܻ����@2016-07-04
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
	int whichPage;  //���������ȷ��������ҳ��

	bool noRTCBattery;

private:
	typedef struct tagTimeOutStruct
	{
		quint32 timeout;
		quint32 cnt;
		pTimeoutFunc timeoutFunc;
	}TimeOutStruct,*LPTimeOutStruct;


	MachineStat(QObject *parent = 0);
	quint32 m_nStartupTimeMsec;									//����ʱ��;
	QTime m_startupTime;										//����ʱ��;
	struct MachineRunningStat m_machineStat;				//����״̬;
	DataBase *pDb;
	CommunicationCoupling *m_pCommunicationCoupling;		//ͨѶ���ϲ�;
	QList<LPTimeOutStruct> m_timeoutList;					//��ʱ�����б�;
	QList<int>warningList;									//��������;
	QList<double>auList;									//au�б��Ӧ��1;
	QList<double>auList2;									//au�б��Ӧ��2;
	bool m_bHomeInitSuccess;								//ԭ���ʼ���ɹ���־		

	QList<double> auOutList;			//�˲����������ݳأ�3���˲���
	QList<double> au2OutList;

	QList<quint32> sampleValOutList;			//�˲����������ݳأ�3���˲���
	QList<quint32> sampleVal2OutList;
	QList<quint32> refValOutList;
	QList<quint32> refVal2OutList;

	QList<quint32> sampleValList;				//MCU�ϴ������ݵ����ݳأ�������ֵ��Ȩ�˲���
	QList<quint32> sampleVal2List;
	QList<quint32> refValList;
	QList<quint32> refVal2List;


	//�˺��޸Ĳ�����Ŀǰ�޸Ĳ���������æ״̬;
	double m_dTempWlen;
	EWLEN m_eWhich;
	QTimer *m_pLatterTimer;

	//��ʱ��;
	int m_nTimerId;
	QTime m_currentTime;

	quint32 m_nAuUploadTime;
	quint32 m_nAuUploadTimeCnt;

//methods:
//��ʼ��;
	void initDb();
	void initIO();
	void initTimer();
	void initMachineStat();
	void initLogicThread();									//��ʼ����̨ͨѶ�����߳�;
	void initTimeoutList();									//��ʼ����ʱ���б�;
	void initCommunication();								//ͨѶ��ʼ��;
	inline void initLamp();									//��Դ��ʼ��;
	void initAulist(quint8 wavetype = 0);										//������ʼ��;
//�ͷ�;
	void releaseTimeoutList();								//�ͷŶ�ʱ���б�;
//����״̬����;
	
//ʱ�����;
	void registerTimeoutFunc(const quint32 time, pTimeoutFunc pFunc);//ע�ᶨʱ����;
	void deRegisterTimeoutFunc(pTimeoutFunc pFunc);					//ע����ʱ����;
	void timerEvent(QTimerEvent *event);							//��ʱ�ϴ�;
	void auUploadTimeOut();									
	
	//������ִ��;
	void saveUsedTime();									//ʹ��ʱ���¼����;
	void saveDataBase(){pDb->saveDb();}						//�������ݿ�;
	void checkTryOut();										//����������Ƿ�ʱ;
	void updateStartupTime();								//��������ʱ��;
	
	void readSandRval();									//��ȡS��Rֵ;
	//void waveScanUpdate();									//ɨ��ģʽʱ����²���;
	//void updateWarning();									//���±���;
	int timeConstToAuListCnt();								//��ȡʱ�䳣������ȡaulist �����ֵ;

	//�����Լ����ʱ��;
	void initStartupTime();										//��ʼ������ʱ��;
	void setStartupTime(quint32 time);							//���ÿ���ʱ��;				
	inline void clearStartupTime();								//�������ʱ��;
	inline void clearUsedTime();								//���ϵͳ�ۼ�ʹ��ʱ��;
	inline void clearXeUsedTime();								//���뮵��ۼ�ʹ��ʱ��;
	inline void clearTunUsedTime();								//����ٵ��ۼ�����ʱ��;
	
	QString getUsedTimeStr();									//��ȡϵͳʹ��ʱ��;

	//Ȩ�����;
	void serialNumberGenerate();								//����������к�;
	quint64 generateActiveCode(quint64 sertialNum, quint8 which);					//���ɼ�����;
	quint32 getTryDayFromActiveCode(quint64 activeNum, quint32 serialId);		//���ݼ����������뷴����������;

	//��������;
	bool checkWaveLenChanged(double wlen, MachineStat::EWLEN which);	//�ж��趨�����������ò����Ƿ����;
		
	void setupUploadTask();										//��̨�ϴ�����׼��;

	//ת������;
	//clarity�µ�auֵת��;
	quint32 changeAuValtoClarity(double au);								

public slots:
	void changeLampSrc(int src);							//��Դ�л�;
	void setUploadPcValChanel(int which);					//�����ϴ�ͨ��;(Au, S, R)


private slots:
	void timeoutFunc();
	void lightIniSuccess(bool success);
	void waveScanUpdate();									//ɨ��ģʽʱ����²���;
	void initStartup();										//����ʱ���ʼ��;
	void delayAfterUpdateWave();							//���²������յ���һ��S/Rֵʱ����ʱ1s;

	void clearWave1();										//�岨��1
	void clearWave2();										//�岨��2

	void dealBulge();			//�����GPE0_4(XciYDATA1)״̬��0��1ʱ�������ϴ�����58 0D 7F��16���ƣ�ʹ��λ������Զ�����ɼ�ͼ��

	void changeWlenLater();

#if INIT_SUCCESS_SIMULATE
	void motorInitSuccessSimulate();
#endif

signals:
	void machineStatChanged(MachineStat::MachineStatment stat);		//����״̬�仯;
	void updateStartupTimeDisplay(quint32);							//��������ʱ����ʾ;	
	void changeLightStat(MachineStat::LampStatment stat);			//��Դ״̬;
	void updateAuValue(quint32 s, quint32 r, double au, quint8 which);//����AUֵ��;

	void wLenChanged(QString str, quint8 which);
	void wLenScanDone();											//ɨ�����;

	void systemError(int num, QString str);
	void motorInitSuccessSignal();									//�����ʼ���ɹ�;
	

	void sampleLow(bool);
	void referenceLow(bool);
	void lampState(quint8 state);

	void testSignal(double);
};

#endif // MACHINESTAT_H
