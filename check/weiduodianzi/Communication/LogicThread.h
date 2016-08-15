#ifndef LOGICTHREAD_H
#define LOGICTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>

#include "Protocol.h"

#ifdef WIN32
#include "Communication/win_qextserialport.h"
#elif linux
#include "Communication//posix_qextserialport.h"
#endif


#define CMD_ASCII_SINGLEWAV	0
#define CMD_NORMAL			1
#define CMD_ASCII_DOUBLEWAV	2
#define CMD_SYNC_COLLECT	3//使上位机软件自动进入采集图谱;
#define CMD_ASCII_SVAL		4//上传S值;
#define CMD_ASCII_RVAL		5//上传R值;



#if 0
//以下为返回16字节完整数据的命令;
#define PFC_READ_PRODUCT_ID			0x01//读取产品ID;
#define PFC_READ_LICENSE_H			0x02//读取序列号高位;
#define PFC_READ_LICENSE_L			0x03//读取序列号低位;
#define PFC_READ_STATUS_1			0x04//读取检测器状态1(灯状态与当前波长);
#define PFC_READ_STATUS_2			0x05//读取检测器状态2（时间常数与输出范围);
#define PFC_READ_VERSION			0x06//读取检测器软件版本号;
#define PFC_READ_REF				0x07//读取ref*;
#define PFC_READ_SIG				0x08//读取sig*;

//以下为返回ACK，NACK的命令;
#define PFC_WAVE_LENGTH				0x10//波长;
#define PFC_TIME_CONST				0x11//时间常数;
#define PFC_OUTPUT_EXTENT			0x12//输出范围;
#define PFC_SYNC_TIME				0X13//设定同步时间;
#define PFC_LIGHT_TURN_ON			0x14//开灯;
#define PFC_LIGHT_TURN_OFF			0x15//关灯;
#define PFC_WAVE_LEN_INI			0x16//波长初始化;
#define PFC_AUTO_RESET				0x17//自动清零命令;
#define PFC_SET_AU_FREQ				0x18//设定Au值发送频率命令;
#define PFC_SET_OUTPUT_EVENT		0x19//设定输出事件;
#define PFC_LIGHT_SEL				0x20//氘灯与钨灯选择;

//以下为下位机主动发送的命令;
#define PFC_READ_AU					0x90//读Au值命令;
#define PFC_INPUT_EVENT				0x91//发送输入事件;
#define PFC_SYS_ERR					0x92//发送系统故障;
#define PFC_STAT_CHANGE_1			0x93//仪器键盘输入导致检测器检测器状态变化1(灯状态与当前波长);
#define PFC_STAT_CHANGE_2			0x94//仪器键盘输入导致检测器检测器状态变化2(时间常数与输出范围);
#endif

#define PFCC_READ_PRODUCT_ID		0x01//读取产品ID;
#define PFCC_READ_LICENSE_H			0x02//读取序列号高位;
#define PFCC_READ_LICENSE_L			0x03//读取序列号低位;
#define PFCC_READ_STATUS1			0x04//读取检测器状态1;
#define PFCC_READ_STATUS2			0x05//读取检测器状态2;
#define PFCC_READ_SFVERSION			0x06//读取软件版本号;
#define PFCC_READ_REF				0x07//读取ref*;
#define PFCC_READ_SIG				0x08//读取sig*;
#define PFCC_READ_WAVE				0x09//读取设定波长;    //张杰华修改@2016-06-18，新协议

//以下为返回ACK，NACK的命令;
#define PFCC_SET_WAVE				0x10//设定波长;
#define PFCC_SET_TIMECST			0x11//设定时间常数;
#define PFCC_SET_OUTPUTRNG			0x12//设定输出范围;
#define PFCC_SET_SYNCTIME			0X13//设定同步时间;
#define PFCC_SET_LIGHTON			0x14//开灯;
#define PFCC_SET_LIGHTOFF			0x15//关灯;
#define PFCC_WAVE_INI				0x16//波长初始化;
#define PFCC_AUTO_CLEAR				0x17//自动清零;
#define PFCC_SET_AUFREQ				0x18//设定au值发送频率命令
#define PFCC_SET_OUTPUTEV			0x19//设置输出事件;
#define PFCC_SET_LIGHT				0x20//氘灯与钨灯的选择;

//张杰华添加@2016-06-18，新协议
#define PFCC_READ_XEUSEDTIME		0x45//读取氘灯时间
#define PFCC_READ_CHECKSTAT			0x46//读取检测器重新状态
#define PFCC_SET_GAIN				0x48//设置增益
#define PFCC_SET_INTEGTIME			0x49//设置积分时间

//以下为下位机主动发送的命令;
#define PFCC_SEND_AU				0x90//读Au值命令;
#define PFCC_INPUT_EVENT			0x91//发送输入事件;

//张杰华修改@2016-06-18，新协议
#define PFCC_CHECK_INFO				0x92//开机发送检测重启信息;
#define PFCC_SYS_ERR				0x93//发送系统故障;
//#define PFCC_SYS_ERR				0x92//发送系统故障;
//#define PFCC_PANEL_CHANGE1			0x93//仪器键盘输入导致检测器状态变化1;
//#define PFCC_PANEL_CHANGE2			0x94//仪器键盘输入导致检测器状态变化2;




