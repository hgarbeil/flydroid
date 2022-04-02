#include "myppmmplot.h"
#define deg2rad 3.141593/180.

MyPPMMPlot::MyPPMMPlot(QWidget* parent) :
    QCustomPlot(parent)
{
    addGraph() ;
    addGraph() ;
    addGraph() ;
    radarCurve = new QCPCurve (xAxis, yAxis) ;

    lzeroAz = new QCPItemText (this) ;
    lfullAz = new QCPItemText (this) ;
    endPtr = new QCPItemLine (this) ;
    endPtr->setPen (QPen(Qt::red)) ;
    endPtr->start->setCoords(0,0) ;
    addPlottable (radarCurve) ;
    qcptxthalf = new QCPItemText (this) ;
    qcptxtfull = new QCPItemText (this) ;
    this->addItem (qcptxthalf) ;
    this->addItem (qcptxtfull) ;
    //addPlottable (endPtr) ;
    addItem (endPtr) ;
    npts = 100 ;
    //this->setAxisScale (QwtPlot::xBottom, 0, 100) ;
    xAxis->setRange (0, npts) ;
    yAxis->setLabel("PPMM");
    xAxis->setLabel("Scan");
    numAngles = 19 ;
    startAng = 0 ;
    endAng = 180 ;
    incAng = 10 ;
    radScale = 1500 ;
    nscansToPlot = 200 ;

    x.fill (0, numAngles);
    y.fill (0, numAngles) ;
    polarFlag = false ;
    updateFlag = false ;




}


void MyPPMMPlot::setYAxisScale (int low, int high) {

    yAxis->setRange (low, high) ;
    QString str, str1 ;


    replot() ;
}

void MyPPMMPlot::setNScansToPlot (int n){
    nscansToPlot = n ;
    updateFlag = true ;

}

void MyPPMMPlot::setRadiusScale (float rval) {
    radScale = rval ;
    QString str, str1 ;
    str = QString("%1").arg(radScale);
    str1 = QString("%1").arg(radScale/2);
    qcptxthalf->setText(str1) ;
    qcptxtfull->setText(str) ;

    replot() ;
}

void  MyPPMMPlot::plotData  (QVector<double> xvals, QVector<double>yvals) {
    int min, minRange ;

    int ival = xvals.count() ;
    if (ival < 5) {
        xAxis->setRange (0, nscansToPlot) ;
    }


    if (ival >= nscansToPlot) {

        xAxis->setRange (ival - nscansToPlot, ival+1) ;
    }

    if (updateFlag){
        if (ival < nscansToPlot){
            xAxis->setRange (0, nscansToPlot) ;

        }
        updateFlag = false ;
    }

    graph(0)->setData (xvals, yvals) ;

    replot() ;
}


void MyPPMMPlot::plotData  (QList<QTime>ltime, QVector<double>lppmm) {

    int i, npts = ltime.count() ;
    //double *x = new double [npts] ; // time in fractional hours
    double val ;

    QTime t0 ;
    QVector<double>timeVec ;
    //foreach (QList<QTime>t_titem, ltime){

    //}

    for (i=0; i<npts; i++) {
        t0 = ltime.at(i) ;
        val = t0.hour()+t0.minute()/60.+t0.second()/3600. ;
        timeVec.append (val) ;
    }
    graph(0)->setData (timeVec, lppmm) ;
}

void MyPPMMPlot::setAngles (int lo, int hi, int inc){
    numAngles = int(float(hi-lo)/ inc) + 1 ;
    startAng = lo ;
    endAng = hi ;
    incAng = inc ;
    x.clear() ;
    y.clear() ;
    x.fill (0, numAngles);
    y.fill (0, numAngles) ;
}


