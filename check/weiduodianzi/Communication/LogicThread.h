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
#define CMD_SYNC_COLLECT	3//ʹ��λ������Զ�����ɼ�ͼ��;
#define CMD_ASCII_SVAL		4//�ϴ�Sֵ;
#define CMD_ASCII_RVAL		5//�ϴ�Rֵ;



#if 0
//����Ϊ����16�ֽ��������ݵ�����;
#define PFC_READ_PRODUCT_ID			0x01//��ȡ��ƷID;
#define PFC_READ_LICENSE_H			0x02//��ȡ���кŸ�λ;
#define PFC_READ_LICENSE_L			0x03//��ȡ���кŵ�λ;
#define PFC_READ_STATUS_1			0x04//��ȡ�����״̬1(��״̬�뵱ǰ����);
#define PFC_READ_STATUS_2			0x05//��ȡ�����״̬2��ʱ�䳣���������Χ);
#define PFC_READ_VERSION			0x06//��ȡ���������汾��;
#define PFC_READ_REF				0x07//��ȡref*;
#define PFC_READ_SIG				0x08//��ȡsig*;

//����Ϊ����ACK��NACK������;
#define PFC_WAVE_LENGTH				0x10//����;
#define PFC_TIME_CONST				0x11//ʱ�䳣��;
#define PFC_OUTPUT_EXTENT			0x12//�����Χ;
#define PFC_SYNC_TIME				0X13//�趨ͬ��ʱ��;
#define PFC_LIGHT_TURN_ON			0x14//����;
#define PFC_LIGHT_TURN_OFF			0x15//�ص�;
#define PFC_WAVE_LEN_INI			0x16//������ʼ��;
#define PFC_AUTO_RESET				0x17//�Զ���������;
#define PFC_SET_AU_FREQ				0x18//�趨Auֵ����Ƶ������;
#define PFC_SET_OUTPUT_EVENT		0x19//�趨����¼�;
#define PFC_LIGHT_SEL				0x20//뮵����ٵ�ѡ��;

//����Ϊ��λ���������͵�����;
#define PFC_READ_AU					0x90//��Auֵ����;
#define PFC_INPUT_EVENT				0x91//���������¼�;
#define PFC_SYS_ERR					0x92//����ϵͳ����;
#define PFC_STAT_CHANGE_1			0x93//�����������뵼�¼���������״̬�仯1(��״̬�뵱ǰ����);
#define PFC_STAT_CHANGE_2			0x94//�����������뵼�¼���������״̬�仯2(ʱ�䳣���������Χ);
#endif

#define PFCC_READ_PRODUCT_ID		0x01//��ȡ��ƷID;
#define PFCC_READ_LICENSE_H			0x02//��ȡ���кŸ�λ;
#define PFCC_READ_LICENSE_L			0x03//��ȡ���кŵ�λ;
#define PFCC_READ_STATUS1			0x04//��ȡ�����״̬1;
#define PFCC_READ_STATUS2			0x05//��ȡ�����״̬2;
#define PFCC_READ_SFVERSION			0x06//��ȡ����汾��;
#define PFCC_READ_REF				0x07//��ȡref*;
#define PFCC_READ_SIG				0x08//��ȡsig*;
#define PFCC_READ_WAVE				0x09//��ȡ�趨����;    //�Žܻ��޸�@2016-06-18����Э��

//����Ϊ����ACK��NACK������;
#define PFCC_SET_WAVE				0x10//�趨����;
#define PFCC_SET_TIMECST			0x11//�趨ʱ�䳣��;
#define PFCC_SET_OUTPUTRNG			0x12//�趨�����Χ;
#define PFCC_SET_SYNCTIME			0X13//�趨ͬ��ʱ��;
#define PFCC_SET_LIGHTON			0x14//����;
#define PFCC_SET_LIGHTOFF			0x15//�ص�;
#define PFCC_WAVE_INI				0x16//������ʼ��;
#define PFCC_AUTO_CLEAR				0x17//�Զ�����;
#define PFCC_SET_AUFREQ				0x18//�趨auֵ����Ƶ������
#define PFCC_SET_OUTPUTEV			0x19//��������¼�;
#define PFCC_SET_LIGHT				0x20//뮵����ٵƵ�ѡ��;

//�Žܻ����@2016-06-18����Э��
#define PFCC_READ_XEUSEDTIME		0x45//��ȡ뮵�ʱ��
#define PFCC_READ_CHECKSTAT			0x46//��ȡ���������״̬
#define PFCC_SET_GAIN				0x48//��������
#define PFCC_SET_INTEGTIME			0x49//���û���ʱ��

//����Ϊ��λ���������͵�����;
#define PFCC_SEND_AU				0x90//��Auֵ����;
#define PFCC_INPUT_EVENT			0x91//���������¼�;

//�Žܻ��޸�@2016-06-18����Э��
#define PFCC_CHECK_INFO				0x92//�������ͼ��������Ϣ;
#define PFCC_SYS_ERR				0x93//����ϵͳ����;
//#define PFCC_SYS_ERR				0x92//����ϵͳ����;
//#define PFCC_PANEL_CHANGE1			0x93//�����������뵼�¼����״̬�仯1;
//#define PFCC_PANEL_CHANGE2			0x94//�����������뵼�¼����״̬�仯2;




