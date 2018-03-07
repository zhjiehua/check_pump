#include "communicationcoupling.h"
#include "machinestat.h"
#include <QStringList>
#include "baseMainPage.h"

#include "msgpage.h"

extern BaseMainPage *g_pMainWindow;

extern QHostAddress remoteAddrTemp;
extern quint16 remotePortTemp;

extern QHostAddress remoteAddr;
extern quint16 remotePort;

CommunicationCoupling::CommunicationCoupling(MachineStat *parent)
	: QObject(parent)
	, m_pMachine(parent)
{
	initCommunication();
	wlen1 = DataBase::getInstance()->queryData("wavelen1").toDouble();
	wlen2 = DataBase::getInstance()->queryData("wavelen2").toDouble();

	//processCmd4PcClarity(0, 0, 0x11, 0x20);
}



CommunicationCoupling::~CommunicationCoupling()
{

}




void CommunicationCoupling::initCommunication()
{
	qDebug()<<QThread::currentThread();
	m_pWorker = new Worker(this);
	connect(this, SIGNAL(cmdSend(quint8, quint32, quint32)), m_pWorker, SLOT(CmdSend(quint8, quint32, quint32)));
	connect(this, SIGNAL(mcuCmdSend(quint8, quint32, quint32)), m_pWorker, SLOT(CmdSend4Mcu(quint8, quint32, quint32)) );
	connect(this, SIGNAL( cmdSendClarity(quint32, quint32, quint32) ), m_pWorker, SLOT( CmdSendClarity(quint32, quint32, quint32)) );
	connect(this, SIGNAL(ackClarity(quint8)), m_pWorker, SLOT(sendAckClarity(quint8)) );
	connect(m_pWorker, SIGNAL(process4Mcu( quint8, quint32, quint32, quint32)), this, SLOT(processCmd4Mcu(quint8, quint32, quint32, quint32)) );
	connect(m_pWorker, SIGNAL(process4Pc( quint8, quint32, quint32, quint32)), this, SLOT(processCmd4Pc(quint8, quint32, quint32, quint32)) );
	connect(m_pWorker, SIGNAL(process4PcClarity( quint8, quint32, quint32, quint32)), this, SLOT(processCmd4PcClarity(quint8, quint32, quint32, quint32)) );
	connect(m_pWorker, SIGNAL(communicationError(int)), this, SLOT(communicationError(int)) );

	connect(this, SIGNAL(s_setPcProtocol(int)), m_pWorker, SLOT(l_setPcProtocol(int)) );
	connect(this, SIGNAL(s_setConnectPort(int)), m_pWorker, SLOT(l_setConnectPort(int)) );
	connect(this, SIGNAL(s_remoteIPChange()), m_pWorker, SLOT(l_setRemoteIP()) );
	connect(this, SIGNAL(s_remotePortChange()), m_pWorker, SLOT(l_setRemotePort()) );
	connect(this, SIGNAL(s_localIPChange()), m_pWorker, SLOT(l_setLocalIP()) );
	connect(this, SIGNAL(s_localPortChange()), m_pWorker, SLOT(l_setLocalPort()) );

	setPcProtocol(DataBase::getInstance()->queryData("pcProtocol").toInt());


}




void CommunicationCoupling::sendMcuCmd(quint8 cmd, quint32 arg, quint32 add)
{
	emit(mcuCmdSend(cmd, arg, add));
}

void CommunicationCoupling::sendCmd(quint8 cmd, quint32 arg, quint32 add)
{
	emit(cmdSend(cmd, arg, add));
}


void CommunicationCoupling::sendCmdClarity(quint32 hAI, quint32 hPFC, quint32 hVal)
{
	emit( cmdSendClarity(hAI, hPFC, hVal) );
}