void MyPPMMPlot::setPolarScales (){
    QVector <double> xtmp, ytmp, xtmp1, ytmp1 ;


    QString str, str1 ;
    str = QString("%1").arg(radScale);
    str1 = QString("%1").arg(radScale/2);
    qcptxthalf->setText(str1) ;
    qcptxtfull->setText(str) ;
    lzeroAz->setText("0");
    lfullAz->setText("180") ;

    qcptxtfull->position->setType(QCPItemPosition::ptAxisRectRatio);
    qcptxthalf->position->setType(QCPItemPosition::ptAxisRectRatio);
    qcptxthalf->position->setCoords (.5, .55);
    qcptxtfull->position->setCoords (.5, .05);
    lzeroAz->position->setType(QCPItemPosition::ptAxisRectRatio);
    lfullAz->position->setType(QCPItemPosition::ptAxisRectRatio);
    lzeroAz->position->setCoords (.1, .95);
    lfullAz->position->setCoords (.85, .95) ;
    //qcptxtfull->setPen(QPen(Qt::black)) ;




    graph(0)->setPen(QPen (Qt::red)) ;
    graph(1)->setPen(QPen (Qt::red,1,Qt::DotLine)) ;
    this->xAxis->grid()->setPen(Qt::NoPen) ;
    this->yAxis->grid()->setPen(Qt::NoPen) ;
    this->xAxis->grid()->setZeroLinePen (QPen(Qt::red ,1, Qt::DashLine)) ;
    this->xAxis->setRange (-700, 800) ;
    this->yAxis->setRange (0, 500) ;

    this->xAxis->setTicks (false) ;
    this->yAxis->setTicks (false) ;

    xAxis->setLabel("");
    yAxis->setVisible (false) ;

    for (int i=0; i<180; i++)
    {
        xtmp.append (cos(float(i)*deg2rad) * 500) ;
        ytmp.append (sin(float(i)*deg2rad) * 500) ;
        xtmp1.append (cos(float(i)*deg2rad) * 250) ;
        ytmp1.append (sin(float(i)*deg2rad) * 250) ;

    }
    graph(0)->setData(xtmp, ytmp) ;
    graph(1)->setData(xtmp1, ytmp1) ;

    replot() ;
    polarFlag = true ;
}


void MyPPMMPlot::togglePlotType (bool pFlag){
    polarFlag = pFlag ;
    if (polarFlag){
        setPolarScales() ;
        lzeroAz->setVisible(true) ;
        lfullAz->setVisible(true) ;
        graph(0)->setVisible (true);
        graph(0)->setPen(QPen(Qt::red)) ;
        graph(1)->setVisible(true);
        graph(2)->setVisible (true);
        qcptxthalf->setVisible (true) ;
        qcptxtfull->setVisible (true) ;
        radarCurve->setVisible(true);
        endPtr->setVisible(true) ;
    } else {
        QString str, str1 ;
        str = QString("") ;
        str1 = QString("") ;
        qcptxthalf->setText(str1) ;
        qcptxtfull->setText(str) ;


        lzeroAz->setVisible(false) ;
        lfullAz->setVisible(false) ;
        xAxis->setTicks (true);
        yAxis->setTicks (true);
        xAxis->setRange (0., nscansToPlot);
        npts = nscansToPlot ;

        yAxis->setLabel("PPMM");
        xAxis->setLabel("Scan");
        yAxis->setVisible (true) ;
        yAxis->setRange(0., this->radScale) ;
        graph(0)->setVisible (true);
        graph(0)->setPen(QPen(Qt::black)) ;
        graph(1)->setVisible (false);
        graph(2)->setVisible (false);
        radarCurve->setVisible(false);
        endPtr->setVisible(false) ;


    }
    replot() ;
}


/***
 * for polar plot, xvals is azimuth, yvals is the ppmm which will be scaled by radscale
 *
 */
void MyPPMMPlot::plotPolarData (QVector<double>xvals, QVector<double>yvals){
    int i, npts, ind ;
    double xvalue, yvalue ;

    npts = xvals.count();
    for (i=npts-numAngles; i<npts; i++){
        if (i<0) continue ;
        ind = (xvals[i] - this->startAng ) / incAng ;

        xvalue = cos (xvals[i] * deg2rad) * yvals[i]/ radScale * 500.  ;
        yvalue = sin (xvals[i]* deg2rad) * yvals[i] / radScale * 500 ;
        x[ind] = xvalue ;
        y[ind] = yvalue ;
        //y.append(yvalue) ;
        //qDebug ()<< xvals[i]<< "  " << yvals[i]<< "  " <<xvalue << " "<< yvalue ;

    }

    //graph(0)->setData(x,y) ;
    radarCurve->setData(x,y) ;
    replot() ;

}


void MyPPMMPlot::plotPolarData (double angle, double ppmm){
    int i, npts, ind ;
    double xvalue, yvalue ;



    ind = (angle - this->startAng ) / incAng ;

    //qDebug () << angle << "  " << ind ;
    angle = 180. - angle ;
    xvalue = cos (angle * deg2rad) * 500.  ;
    yvalue = sin (angle * deg2rad)  * 500 ;
    y[ind] = sin (angle * deg2rad) * ppmm / radScale * 500 ;
    x[ind] = cos (angle * deg2rad) * ppmm/ radScale * 500.  ;



    //graph(0)->setData(x,y) ;
    radarCurve->setData(x,y) ;
    endPtr->end->setCoords(xvalue, yvalue) ;
    replot() ;
    //for (i=0; i<x.count(); i++){
        //qDebug () << angle << " " << ind << "  " << x[i] << "  " << y[i]  ;
    //}

}

