#ifndef _STRANGER_H_
#define _STRANGER_H_

#include <QObject>
#include <QString>

class Stranger : public QObject
{
	Q_OBJECT

	public:
		enum StrangerType { Text, Spy, Question, Video };
		Stranger(StrangerType t = Text);
		~Stranger(){};

	signals:
		void message(QString);

	public slots:
		void send(QString){};

	private:
		const StrangerType type;
};

#endif