void CommunicationCoupling::processCmd4Pc(quint8 type, quint32 cmd, quint32 arg, quint32 add)
{
	QString strDisp("");

	remoteAddr = remoteAddrTemp;
	remotePort = remotePortTemp;

	//命令处理;
	switch( cmd )
	{
	case PFC_SET_WLEN1://设置波长1;
		{
			//g_pMainWindow->changePage(RUNPAGE_INDEX);
			m_pMachine->changeWaveLength(arg, MachineStat::EWLEN1);
		}
		break;
	case PFC_SET_WLEN2://设置波长2;
		{
			//if(DataBase::getInstance()->queryData("chanel").toInt() == 1)
			//	g_pMainWindow->changePage(RUNPAGE_INDEX);
			m_pMachine->changeWaveLength(arg, MachineStat::EWLEN2);
		}
		break;
	case PFC_RESET_AU://AU清零;
		{
			//g_pMainWindow->changePage(RUNPAGE_INDEX);
			m_pMachine->setPercentOfRandS();
		}
		break;
	case PFC_TURNON_LIGHT://开关灯;
		{
			//g_pMainWindow->changePage(RUNPAGE_INDEX);
			if(arg == 1)
				m_pMachine->setLampStat(MachineStat::ON);
			else
				m_pMachine->setLampStat(MachineStat::OFF);
		}
		break;
	case PFC_SET_TIMECONST://设置时间常数;
		{
			//g_pMainWindow->changePage(RUNPARAMPAGE_INDEX);
			QStringList list;
			list<<"1"<<"2"<<"5"<<"10"<<"20"<<"50";
			QString data = QString::number(arg);
			int index = list.indexOf(data);
			if(index != -1)
				DataBase::getInstance()->updateDate("timeconst", QString::number(index));
		}
		break;
	case PFC_SET_RANGCONST://设置量程
		{
			//g_pMainWindow->changePage(RUNPARAMPAGE_INDEX);
			int index = arg%16;
			DataBase::getInstance()->updateDate("range", QString::number(index));
		}
		break;
	case PFC_MOTOR_INIT://MCU初始化;
		{
			m_pMachine->resetWaveAndAngle();
			m_pMachine->setWaveCtrlWordAndHome();
		}
		break;
	case PFC_READ_LICENSE:
		{
			qDebug()<<"PFC_READ_LICENSE";
		}
		break;
	case PFC_READ_LGTIME://读氘灯运行时间;
		{
			m_pMachine->uploadTimeToPc(MachineStat::XEUSEDTIME, arg);
		}
		break;
	case PFC_READ_LGLICENSE:
		{
			qDebug()<<"PFC_READ_LGLICENSE";
		}
		break;
	case PFC_READ_SYSTIME://同步PC时间;
		{
			m_pMachine->uploadTimeToPc(MachineStat::SYSTIME, arg);
		}
		break;
	case PFC_READ_AU:
		{
			qDebug()<<"PFC_READ_AU";
		}
		break;
	case PFC_WAVEADD_MOTOR:
		{
			qDebug()<<"PFC_WAVEADD_MOTOR";
			m_pMachine->setStepTo(arg, 0);
		}
		break;
	case PFC_WAVEDEL_MOTOR:
		{
			qDebug()<<"PFC_WAVEDEL_MOTOR";
			m_pMachine->setStepTo(arg, 0x10);
		}
		break;
	case PFC_RESET_TIME:// 清空时间;
		{
			//g_pMainWindow->changePage(RUNPAGE_INDEX);
			m_pMachine->clearTime(MachineStat::STARTUPTIME);
		}
		break;
	default:
		strDisp = QString("cmd not found?????");
		qDebug()<<strDisp;
		break;
	}


}


