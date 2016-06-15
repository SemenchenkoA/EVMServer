#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QVector>

#include <windows.h>

#include "Signal.h"

#define SAVED_BATCH 4

using namespace std;

/*!
	\brief Server

	Server for recive signal from EVM
*/
class Server: public QObject //все таки отдельный поток и работать с указателем на сервер Server * server = NULL а потом создаем где нужно
{
	Q_OBJECT
public:
	Server(QObject * parent = 0);///<Constructor
	~Server();///<Destructor
		
	void endPlotting();///<Set mark about end draw plot
	bool startListen();///<Say server start listen

	void setServerParameters(int port, int signalLength);///<Set server parameters port and signal length

	void setServerStopped(bool stopped);///<Set server stopped
	bool getServerStopped();///Get server stopped

	double* getReal();///<Get reals array data
	QVector<Signal> getSignals();///<Get collect of signals
	int getPacketCount();///<Get packet count
	
	QVector<Signal> recSignals;///<Received packets

	Signal signal;
private:
	//double *real;///<For saving received signal
	int sCount;///<Counter for real
	

	int signalBatchSize;///<Signal batch size
	int port;///<Port value for server

	bool nowPlotting;///<Using for checking now plot drawing or not
	bool serverStopped;///<Using for stop showing actual values on plot, but server not disconnected

	QTcpServer server;///<TcpServer
	QTcpSocket* client;///<Tcp socket client

	int pCount;///<Count of received packets

	double parseDouble(const char *s);///<Get double value from chars sequence
private slots:
	void acceptConnection();///<Catching connection
	void startRead();///<Start reading from client	
signals:
	void refreshGraph();///<Signal about can draw plot from newest values
};
#endif
