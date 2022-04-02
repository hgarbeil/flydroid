#ifndef MIRRORCONFIGDIALOG_H
#define MIRRORCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class MirrorConfigDialog;
}

class MirrorConfigDialog : public QDialog
{
    Q_OBJECT


public:
    float startAngle, endAngle, increment, scale, off ;
    explicit MirrorConfigDialog(QWidget *parent = 0);
    void getAngles (float *, float *, float *) ;
    void setAngles (float, float, float) ;
    void setScanScaleOff (float off, float scale) ;
    void getScanConfig (float *scanoff, float *scanscale) ;
    ~MirrorConfigDialog();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::MirrorConfigDialog *ui;
};

#endif // MIRRORCONFIGDIALOG_H
