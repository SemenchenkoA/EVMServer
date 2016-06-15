#ifndef TH_H
#define TH_H

#include <QThread>

#include "server.h"
/*!
	\brief Thread class

	Thread for tcp server
*/
class Th : public QThread
{
	Q_OBJECT

public:
	Server *server;///<Server pointer

	Th(QObject *parent);///<Counstructor
	~Th();///<Destructor

	void setSignalLength(int length);///<Set signal length
	int getSignalLength();///<Get signal length
	void setPort(int port);///<Set port
	int getPort();///<Get port
	
	void stop();///<Using for disconnect server
	void stopPloting();///<Say server about drawing plot was ended
	bool startWorkServer();///<Say server start listen
private:
	void run();///<Run thread (call from start())

	int signalLength;///<Length for signal batch
	int port;///<Port value for server
public slots:
	void sendToGUIFunc();///<Send signal in gui thread - start drawing plot
signals:
	void sendToGUI(int mode);///<Singal - can drawing on gui plot
};

#endif // TH_H
