/*
	DATE			VERSION		DESCRIPTION							AUTHER
	2016-08-11		V0.90		许可证控件不能保存首位是0的数字		zhjiehua
	2016-08-12		V0.91		修改GLP页面（生产日期、安装日期等）	zhjiehua
	2016-08-17		V0.92		解决模拟口的bug						zhjiehua
	2016-09-01		V0.93		添加灯源密码，调整灯源记录表格式
								修正Clarity协议的上传频率bug		zhjiehua
	2016-10-17		V0.94		去掉电池检测						zhjiehua
	2016-11-17		V0.95		Clarity协议流程修改：开机后要PC修改完上传频率才开始上传Au值
																	zhjiehua
	2016-11-17		V0.96		Clarity协议的时间跟上传频率无关		zhjiehua
	2017-03-17		V0.97		将保存数据和更新数据按钮从信息页面移到管理员页面
																	zhjiehua
	2017-08-15		V0.98		将超级管理员的密码由111111改成173895    
																	zhjiehua
	2017-11-07		V0.99		添加上位机模拟检测器的宏；
								使用debug页面。						zhjiehua
*/

#include "baseMainPage.h"
//#if QT_VERSION >= 0x050000
//#include <QtWidgets/QApplication>
//#else
//#include <QtGui/QApplication>
//#endif
#include <QApplication>

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
#if QT_VERSION >= 0x050000
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
#endif
	QApplication a(argc, argv);

	QDesktopWidget* desktopWidget = QApplication::desktop();
	//获取可用桌面大小
	//QRect deskRect = desktopWidget->availableGeometry();
	//获取设备屏幕大小
	QRect screenRect = desktopWidget->screenGeometry();
	g_nActScreenX = screenRect.width();
	g_nActScreenY = screenRect.height();

	qDebug() << "m_nActScreenX = " << g_nActScreenX;
	qDebug() << "m_nActScreenY = " << g_nActScreenY;

	//QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
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

#if QT_VERSION < 0x050000
	QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb18030"));
#endif

	//QFont font;
	//font.setPointSize(8);
	//font.setFamily(("黑体"));
	QFontDatabase database;
	//qDebug()<<database.families();
	a.setFont(font);
	BaseMainPage w("UV3000U");
	w.resize(SCREEN_WIDTH, SCREEN_HEIGH);
	
#ifdef linux
	QApplication::setOverrideCursor(Qt::BlankCursor);//隐藏鼠标
	w.setWindowFlags(Qt::FramelessWindowHint);
	w.showFullScreen ();
#else
	//w.setWindowFlags(Qt::FramelessWindowHint);
	w.show();
#endif
	return a.exec();
}
