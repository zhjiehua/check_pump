#include "mykeydriverplugin.h"
#include <QDebug>
#include "qkbdmy_qws.h"

MyKeyDriverPlugin::MyKeyDriverPlugin(QObject *parent):QKbdDriverPlugin(parent)
{
	qDebug()<<"plugin created"; 
}

MyKeyDriverPlugin::~MyKeyDriverPlugin()
{

}


QStringList MyKeyDriverPlugin::keys() const
{ 
	return QStringList() << "wdakey"; 
} 
// 
// The create() functions are responsible for returning an instance of 
// the keypad driver. We do this only if the driver parameter matches our key. 
// 
QWSKeyboardHandler *MyKeyDriverPlugin::create(const QString &driver, const QString &device) 
{ 
	qDebug("MyKeyDriverPlugin::create###: %s\n",driver.toLocal8Bit().constData()); 
	if (driver.toLower() == "wdakey") 
	{ 
		qDebug("Before creating MyKeyHandler\n"); 
		return new MyKeyHandler(device); 
	} 

	return 0; 
} 

QWSKeyboardHandler *MyKeyDriverPlugin::create(const QString &driver) 
{ 
	if (driver.toLower() == "wdakey") 
	{ 
		qDebug("Before creating MyKeyHandler"); 
		return new MyKeyHandler(); 
	} 

	return 0; 
}

Q_EXPORT_PLUGIN2(wdakey,MyKeyDriverPlugin) 
