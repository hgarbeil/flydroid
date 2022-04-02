#include "plotlimitsdlg.h"
#include "ui_plotlimitsdlg.h"

PlotLimitsDlg::PlotLimitsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotLimitsDlg)
{
    ui->setupUi(this);
    nscans = 0 ;
}

PlotLimitsDlg::~PlotLimitsDlg()
{
    delete ui;
}

void PlotLimitsDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void PlotLimitsDlg::setValues (float dnmin, float dnmax, float ppmmmin, float ppmmmax, int nscans){

    QString str ;
    str.sprintf ("%5.0f", dnmin) ;
    ui->DNMinLE->setText(str) ;
    str.sprintf ("%5.0f", dnmax) ;
    ui->DNMaxLE->setText(str) ;

    str.sprintf ("%5.0f", ppmmmin) ;
    ui->PPMMMinLE->setText(str) ;
    str.sprintf ("%5.0f", ppmmmax) ;
    ui->PPMMMaxLE->setText(str) ;
    str.sprintf ("%d", nscans);
    ui->nscansPlotLE->setText(str) ;

}

void PlotLimitsDlg::on_buttonBox_accepted()
{
    dnMax = ui->DNMaxLE->text().toFloat() ;
    dnMin = ui->DNMinLE->text().toFloat() ;
    ppmmMax = ui->PPMMMaxLE->text().toFloat() ;
    ppmmMin = ui->PPMMMinLE->text().toFloat() ;
    nscans = ui->nscansPlotLE->text().toInt() ;


}
