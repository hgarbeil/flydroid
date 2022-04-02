#include "serverconnectdlg.h"
#include "ui_serverconnectdlg.h"

ServerConnectDlg::ServerConnectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConnectDlg)
{
    ui->setupUi(this);
}

ServerConnectDlg::~ServerConnectDlg()
{
    delete ui;
}

void ServerConnectDlg::setPortString (QString str) {
    ui->portLE->setText (str) ;

}

void ServerConnectDlg::setServerString (QString str) {
    ui->serverLE->setText (str) ;

}


void ServerConnectDlg::changeEvent(QEvent *e)
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

void ServerConnectDlg::on_OKButton_clicked()
{
    this->setResult (QDialog::Accepted) ;
    serverString = ui->serverLE->text() ;
    portString = ui->portLE->text() ;
    this->accept() ;
    this->close() ;

}

void ServerConnectDlg::on_CancelButton_clicked()
{
    this->setResult (QDialog::Rejected) ;
    this->reject() ;
    this->close() ;
}
