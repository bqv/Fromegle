#ifndef _MODE_H_
#define _MODE_H_

#include <QDesktopWidget>
#include <QApplication>
#include <QCloseEvent>
#include <QMainWindow>
#include <iostream>
#include <QWidget>
#include <QIcon>

#include "selector.h"

class ModeWindow : public QMainWindow
{
	public:
		ModeWindow(Selector *selector, int w, int h) : QMainWindow(),
													   instance(selector),
													   width(w),
													   height(h)
	{
		instance->hide();

		QDesktopWidget *desktop = QApplication::desktop();

		MAX_X = desktop->width();
		MAX_Y = desktop->height();
		this->setWindowIcon(QIcon("icon.png"));
		this->setMinimumSize(width, height);
		this->resize(width, height);
		this->move((MAX_X - width) / 2, (MAX_Y - height) / 2);
	}
		virtual ~ModeWindow(){};
	
	protected:
		Selector *instance;
		int width, height;
		int MAX_X, MAX_Y;
		virtual void onClose(){};

	private:
		void closeEvent(QCloseEvent *event)
	{
		std::cout << "Returning to Selector..." << std::endl;
		this->onClose();
		instance->show();
		event->accept();
	}
};

#endif
