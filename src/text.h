#ifndef _TEXT_H_
#define _TEXT_H_

#include <QStackedLayout>
#include <QKeySequence>
#include <QApplication>
#include <QPushButton>
#include <QSizePolicy>
#include <QTabWidget>
#include <QBoxLayout>
#include <QStatusBar>
#include <QGroupBox>
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
		void fileActions();
		void editActions();
		void strnActions();
		void makeFiltersA();
		void makeFiltersB();
		void windActions();
		void helpActions();
		QMenuBar* makeMenus();
		QStatusBar* makeStatus();

	private:
		QWidget *body;
		QLabel *leftstatus;
		QLabel *rightstatus;
		QTabWidget *left_tab, *right_tab;
		QSizePolicy policy;
		QAction *m_new, *m_open, *m_save, *m_saveas;
		QAction *m_close, *m_exit;
		QAction *m_cut, *m_copy, *m_paste;
		QAction *m_nsa, *m_nsb;
		QAction	*m_asa, *m_asb;
		QMenu	*m_fsa, *m_fsb;
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
		void a_clear(){}
		void nsb(){};
		void asb(){};
		void b_clear(){}
		void textc();
		void spyee();
		void quest();
		void video();
		void manu(){};
		void about(){};
};

#endif
