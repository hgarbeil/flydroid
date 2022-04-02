#include "myplot.h"
#include <math.h>

MyPlot::MyPlot(QWidget *parent) :
    QCustomPlot(parent)
{
    for (int i=0; i<5; i++) addGraph() ;
    xAxis->setLabel("Pixel") ;
    yAxis->setLabel("DN") ;

    l0 = new QCPItemLine (this) ;
    l1 = new QCPItemLine (this) ;
    h0 = new QCPItemLine (this) ;
    h1 = new QCPItemLine (this) ;
    graph(0)->setPen (QPen(Qt::yellow)) ;
    graph(1)->setPen (QPen(Qt::red)) ;
    graph(2)->setPen (QPen(Qt::green)) ;
    graph(3)->setPen (QPen(Qt::blue)) ;
    graph(4)->setPen (QPen(Qt::black)) ;
}


void MyPlot::detachCals (){
    int i ;
    for (i=0; i<4; i++)
        graph(i)->setVisible(false) ;
    replot() ;
}

void MyPlot::attachCals (){
    int i ;
    for (i=0; i<4; i++)
        graph(i)->setVisible(true) ;
}

void MyPlot::dummyPlot(){

    xvals.clear() ;
    yvals.clear() ;

    for (int i=0; i<360; i++){
        xvals.append(  float(i) * 2. * 3.1415 / 180.) ;
        yvals.append(sin(xvals[i])) ;

    }
    graph(0)->addData (xvals, yvals) ;
    this->replot() ;
}

void MyPlot::setYAxis (int low, int high) {
    yAxis->setRange (low, high) ;
    replot() ;
}

void MyPlot::setXAxis (int darkLow, int low, int high, int low1, int high1){
    xAxis->setRange (darkLow, high1+50) ;
    l0->setPen (QPen (Qt::green)) ;
    l0->start->setCoords (low, 0) ;
    l0->end->setCoords (low, 65500) ;
    h0->setPen (QPen (Qt::green)) ;
    h0->start->setCoords (high, 0) ;
    h0->end->setCoords (high, 65500) ;

    l1->setPen (QPen (Qt::red)) ;
    l1->start->setCoords (low1, 0) ;
    l1->end->setCoords (low1, 65500) ;
    h1->setPen (QPen (Qt::red)) ;
    h1->start->setCoords (high1, 0) ;
    h1->end->setCoords (high1, 65500) ;

    /*
    this->setAxisScale (QwtPlot::xBottom, low-50, high1+50, 50) ;
    QwtPlotMarker *vert = new QwtPlotMarker () ;
    vert->setLineStyle (QwtPlotMarker::VLine) ;
    vert->setLinePen (QPen(Qt::blue) ) ;
    vert->setXValue (low) ;
    vert->attach (this) ;
    QwtPlotMarker *vert1 = new QwtPlotMarker () ;
    vert1->setLineStyle (QwtPlotMarker::VLine) ;
    vert1->setLinePen (QPen(Qt::blue) ) ;
    vert1->setXValue (low1) ;
    vert1->attach (this) ;
    QwtPlotMarker *vert2 = new QwtPlotMarker () ;
    vert2->setLineStyle (QwtPlotMarker::VLine) ;
    vert2->setLinePen (QPen(Qt::red) ) ;
    vert2->setXValue (high) ;
    vert2->attach (this) ;
    QwtPlotMarker *vert3 = new QwtPlotMarker () ;
    vert3->setLineStyle (QwtPlotMarker::VLine) ;
    vert3->setXValue (high1) ;
    vert3->setLinePen (QPen(Qt::red) ) ;
    vert3->attach (this) ;
    */

}

void MyPlot::setAxisScale (float xmin, float xmax, float ymin, float ymax) {

    this->xAxis->setRange (xmin, xmax) ;
    this->yAxis->setRange (ymin, ymax);


}

void MyPlot::plotSpectrum (double *ydat, int npts){
    if (xvals.count() != npts || yvals.count() != npts){
        xvals.resize(npts) ;
        yvals.resize(npts) ;
    }

    for (int i=0; i<npts; i++) {
       xvals[i]= i ;
       yvals[i]= ydat[i] ;
    }
    graph(4)->setData (xvals,yvals) ;
    replot() ;

}


void MyPlot::setCals (double *dark, double *low, double *high, double *ref){

    int i ;
    double *x=new double [2048] ;
    darkv.clear() ;
    lowv.clear() ;
    refv.clear() ;
    xvals.clear() ;
    highv.clear() ;
    for (i=0; i<2048; i++) {
        xvals.append (i) ;
        darkv.append(dark[i] ) ;
        lowv.append(low[i] ) ;
        highv.append(high[i] ) ;
        refv.append(ref[i] ) ;
    }
    attachCals () ;
    graph(0)->setData (xvals,darkv) ;
    graph(1)->setData (xvals,lowv) ;
    graph(2)->setData (xvals,highv) ;
    graph(3)->setData (xvals,refv) ;
    replot() ;
    delete [] x ;

}
