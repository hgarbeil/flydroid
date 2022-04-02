#ifndef MYPLOT_H
#define MYPLOT_H
//#include <qwt-qt4/qwt_plot.h>
//#include <qwt-qt4/qwt_plot_curve.h>
#include "qcustomplot.h"


class MyPlot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit MyPlot(QWidget *parent = 0);
    void dummyPlot() ;
    void plotSpectrum (double *, int) ;
    void setAxisScale (float min, float max, float ymin, float ymax) ;
    void setXAxis (int ll, int l, int h, int l1, int h1) ;
    void setYAxis (int l, int h) ;
    void setCals (double *dark, double *low, double *high, double *ref) ;
    QVector <double> darkv, lowv, highv, refv, scanv, xvals, yvals ;
    void detachCals() ;
    void attachCals() ;
    QCPItemLine *l0, *l1, *h0, *h1 ;
signals:
    
public slots:
    
};

#endif // MYPLOT_H
