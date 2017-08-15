#include "LogicThread.h"
#include "Communication/Protocol.h"
#include <QString>
#include "baseMainPage.h"

#ifdef linux
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <asm-generic/ioctl.h>
#include <fcntl.h>

#include <stdint.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <unistd.h>

static int fd_spi = -1;
static const char *device = "/dev/spidev1.0";
static uint8_t mode;
static uint8_t bits = 16;
static uint32_t speed = 500000;
static uint16_t delay;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static int fd = -1;
static unsigned long temp_read = 0;
#endif


#define TIMEOUT_PERIOD 20  //�Žܻ��޸�@2016-07-04����100�ĳ�200


//#define LOCAL_PORT	8080  //���ض˿�
//#define REMOTE_PORT	8090  //Զ�̶˿�
//#define REMOTE_IPADDRESS  "192.168.19.254"	//Զ��IP

//#define COMMUNICATION_NETWORK//����ͨѶ;
#define COMMUNICATION_SERIAL//����ͨѶ;
#define COMMUNICATION_WITH_MCU//�Ƿ��ô��ں�MCUͨѶ;

#define SPICOM

//check
#ifdef WIN32
#define MAINCOMPORT		"COM2"//��λ��ͨѶ�ӿ�
#define MCUCOMPORT		"COM4"//��Ƭ��ͨѶ�ӿ�
#elif linux
#define MAINCOMPORT		"/dev/ttySAC2"//��λ��ͨѶ�ӿ�
#define MCUCOMPORT		"/dev/ttySAC1"//��Ƭ��ͨѶ�ӿ�
#endif


Worker *g_pWorker;


QHostAddress remoteAddrTemp;
quint16 remotePortTemp;

QHostAddress remoteAddr;
quint16 remotePort;

#ifdef WIN32
Win_QextSerialPort *myCom = 0;

Win_QextSerialPort *mcuCom = 0;//��װ�MCUͨѶ;

#elif linux
Posix_QextSerialPort *myCom = 0;

Posix_QextSerialPort *mcuCom = 0;//��װ�MCUͨѶ;

#endif


//ͨѶ׼��;
#define PC_COMMUNICATION_PORT_UART  0
#define PC_COMMUNICATION_PORT_NET   1
#define PC_COMMUNICATION_PORT_ANALOG   2



//int spiWrite();

