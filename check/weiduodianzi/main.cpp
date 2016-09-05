/*
	DATE			VERSION		DESCRIPTION							AUTHER
	2016-08-11		V0.90		���֤�ؼ����ܱ�����λ��0������		zhjiehua
	2016-08-12		V0.91		�޸�GLPҳ�棨�������ڡ���װ���ڵȣ�	zhjiehua
	2016-08-17		V0.92		���ģ��ڵ�bug						zhjiehua
	2016-09-01		V0.93		��ӵ�Դ���룬������Դ��¼���ʽ
								����ClarityЭ����ϴ�Ƶ��bug		zhjiehua
*/

#include "baseMainPage.h"
#include <QtGui/QApplication>
#include <QFont>
#include <QTextCodec>
#include "Common.h"
#include <QDebug>
#include <QString>
#include <QFontDatabase>
#include "QDesktopWidget"

int g_nActScreenX;
int g_nActScreenY;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QDesktopWidget* desktopWidget = QApplication::desktop();
	//��ȡ���������С
	//QRect deskRect = desktopWidget->availableGeometry();
	//��ȡ�豸��Ļ��С
	QRect screenRect = desktopWidget->screenGeometry();
	g_nActScreenX = screenRect.width();
	g_nActScreenY = screenRect.height();

	qDebug() << "m_nActScreenX = " << g_nActScreenX;
	qDebug() << "m_nActScreenY = " << g_nActScreenY;

	QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
	QFont font;
	if(g_nActScreenX < 420)
		font.setPointSize(8);
	else
	{
#ifdef linux
		font.setPointSize(12);
#else
		font.setPointSize(8);
#endif
	}

	QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb18030"));
	//QFont font;
	//font.setPointSize(8);
	//font.setFamily(("����"));
	QFontDatabase database;
	//qDebug()<<database.families();
	a.setFont(font);
	BaseMainPage w("UV3000U");
	w.resize(SCREEN_WIDTH, SCREEN_HEIGH);
	
#ifdef linux
	QApplication::setOverrideCursor(Qt::BlankCursor);//�������
	w.setWindowFlags(Qt::FramelessWindowHint);
	w.showFullScreen ();
#else
	//w.setWindowFlags(Qt::FramelessWindowHint);
	w.show();
#endif
	return a.exec();
}
