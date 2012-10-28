#ifndef _TEXT_H_
#define _TEXT_H_

#include <QDesktopWidget>
#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <QWidget>
#include <QIcon>

#include "selector.h"

class TextWindow : public QWidget
{
	Q_OBJECT

	public:
		TextWindow(Selector *selector = 0);
	
	private slots:
		
	private:
		Selector *instance;
};

#endif
