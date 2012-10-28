#ifndef _TEXT_H_
#define _TEXT_H_

#include <QApplication>
#include <QPushButton>
#include <QSizePolicy>
#include <QStatusBar>
#include <QMenuBar>
#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QFrame>

#include "selector.h"
#include "mode.h"

class TextWindow : public ModeWindow
{
	Q_OBJECT

	public:
		TextWindow(Selector *selector = 0);
		~TextWindow();
	
	private:
		void onClose();
		QMenuBar* makeMenus();
		QStatusBar* makeStatus();

	private:
		QLabel *leftstatus;
		QLabel *rightstatus;
};

#endif
