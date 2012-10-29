#ifndef _TEXT_H_
#define _TEXT_H_

#include <QKeySequence>
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
		inline void m_connect(QMenu*, QString*, char*);
		void makeActions();
		QMenuBar* makeMenus();
		QStatusBar* makeStatus();

	private:
		QLabel *leftstatus;
		QLabel *rightstatus;
		QAction *m_spyee, *m_quest, *m_video;
		QAction *m_close, *m_exit;

	private slots:
		void spyee(){};
		void quest(){};
		void video(){};
};

#endif
