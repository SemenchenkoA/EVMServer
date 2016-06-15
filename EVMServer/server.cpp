#include "server.h"

#include <iostream>
using namespace std;

Server::Server(QObject* parent ): QObject(parent){
	connect(&server, SIGNAL(newConnection()),
		this, SLOT(acceptConnection()));

	sCount = 0;
	nowPlotting = false;
	serverStopped = false;
//	real = NULL;
	pCount=0;
}

QVector<Signal> Server::getSignals(){
	return recSignals;
}

void Server::setServerParameters(int port, int signalLength){
	this->port = port;
	this->signalBatchSize = signalLength;
//	this->real = new double[signalLength*2];
}

bool Server::startListen(){
	if(!server.listen(QHostAddress::Any, port)){
		//error this port used already
		QMessageBox::critical(0, "Error", "This port used already. Change port and try again.");
		return false;
	}

	return true;
}

Server::~Server(){
	server.close();
}

void Server::acceptConnection(){
	client = server.nextPendingConnection();
	
	connect(client, SIGNAL(readyRead()),
		this, SLOT(startRead()));

	qDebug("accept connection");
}

int Server::getPacketCount(){
	return pCount;
}

void Server::startRead(){
	for(;;){
		if(!nowPlotting){//if now plotting graph, dont doing changes in real[]		
			if(sCount==0){
				signal.real = new double[signalBatchSize*2];
				if(pCount>=SAVED_BATCH){
					if(recSignals.at(0).real!=NULL)delete [] recSignals.at(0).real;

					recSignals.erase(recSignals.begin());
				}
				
				recSignals.push_back(signal);
				pCount++;
			}

			if(client->bytesAvailable() >= 8){
				if(client->isReadable()){
					QByteArray byteArray = client->read(8);
					
					/*
					QVector<double> data;
					QDataStream stream(byteArray);
					stream >> data;

					qDebug()<<"byteArray to double: "<<byteArray.toDouble();
					qDebug()<<"data size: "<<data.size();
					recSignals.at(recSignals.size()-1).real[sCount] = data.at(0);*/

					recSignals.at(recSignals.size()-1).real[sCount] = parseDouble(byteArray.constData());
					sCount++;
				}
			}else break;
		}else{//если сейчас рисуем
			//Sleep(1200);
			//continue;
		}

		if(sCount >= (signalBatchSize*2)){//32768*2
			sCount = 0;

			if(serverStopped) continue;

			nowPlotting = true;
			
			qDebug("Send refresh graph from server");
			emit refreshGraph();
		}
	}
}

void Server::endPlotting(){
	qDebug("nowPlotting = false");
	nowPlotting = false;
}

void Server::setServerStopped(bool stopped){
	this->serverStopped = stopped;
}

bool Server::getServerStopped(){
	return this->serverStopped;
}

double * Server::getReal(){
	return NULL;//this->real;
}

double Server::parseDouble(const char *s){
	double x = 0.0;
	double div = 1.0;
	double exp = 0.0;
	int    done = 0;
	int    state = 0;
	int    minus = 0;
	int    negexp = 0;
	const char  *cp = s;

	while(*cp != '\0' && !done)
	{
		switch(state)
		{
		case 0:
			if (isdigit(*cp))
			{
				x = (double)((*cp) - '0');
				state = 1;
			}
			else if (*cp == '-')
				minus = 1;
			break;
		case 1:
			if (*cp == '.')
				state = 2;
			else if (toupper(*cp) == 'E')
				state = 3;
			else if (isdigit(*cp))
			{
				x *= 10.0;    
				x += (double)((*cp) - '0');
			}                    
			else
				done = 1;
			break;
		case 2:
			if (isdigit(*cp))
			{
				div *= 10.0;
				x += ((double)((*cp) - '0')) / div;
			}
			else if (toupper(*cp) == 'E')
				state = 3;
			else
				done = 1;
			break;
		case 3: 
			if (*cp == '+')
			{
				negexp = 0;
				state = 4;
			}
			else if (*cp == '-')
			{
				negexp = 1;
				state = 4;
			}
			else if (isdigit(*cp))
			{
				exp = (double)((*cp) - '0');
				state = 4;
			}
			else
				done = 1;
			break;
		case 4:
			if (*cp == '.')
			{
				div = 1.0;
				state = 5;
			}    
			else if (isdigit(*cp))
			{
				exp *= 10.0;    
				exp += (double)((*cp) - '0');
			}                    
			else
				done = 1;
			break;
		case 5:
			if (isdigit(*cp))
			{
				div *= 10.0;
				x += ((double)((*cp) - '0')) / div;
			}
			else
				done = 1;
			break;
		}

		cp++;
	}

	if (minus)
		x = -x;

	if (exp != 0.0)
	{
		if (negexp)
			exp = - exp;
		x *= pow(10.0,exp);
	}
	else if (negexp)
		x = 1.0/x;

	return x;
}


