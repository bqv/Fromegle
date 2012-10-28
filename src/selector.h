#ifndef _SELECTOR_H_
#define _SELECTOR_H_

#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QPushButton>
#include <QStringList>
#include <iostream>
#include <QString>
#include <QThread>
#include <QLocale>
#include <QWidget>
#include <QIcon>

#include "poll.h"
#include "text.h"

class Selector : public QWidget
{
	Q_OBJECT

	public:
		Selector(QWidget *parent = 0);

	public slots:
		void updateCount(long);
		void updateServers(QStringList);

	private slots:
		void initText();
		void initSpye();
		void initQuest();
		void initVideo();

	private:
		const int X, Y, W, H;
		PollThread poller;
		QStringList servers;
		long count;
};

#endif
