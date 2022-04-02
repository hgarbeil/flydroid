#include "mirrorconfigdialog.h"
#include "ui_mirrorconfigdialog.h"

MirrorConfigDialog::MirrorConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MirrorConfigDialog)
{
    ui->setupUi(this);
}

MirrorConfigDialog::~MirrorConfigDialog()
{
    delete ui;
}

void MirrorConfigDialog::on_okButton_clicked()
{

    startAngle = ui->startangLE->text().toFloat () ;
    endAngle = ui->endangLE->text().toFloat () ;
    increment = ui->incLE->text().toFloat () ;
    scale = ui->mirScaleLE->text().toFloat () ;
    off = ui->mirOffLE->text().toFloat () ;
    this->accept() ;
    this->done (QDialog::Accepted) ;

}

void MirrorConfigDialog::on_cancelButton_clicked()
{
    this->done (QDialog::Rejected) ;
}

void MirrorConfigDialog::setAngles (float st, float end, float inc) {
    startAngle = st ;
    endAngle = end ;
    increment = inc ;
    ui->startangLE->setText (QString("%1").arg(startAngle));
    ui->endangLE->setText (QString("%1").arg(endAngle));
    ui->incLE->setText (QString("%1").arg(increment));
}


void MirrorConfigDialog::setScanScaleOff (float off, float scale){
    ui->mirOffLE->setText(QString("%1").arg(off));
    ui->mirScaleLE->setText(QString("%1").arg(scale));
}

void MirrorConfigDialog::getAngles (float *st, float *end, float *inc){

    *st = startAngle ;
    *end = endAngle ;
    *inc = increment ;

}
void MirrorConfigDialog::getScanConfig (float *scanoff, float *scanscale) {

    *scanoff = this->off ;
    *scanscale = this->scale ;
}