#define PFC_TURNON_LIGHT			0x03//����/�ص�; 
#define PFC_RESET_AU				0x04//A/Z��AU����; 
#define PFC_RESET_TIME				0x05//���ÿ�����ʱ;
#define PFC_SET_WLEN2				0x07//���ò���2; 
#define PFC_SET_WLEN1				0x08//���ò���; 
#define PFC_SET_TIMECONST			0x09//����ʱ�䳣��;
#define PFC_SET_RANGCONST			0x0A//��������;
#define PFC_MOTOR_INIT				0x0B//����ʼ��;
#define PFC_READ_LICENSE			0x0C//��ȡ���к�;
#define PFC_READ_LGTIME				0x0D//��ȡ�ƹ���ʱ��;
#define PFC_READ_LGLICENSE			0x0E//��ȡ�����к�;
#define PFC_READ_SYSTIME			0x0F//��ȡϵͳ����ʱ��;
#define PFC_READ_AU					0x0//��ȡAUֵ;
#define PFC_WAVEADD_MOTOR			0x01//�������ӷ���ת�����
#define PFC_WAVEDEL_MOTOR			0x02//�������ٷ���ת�����



/******************************MUCͨѶ����ʶ��**********************************/
#define MCU_SET_PARAM				0x01//���ò���;
#define MCU_MOTOR_INI				0x02//����ʼ��;//!!!!!!!!!!!!!!!!!!
#define MCU_MOTOR_INI_STOP			0x03//����ʼ��;//!!!!!!!!!!!!!!!!!!
#define MCU_SETWAV_TO				0x04//���ò���������;//!!!!!!!!!!!!!!!!!
#define MCU_STEP_TO					0x05//�����������ָ��;
#define MCU_READ_PARAM				0x09//��ȡ����;
//#define MCU_READ_VERSION			0x0a//��ȡ�ֿذ汾��;
#define MCU_READ_AU_VAL_1			0x0a//��ȡAUֵ;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!(����1)
#define MCU_READ_AU_VALB_1			0x0b//��ȡAUֵ;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define MCU_READ_AU_VAL_2			0x0c//��ȡAUֵ;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!(����2)
#define MCU_READ_AU_VALB_2			0x0d//��ȡAUֵ;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!



struct SendMcuData{
	mbyte type;
	uint32 cmd; 
	uint32 arg;
};



/*�����̨�߼�����;*/
class Worker : public QObject
{

	Q_OBJECT
public:
	Worker(QObject *parent = 0);
	~Worker();

	void startTimer();
	
	int getPcProtocol(){return m_nPcProtocol;};
	
    //! ������ؽӿ�;
    //! ��ȡPCͨѶ�˿�����(���ڻ�����);
    quint32 getConnectPortType(){return m_nConnectPort;}
    //! ��ȡԶ��IP;
    QString getRemoteIP(){return m_strRemoteIp;}
    //! ��ȡԶ�˶˿�;
    quint32 getRemotePort(){return m_nRemotePort;}

	//tcp
	QTcpServer *tcpSocketServer;				//�Žܻ����@2016-06-22����������ͨ��
	QTcpSocket *tcpSocketClientConnection;
	//void setupNetworkCommunication();
	//udp
	QUdpSocket *udpSocket;
	void setupMCUCommunication();
	void setupNetworkCommunication();
private:
	int m_nPcProtocol;							//��λ��ͨѶЭ��ѡ��(0 ��Э�飬 1��Э��);
	QThread m_workerThread;
	QTimer *m_pTimer;								//���ڶ�ʱ��ȡͨѶ���ݵĶ�ʱ��;
	quint32 m_nResendTimeout;						//�ط���ʱ;
	quint32 m_nResendCnt;							//�ط�����;
	QList< QList<quint32> >sendList4Mcu;			//�����б�;
	QList< QList<quint32> >sendList4Pc;				//�����б�;


    //! ��λ����ͨѶ�ӿ�(���ڡ�����);
    quint32 m_nConnectPort;

    //! �����������;
    quint32 m_nLocalPort;

    //! Զ���������;
    quint32 m_nRemotePort;
    QString m_strRemoteIp;


	void setupCommunication();						//����ͨѶ�������Ǵ��ڻ�������;
	void setupSerialCommunication();				//���ô���ͨѶ;
	void uploadAuToPc(quint8 chanel, quint32 au, quint32 au2);	//����auֵ����λ��;

	void syncPCtoCollect();//ʹ��λ������Զ�����ɼ�ͼ��
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
	void processCmd4Pc( mbyte type, uint32 cmd, uint32 arg, uint32 add);				//�Խ��յ������ݽ��д���;
	void processCmd4Clarity(mbyte hID, mbyte hAI, mbyte hPFC, uint32 nVal);		//�Խ��յ������ݽ��д�������ClarityЭ��;
	void processCmd4Mcu( mbyte type, uint32 cmd, uint32 arg, uint32 add);			//�Խ��յ������ݽ��д���;
	void check4Mcu(uint32 cmd);														//У��;

	//�Žܻ����@2016-06-22�����socketͨ��
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
