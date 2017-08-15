#include "topwidget.h"
//#include <QtGui/QApplication>

TopWidget::TopWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

TopWidget::~TopWidget()
{

}

void TopWidget::setTitle( QString title )
{
	ui.label->setText(title);
}
