#include "selector.h"

void Selector::updateCount(int cnt)
{
	count = cnt;
	QString title = "Fromegle - ";
	title.append(QLocale(QLocale::English).toString((double)cnt, 'f', 0));
	title.append(" strangers online");
	setWindowTitle(title);
}

void Selector::updateQueueTimes(double spye, double spy)
{
	// True lean favours spy
	if((spy < 2) && (spye < 2)) lean = (rand() % 4) == 0;
	else if(spy > spye) lean = false;
	else lean = true;

	textc->setFont(QFont(0, 0, QFont::Bold));
	if(lean)
	{
		spyee->setFont(QFont(0, 0, QFont::Normal));
		quest->setFont(QFont(0, 0, QFont::Bold));
	}
	else
	{
		spyee->setFont(QFont(0, 0, QFont::Bold));
		quest->setFont(QFont(0, 0, QFont::Normal));
	}
	video->setFont(QFont(0, 0, QFont::Bold));
}

void Selector::updateTimestamp(double ts)
{
	timestamp = ts;
}

void Selector::updateServers(QStringList list)
{
	servers = list;
	textc->setEnabled(true);
	spyee->setEnabled(true);
	quest->setEnabled(true);
	video->setEnabled(false);
}

Selector::Selector(QApplication *app) : QWidget(),
										qapp(app),
										X(16), Y(16),
										W(128), H(32),
										poller()
{
	connect(&poller, SIGNAL(count(int)), this, SLOT(updateCount(int)));
	connect(&poller, SIGNAL(queuetimes(double, double)), this, SLOT(updateQueueTimes(double, double)));
	connect(&poller, SIGNAL(timestamp(double)), this, SLOT(updateTimestamp(double)));
	connect(&poller, SIGNAL(servers(QStringList)), this, SLOT(updateServers(QStringList)));

	textc = new QPushButton("&Text Chat", this);
	textc->setGeometry(X, Y, W, H-2);
	textc->setEnabled(false);
	textc->setToolTip("Talk to Strangers!");

	spyee = new QPushButton("&Spy Mode", this);
	spyee->setGeometry(X, Y+(H), W, H-2);
	spyee->setEnabled(false);
	spyee->setToolTip("Answer questions with another stranger!");

	quest = new QPushButton("&Question Mode", this);
	quest->setGeometry(X, Y+(2*H), W, H-2);
	quest->setEnabled(false);
	quest->setToolTip("Watch two strangers discuss your question!");

	video = new QPushButton("&Video Chat", this);
	video->setGeometry(X, Y+(3*H), W, H-2);
	video->setEnabled(false);
	video->setToolTip("Video Chat with Strangers!");

	connect(textc, SIGNAL(clicked()), this, SLOT(initTextc()));
	connect(spyee, SIGNAL(clicked()), this, SLOT(initSpyee()));
	connect(quest, SIGNAL(clicked()), this, SLOT(initQuest()));
	connect(video, SIGNAL(clicked()), this, SLOT(initVideo()));
}

Selector::~Selector()
{
	;
}

void Selector::initTextc()
{
	std::cout << "Entering Text Mode..." << std::endl;

	new TextWindow(this);
}

void Selector::initSpyee()
{
	std::cout << "Entering Spy Mode..." << std::endl;
}
void Selector::initQuest()
{
	std::cout << "Entering Question Mode..." << std::endl;
}
void Selector::initVideo()
{
	std::cout << "Entering Video Mode..." << std::endl;
	std::cout << "ERROR: Not Implemented!" << std::endl;
	QMessageBox *e = new QMessageBox(this);
	e->setText("ERROR");
	e->setInformativeText("Not Implemented!\n\nAnd how did you even get here?!");
	e->show();
}

QString Selector::randomServer()
{
	return servers[rand() % servers.size()];
}

int Selector::getCount()
{
	return count;
}

QApplication* Selector::app()
{
	return qapp;
}

int main(int argc, char *argv[])
{
	const int WIDTH = 158;
	const int HEIGHT = 160;

	QApplication app(argc, argv);

	QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

	QDesktopWidget *desktop = QApplication::desktop();

	int x = (desktop->width() - WIDTH) / 2;
	int y = (desktop->height() - HEIGHT) / 2;

	Selector *sel = new Selector(&app);
	sel->setFixedSize(WIDTH, HEIGHT);
	sel->move(x, y);
	sel->setWindowTitle("Loading...");
	sel->setToolTip("Select a mode");
	sel->setWindowIcon(QIcon("icon.png"));
	sel->show();

	return app.exec();
}