void CommunicationCoupling::processCmd4Mcu(quint8 type, quint32 cmd, quint32 arg,quint32 add)
{
	QString strDisp;
	switch( cmd )
	{
	case MCU_SET_PARAM:
		{
			strDisp = QString("mcu set param;");
		}
		break;
	case MCU_MOTOR_INI://MCU初始化成功!
		{
			strDisp = QString("mcu motor ini success;");
			m_pMachine->motorInitSuccess();
			qDebug() << strDisp;

			if(m_pMachine->m_bSetWaveAfterHome)
			{
				m_pMachine->m_bSetWaveAfterHome = false;
				//张杰华修改@2016-07-03，将初始化电机前设置波长改成初始化完成后设置波长
				m_pMachine->setWaveCtrlWord();		//下发MCU波长值;
			}
		}
		break;
	case MCU_SETWAV_TO://mcu定位波长成功;
		{
			m_pMachine->mcuLocateWaveSuccess(true);
			qDebug() << "\nmcuLocateWaveSuccess!!!!!!" ;//<< DataBase::getInstance()->queryData("wavelen1");

			//定位成功立即发送读S R命令
			m_pMachine->m_nReadAuCnt = 0;
			m_pMachine->m_nDouleWaveEqualReadAuCnt = 0;
			sendMcuCmd(1, MCU_READ_AU_VAL_1, 0);
		}
		break;
	case MCU_READ_PARAM:
		{
			strDisp = QString("mcu read param;");
		}
		break;
		/*case MCU_READ_VERSION:
		{
		strDisp = QString("mcu read version;");
		}
		break;*/
	case MCU_READ_AU_VAL_1:
		{
			strDisp = QString("mcu read au val;");

#if 0
			static qint32 last_arg = 0;
			if(abs(last_arg - (qint32)arg) > 30)
			{
				qDebug() << "\nlast_arg = " << last_arg;
				qDebug() << "arg = " << arg << "\n";
			}
			last_arg = arg;
#endif

			m_pMachine->setCurrentWave(0);
			m_pMachine->updateSampleVal(arg);
		}
		break;
	case MCU_READ_AU_VALB_1:
		{
			strDisp = QString("mcu read au val;");
			m_pMachine->setCurrentWave(0);
			m_pMachine->updateRefVal(arg);
		}
		break;
	case MCU_READ_AU_VAL_2://!!!!!!!!!!!!!!!!!!!!!
		{
			strDisp = QString("mcu read au val;");
			m_pMachine->setCurrentWave(1);
			m_pMachine->updateSampleVal(arg);
		}
		break;
	case MCU_READ_AU_VALB_2://!!!!!!!!!!!!!!!!!!!!!!!
		{
			strDisp = QString("mcu read au val;");
			m_pMachine->setCurrentWave(1);
			m_pMachine->updateRefVal(arg);
		}
		break;
	default:
		//qDebug() << "\nthe motor is not moved!!!!!!!!";
		qDebug() << "processCmd4Mcu() cmd = " << cmd << "";
		qDebug() << "processCmd4Mcu() arg = " << arg << "\n";
		strDisp = QString("mcu command not found;");
		break;
	}
}

void CommunicationCoupling::communicationError(int error)
{
	m_pMachine->sysError(COMUNICATION_ERR, error);
}

void CommunicationCoupling::setPcProtocol(int idx)
{
	//m_pWorker->setPcProtocol(idx);
	emit(s_setPcProtocol(idx));
}

void CommunicationCoupling::setConnectPort(int idx)
{
	//m_pWorker->setConnectPort(idx);
	emit(s_setConnectPort(idx));
}

void CommunicationCoupling::remoteIPChange()
{
	//m_pWorker->setRemoteIP();
	emit(s_remoteIPChange());
}

void CommunicationCoupling::remotePortChange()
{
	//m_pWorker->setRemotePort();
	emit(s_remotePortChange());
}

void CommunicationCoupling::localIPChange()
{
	//m_pWorker->setLocalIP();
	emit(s_localIPChange());
}

void CommunicationCoupling::localPortChange()
{
	//m_pWorker->setLocalPort();
	emit(s_localPortChange());
}

