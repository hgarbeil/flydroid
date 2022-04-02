#include "posmirrordialog.h"
#include "ui_posmirrordialog.h"
#include <QString>
PosMirrorDialog::PosMirrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PosMirrorDialog)
{
    ui->setupUi(this);
}

PosMirrorDialog::~PosMirrorDialog()
{
    delete ui;
}

void PosMirrorDialog::setMirrorPos(int val){
    QString str = QString ("%1").arg(val) ;

    ui->mirPosLE->setText (str) ;
    this->mirrorPos = val ;

}

void PosMirrorDialog::changeEvent(QEvent *e)
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


// Ok button - get value from the text edit
// set return value
// close
void PosMirrorDialog::on_pushButton_clicked()
{
    mirrorPos = ui->mirPosLE->text().toInt () ;
    this->accept() ;
    this->close() ;

}

void PosMirrorDialog::on_cancelButton_clicked()
{
    //this->setResult(QDialog::Rejected);
    this->reject() ;
    this->close() ;

}
