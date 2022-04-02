#ifndef MYPPMMPLOT_H
#define MYPPMMPLOT_H
#include "qcustomplot.h"
#include <QTime>
#include <QList>
#include <QVector>



class MyPPMMPlot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit MyPPMMPlot(QWidget *parent = 0);
    void dummyPlot () ;
    void setYAxisScale (int l, int h) ;
    void setRadiusScale (float f) ;
    void setAngles (int lo, int hi, int inc);
    void setNScansToPlot(int) ;
    void plotData (QList<QTime>time, QVector<double>ppmm) ;
    void plotData  (QVector<double> xvals, QVector<double>yvals) ;
    void plotPolarData (QVector<double>angle, QVector<double>yvals);
    void plotPolarData (double angle, double yvals);
    void setPolarScales() ;
    void togglePlotType (bool pFlag);
    QVector <double> x,y ;
    QCPCurve *radarCurve ;
    QCPItemLine *endPtr ;
    QCPItemText *qcptxtfull, *qcptxthalf, *lzeroAz, *lfullAz ;
    int npts, numAngles, startAng, endAng, incAng, nscansToPlot ;
    bool polarFlag, updateFlag ;
    float radScale ;

signals:
    
public slots:
    
};

#endif // MYPPMMPLOT_H
