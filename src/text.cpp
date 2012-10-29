#include "text.h"

TextWindow::TextWindow(Selector *selector) : ModeWindow(selector, 768, 512)
{
	setWindowTitle("Fromegle - Text Chat");
	makeMenus();
	makeStatus();

	(left_tab = new QTabWidget)->setTabPosition(QTabWidget::East);
	left_tab->addTab(new QWidget, "Conversation");
	(right_tab = new QTabWidget)->setTabPosition(QTabWidget::West);
	right_tab->addTab(new QWidget, "Conversation");

	QLabel *left_title = new QLabel("Stranger A");
	left_title->setFont(QFont(0, 0, QFont::Bold));
	QVBoxLayout vlt_a, vlt_b;
	vlt_a.addWidget(left_title);
	vlt_a.addWidget(left_tab);
	QLabel *right_title = new QLabel("Stranger B");
	right_title->setAlignment(Qt::AlignRight);
	right_title->setFont(QFont(0, 0, QFont::Bold));
	vlt_b.addWidget(right_title);
	vlt_b.addWidget(right_tab);

	body = new QWidget(this);
	QHBoxLayout *main_lt = new QHBoxLayout();
	main_lt->addLayout(&vlt_a);
	main_lt->addLayout(&vlt_b);
	body->setLayout(main_lt);

	setCentralWidget(body);

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

void TextWindow::fileActions()
{
	m_new = new QAction("&New", this);
	m_new->setShortcuts(QKeySequence::New);
	connect(m_new, SIGNAL(triggered()), this, SLOT(newl()));
	m_open = new QAction("&Open", this);
	m_open->setShortcuts(QKeySequence::Open);
	connect(m_open, SIGNAL(triggered()), this, SLOT(open()));
	m_save = new QAction("&Save", this);
	m_save->setShortcuts(QKeySequence::Save);
	connect(m_save, SIGNAL(triggered()), this, SLOT(save()));
	m_saveas = new QAction("&Save as", this);
	m_saveas->setShortcuts(QKeySequence::SaveAs);
	connect(m_saveas, SIGNAL(triggered()), this, SLOT(saveas()));
	m_close = new QAction("&Close", this);
	m_close->setShortcuts(QKeySequence::Close);
	connect(m_close, SIGNAL(triggered()), this, SLOT(close()));
	m_exit = new QAction("&Exit", this);
	m_exit->setShortcut(QKeySequence("Alt+Q"));
	connect(m_exit, SIGNAL(triggered()), instance->app(), SLOT(quit()));
}
void TextWindow::editActions()
{
	m_cut = new QAction("&Cut", this);
	m_cut->setShortcuts(QKeySequence::Cut);
	connect(m_cut, SIGNAL(triggered()), this, SLOT(cut()));
	m_copy = new QAction("&Copy", this);
	m_copy->setShortcuts(QKeySequence::Copy);
	connect(m_copy, SIGNAL(triggered()), this, SLOT(copy()));
	m_paste = new QAction("&Paste", this);
	m_paste->setShortcuts(QKeySequence::Paste);
	connect(m_paste, SIGNAL(triggered()), this, SLOT(paste()));
}
void TextWindow::strnActions()
{
	m_nsa = new QAction("&New Stranger A", this);
	m_nsa->setShortcut(QKeySequence("Ctrl+,"));
	connect(m_nsa, SIGNAL(triggered()), this, SLOT(nsa()));
	m_asa = new QAction("&Auto Stranger A", this);
	m_asa->setShortcut(QKeySequence("Ctrl+Shift+,"));
	m_asa->setCheckable(true);
	connect(m_asa, SIGNAL(triggered()), this, SLOT(asa()));
	m_nsb = new QAction("&New Stranger B", this);
	m_nsb->setShortcut(QKeySequence("Ctrl+."));
	connect(m_nsb, SIGNAL(triggered()), this, SLOT(nsb()));
	m_asb = new QAction("&Auto Stranger B", this);
	m_asb->setShortcut(QKeySequence("Ctrl+Shift+."));
	m_asb->setCheckable(true);
	connect(m_asb, SIGNAL(triggered()), this, SLOT(asb()));
	makeFiltersA();
	makeFiltersB();
}
void TextWindow::makeFiltersA()
{
	m_fsa = new QMenu("&A Filters", this);
	m_fsa->setTearOffEnabled(true);
	m_fsa->addSeparator();
	QAction *f_clear = new QAction("&Clear All", this);
	f_clear->setStatusTip("Disable all A to B Filters");
	connect(f_clear, SIGNAL(triggered()), this, SLOT(a_clear()));
	m_fsa->addAction(f_clear);
}
void TextWindow::makeFiltersB()
{
	m_fsb = new QMenu("&B Filters", this);
	m_fsb->setTearOffEnabled(true);
	m_fsb->addSeparator();
	QAction *f_clear = new QAction("&Clear All", this);
	f_clear->setStatusTip("Disable all B to A Filters");
	connect(f_clear, SIGNAL(triggered()), this, SLOT(b_clear()));
	m_fsb->addAction(f_clear);
}
void TextWindow::windActions()
{
	m_textc = new QAction("&Text Mode", this);
	m_textc->setShortcut(QKeySequence("Ctrl+1"));
	m_textc->setStatusTip("Talk to strangers!");
	m_textc->setCheckable(true);
	connect(m_textc, SIGNAL(triggered()), this, SLOT(textc()));
	m_spyee = new QAction("&Spy Mode", this);
	m_spyee->setShortcut(QKeySequence("Ctrl+2"));
	m_spyee->setStatusTip("Answer questions with another stranger!");
	m_spyee->setCheckable(true);
	connect(m_spyee, SIGNAL(triggered()), this, SLOT(spyee()));
	m_quest = new QAction("&Quest Mode", this);
	m_quest->setShortcut(QKeySequence("Ctrl+3"));
	m_quest->setStatusTip("Watch two strangers discuss your question!");
	m_quest->setCheckable(true);
	connect(m_quest, SIGNAL(triggered()), this, SLOT(quest()));
	m_video = new QAction("&Video Mode", this);
	m_video->setShortcut(QKeySequence("Ctrl+4"));
	m_video->setStatusTip("Video Chat with Strangers!");
	m_video->setCheckable(true);
	m_video->setEnabled(false);
	connect(m_video, SIGNAL(triggered()), this, SLOT(video()));
	QActionGroup *mode = new QActionGroup(this);
	mode->addAction(m_textc);
	mode->addAction(m_spyee);
	mode->addAction(m_quest);
	mode->addAction(m_video);
	m_textc->setChecked(true);
}
void TextWindow::helpActions()
{
	m_manu = new QAction("&Manual", this);
	m_manu->setShortcuts(QKeySequence::HelpContents);
	connect(m_manu, SIGNAL(triggered()), this, SLOT(manu()));
	m_about = new QAction("&About", this);
	connect(m_about, SIGNAL(triggered()), this, SLOT(about()));
}

QMenuBar* TextWindow::makeMenus()
{
	QMenuBar *menu = menuBar();
	QMenu *m_file = menu->addMenu("&File");
	fileActions();
	m_file->addAction(m_new);
	m_file->addAction(m_open);
	m_file->addAction(m_save);
	m_file->addAction(m_saveas);
	m_file->addSeparator();
	m_file->addAction(m_close);
	m_file->addAction(m_exit);
	QMenu *m_edit = menu->addMenu("&Edit");
	editActions();
	m_edit->addAction(m_cut);
	m_edit->addAction(m_copy);
	m_edit->addAction(m_paste);
	QMenu *m_strn = menu->addMenu("&Strangers");
	strnActions();
	m_strn->setTearOffEnabled(true);
	m_strn->addAction(m_nsa);
	m_strn->addAction(m_asa);
	m_strn->addMenu(m_fsa);
	m_strn->addSeparator();
	m_strn->addAction(m_nsb);
	m_strn->addAction(m_asb);
	m_strn->addMenu(m_fsb);
	menu->addSeparator();
	QMenu *m_wind = menu->addMenu("&Window");
	windActions();
	m_wind->addAction(m_textc);
	m_wind->addAction(m_spyee);
	m_wind->addAction(m_quest);
	m_wind->addAction(m_video);
	QMenu *m_help = menu->addMenu("&Help");
	helpActions();
	m_help->addAction(m_manu);
	m_help->addAction(m_about);

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

void TextWindow::textc()
{
}
void TextWindow::spyee()
{
}
void TextWindow::quest()
{
}
void TextWindow::video()
{
}

