#include "gpsinfodialog.h"
#include "ui_gpsinfodialog.h"


GPSInfoDialog::GPSInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GPSInfoDialog)
{
    ui->setupUi(this);
    qtim = new QTimer () ;
    qtim->setInterval (1000) ;

    connect (qtim, SIGNAL (timeout()), this, SLOT(updateGUI())) ;
    qtim->start () ;
    gps = NULL ;
}

GPSInfoDialog::~GPSInfoDialog()
{
    qtim->stop() ;
    delete ui;
}

void GPSInfoDialog::setGPS (QGPSDevice *m) {
    gps = m ;

}


void GPSInfoDialog::updateGUI() {
    if (!gps) return ;

    QString str ;
    //str.sprintf ("%f" , gps->time) ;
    ui->gpsPortLE->setText (*gps->timestring) ;
    ui->posLE->setText (*gps->posstring) ;
    switch (gps->fix) {
    case 0 :
        ui->FixLabel->setText ("NO FIX") ;
        ui->FixLabel->setStyleSheet ("background-color : rgb(255, 0, 0)") ;
        break ;
    case 1 :
        ui->FixLabel->setText ("FIX") ;
        ui->FixLabel->setStyleSheet ("background-color : rgb(0, 255, 0)") ;
        break ;
    default :
        ui->FixLabel->setText ("NO FIX") ;
        ui->FixLabel->setStyleSheet ("background-color : rgb(255, 0, 0)") ;
        break ;
    }
    str.sprintf ("%d" , gps->nSats) ;
    ui->nSatsLE->setText (str) ;
}
