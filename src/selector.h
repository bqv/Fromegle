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
#include <cstdlib>
#include <QIcon>

#include "poll.h"

class Selector : public QWidget
{
	Q_OBJECT

	public:
		Selector(QApplication *app = 0);
		~Selector();
		QString randomServer();
		int getCount();
		QApplication* app();

	public slots:
		void updateCount(int);
		void updateQueueTimes(double, double);
		void updateTimestamp(double);
		void updateServers(QStringList);

	private slots:
		void initTextc();
		void initSpyee();
		void initQuest();
		void initVideo();

	private:
		QApplication *qapp;
		const int X, Y, W, H;
		PollThread poller;
		QPushButton *textc, *spyee, *quest, *video;
		QStringList servers;
		double timestamp;
		bool lean;
		int count;
};

#include "text.h"

#endif
