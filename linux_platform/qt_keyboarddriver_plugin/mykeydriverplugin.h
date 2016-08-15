#ifndef MYKEYDRIVERPLUGIN_H
#define MYKEYDRIVERPLUGIN_H

#include "mykey_global.h"
#include <QStringList>
#include <QtGui/QKbdDriverPlugin>


class MYKEY_EXPORT MyKeyDriverPlugin: public QKbdDriverPlugin 
{
	Q_OBJECT
public:
	MyKeyDriverPlugin(QObject *parent = 0);
	~MyKeyDriverPlugin();

 	QWSKeyboardHandler *create(const QString &driver, const QString &device); 
 	QWSKeyboardHandler *create(const QString &driver); 
	QStringList keys() const; 

};

#endif // MYKEYDRIVERPLUGIN_H
