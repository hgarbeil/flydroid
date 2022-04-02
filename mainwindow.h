#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "myspectrometer.h"
#include "phidgetsMot.h"
#include "calscan.h"
#include "scanthread.h"
#include "repeatScan.h"
#include "gpsinfodialog.h"
#include "qgpsdevice.h"
#include "processso2.h"
#include "myinterfacekit.h"
#include "autoint.h"
#include "mysocket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MySpectrometer *mySpec ;
    phidgetsMot *pm ;
    CalScan *cscan ;
    ScanThread *scanthread ;
    repeatScan *repeatscan ;
    QGPSDevice *gps ;
    MySocket *mysocket ;
    myInterfaceKit *myIntKit ;
    ProcessSO2 *pso2 ;
    QString modeString, serverString, portString, gpsLabel, ancilLabel ;
    QString workDir ;
    GPSInfoDialog *gpsdlg ;
    AutoInt *aint ;
    int calFlag, intLevel, oldFix, numScans, voltOnlyFlag ;
    bool polarFlag ;
    void readParameterFile (char *) ;
    void writeParamFile (QString str);
    void setParamFile (char *) ;
    void setWorkDir (QString w) ;
    void setGPSFix (int) ;
    QVector <double>xvalsVec, yvalsVec ;
    float minPPMM, maxPPMM, minDN, maxDN, base_angle ;
    float startTime, endTime ;
    float startAngle, endAngle, incAngle ;
    QString paramFile, darkFile, lowFile, highFile, refFile ;
    
public slots :
    void setCellState (int) ;
    void satAlert (bool) ;
private slots:
    void on_AlertButton_clicked();
    void plotCal (int, double*) ;
    void plotScan (int, double*) ;
    void intChange (int) ;
    void getGPSInfo () ;
    void updateGUI() ;
    void setCalFlag (int) ;
    void on_scanButton_clicked();
    void filecal () ;
    void scanComplete () ;


    void on_autoIntButton_clicked();
    void auto_int_done(int) ;

    void on_actionProcess_Scanfile_triggered();

    void on_actionFull_Cal_triggered();

    void on_actionDark_Cal_triggered();

    void on_actionLow_Cal_triggered();

    void on_actionHigh_Cal_triggered();

    void on_actionRef_Cal_triggered();

    void on_actionSet_Working_Directory_triggered();

    void on_actionFile_Cale_triggered();

    void on_actionRead_Parameter_File_triggered();

    void on_actionPlots_triggered();

    void on_intCB_currentIndexChanged(const QString &arg1);

    //void on_checkBox_clicked();

    void on_stopButton_clicked();

    void on_insertLowButton_clicked();

    void on_insertHighButton_clicked();


    void on_repeatScanButton_clicked();

    void on_actionScan_Mirror_triggered();

    void on_actionPosition_Mirror_triggered();

    void on_actionScan_Parameters_triggered();

    void on_actionPolar_Plot_changed();

    void on_actionConnect_to_Server_triggered();


    void on_checkBox_2_clicked();

    void on_actionDisconnect_triggered();

    void on_timeSeriesRB_toggled(bool checked);

    void on_actionAbout_triggered();

    void on_MirrorScanCB_toggled(bool checked);

    void on_MirrorScanCB_clicked();

    void on_scanAvgCBox_stateChanged(int arg1);

    void on_scanAvgCBox_clicked();

    void reconServer() ;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
