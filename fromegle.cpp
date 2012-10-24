#include <QDesktopWidget>
#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <QWidget>
#include <QIcon>

class Selector : public QWidget
{
	Q_OBJECT

	public:
		Selector(QWidget *parent = 0);

	private slots:
		void initText();
};

Selector::Selector(QWidget *parent) : QWidget(parent)
{
	QPushButton *text = new QPushButton("Text Chat", this);
	text->setGeometry(50, 40, 150, 30);

	connect(text, SIGNAL(clicked()), this, SLOT(initText()));
}

void Selector::initText()
{
	;
}

int main(int argc, char *argv[])
{

	int WIDTH = 250;
	int HEIGHT = 150;

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
