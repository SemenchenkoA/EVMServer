#include "evmserver.h"

EVMServer::EVMServer(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags){
	ui.setupUi(this);

	QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

	plot = new QwtPlot(tr("Спектр сигнала"),this);
	plot->setGeometry(10, 40, 800, 600);
	
	QPen sinPen = QPen(Qt::red);

	curve = new QwtPlotCurve;
	curve->setRenderHint(QwtPlotItem::RenderAntialiased);
	curve->setPen(sinPen);
	curve->attach(plot);

	plot->setAxisTitle(QwtPlot::xBottom, tr(""));
	plot->setAxisTitle(QwtPlot::yLeft, tr(""));
	plot->setAutoReplot(true);
	plot->setCanvasBackground(Qt::white);

	grid = new QwtPlotGrid;
	grid->enableXMin(true);
	grid->enableYMin(true);
	grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));
	grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
	grid->attach(plot);

	zoom = new QwtPlotZoomer(plot->canvas());
	zoom->setMousePattern(QwtEventPattern::MouseSelect1,Qt::LeftButton,Qt::ControlModifier);
	zoom->setSelectionFlags (QwtPicker::RectSelection & QwtPicker::DragSelection);
	zoom->setRubberBand(QwtPicker::RectRubberBand);
	zoom->setRubberBandPen(QPen(Qt::black,0,Qt::DashDotLine));

	stack.clear();
	stack.push_back(zoom->zoomRect());

	plot->setAxisAutoScale(QwtPlot::xBottom);
	plot->setAxisAutoScale(QwtPlot::yLeft);

	const QColor c(Qt::black);
	zoom->setTrackerPen(c);

	setDataOnPlot();

	connect(ui.connectBut, SIGNAL(clicked()), this, SLOT(clickConnect()));
	connect(ui.disconnectBut, SIGNAL(clicked()), this, SLOT(clickDisConnect()));

	connect(ui.pushLeft, SIGNAL(clicked()), this, SLOT(changePacketsLeft()));
	connect(ui.pushRight, SIGNAL(clicked()), this, SLOT(changePacketsRight()));

	ui.pushLeft->setEnabled(false);
	ui.pushRight->setEnabled(false);
	
	thread = NULL;	
	//x = NULL;
	//data = NULL;
	lrCount=0;
}

void EVMServer::checkLR(){
	ui.pushRight->setEnabled(false);

	if(thread->server->getPacketCount()>1)ui.pushLeft->setEnabled(true);
}

void EVMServer::changePacketsLeft(){
	lrCount--;

	if(thread->server->getSignals().size()-1+lrCount-1==0){
		ui.pushLeft->setEnabled(false);
	}

	ui.pushRight->setEnabled(true);

	setDataOnPlot_upd(-1);
}
void EVMServer::changePacketsRight(){
	lrCount++;

	if(thread->server->getSignals().size()-1+lrCount-1==thread->server->getSignals().size()-1-1){
		ui.pushRight->setEnabled(false);
	}

	ui.pushLeft->setEnabled(true); 

	setDataOnPlot_upd(-1);
}

void EVMServer::clickConnect(){ 
	bool connectBool = false;
	if(thread == NULL){
		thread = new Th(this);
		connect(thread, SIGNAL(sendToGUI(int)), this, SLOT(setDataOnPlot_upd(int)));	
	}else{
		
	}
	
	thread->setSignalLength(ui.spinLen->value());
	thread->setPort(ui.spinPort->value());
	connectBool = thread->startWorkServer();		

	lrCount = 0;

	qDebug("Click connect thread start");

	ui.connectBut->setEnabled(!connectBool);
	ui.disconnectBut->setEnabled(connectBool);
}

void EVMServer::clickDisConnect(){
	thread->stop();

	ui.connectBut->setEnabled(true);
	ui.disconnectBut->setEnabled(false);

	checkLR();
}

EVMServer::~EVMServer(){

}

void EVMServer::setDataOnPlot_upd(int mode){
	int dI = this->ui.spinLen->value() * 2;
	
	qDebug("Start setting data.");
	double *x = new double[ dI ];
	double *data = new double[ dI ];	
	qDebug("new done.");
	for(int i = 0; i < dI; i++){
			data[ i ] = thread->server->getSignals().at(thread->server->getSignals().size() - 1 + lrCount + mode).real[i];

			//mode это смещение т.к. если нажимаем влево вправо последним будет недополученный сигнал

			x[ i ] = i;
	}
	qDebug("start set on graph");
	curve->setData(x, data, dI);
	curve->setPaintAttribute(QwtPlotCurve::ClipPolygons);//
	qDebug("Start del.");
	if(x != NULL) delete [] x;
	if(data != NULL) delete [] data;

	qDebug("Set data on plot done.");
	//checkLR();
	
	if(thread != NULL)thread->stopPloting();
}

void EVMServer::setDataOnPlot(){//stub
	int dI = 200;
	double *x = new double[ dI ];
	double *data = new double[ dI ];

	for(int i = 0; i < dI; i++){
		data[i] = sin((double) i);
		x[i] = i;
	}

	curve->setData(x, data, dI);
	curve->setPaintAttribute(QwtPlotCurve::ClipPolygons);//
	if(x != NULL)delete [] x;
	if(data != NULL)delete [] data;
}

void EVMServer::wheelEvent(QWheelEvent* pe){
	if(!(pe->x() >= plot->x() && pe->x() <= plot->x() + plot->width() && pe-> y() >= plot->y() && pe->y() <= 120 + plot->height()))return;

	QwtScaleMap  xx=plot->canvasMap(QwtPlot::xBottom);
	QwtScaleMap  yy=plot->canvasMap(QwtPlot::yLeft);
	int x = pe->x() - plot->x();
	double xi = xx.invTransform(x);
	int y = pe->y() - plot->y();
	double yi = plot->invTransform(QwtPlot::yLeft,y);

	QwtDoubleRect rect=zoom->zoomRect();

	if(stack.size()==0)stack.push_back(rect);

	if(pe->delta()>0){
		rect.setWidth(rect.width()/2.);
		rect.moveCenter(QPointF(xi,yi));

		zoom->zoom(rect);

		stack.push_back(rect);
	}else{
		if(stack.size()!=0){
			zoom->zoom(stack.back());
			stack.pop_back();
		}
	}
	
	//if(stack.size()==0)plot->setAxisScale(QwtPlot::xBottom,0.,(double)dI, 100.);
}