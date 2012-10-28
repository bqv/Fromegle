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

QMenuBar* TextWindow::makeMenus()
{
	QMenuBar *menu = menuBar();
	menu->addMenu("&File");
	menu->addAction("&Exit");
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

