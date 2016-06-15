#ifndef EVMSERVER_H
#define EVMSERVER_H

#include <QtGui/QMainWindow>
#include "ui_evmserver.h"

#include <qtextcodec.h>
#include <QMouseEvent>

#include "QwT\qwt_plot.h"
#include "QwT\qwt_plot_curve.h"
#include "QwT\qwt_plot_grid.h"
#include "QwT\qwt_plot_zoomer.h"
#include "QwT\qwt_curve_fitter.h"
#include "QwT\qwt_scale_widget.h"
#include "QwT\qwt_color_map.h" 
#include "QwT\qwt_plot_marker.h"
#include "QwT\qwt_scale_widget.h"
#include "QwT\qwt_plot_layout.h"
#include "QwT\qwt_plot_panner.h"

#include "th.h"

/*!
	\brief Class GUI

	Class user interface, you can connect and disconnect with client (EVM) using socket connection.
	On the plot you can see received signal.

	\author SemenchenkoA
*/
class EVMServer : public QMainWindow{
	Q_OBJECT
public:
	EVMServer(QWidget *parent = 0, Qt::WFlags flags = 0);///<Constructor
	~EVMServer();///<Destructor
	
	Th *thread;///<Thread for server working
private:
	QwtPlot *plot;///<Plot for data
	QwtPlotCurve *curve;///<Curve for ploting
	QwtPlotGrid *grid;///<Grid for plot
	QwtPlotZoomer *zoom;///<Plot zoomer

	QVector<QwtDoubleRect> stack;///<Save imges of zoomer rectangles (not stack, vector)

	

	//double *x;///<X axis values
	//double *data;///<Y axis values (user data)

	int lrCount;///<Counter for change showing left-right plot

	void checkLR();///<Check position images on plot
private:
	Ui::EVMServerClass ui;

public slots:
	void setDataOnPlot();///<Set data on the plot (stub data on the app start)

	virtual void wheelEvent(QWheelEvent* pe);///<Catching wheel events for zoomer

	void clickConnect();///<Button click Connect function
	void clickDisConnect();///<Button click Disconnect function

	void setDataOnPlot_upd(int mode);///<Set data on the plot from EVM client
	void changePacketsLeft();
	void changePacketsRight();
};
#endif // EVMSERVER_H
