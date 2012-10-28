#include "selector.h"

void Selector::updateCount(int cnt)
{
	count = cnt;
	QString title = "Fromegle - ";
	title.append(QLocale(QLocale::English).toString((double)cnt, 'f', 0));
	title.append(" strangers online");
	setWindowTitle(title);
}

void Selector::updateQueueTimes(double spyee, double spy)
{
	spyeeQueue = spyee;
	spyQueue = spy;
}

void Selector::updateTimestamp(double ts)
{
	timestamp = ts;
}

void Selector::updateServers(QStringList list)
{
	servers.swap(list);
	QString server = servers[rand() % servers.size()];
	std::cout << "Random server: " << server.toStdString() << std::endl;
}

Selector::Selector(QWidget *parent) : QWidget(parent),
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
	textc->setToolTip("Talk to Strangers!");

	spyee = new QPushButton("&Spy Mode", this);
	spyee->setGeometry(X, Y+(H), W, H-2);
	spyee->setToolTip("Answer questions with another stranger!");

	quest = new QPushButton("&Question Mode", this);
	quest->setGeometry(X, Y+(2*H), W, H-2);
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

int main(int argc, char *argv[])
{
	const int WIDTH = 158;
	const int HEIGHT = 160;

	QApplication app(argc, argv);

	Selector selector;

	QDesktopWidget *desktop = QApplication::desktop();

	int x = (desktop->width() - WIDTH) / 2;
	int y = (desktop->height() - HEIGHT) / 2;

	selector.setFixedSize(WIDTH, HEIGHT);
	selector.move(x, y);
	selector.setWindowTitle("Fromegle");
	selector.setToolTip("Select a mode");
	selector.setWindowIcon(QIcon("icon.png"));
	selector.show();

	return app.exec();
}
