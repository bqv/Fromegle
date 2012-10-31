#ifndef _TEXT_H_
#define _TEXT_H_

#include <QStackedLayout>
#include <QKeySequence>
#include <QTextBrowser>
#include <QApplication>
#include <QPushButton>
#include <QSizePolicy>
#include <QTabWidget>
#include <QBoxLayout>
#include <QStatusBar>
#include <QGroupBox>
#include <QLineEdit>
#include <QMenuBar>
#include <QWidget>
#include <QDebug>
#include <QFrame>
#include <QLabel>

#include "selector.h"
#include "mode.h"
#include "stranger.h"

class TextWindow : public ModeWindow
{
	Q_OBJECT

	public:
		TextWindow(Selector *selector = 0);
		~TextWindow();
	
	private:
		void onClose();
		void initStrangers();
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
		QLabel *count;
		QTabWidget *left_tab, *right_tab;
		QTextBrowser *lconvo, *rconvo;
		QLabel *ltyping, *rtyping;
		QWidgetList lefttabs, righttabs;
		QLineEdit *leftbox, *rightbox;
		QAction *m_new, *m_open, *m_save, *m_saveas;
		QAction *m_close, *m_exit;
		QAction *m_cut, *m_copy, *m_paste;
		QAction *m_nsa, *m_nsb;
		QAction	*m_asa, *m_asb;
		QMenu	*m_fsa, *m_fsb;
		QAction *m_textc, *m_spyee, *m_quest, *m_video;
		QAction *m_manu, *m_about;
		Stranger *a, *b;

	signals:
		void sendMessageA(QString);
		void sendMessageB(QString);
		void disconnectA();
		void disconnectB();
		void reconnectA();
		void reconnectB();

	private slots:
		void updateStatus();
		void gotMessageA(QString);
		void gotMessageB(QString);
		void sentMessageA(QString);
		void sentMessageB(QString);
		void gotDisconnectA();
		void gotDisconnectB();
		void gotConnectA();
		void gotConnectB();
		void sendDisconnectA();
		void sendDisconnectB();
		void sendDisconnectE();
		void sendConnectA();
		void sendConnectB();
		void sendConnectE();
		void spoolA();
		void spoolB();
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
