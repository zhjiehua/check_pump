/*
	DATE			VERSION		DESCRIPTION								AUTHER
	2016-08-11		V0.90		许可证控件不能保存首位是0的数字			zhjiehua
	2016-08-12		V0.91		修改GLP页面（生产日期、安装日期等）		zhjiehua
	2016-08-17		V0.92		流量校正页面加30min定时					zhjiehua
	2016-08-17		V0.93		压力量程从40MPa改为60MPa；
								电池检测改为每次开机都更新last_time		zhjiehua
	2016-09-12		V0.94		添加4个泵型号；
								修改总吸液量的bug						zhjiehua
	2016-10-17		V0.95		压力量程改回40MPa						zhjiehua
	2016-10-17		V0.96		压力量程改为51MPa						zhjiehua
*/

#include "baseMainPage.h"
#include <QtGui/QApplication>
#include <QFont>
#include <QTextCodec>
#include "Common.h"
#include "QDesktopWidget"


int g_nActScreenX;
int g_nActScreenY;

int main(int argc, char *argv[])
{
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
	//font.setFamily(("wenquanyi"));
	a.setFont(font);
	BaseMainPage w("LC3000U");
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
