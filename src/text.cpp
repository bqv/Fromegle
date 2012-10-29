#include "text.h"

TextWindow::TextWindow(Selector *selector) : ModeWindow(selector, 768, 512)
{
	setWindowTitle("Fromegle - Text Chat");
	makeMenus();
	makeStatus();
	show();
}

TextWindow::~TextWindow()
{
	;
}

void TextWindow::onClose()
{
	;
}

void TextWindow::makeActions()
{
	m_spyee = new QAction("&Spy Mode", this);
	m_spyee->setShortcut(QKeySequence("Ctrl+2"));
	m_spyee->setStatusTip("Answer questions with another stranger!");
	connect(m_spyee, SIGNAL(triggered()), this, SLOT(spyee()));
	m_quest = new QAction("&Quest Mode", this);
	m_quest->setShortcut(QKeySequence("Ctrl+3"));
	m_quest->setStatusTip("Watch two strangers discuss your question!");
	connect(m_quest, SIGNAL(triggered()), this, SLOT(quest()));
	m_video = new QAction("&Video Mode", this);
	m_video->setShortcut(QKeySequence("Ctrl+4"));
	m_video->setStatusTip("Video Chat with Strangers!");
	m_video->setEnabled(false);
	connect(m_video, SIGNAL(triggered()), this, SLOT(video()));
	m_close = new QAction("&Close", this);
	m_close->setShortcuts(QKeySequence::Close);
	connect(m_close, SIGNAL(triggered()), this, SLOT(close()));
	m_exit = new QAction("&Exit", this);
	m_exit->setShortcut(QKeySequence("Alt+Q"));
	connect(m_exit, SIGNAL(triggered()), instance->app(), SLOT(quit()));
}

QMenuBar* TextWindow::makeMenus()
{
	QMenuBar *menu = menuBar();
	makeActions();
	QMenu *m_file = menu->addMenu("&File");
	m_file->addAction(m_spyee);
	m_file->addAction(m_quest);
	m_file->addAction(m_video);
	m_file->addSeparator();
	m_file->addAction(m_close);
	m_file->addAction(m_exit);
	menu->addMenu("&Edit");
	menu->addMenu("&Strangers");
	menu->addMenu("&Window");
	menu->addMenu("&Help");

	return menu;
}

QStatusBar* TextWindow::makeStatus()
{
	QStatusBar *status = statusBar();
	leftstatus = new QLabel("A is loading", status);
	leftstatus->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	rightstatus = new QLabel("B is loading", status);
	rightstatus->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	status->addPermanentWidget(leftstatus);
	status->addPermanentWidget(rightstatus);
	
	return status;
}

