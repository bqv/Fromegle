#include "selector.h"

Selector::Selector(QWidget *parent) : QWidget(parent)
{
	const int X = 16;
	const int Y = 16;
	const int W = 128;
	const int H = 32;

	QPushButton *text = new QPushButton("Text Chat", this);
	text->setGeometry(X, Y, W, H-2);

	QPushButton *spye = new QPushButton("Spy Mode", this);
	spye->setGeometry(X, Y+(H), W, H-2);

	QPushButton *quest = new QPushButton("Question Mode", this);
	quest->setGeometry(X, Y+(2*H), W, H-2);

	QPushButton *video = new QPushButton("Video Chat", this);
	video->setGeometry(X, Y+(3*H), W, H-2);
	video->setEnabled(false);

	connect(text, SIGNAL(clicked()), this, SLOT(initText()));
	connect(spye, SIGNAL(clicked()), this, SLOT(initSpye()));
	connect(quest, SIGNAL(clicked()), this, SLOT(initQuest()));
	connect(video, SIGNAL(clicked()), this, SLOT(initVideo()));
}

void Selector::initText()
{
	std::cout << "Entering Text Mode..." << std::endl;
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
}

int main(int argc, char *argv[])
{

	const int WIDTH = 158;
	const int HEIGHT = 160;

	QApplication app(argc, argv);

	Selector selector;

	QDesktopWidget *desktop = QApplication::desktop();

	int screenWidth = desktop->width();
	int screenHeight = desktop->height();

	int x = (screenWidth - WIDTH) / 2;
	int y = (screenHeight - HEIGHT) / 2;

	selector.setFixedSize(WIDTH, HEIGHT);
	selector.move(x, y);
	selector.setWindowTitle("Fromegle");
	selector.setToolTip("Select a mode");
	selector.setWindowIcon(QIcon("icon.png"));
	selector.show();

	return app.exec();
}
