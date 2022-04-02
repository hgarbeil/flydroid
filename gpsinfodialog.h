#ifndef GPSINFODIALOG_H
#define GPSINFODIALOG_H

#include <QDialog>
#include <QTimer>
//#include "mygps.h"
#include "qgpsdevice.h"
namespace Ui {
class GPSInfoDialog;
}

class GPSInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GPSInfoDialog(QWidget *parent = 0);
    ~GPSInfoDialog();
    void setGPS (QGPSDevice *) ;
    QTimer *qtim ;
    QGPSDevice *gps ;
    
private:
    Ui::GPSInfoDialog *ui;
private slots :
    void updateGUI() ;
};

#endif // GPSINFODIALOG_H
