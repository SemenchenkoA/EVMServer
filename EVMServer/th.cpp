#include "th.h"

Th::Th(QObject *parent) : QThread(parent){
	server = new Server();
	connect(server, SIGNAL(refreshGraph()), this, SLOT(sendToGUIFunc()));
}

Th::~Th(){
	if(server != NULL) delete [] server;
	server = 0;
}

void Th::run(){//not used
	server->setServerStopped(false);
	qDebug("Run thread");
}

void Th::stop(){
	server->setServerStopped(true);
	server->disconnect();
	qDebug("stop th");
}

void Th::sendToGUIFunc(){
	qDebug("emit send to gui");
	emit sendToGUI(0);
}

void Th::stopPloting(){
	if(server != NULL){
		server->endPlotting();
	}else{
		//error
	}
}

bool Th::startWorkServer(){
	if(server!=NULL){
		server->setServerParameters(getPort(), getSignalLength());
		server->startListen();

		return true;
	}else{
		//error emit error message
		return false;
	}
}

void Th::setSignalLength(int length){
	this->signalLength = length;
}

int Th::getSignalLength(){
	return this->signalLength;
}

void Th::setPort(int port){
	this->port = port;
}

int Th::getPort(){
	return this->port;
}
