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
		void fileActions();
		void editActions();
		void strnActions();
		void windActions();
		void helpActions();
		QMenuBar* makeMenus();
		QStatusBar* makeStatus();

	private:
		QLabel *leftstatus;
		QLabel *rightstatus;
		QAction *m_new, *m_open, *m_save, *m_saveas;
		QAction *m_close, *m_exit;
		QAction *m_cut, *m_copy, *m_paste;
		QAction *m_nsa, *m_asa, *m_nsb, *m_asb;
		QAction *m_textc, *m_spyee, *m_quest, *m_video;
		QAction *m_manu, *m_about;

	private slots:
		void newl(){};
		void open(){};
		void save(){};
		void saveas(){};
		void close(){};
		void cut(){};
		void copy(){};
		void paste(){};
		void nsa(){};
		void asa(){};
		void nsb(){};
		void asb(){};
		void textc();
		void spyee();
		void quest();
		void video();
		void manu(){};
		void about(){};
};

#endif