int initSPIDevice()
{

	int ret = 0;
#ifdef linux

    fd_spi = open(device, O_RDWR);
    if (fd_spi < 0)
	{
		printf("can't open device");
		return -1;
	}

    /*
    * spi mode
    */
    ret = ioctl(fd_spi, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
	{
		printf("can't set spi mode");
		return -1;
	}

    ret = ioctl(fd_spi, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
	{
		printf("can't get spi mode");
		return -1;
	}

    /*
	* bits per word
	*/
    ret = ioctl(fd_spi, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
	{
		printf("can't set bits per word");
		return -1;
	}

    ret = ioctl(fd_spi, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
	{
		printf("can't get bits per word");
		return -1;
	}

    /*
    * max speed hz
    */
    ret = ioctl(fd_spi, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
	{
		printf("can't set max speed hz");
		return -1;
	}

    ret = ioctl(fd_spi, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
	{
		printf("can't get max speed hz");
		return -1;
	}

    printf("spi mode: %d\n", mode);
    printf("bits per word: %d\n", bits);
    printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

	//spiWrite();
#endif

	return 0;
}

int spiWrite(quint16* data, quint16 sz)
//int spiWrite()
{
	int ret = 0;

#ifdef linux

	uint16_t rx[1] = {0, };
	struct spi_ioc_transfer tr = {
		(unsigned long)data,
		(unsigned long)rx,
		2*sz,
		speed,
		delay,
		bits,
		0,
		0
	};
	ret = ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr);
	if (ret == 1)
		printf("can't send spi message");

	//printf("%.4X ", *data);

#endif

	return ret;

	//int ret;
	//uint16_t tx[] = {
	//	0xFF00, 0xFF01, 0xFF02, 0xFF03, 0xFF04, 0xFF05,
	//	0x4000, 0x1001, 0x1002, 0x1003, 0x1004, 0x9505,
	//	0xFF00, 0xFF01, 0xFF02, 0xFF03, 0xFF04, 0xFF05,
	//	0xFF00, 0xFF01, 0xFF02, 0xFF03, 0xFF04, 0xFF05,
	//	0xFF00, 0xFF01, 0xFF02, 0xFF03, 0xFF04, 0xFF05,
	//	0xDE00, 0xAD01, 0xBE02, 0xEF03, 0xBA04, 0xAD05,
	//	0xF006, 0x1D07,
	//};
	//uint16_t rx[ARRAY_SIZE(tx)] = {0, };
	//struct spi_ioc_transfer tr = {
	//	(unsigned long)tx,
	//	(unsigned long)rx,
	//	2*ARRAY_SIZE(tx),
	//	speed,
	//	delay,
	//	bits,
	//	0,
	//	0

	//	//__u64 tx_buf; /* д���ݻ��� */
	//	//__u64 rx_buf; /* �����ݻ��� */
	//	//__u32 len; /* ����ĳ��� */
	//	//__u32 speed_hz; /* ͨ�ŵ�ʱ��Ƶ�� */
	//	//__u16 delay_usecs; /* ����spi_ioc_transfer֮�����ʱ */
	//	//__u8 bits_per_word; /* �ֳ����������� */
	//	//__u8 cs_change; /* �Ƿ�ı�Ƭѡ */
	//	//__u32 pad; 

	//};

	//ret = ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr);
	//if (ret == 1)
	//	printf("can't send spi message");

	//for (ret = 0; ret < ARRAY_SIZE(tx); ret++) {
	//	if (!(ret % 6))
	//		puts("");
	//	printf("%.2X ", rx[ret]);
	//}
	//puts("");

	//return 0;
}


qint16 writeFunc( quint8* data, uint16 sz )
{
    qint16 ret = -1;
	quint32 type = g_pWorker->getConnectPortType();
    if( type == PC_COMMUNICATION_PORT_UART)
    {
        if(myCom)
        {
            ret = myCom->write((const char*)data, sz);//�Žܻ��޸�@2016-06-23
			//qDebug() << "myCom->write()";
        }
    }
    else if(type == PC_COMMUNICATION_PORT_NET)
    {
        //QByteArray data;  
        //data.append(text.toUtf8());
        if(g_pWorker->udpSocket)
		{
			ret = g_pWorker->udpSocket->writeDatagram((const char*)data, sz, QHostAddress(g_pWorker->getRemoteIP()), g_pWorker->getRemotePort());
			//if(g_pWorker->getPcProtocol() == 0)
			//{
			//	ret = g_pWorker->udpSocket->writeDatagram((const char*)data, sz, QHostAddress(g_pWorker->getRemoteIP()), g_pWorker->getRemotePort());
			//}
			//else
			//{
			//	ret = g_pWorker->udpSocket->writeDatagram((const char*)data, sz, remoteAddr, remotePort);
			//}
		}

		//qDebug() << "g_pWorker->getRemoteIP() = " << QHostAddress(g_pWorker->getRemoteIP());
		//qDebug() << "g_pWorker->getRemotePort() = " << g_pWorker->getRemotePort();

		//qDebug() << "writeDatagram:";
		//for(int i=0;i<sz;i++)
		//{
		//	qDebug() << data[i];
		//}
		//qDebug() << "end";
    }

    return ret;
}

void processFunc( mbyte type, uint32 cmd, uint32 arg, quint32 add)
{
	g_pWorker->processCmd4Pc( type, cmd, arg, add);
}


void processFunc4Clarity(  mbyte hID, mbyte hAI, mbyte hPFC, uint32 nVal )
{
	g_pWorker->processCmd4Clarity( hID, hAI, hPFC, nVal);
}


//*****************MCUͨѶ********************************/
qint16 writeFunc4Mcu( quint8* data, uint16 sz )
{
	qint16 ret = -1;

	if(mcuCom)
		ret = mcuCom->write((const char*)data, sz);

#if 0

	qDebug()<<"mcu port send:"<<sz<<"=========";
	QString temp;
	for(int i = 0; i < sz; i++)
	{
		quint8 d = (quint8)(data[i]);
		temp += QString::number(data[i],16).right(2)+"-";
	}
	qDebug()<<temp;

#endif

	return ret;
}

void processFunc4Mcu( mbyte type, uint32 cmd, uint32 arg, quint32 add )
{
	g_pWorker->processCmd4Mcu( type, cmd, arg, add);
}

void checkFunc4Mcu(uint32 cmd)
{
	g_pWorker->check4Mcu(cmd);
}



/*************************************************Worker*********************************************************/

Worker::Worker(QObject *parent /*= 0*/)
{
	udpSocket = NULL;
	setupCommunication();
	m_pTimer = new QTimer(this);
	QObject::connect(m_pTimer, SIGNAL(timeout()), this, SLOT(timeoutFunc()) );//��ʱ��ȡ����;
	startTimer();
	moveToThread(&m_workerThread);
	g_pWorker = this;
	m_nResendTimeout = 0;
	m_nResendCnt = 0;
	m_workerThread.start();
}



Worker::~Worker()
{
	
}



void Worker::timeoutFunc()
{
	static bool errorFlag = false;

#if 1
	if(sendList4Mcu.count() > 0)
	{
		if(++m_nResendTimeout >3)
		{
			m_nResendTimeout = 0;
			QList<quint32>list = sendList4Mcu.at(0);
			API_McuCmdSend(list.at(0), list.at(1),list.at(2));

			//qDebug() << "timeout! " << list;

			m_nResendCnt++;
			if(m_nResendCnt > 5)
			{
				errorFlag = true;
				emit(communicationError(1));
			}
			
		}
	}
	else
	{
		m_nResendTimeout = 0;
		m_nResendCnt = 0;
		if(errorFlag)
		{
			errorFlag = false;
			emit(communicationError(0));
		}
	}
#endif

	QByteArray data;
	QByteArray data2;


	if(myCom)
		data  = myCom->readAll();


	if(mcuCom)
		data2 = mcuCom->readAll();




#if 0

	qDebug()<<"recv:"<<data.size();
	QString temp;
	for(int i = 0; i < data.size(); i++)
		temp+=QString(" %1").arg( (quint8)data.at(i) );
	qDebug()<<temp;

#endif

#if 0

	if(data2.size())
	{
		qDebug()<<"mcu port recv:"<<data2.size();
		QString temp;
		for(int i = 0; i < data2.size(); i++)
		{
			quint8 d = (quint8)(data2.at(i));
			//temp+=QString(" %1").arg(d);
			temp += QString::number(data2.at(i),16).right(2)+"-";
		}
		qDebug()<<temp;
	}

#endif

	//����Э��;
	if(data.size() > 0)
	{
		if(m_nPcProtocol == 0)
			API_Protocol((mbyte *)data.data(), data.size());				//������Э��;
		else
			API_ClarityProtocol((mbyte *)data.data(), data.size());		//�����µ�Э��;
	}

	if(data2.size() > 0)
		API_McuProtocol((mbyte *)data2.data(), data2.size());//MCUЭ�����;


}



void Worker::processCmd4Pc( mbyte type, uint32 cmd, uint32 arg, uint32 add)
{
	emit(process4Pc(type, cmd, arg, add));
}




void Worker::processCmd4Clarity(mbyte hID, mbyte hAI, mbyte hPFC, uint32 nVal)
{
	emit( process4PcClarity(hID, hAI, hPFC, nVal) );
}



void Worker::processCmd4Mcu(mbyte type, uint32 cmd, uint32 arg,uint32 add)
{
	emit(process4Mcu( type, cmd, arg, add));
}


void Worker::CmdSend(quint8 type, quint32 cmd, quint32 arg)
{
	if(m_nPcProtocol == 0)//��Э��;
	{
		if(type == CMD_ASCII_SINGLEWAV || type == CMD_ASCII_SVAL || type == CMD_ASCII_RVAL)
			uploadAuToPc(0, cmd, arg);
		else if(type == CMD_ASCII_DOUBLEWAV)
			uploadAuToPc(1, cmd, arg);
		else if(type == CMD_SYNC_COLLECT)//ʹ��λ������Զ�����ɼ�ͼ��
			syncPCtoCollect();
		else
			API_CmdSend(type, cmd, arg);
	}
	else
	{
		if(type == CMD_ASCII_SINGLEWAV || CMD_ASCII_DOUBLEWAV) //??????����õ���
			CmdSendClarity(0, PFCC_SEND_AU, cmd);	
	}
	
}



void Worker::CmdSendClarity(quint32 hAI, quint32 hPFC, quint32 hVal)
{
	API_CmdSendClarity(hAI, hPFC, hVal);
}



//���뷢�Ͷ���;
void Worker::CmdSend4Mcu(quint8 type, quint32 cmd, quint32 arg)
{
	QList<quint32>list;
	list.append(type);
	list.append(cmd);
	list.append(arg);

	if(sendList4Mcu.count() == 0)//�Žܻ��޸�@2016-07-04��һ֡���ݷ�����ɲ��ܷ�����һ֡
		API_McuCmdSend(list.at(0), list.at(1),list.at(2));
	//else if(cmd == 0x0a)
	//{
	//	sendList4Mcu.append(list);
	//}

	if(cmd != 0x0a)
	{
		//qDebug()<<"------------";
		//qDebug()<<list;
		sendList4Mcu.append(list);
	}
}


void Worker::check4Mcu( uint32 cmd )
{
	//qDebug()<<QThread::currentThread();
	//qDebug()<<sendList4Mcu.count();
	
	if(sendList4Mcu.count() > 0)
	{
		/*for (int i = 0; i < sendList4Mcu.count(); i++)
		{
			qDebug()<<"!!!!!!before!!!!!!!!";
			qDebug()<<sendList4Mcu.at(i);
			qDebug()<<"!!!!!!!!!!!!!!!!";
		}*/
		
		//qDebug()<< "check4Mcu() " << sendList4Mcu.at(0).at(1) << sendList4Mcu.at(0).at(2);
		
		if((cmd&0x0f) == sendList4Mcu.at(0).at(1))
		{
			//qDebug()<< "removeAt() = " << sendList4Mcu.at(0).at(1) << sendList4Mcu.at(0).at(2);
			sendList4Mcu.removeAt(0);

			//�Žܻ��޸�@2016-07-07����ʱ��Ӧ�����־
			m_nResendTimeout = 0;
			m_nResendCnt = 0;

			if(sendList4Mcu.count() > 0) //������յ��ظ��������·���һ��ָ��
				API_McuCmdSend(sendList4Mcu.at(0).at(0), sendList4Mcu.at(0).at(1),sendList4Mcu.at(0).at(2));
		}

		/*for (int i = 0; i < sendList4Mcu.count(); i++)
		{
		qDebug()<<"!!!!!!after!!!!!!!!";
		qDebug()<<sendList4Mcu.at(i);
		qDebug()<<"!!!!!!!!!!!!!!!!";
		}*/
	}
}

//ͨѶ׼��;
void Worker::setupCommunication()
{
	m_nConnectPort = DataBase::getInstance()->queryData("connect_port").toUInt();
    //! �ж�ʹ�ô��ڻ������ں�PCͨѶ;
    if( m_nConnectPort == PC_COMMUNICATION_PORT_UART )
        setupSerialCommunication();
    else if(m_nConnectPort == PC_COMMUNICATION_PORT_NET)
        setupNetworkCommunication();//�Žܻ����@2016-06-23
	else
		initSPIDevice();

	setupMCUCommunication();

	//ע��ͨѶ����;
	ProtocolConf proConf;
	proConf.write = writeFunc;								//ʵ�ִ˺���!!!!!!!!!!!!!!!!!!!!!;
	proConf.process = processFunc;							//ʵ�ִ˺���!!!!!!!!!!!!!!!!!���������;
	proConf.processClarity = processFunc4Clarity;			//������Э��������ݴ���;
	SetProtocolConf( &proConf, PROTOCOL_CONF_WRITEFUN|PROTOCOL_CONF_PROCESSFUN|PROTOCOL_CONF_PROCESSFUNCLARITY);


	//ע��MCUͨѶ����;
	Protocol4McuConf mcuProConf;
	mcuProConf.write = writeFunc4Mcu;
	mcuProConf.process = processFunc4Mcu;
	mcuProConf.checkCompare = checkFunc4Mcu;
	SetMcuProtocolConf(&mcuProConf, PROTOCOL_CONF_PROCESSFUN|PROTOCOL_CONF_WRITEFUN|PROTOCOL_CONF_CHECKFUN);


}

//�Žܻ����@2016-06-22�����socketͨ��
void Worker::acceptConnection()
{
	tcpSocketClientConnection = tcpSocketServer->nextPendingConnection();
	connect(tcpSocketClientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void Worker::readClient()
{
	QString str = tcpSocketClientConnection->readAll();
	//����
	char buf[1024];
	tcpSocketClientConnection->read(buf,1024);
}


void Worker::processPendingDatagrams()  
{   

	while(udpSocket -> hasPendingDatagrams())  
	{   
		QByteArray datagram;  
		datagram.resize(udpSocket->pendingDatagramSize());   
		udpSocket->readDatagram(datagram.data(), datagram.size(), &remoteAddrTemp, &remotePortTemp);   
		//QString messages = QString::fromUtf8(datagram); 

		//qDebug() << "remoteAddr = " << remoteAddrTemp;
		//qDebug() << "remotePort = " << remotePortTemp;

		if(m_nPcProtocol == 0)
			API_Protocol((mbyte *)datagram.data(), datagram.size());			//������Э��;
		else
			API_ClarityProtocol((mbyte *)datagram.data(), datagram.size());		//�����µ�Э��;
		
		qDebug() << "API_ClarityProtocol:" << datagram.data();
		//qDebug() << "peerIP:" <<  udpSocket->peerAddress();
		//qDebug() << "peerPORT:" << udpSocket->peerPort();
		//qDebug() << "loaclIP:" <<  udpSocket->localAddress();
		//qDebug() << "localPORT:" << udpSocket->localPort();
	}
} 

//�Žܻ����@2016-06-22�����socketͨ��
void Worker::setupNetworkCommunication()
{

    //! ��ȡ�������;
    //! ���ض˿ں�;
    m_nLocalPort = DataBase::getInstance()->queryData("port").toUInt();
    //! Զ�̶˿ں�IP;
    m_nRemotePort = DataBase::getInstance()->queryData("remote_port").toUInt();
    m_strRemoteIp =  QString("%1.%2.%3.%4").arg(DataBase::getInstance()->queryData("remote_ip1")).arg(DataBase::getInstance()->queryData("remote_ip2")).arg(DataBase::getInstance()->queryData("remote_ip3")).arg(DataBase::getInstance()->queryData("remote_ip4"));

	//tcpSocketServer = new QTcpServer();
	//tcpSocketServer->listen(QHostAddress::Any, 6665);
	//connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

	if(udpSocket != NULL)
		udpSocket->deleteLater();

	udpSocket = new QUdpSocket(this);  
	//udpSocket->bind (QHostAddress("192.168.19.254"), LOCAL_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);  
	udpSocket->bind (m_nLocalPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);   //ע�⣺bind���Ǳ���IP�ͱ��ض˿ڣ����͵���Զ��IP��Զ�˶˿�
	connect (udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));  

}

void Worker::l_setConnectPort(int nCon)
{ 
	m_nConnectPort = nCon; 
}

void Worker::l_setPcProtocol(int nPro)
{ 
	m_nPcProtocol = nPro; 
}

void Worker::l_setRemoteIP()
{
	m_strRemoteIp =  QString("%1.%2.%3.%4").arg(DataBase::getInstance()->queryData("remote_ip1")).arg(DataBase::getInstance()->queryData("remote_ip2")).arg(DataBase::getInstance()->queryData("remote_ip3")).arg(DataBase::getInstance()->queryData("remote_ip4"));
}

void Worker::l_setRemotePort()
{
	m_nRemotePort = DataBase::getInstance()->queryData("remote_port").toUInt();
}

void Worker::l_setLocalIP()
{

}

void Worker::l_setLocalPort()
{
	m_nLocalPort = DataBase::getInstance()->queryData("port").toUInt();

	if(udpSocket != NULL)
		udpSocket->deleteLater();

	udpSocket = new QUdpSocket(this); 
	udpSocket->bind (m_nLocalPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);   //ע�⣺bind���Ǳ���IP�ͱ��ض˿ڣ����͵���Զ��IP��Զ�˶˿�
	connect (udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));  
}

void Worker::setupSerialCommunication()
{
	//����һ���ṹ�壬������Ŵ��ڸ�������;
	struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
	//���崮�ڶ��󣬲����ݲ������ڹ��캯���������г�ʼ��;
#ifdef WIN32

	myCom = new Win_QextSerialPort(MAINCOMPORT);

#elif linux

	myCom = new Posix_QextSerialPort(MAINCOMPORT,myComSetting,QextSerialBase::Polling);//LINUX�´����޷�ʹ���¼�����;

#endif

	//�Կɶ�д��ʽ�򿪴���;
	myCom ->open(QIODevice::ReadWrite);	
	myCom->setTimeout(10);
	myCom->setBaudRate(BAUD9600);
	myCom->setDataBits(DATA_8);
	myCom->setStopBits(STOP_1);
	myCom->setParity(PAR_NONE);
	myCom->setFlowControl(FLOW_OFF);
}

void Worker::setupMCUCommunication()
{
	//����һ���ṹ�壬������Ŵ��ڸ�������;
	struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
#ifdef WIN32

	mcuCom = new Win_QextSerialPort(MCUCOMPORT);

#elif linux

	mcuCom = new Posix_QextSerialPort(MCUCOMPORT,myComSetting,QextSerialBase::Polling);

#endif

	mcuCom->open(QIODevice::ReadWrite);
	mcuCom->setTimeout(10);
	mcuCom->setBaudRate(BAUD9600);
	mcuCom->setDataBits(DATA_8);
	mcuCom->setStopBits(STOP_1);
	mcuCom->setParity(PAR_NONE);
	mcuCom->setFlowControl(FLOW_OFF);

}

void Worker::startTimer()
{
	m_pTimer->start(TIMEOUT_PERIOD);
}


void Worker::uploadAuToPc(quint8 chanel, quint32 au , quint32 au2)
{
	//�ֵ�˫����;
	QByteArray data;
	if(chanel == 0)//������;
	{
		data.append(0x53);
		data.append(0x4d);
		data.append(0x20);
#if QT_VERSION >= 0x050000
		data.append(QString("%1").arg(au, 6, 16, QLatin1Char('0')).toUpper().toLatin1());
#else
		data.append(QString("%1").arg(au,6,16,QLatin1Char('0')).toUpper().toAscii());
#endif
		data.append(0x0d);
		data.append(0x7f);
	}
	else//˫����;
	{
		data.append(0x53);
		data.append(0x4d);
		data.append(0x20);
#if QT_VERSION >= 0x050000
		data.append(QString("%1").arg(au, 6, 16, QLatin1Char('0')).toUpper().toLatin1());
#else
		data.append(QString("%1").arg(au, 6, 16, QLatin1Char('0')).toUpper().toAscii());
#endif
		data.append(0x0d);

		data.append(0x53);
		data.append(0x6d);
		data.append(0x20);
#if QT_VERSION >= 0x050000
		data.append(QString("%1").arg(au, 6, 16, QLatin1Char('0')).toUpper().toLatin1());
#else
		data.append(QString("%1").arg(au, 6, 16, QLatin1Char('0')).toUpper().toAscii());
#endif
		data.append(0x0d);
		data.append(0x7f);
	}
	
	//�Žܻ��޸�@2016-06-22�����ڳ��Է���10��
	//qint8 cnt = 0;
	//qint16 sz = 0;
	//while(cnt < 10 && sz >= 0)
	//{
	//	sz = writeFunc((quint8 *)data.data(), data.size());
	//	cnt++;
	//}
	//if(sz == -1)
	//{
	//	qDebug() << "serial fatal error !!!!!!!!!!!!!!!!!!!!!!!!";
	//	//while(1);
	//}

	quint32 type = g_pWorker->getConnectPortType();
	if(type != PC_COMMUNICATION_PORT_ANALOG)
	{
		if(writeFunc((quint8 *)data.data(), data.size()) == -1)
			qDebug() << "serial fatal error !!!!!!!!!!!!!!!!!!!!!!!!\n";
	}
	else
	{
		quint32 spi_temp;
		quint32 spi_temp2;
		quint16 temp;

		if(chanel == 0)
		{
			spi_temp = au>>8;
			if(spi_temp > 0xFFFF)
				spi_temp = 0xFFFF;
			temp = (quint16)spi_temp;
			//qDebug() << "au = " << au;
			//qDebug() << "spi_temp = " << temp;
			spiWrite(&temp, 1);
		}
		else
		{
			spi_temp = au>>8;	
			if(spi_temp > 0xFFFF)
				spi_temp = 0xFFFF;
			temp = (quint16)spi_temp;
			spiWrite(&temp, 1);

			spi_temp2 = au2>>8;
			if(spi_temp2 > 0xFFFF)
				spi_temp2 = 0xFFFF;
			temp = (quint16)spi_temp2;
			spiWrite(&temp, 1);
		}
	}
}

void Worker::syncPCtoCollect()
{
	QByteArray data;
	data.append(0x53);
	data.append(0x58);
	data.append(0x0d);
	data.append(0x7f);

	//�Žܻ��޸�@2016-06-22�����ڳ��Է���10��
	//qint8 cnt = 0;
	//uint16 sz = 0;
	//while(cnt < 10 && sz == 0)
	//{
	//	sz = writeFunc((quint8 *)data.data(), data.size());
	//	cnt++;
	//}
	//if(sz == 0)
	//{
	//	qDebug() << "serial fatal error !!!!!!!!!!!!!!!!!!!!!!!!";
	//	//while(1);
	//}
	if(writeFunc((quint8 *)data.data(), data.size()) == -1)
		qDebug() << "serial fatal error !!!!!!!!!!!!!!!!!!!!!!!!\n";
}

void Worker::sendAckClarity(quint8 ack)
{
	ack ? SendACK() : SendNAK();
}



