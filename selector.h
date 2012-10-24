#ifndef _SELECTOR_H_
#define _SELECTOR_H_

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
		void initSpye();
		void initQuest();
		void initVideo();
};

#endif
