#ifndef SERVERCONNECTDLG_H
#define SERVERCONNECTDLG_H

#include <QDialog>

namespace Ui {
class ServerConnectDlg;
}

class ServerConnectDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit ServerConnectDlg(QWidget *parent = 0);
    ~ServerConnectDlg();
    QString serverString, portString ;
    void setServerString (QString) ;
    void setPortString (QString) ;
    
protected:
    void changeEvent(QEvent *e);
    
private slots:
    void on_OKButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::ServerConnectDlg *ui;
};

#endif // SERVERCONNECTDLG_H
