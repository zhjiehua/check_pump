/*
	DATE			VERSION		DESCRIPTION								AUTHER
	2016-08-11		V0.90		���֤�ؼ����ܱ�����λ��0������			zhjiehua
	2016-08-12		V0.91		�޸�GLPҳ�棨�������ڡ���װ���ڵȣ�		zhjiehua
	2016-08-17		V0.92		����У��ҳ���30min��ʱ					zhjiehua
	2016-08-17		V0.93		ѹ�����̴�40MPa��Ϊ60MPa��
								��ؼ���Ϊÿ�ο���������last_time		zhjiehua
	2016-09-12		V0.94		���4�����ͺţ�
								�޸�����Һ����bug						zhjiehua
	2016-10-17		V0.95		ѹ�����̸Ļ�40MPa						zhjiehua
	2016-10-17		V0.96		ѹ�����̸�Ϊ51MPa						zhjiehua
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
	//font.setFamily(("wenquanyi"));
	a.setFont(font);
	BaseMainPage w("LC3000U");
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