void CommunicationCoupling::processCmd4PcClarity(quint8 hID, quint32 hAI, quint32 hPFC,quint32 hVal)
{
	////0x01是读取产品ID，因此不需要匹配ID;
	//if(hPFC != PFCC_READ_PRODUCT_ID && hID != m_pMachine->getMachineCode())
	//	return;

	QString strDisp("");

	remoteAddr = remoteAddrTemp;
	remotePort = remotePortTemp;

	//命令处理;
	switch( hPFC )
	{
		//以下需要回复数据;
	case PFCC_READ_PRODUCT_ID:
		{
			strDisp = QString("read ID");
			sendCmdClarity(0,PFCC_READ_PRODUCT_ID,ID);
			
		}
		break;
	case PFCC_READ_LICENSE_H:
		{
			strDisp = QString("read licnese h");
			//quint64 license = DataBase::getInstance()->queryData("license").toULong();
			QString s =  DataBase::getInstance()->queryData("serial");
			quint64 l = s.toULongLong();
			quint64 license = DataBase::getInstance()->queryData("serial").toULongLong();
			license/=1000000;
			license = DectoBCD(license,6);
			sendCmdClarity(0,PFCC_READ_LICENSE_H,license);
		}
		break;
	case PFCC_READ_LICENSE_L:
		{
			strDisp = QString("read licnese l");
			//quint64 license = DataBase::getInstance()->queryData("license").toULong();
			quint64 license = DataBase::getInstance()->queryData("serial").toULongLong();
			license%=1000000;
			license = DectoBCD(license,6);
			sendCmdClarity(0,PFCC_READ_LICENSE_L,license);
		}
		break;
	case PFCC_READ_STATUS1:
		{

			/*00XXXX：氘灯关状态
			01XXXX：氘灯开状态
			10XXXX：乌灯关状态
			11XXXX：乌灯开状态
			XXXX为当前检测器波长，190～700nm
			*/
			quint32 val = m_pMachine->getMachineStat1();
			sendCmdClarity(0,PFCC_READ_STATUS1,val);
		}
		break;
	case PFCC_READ_STATUS2:
		{
			quint32 val = m_pMachine->getMachineStat2();
			sendCmdClarity(0,PFCC_READ_STATUS2,val);
		}
		break;
	case PFCC_READ_SFVERSION:
		{
			strDisp = QString("read software version");
			//DectoBCD(VERSION,4);
			//quint32 verionH = VERSION;
			//quint32 verionL = (VERSION - verionH)*100;
			//DectoBCD(verionH,2)
			//	//(VERSION)
			sendCmdClarity(0,PFCC_READ_SFVERSION,1);
		}
		break;
	case PFCC_READ_REF:   //张杰华修改@2016-06-18，PFCC_READ_REF和PFCC_READ_SIG的函数调换过来了
		{
			//strDisp = QString("read ref");
			quint32 refVal =m_pMachine->getRefVal();
			sendCmdClarity(0,PFCC_READ_REF, refVal);
		}
		break;
	case PFCC_READ_SIG:
		{	
			quint32 sampleVal =m_pMachine->getSamleVal();
			//sampleVal = 74746;      //这是搞什么呢？？？？？？
			sendCmdClarity(0,PFCC_READ_SIG,sampleVal);
		}
		break;	
	case PFCC_READ_WAVE://张杰华修改@2016-06-18，新协议
		{
			//QString::number(((hVal>>12)&0xfff), 16).toInt();
			wlen1 = DataBase::getInstance()->queryData("wavelen1").toInt();
			wlen2 = DataBase::getInstance()->queryData("wavelen2").toInt();

			sendCmdClarity(0,PFCC_READ_WAVE, (DectoBCD((int)(wlen1), 4) | DectoBCD(((int)(wlen2)), 4) << 12 ));
			
		/*	qDebug() << "PFCC_READ_WAVE wlen1 = " << wlen1;
			qDebug() << "PFCC_READ_WAVE wlen2 = " << wlen2;*/

			//m_pMachine->changeWaveLength(QString::number(hVal, 16).toDouble(), MachineStat::EWLEN2);
			//sendClarityACK();
		}
	break;
	//以下需要回复ACK或者NACK
	case PFCC_SET_WAVE:
		{
			//张杰华修改@2016-06-18，新协议
			wlen1 = QString::number((hVal&0xfff), 16).toInt();
			if(DataBase::getInstance()->queryData("chanel").toInt())//如果是双波长
				wlen2 = QString::number(((hVal>>12)&0xfff), 16).toInt();
			else
				wlen2 = DataBase::getInstance()->queryData("wavelen2").toInt();

			m_pMachine->changeWaveLengthClarity(wlen1, wlen2);

			//qDebug() << "wlen1 = " << wlen1;
			//qDebug() << "wlen2 = " << wlen2;

			sendClarityACK();
		}
		break;
	case PFCC_SET_TIMECST:
		{
			QStringList list;
			list<<"1"<<"2"<<"5"<<"10"<<"20"<<"50";
			QString data = QString::number(hVal,16);
			int index = list.indexOf(data);
			//qDebug() << "index = " << index;
			//qDebug() << "data = " << data;
			if(index != -1)
				DataBase::getInstance()->updateDate("timeconst", QString::number(index));

			////张杰华修改@2016-06-29
			//double timeconst = QString::number(hVal,16).toDouble()/10.0;
			//DataBase::getInstance()->updateDate("timeconst", QString::number(timeconst, 'f', 1));
			//qDebug() << "timeconst = " << timeconst;

			sendClarityACK();
		}
		break;

	case PFCC_SET_OUTPUTRNG:
		{
			int index = QString::number(hVal,16).toInt();
			DataBase::getInstance()->updateDate("range", QString::number(index%16));
			sendClarityACK();
		}
		break;
	case PFCC_SET_SYNCTIME:
		{
			strDisp = QString("synctime!");
			//int time = QString::number(hVal,16).toInt()/100;
			//m_pMachine->uploadTimeToPc(MachineStat::SYSTIME, arg);
			sendClarityACK();
		}
		break;
	case PFCC_SET_LIGHTON:
		{
			m_pMachine->setLampStat(MachineStat::ON);
			sendClarityACK();
		}
		break;
	case PFCC_SET_LIGHTOFF:
		{
			m_pMachine->setLampStat(MachineStat::OFF);
			sendClarityACK();
		}
		break;
	case PFCC_WAVE_INI:
		{
			m_pMachine->resetWaveAndAngle();
			m_pMachine->setWaveCtrlWordAndHome();
			sendClarityACK();
		}
		break;
	case PFCC_AUTO_CLEAR:
		{
			m_pMachine->setPercentOfRandS();
			sendClarityACK();

			//qDebug() << "PFCC_AUTO_CLEAR ";
		}
		break;
	case PFCC_SET_AUFREQ:
		{
			//设置上传频率;
			//m_pMachine->setUploadAuFreq(!!hVal);
			hVal = QString::number(hVal, 16).toInt();
			m_pMachine->setUploadAuFreq(hVal);
			m_pMachine->m_bClaritySetFreq = true;
			sendClarityACK();
		}
		break;
	case PFCC_SET_OUTPUTEV:
		{
			strDisp = QString("set mode;");
			sendClarityACK();
		}
		break;
	case PFCC_SET_LIGHT:
		{
			m_pMachine->changeLampSrc(hVal);
			sendClarityACK();
			qDebug() << "PFCC_SET_LIGHT   "  << hVal;
		}
		break;
	case PFCC_READ_XEUSEDTIME:  //张杰华添加@2016-06-18，新协议
		{
			MachineStat::getInstance()->uploadTimeToPc( MachineStat::XEUSEDTIME, 1 );//读取氘灯时间，单位小时
		}
		break;
	default:
		strDisp = QString("命令无法识别...;");
		break;
	}
	qDebug()<<strDisp;
}

void CommunicationCoupling::sendClarityACK()
{
	emit( ackClarity(1) );
}

void CommunicationCoupling::sendClarityNAK()
{
	emit( ackClarity(0) );
}




