#ifndef PLOTLIMITSDLG_H
#define PLOTLIMITSDLG_H

#include <QDialog>

namespace Ui {
class PlotLimitsDlg;
}

class PlotLimitsDlg : public QDialog
{
    Q_OBJECT

    
public:
    float ppmmMax, ppmmMin,  dnMax, dnMin, nscans ;
    void setValues (float dnmin, float dnmax,  float ppmmmin, float ppmmmax, int nscans) ;
    explicit PlotLimitsDlg(QWidget *parent = 0);
    ~PlotLimitsDlg();
    
protected:
    void changeEvent(QEvent *e);
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::PlotLimitsDlg *ui;
};

#endif // PLOTLIMITSDLG_H
