#include "text.h"

TextWindow::TextWindow(Selector *selector) : ModeWindow(selector, 768, 512)
{
	setWindowTitle("Fromegle - Text Chat");
	makeMenus();
	makeStatus();
	body = new QWidget(this);
	QBoxLayout *main_vlt = new QVBoxLayout();
	body->setLayout(main_vlt);
	setCentralWidget(body);

	QBoxLayout *display = new QHBoxLayout();
	QBoxLayout *bottombar = new QHBoxLayout();
	main_vlt->addLayout(display);
	main_vlt->addLayout(bottombar);

	QBoxLayout *leftpanel = new QVBoxLayout();
	QBoxLayout *rightpanel = new QVBoxLayout();
	display->addLayout(leftpanel);
	display->addLayout(rightpanel);

	QLabel *left_title = new QLabel("Stranger A");
	left_title->setFont(QFont(0, 0, QFont::Bold));
	(left_tab = new QTabWidget)->setTabPosition(QTabWidget::East);
	QBoxLayout *leftinject = new QHBoxLayout();
	leftpanel->addWidget(left_title);
	leftpanel->addWidget(left_tab);
	leftpanel->addLayout(leftinject);

	QWidget *leftconvo = new QWidget;
	left_tab->addTab(leftconvo, "Conversation");
	QBoxLayout *lconvo_vlt = new QVBoxLayout();
	leftconvo->setLayout(lconvo_vlt);

	lconvo = new QTextBrowser;
	ltyping = new QLabel("Stranger A is typing...");
	lconvo_vlt->addWidget(lconvo);
	lconvo_vlt->addWidget(ltyping);
	ltyping->hide();
	lscroll = lconvo->verticalScrollBar();

	lconvo->setHtml("");
	lconvo->setFrameShadow(QFrame::Plain);
	lconvo->viewport()->setAutoFillBackground(false);

	leftbox = new QLineEdit();
	leftbox->setPlaceholderText("Type to here to talk as Stranger A");
	QPushButton *leftsend = new QPushButton("Send");
	connect(leftsend, SIGNAL(clicked()), this, SLOT(spoolA()));
	connect(leftbox, SIGNAL(returnPressed()), this, SLOT(spoolA()));
	leftinject->addWidget(leftbox);
	leftinject->addWidget(leftsend);

	QLabel *right_title = new QLabel("Stranger B");
	right_title->setAlignment(Qt::AlignRight);
	right_title->setFont(QFont(0, 0, QFont::Bold));
	(right_tab = new QTabWidget)->setTabPosition(QTabWidget::West);
	QBoxLayout *rightinject = new QHBoxLayout();
	rightpanel->addWidget(right_title);
	rightpanel->addWidget(right_tab);
	rightpanel->addLayout(rightinject);

	QWidget *rightconvo = new QWidget;
	right_tab->addTab(rightconvo, "Conversation");
	QBoxLayout *rconvo_vlt = new QVBoxLayout();
	rightconvo->setLayout(rconvo_vlt);

	rconvo = new QTextBrowser;
	rtyping = new QLabel("Stranger B is typing...");
	rconvo_vlt->addWidget(rconvo);
	rconvo_vlt->addWidget(rtyping);
	rtyping->hide();
	rscroll = rconvo->verticalScrollBar();

	rconvo->setHtml("");
	rconvo->setFrameShadow(QFrame::Plain);
	rconvo->viewport()->setAutoFillBackground(false);

	rightbox = new QLineEdit();
	rightbox->setPlaceholderText("Type to here to talk as Stranger B");
	QPushButton *rightsend = new QPushButton("Send");
	connect(rightsend, SIGNAL(clicked()), this, SLOT(spoolB()));
	connect(rightbox, SIGNAL(returnPressed()), this, SLOT(spoolB()));
	rightinject->addWidget(rightbox);
	rightinject->addWidget(rightsend);

	QPushButton *ra, *rb, *re, *de, *db, *da;
	bottombar->addWidget(ra = new QPushButton("Reconnect A"));
	bottombar->addWidget(rb = new QPushButton("Reconnect B"));
	bottombar->addWidget(re = new QPushButton("Reconnect")); //italic
	bottombar->addWidget(de = new QPushButton("Disconnect"));//italic
	bottombar->addWidget(db = new QPushButton("Disconnect B"));
	bottombar->addWidget(da = new QPushButton("Disconnect A"));
	re->setFont(QFont(0, 0, 0, true));
	de->setFont(QFont(0, 0, 0, true));

	connect(ra, SIGNAL(clicked()), this, SLOT(sendConnectA()));
	connect(rb, SIGNAL(clicked()), this, SLOT(sendConnectB()));
	connect(re, SIGNAL(clicked()), this, SLOT(sendConnectE()));
	connect(de, SIGNAL(clicked()), this, SLOT(sendDisconnectE()));
	connect(db, SIGNAL(clicked()), this, SLOT(sendDisconnectB()));
	connect(da, SIGNAL(clicked()), this, SLOT(sendDisconnectA()));

	initStrangers();

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

void TextWindow::initStrangers()
{
	a = new Stranger(Stranger::Text, instance->getServers());
	{
		connect(a, SIGNAL(connected()), this, SLOT(gotConnectA()));
		connect(a, SIGNAL(message(QString)), this, SLOT(gotMessageA(QString)));
		connect(a, SIGNAL(disconnected()), this, SLOT(gotDisconnectA()));
		connect(a, SIGNAL(typing()), this, SLOT(gotTypingA()));
		connect(a, SIGNAL(stopped()), this, SLOT(gotStoppedA()));
	}
	a->begin();
	b = new Stranger(Stranger::Text, instance->getServers());
	{
		connect(b, SIGNAL(connected()), this, SLOT(gotConnectB()));
		connect(b, SIGNAL(message(QString)), this, SLOT(gotMessageB(QString)));
		connect(b, SIGNAL(disconnected()), this, SLOT(gotDisconnectB()));
		connect(b, SIGNAL(typing()), this, SLOT(gotTypingB()));
		connect(b, SIGNAL(stopped()), this, SLOT(gotStoppedB()));
	}
	b->begin();
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
	int cnt = instance->getCount();
	QString countstr = "";
	countstr.append(QLocale(QLocale::English).toString((double)cnt, 'f', 0));
	countstr.append(" strangers online");
	count = new QLabel(countstr, status);
	status->addPermanentWidget(count);

	connect(instance, SIGNAL(countChanged()), this, SLOT(updateStatus()));
	
	return status;
}

void TextWindow::lwrite(QString text)
{
	bool ascroll = (lscroll->value() == lscroll->maximum());
	lconvo->append(text);
	if(ascroll) lscroll->setValue(lscroll->maximum());
}
void TextWindow::rwrite(QString text)
{
	bool ascroll = (rscroll->value() == rscroll->maximum());
	rconvo->append(text);
	if(ascroll) rscroll->setValue(rscroll->maximum());
}

void TextWindow::updateStatus()
{
	int cnt = instance->getCount();
	QString countstr = "";
	countstr.append(QLocale(QLocale::English).toString((double)cnt, 'f', 0));
	countstr.append(" strangers online");
	count->setText(countstr);
}

void TextWindow::sendDisconnectA()
{
	a->disconnect();
}
void TextWindow::sendDisconnectB()
{
	b->disconnect();
}
void TextWindow::sendDisconnectE()
{
	sendDisconnectA();
	sendDisconnectB();
}
void TextWindow::sendConnectA()
{
	sendDisconnectA();
	a->begin();
}
void TextWindow::sendConnectB()
{
	sendDisconnectB();
	b->begin();
}
void TextWindow::sendConnectE()
{
	sendDisconnectE();
	sendConnectA();
	sendConnectB();
}

void TextWindow::gotConnectA()
{
	lwrite("<strong>You're now chatting with a random stranger. Say hi!</strong>");
}
void TextWindow::gotConnectB()
{
	rwrite("<strong>You're now chatting with a random stranger. Say hi!</strong>");
}
void TextWindow::gotMessageA(QString message) // Recieved from A, to send to B
{
	lwrite("<strong style='color:red'>You: </strong><span>"+message+"</span>");
	b->send(message);
	rwrite("<strong style='color:red'>Stranger: </strong><span>"+message+"</span>");
	ltyping->hide();
}
void TextWindow::gotMessageB(QString message)
{
	rwrite("<strong style='color:blue'>You: </strong><span>"+message+"</span>");
	a->send(message);
	lwrite("<strong style='color:blue'>Stranger: </strong><span>"+message+"</span>");
	rtyping->hide();
}
void TextWindow::gotDisconnectA()
{
	lwrite("<strong>This stranger has disconnected.</strong>");
}
void TextWindow::gotDisconnectB()
{
	rwrite("<strong>This stranger has disconnected.</strong>");
}
void TextWindow::gotTypingA()
{
	ltyping->show();
	b->type();
}
void TextWindow::gotTypingB()
{
	rtyping->show();
	a->type();
}
void TextWindow::gotStoppedA()
{
	ltyping->hide();
	b->stop();
}
void TextWindow::gotStoppedB()
{
	rtyping->hide();
	a->stop();
}

void TextWindow::spoolA()
{
	QString message = leftbox->text();
	leftbox->clear();

	if(!message.isEmpty()) gotMessageA(message);
}
void TextWindow::spoolB()
{
	QString message = rightbox->text();
	rightbox->clear();

	if(!message.isEmpty()) gotMessageB(message);
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

