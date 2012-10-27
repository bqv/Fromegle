#include "selector.h"

void Selector::updateCount(int cnt)
{
	count = cnt;
}
void Selector::updateServers(int cnt, QString srv[])
{
	if((cnt < 0) || (cnt > 8)) return;
	for(int i=0; i < cnt; i++) //could just use cnt here...
	{
		servers[i] = srv[i];
	}
	serverct = cnt;
}

Selector::Selector(QWidget *parent) : QWidget(parent),
									  X(16), Y(16),
									  W(128), H(32),
									  poller(),
									  servers(new QString[8])
{
	QPushButton *text = new QPushButton("&Text Chat", this);
	text->setGeometry(X, Y, W, H-2);
	text->setToolTip("Talk to Strangers!");

	QPushButton *spye = new QPushButton("&Spy Mode", this);
	spye->setGeometry(X, Y+(H), W, H-2);
	spye->setToolTip("Answer questions with another stranger!");

	QPushButton *quest = new QPushButton("&Question Mode", this);
	quest->setGeometry(X, Y+(2*H), W, H-2);
	quest->setToolTip("Watch two strangers discuss your question!");

	QPushButton *video = new QPushButton("&Video Chat", this);
	video->setGeometry(X, Y+(3*H), W, H-2);
	video->setEnabled(false);
	quest->setToolTip("Video Chat with Strangers!");

	connect(text, SIGNAL(clicked()), this, SLOT(initText()));
	connect(spye, SIGNAL(clicked()), this, SLOT(initSpye()));
	connect(quest, SIGNAL(clicked()), this, SLOT(initQuest()));
	connect(video, SIGNAL(clicked()), this, SLOT(initVideo()));
}

void Selector::initSpye()
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
