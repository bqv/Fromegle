#include "selector.h"
#include "text.h"

void Selector::initText()
{
	const int WIDTH = 512;
	const int HEIGHT = 512;

	std::cout << "Entering Text Mode..." << std::endl;
	hide();

	QDesktopWidget *desktop = QApplication::desktop();

	int x = (desktop->width() - WIDTH) / 2;
	int y = (desktop->height() - HEIGHT) / 2;

	TextWindow *text = new TextWindow();
	text->setFixedSize(WIDTH, HEIGHT);
	text->move(x, y);
	text->setWindowTitle("Fromegle - Text Chat");
	text->setWindowIcon(QIcon("icon.png"));
	text->show();
}

TextWindow::TextWindow(QWidget *parent) : QWidget(parent)
{
	;
}