#define PFC_TURNON_LIGHT			0x03//开灯/关灯; 
#define PFC_RESET_AU				0x04//A/Z键AU清零; 
#define PFC_RESET_TIME				0x05//重置开机计时;
#define PFC_SET_WLEN2				0x07//设置波长2; 
#define PFC_SET_WLEN1				0x08//设置波长; 
#define PFC_SET_TIMECONST			0x09//设置时间常数;
#define PFC_SET_RANGCONST			0x0A//设置量程;
#define PFC_MOTOR_INIT				0x0B//马达初始化;
#define PFC_READ_LICENSE			0x0C//读取序列号;
#define PFC_READ_LGTIME				0x0D//读取灯工作时间;
#define PFC_READ_LGLICENSE			0x0E//读取灯序列号;
#define PFC_READ_SYSTIME			0x0F//读取系统工作时间;
#define PFC_READ_AU					0x0//读取AU值;
#define PFC_WAVEADD_MOTOR			0x01//波长增加方向转动马达
#define PFC_WAVEDEL_MOTOR			0x02//波长减少方向转动马达



/******************************MUC通讯命令识别**********************************/
#define MCU_SET_PARAM				0x01//设置参数;
#define MCU_MOTOR_INI				0x02//马达初始化;//!!!!!!!!!!!!!!!!!!
#define MCU_MOTOR_INI_STOP			0x03//马达初始化;//!!!!!!!!!!!!!!!!!!
#define MCU_SETWAV_TO				0x04//设置波长控制字;//!!!!!!!!!!!!!!!!!
#define MCU_STEP_TO					0x05//步进电机步进指令;
#define MCU_READ_PARAM				0x09//读取参数;
//#define MCU_READ_VERSION			0x0a//读取分控版本号;
#define MCU_READ_AU_VAL_1			0x0a//读取AU值;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!(波长1)
#define MCU_READ_AU_VALB_1			0x0b//读取AU值;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define MCU_READ_AU_VAL_2			0x0c//读取AU值;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!(波长2)
#define MCU_READ_AU_VALB_2			0x0d//读取AU值;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!



struct SendMcuData{
	mbyte type;
	uint32 cmd; 
	uint32 arg;
};



/*负责后台逻辑处理;*/
class Worker : public QObject
{

	Q_OBJECT
public:
	Worker(QObject *parent = 0);
	~Worker();

	void startTimer();
	
	int getPcProtocol(){return m_nPcProtocol;};
	
    //! 网络相关接口;
    //! 获取PC通讯端口类型(串口或网口);
    quint32 getConnectPortType(){return m_nConnectPort;}
    //! 获取远端IP;
    QString getRemoteIP(){return m_strRemoteIp;}
    //! 获取远端端口;
    quint32 getRemotePort(){return m_nRemotePort;}

	//tcp
	QTcpServer *tcpSocketServer;				//张杰华添加@2016-06-22，设置网口通信
	QTcpSocket *tcpSocketClientConnection;
	//void setupNetworkCommunication();
	//udp
	QUdpSocket *udpSocket;
	void setupMCUCommunication();
	void setupNetworkCommunication();
private:
	int m_nPcProtocol;							//上位机通讯协议选择(0 旧协议， 1新协议);
	QThread m_workerThread;
	QTimer *m_pTimer;								//用于定时读取通讯数据的定时器;
	quint32 m_nResendTimeout;						//重发计时;
	quint32 m_nResendCnt;							//重发计数;
	QList< QList<quint32> >sendList4Mcu;			//发送列表;
	QList< QList<quint32> >sendList4Pc;				//发送列表;


    //! 上位机的通讯接口(串口、网口);
    quint32 m_nConnectPort;

    //! 本地网络参数;
    quint32 m_nLocalPort;

    //! 远程网络参数;
    quint32 m_nRemotePort;
    QString m_strRemoteIp;


	void setupCommunication();						//设置通讯，可以是串口或者网口;
	void setupSerialCommunication();				//设置串口通讯;
	void uploadAuToPc(quint8 chanel, quint32 au, quint32 au2);	//更新au值到上位机;

	void syncPCtoCollect();//使上位机软件自动进入采集图谱
signals:
	void process4Mcu( quint8 type, quint32 cmd, quint32 arg, quint32 add);
	void process4Pc( quint8 type, quint32 cmd, quint32 arg, quint32 add);
	void process4PcClarity( quint8 hID, quint32 hAI, quint32 hPFC, quint32 nVal);
	void communicationError(int reSend);

private slots:
	void CmdSend(quint8 type, quint32 cmd, quint32 arg);
	void CmdSendClarity(quint32 hAI, quint32 hPFC, quint32 hVal);
	void CmdSend4Mcu(quint8 type, quint32 cmd, quint32 arg);
	void sendAckClarity(quint8 ack);

public slots:
	void timeoutFunc();
	void processCmd4Pc( mbyte type, uint32 cmd, uint32 arg, uint32 add);				//对接收到的数据进行处理;
	void processCmd4Clarity(mbyte hID, mbyte hAI, mbyte hPFC, uint32 nVal);		//对接收到的数据进行处理，基于Clarity协议;
	void processCmd4Mcu( mbyte type, uint32 cmd, uint32 arg, uint32 add);			//对接收到的数据进行处理;
	void check4Mcu(uint32 cmd);														//校验;

	//张杰华添加@2016-06-22，添加socket通信
	//tcp
	void acceptConnection();
	void readClient();
	//udp
	void processPendingDatagrams();

	void l_setConnectPort(int nCon);
	void l_setPcProtocol(int nPro);
	void l_setRemoteIP();
	void l_setRemotePort();
	void l_setLocalIP();
	void l_setLocalPort();
};



#endif // LOGICTHREAD_H
