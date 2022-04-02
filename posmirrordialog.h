#ifndef POSMIRRORDIALOG_H
#define POSMIRRORDIALOG_H

#include <QDialog>

namespace Ui {
class PosMirrorDialog;
}

class PosMirrorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PosMirrorDialog(QWidget *parent = 0);
    ~PosMirrorDialog();
    int mirrorPos ;
    void setMirrorPos (int);

    
protected:
    void changeEvent(QEvent *e);
    
private slots:
    void on_pushButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::PosMirrorDialog *ui;
};

#endif // POSMIRRORDIALOG_H
