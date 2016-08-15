#include "qkbdmy_qws.h"

#ifndef QT_NO_QWS_KBD_MY

#include <fcntl.h>
#include <QDebug>
#include <qnamespace.h>
#include <asm-generic/ioctl.h>
#include <sys/ioctl.h>

#define SIZE_KEYMATRIX_ROW 3
#define SIZE_KEYMATRIX_COL 8


#define IOC_MAGIC  'B'
// #define BTN_IOCTL_STOP_MOTOR		_IO(IOC_MAGIC, 7)
#define BTN_IOCTL_WARNING			_IO(IOC_MAGIC, 8)

static int kbd_keycode[ SIZE_KEYMATRIX_ROW ][ SIZE_KEYMATRIX_COL ] = {
	{Qt::Key_F8, Qt::Key_B, Qt::Key_C, Qt::Key_D, Qt::Key_E, Qt::Key_F5, Qt::Key_Backspace, Qt::Key_F6 },
	{Qt::Key_9, Qt::Key_0, Qt::Key_F7, Qt::Key_F2, Qt::Key_F1, Qt::Key_L, Qt::Key_Return, Qt::Key_F3 },
	{Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4, Qt::Key_5, Qt::Key_6, Qt::Key_7, Qt::Key_8 },
};

static int kbd_unicode[ SIZE_KEYMATRIX_ROW ][ SIZE_KEYMATRIX_COL ] = {
	{0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, Qt::Key_Backspace, 0xffff },
	{Qt::Key_9, Qt::Key_0, 0xffff, 0xffff, 0xffff, 0xffff, Qt::Key_Return, 0xffff },
	{Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4, Qt::Key_5, Qt::Key_6, Qt::Key_7, Qt::Key_8 },
};

int MyKeyHandler::kbFd = 0;

MyKeyHandler::MyKeyHandler(const QString &device)
{
	qDebug()<<"buttonpressed!"; 
	kbFd=open(device.toLocal8Bit().constData(),O_RDONLY,0); 
	if(kbFd>=0){ 
		notify=new QSocketNotifier(kbFd,QSocketNotifier::Read,this); 
		connect(notify,SIGNAL(activated(int)),this,SLOT(readData())); 
		qDebug()<<"plugin keyboard success";
	}else{ 
		qWarning("Cannot open %s for keyboard input", 
			device.toLocal8Bit().constData()); 
		return; 
	} 
}


MyKeyHandler::~MyKeyHandler(void)
{
	if(kbFd>=0) 
		close(kbFd); 
}

void MyKeyHandler::readData() 
{ 
	Qt::KeyboardModifiers modifiers = Qt::NoModifier; //enum of Modifiers 
	int row,col;
	int i; 
	int nread = read( kbFd, keyData, 2*sizeof( keyData ) );
	nread /= sizeof(struct key_action_data);
	if( nread <= 0 ){ 
		qWarning("Cannot read buttons"); 
		return; 
	}

	int flag = 0;
	for( i = 0; i < nread; ++i ){
		row = ( keyData[i].keycode / 10 - 1 ) % 3;
		col = ( keyData[i].keycode % 10 - 1 ) % 8;
		if(nread == 2)//组合键;
		{
			if(kbd_keycode[row][col] == Qt::Key_F2)
				flag |= 0x1;
			else if(kbd_keycode[row][col] == Qt::Key_F5)
				flag |= 0x2;
			
			if(flag == 0x3)
			{
				flag = 0;
				processKeyEvent(kbd_unicode[row][col] , kbd_keycode[row][col],Qt::ControlModifier,keyData[i].bPress,false);
				break;
			}
				
		}
		else
		{
			//qDebug("%x",kbd_keycode[row][col]);
			//Sends a key event to the Qt for Embedded Linux server application. 
			processKeyEvent(kbd_unicode[row][col] , kbd_keycode[row][col],modifiers,keyData[i].bPress,false); 
		}
		
		
	}
} 

void MyKeyHandler::stopMotor()
{
	//qDebug()<<"io stop motor";
	//ioctl(kbFd, BTN_IOCTL_STOP_MOTOR);	
}

void MyKeyHandler::turnOnWarning(bool on)
{
	qDebug()<<"io turn on warning";
	if(on)
		ioctl(kbFd, BTN_IOCTL_WARNING, 1);
	else
		ioctl(kbFd, BTN_IOCTL_WARNING, 0);
}

#endif    // QT_NO_QWS_KBD_MY
