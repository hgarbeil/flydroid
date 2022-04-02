#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpsinfodialog.h"
#include "processso2.h"
#include "plotlimitsdlg.h"
#include "repeatscandialog.h"
#include "mirrorconfigdialog.h"
#include "posmirrordialog.h"
#include "serverconnectdlg.h"


#include <QFileDialog>
#include <stdio.h>
#include  <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    printf ("Starting interface ") ;
    ui->setupUi(this);

    mySpec = 0L ;
    mySpec = new MySpectrometer() ;

    pm = new phidgetsMot() ;
    pso2 = new ProcessSO2 () ;
    cscan = new CalScan () ;
    cscan->setObjects (mySpec, pm) ;
    cscan->setPlotWidget(ui->plotWidget) ;
    cscan->setPSO2(pso2) ;


    scanthread = new ScanThread () ;
    scanthread->setObjects (mySpec, pm) ;
    scanthread->setPlotWidget(ui->plotWidget, ui->ppmmWidget) ;


    repeatscan = new repeatScan () ;
    repeatscan->setObjects (mySpec, pm) ;
    repeatscan->setPlotWidget(ui->plotWidget, ui->ppmmWidget) ;

    aint = new AutoInt () ;
    aint->setSpec (mySpec) ;

    mySpec->setIntegrationTime (AutoInt::intlevels[2]) ;
    mySpec->setNScansAvg (AutoInt::nscansAvg[2]) ;

    mySpec->setIntLevel (2) ;

    pso2->setCals (cscan->dark, 0) ;
    pso2->setCals (cscan->low, 1) ;
    pso2->setCals (cscan->high, 2) ;
    pso2->setCals (cscan->ref, 3) ;

    pso2->setSatDN ((int)(mySpec->maxDN * .98)) ;
    gps = 0L;
    gps = new QGPSDevice (this) ;
    gps->setPort ("/dev/ttyUSB0") ;
    gpsLabel = "No GPS" ;
    ancilLabel = "V : 0.    T : 0." ;

    //gps->start();
    connect (cscan, SIGNAL(plotData(int, double*)),this, SLOT(plotCal(int, double*)) ) ;
    connect (scanthread, SIGNAL (plotData(int, double * )), this, SLOT(plotScan(int, double*))) ;
    connect (scanthread, SIGNAL(satAlert(bool)), this, SLOT(satAlert(bool))) ;
    connect (scanthread, SIGNAL(scanComplete()), this, SLOT(scanComplete())) ;
    connect (scanthread, SIGNAL (intChange(int)), this, SLOT(intChange(int))) ;

    connect (repeatscan, SIGNAL (plotData(int, double * )), this, SLOT(plotScan(int, double*))) ;
    connect (repeatscan, SIGNAL(satAlert(bool)), this, SLOT(satAlert(bool))) ;
    connect (repeatscan, SIGNAL(scanComplete()), this, SLOT(scanComplete())) ;
    connect (repeatscan, SIGNAL (intChange(int)), this, SLOT(intChange(int)) );
    connect (repeatscan, SIGNAL (reconnect()), this, SLOT (reconServer())) ;
    connect (cscan, SIGNAL(satAlert(bool)), this, SLOT(satAlert(bool))) ;
    connect (aint, SIGNAL(plotData(int, double*)),this, SLOT(plotCal(int, double*)) ) ;
    connect (aint, SIGNAL(complete(int)),this, SLOT(auto_int_done(int)) ) ;
    connect (ui->actionGPS, SIGNAL (triggered()), this, SLOT (getGPSInfo())) ;
    connect (ui->actionFileCal, SIGNAL(triggered()), this, SLOT (filecal())) ;
    connect (cscan, SIGNAL(calFlag(int)),this, SLOT(setCalFlag(int)) ) ;
    connect (pm, SIGNAL (cellState(int)), this, SLOT(setCellState(int)));
    modeString ="" ;
    workDir = "/home/odroid/data" ;
    calFlag = 0 ;
    minDN = 0 ;
    maxDN = 4095 ;
    if (mySpec->flagPlus)
        maxDN = 65000 ;
    minPPMM = 0 ;
    maxPPMM = 1500 ;
    intLevel = 2 ;
    startTime = 8. ;
    endTime = 15. ;
    ui->ppmmWidget->setYAxisScale (0, maxPPMM) ;
    ui->plotWidget->setAxisScale (0, 2048, 0, maxDN);
    ui->stopButton->setEnabled (false) ;
    ui->repeatScanButton->setEnabled(false);
    myIntKit = new myInterfaceKit () ;
    myIntKit->setLabel (&ancilLabel) ;

    numScans = 50000 ;
    ui->nscansLE->setText (QString ("%1").arg(numScans)) ;


    setCalFlag (calFlag) ;
    cscan->setModeString (&modeString) ;
    scanthread->setModeString (&modeString) ;
    scanthread->setPS (pso2) ;
    repeatscan->setModeString (&modeString) ;
    repeatscan->setPS (pso2) ;
    aint->setModeString (&modeString) ;
    QTimer *qtim = new QTimer () ;
    qtim->setInterval (300) ;
    connect (qtim, SIGNAL(timeout()),this, SLOT(updateGUI()) ) ;

    satAlert (false) ;
    setCellState (3) ;
    ui->GPSFixButton->setStyleSheet ("font:bold 12px;background-color:red;color:yellow;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
    ui->GPSFixButton->setText ("GPS- NoFix") ;
    ui->ServerStatusButton->setStyleSheet ("background-color:orange;color:black;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
    ui->ServerStatusButton->setText ("Server: Disconn.") ;
    oldFix = 0 ;
    startAngle = 20 ;
    endAngle = 160 ;
    incAngle = 20 ;
    voltOnlyFlag = 1 ;
    polarFlag = false ;
    pm->setMirrorAngles (startAngle, endAngle, incAngle) ;
    pm->scanHome() ;
    ui->ppmmWidget->setAngles (startAngle, endAngle, incAngle) ;
    serverString = "127.0.0.1" ;
    portString = "8890" ;
    mysocket = new MySocket () ;
    scanthread->setSocket (mysocket) ;
    repeatscan->setSocket (mysocket) ;
    repeatscan->setCalscan (this->cscan) ;
    scanthread->setCalscan (this->cscan) ;
    qtim->start() ;

    base_angle = 0. ;
    //cscan->autoDark() ;

}




MainWindow::~MainWindow()
{
    if (gps) {
        //gps->runGPS = false ;

    }

    delete ui;
    if (mySpec) {
        delete mySpec;
    }
    if (pm) delete pm ;


    if (gps) {
        //gps->terminate() ;
        //delete gps ;
    }
}
// actually full cal button
void MainWindow::on_AlertButton_clicked()
{
    //ui->statusLE->setText ("HELLO") ;
    QString filestring ;
    QTime qtim = QTime::currentTime () ;
    QDate qdat = QDate::currentDate() ;
    filestring.sprintf ("%s/Cal_%04d_%02d_%02d_%02d%02d", workDir.toLatin1().data(),qdat.year(), qdat.month(), qdat.day(), qtim.hour(), qtim.minute()) ;
    qDebug() << "Path is " << filestring  ;
    QString str = QFileDialog::getSaveFileName(this, "Dark File",filestring) ;
    if (str.length() <  1) return ;
    ui->plotWidget->detachCals () ;
    calFlag = 0 ;
    cscan->setFName (str) ;
    base_angle = pm->curAng ;

    //ui->plotWidget->dummyPlot () ;
    ui->AlertButton->setStyleSheet ("background-color:green;color:yellow") ;
    cscan->setMode (0) ;
    cscan->start() ;

    //pm->setPosition (90) ;



}

void MainWindow::setParamFile (char *ifil){
    readParameterFile(ifil) ;
}

void MainWindow::readParameterFile (char *ifile){

    char gpsdev[240] ;
    float lowCell, highCell, scanoff, caloff, scanscale ;
    float val0, val1 ;
    int d0, d1, r0, r1, r0h, r1h ;
    int cellSer, scanSer ;
    int dpos, lpos, hpos, rpos ;
    int nmotors ;
    FILE *fin = fopen (ifile, "r") ;

    if (fin==0L) {
        return ;
    }
    paramFile = QString (ifile);
    // first line is low and high cell conctn
    fscanf (fin, "%f %f", &val0, &val1) ;
    lowCell = val0 ;
    highCell = val1 ;

    printf ("Low and high cell vals are : %f %f\r\n", lowCell, highCell) ;
    pso2->setConcentrations (lowCell, highCell) ;
    // second line is start and stop of dark range
    fscanf (fin, "%d %d", &d0, &d1) ;
    printf ("Dark range is %d %d\r\n", d0, d1) ;


    // third line is start and stop of fit range
    fscanf (fin, "%d %d", &r0, &r1) ;
    printf ("Fit range is %d %d\r\n", r0, r1) ;
    fscanf (fin, "%d %d", &r0h, &r1h) ;
    pso2->setRanges (d0, d1, r0, r1, r0h, r1h) ;
    mySpec->setRanges ( r0, r1, r0h, r1h) ;
    printf ("Long fit range is %d %d\r\n", r0h, r1h) ;
    ui->plotWidget->setXAxis (d0, r0, r1, r0h, r1h) ;

    // fourth line is nmotors, caloff, scanoff, scanscale
    fscanf (fin, "%d %f %f %f", &nmotors, &caloff, &scanoff, &scanscale) ;
    pm->setMotors (nmotors, caloff, scanoff, scanscale) ;
    // fifth line is cell positions ref,high, dark, low
    fscanf (fin, "%d %d %d %d", &rpos, &hpos, &dpos, &lpos) ;

    this->pm->setCalPositions (dpos, lpos, hpos, rpos) ;
    // slope offset correction - not used in this program
    fscanf (fin, "%f %f", &val0, &val1) ;
    // the two motor serial numbers
    fscanf (fin, "%d %d",  &cellSer, &scanSer) ;
	// gps serial device name
    fscanf (fin, "%s",  gpsdev) ;
	// 0 or 1 flag for volts
    fscanf (fin, "%d",  &voltOnlyFlag) ;

    fscanf (fin, "%f %f",  &startTime, &endTime) ;


    gps->setPort (gpsdev) ;
    gps->init() ;
    if (voltOnlyFlag) myIntKit->setVOnly (true) ;
    else myIntKit->setVOnly(false);
    /*if (gps->gpsStatus)
        gps->start() ;
    */
    pm->setSerialNumbers (cellSer, scanSer) ;
    pm->init() ;
    bool mFlag ;
    if (nmotors >1) {
        mFlag = true ;
        polarFlag = true ;
        ui->scanAvgCBox->setChecked(false);
        ui->polarRB->setChecked(true) ;
        ui->ppmmWidget->setPolarScales() ;
        ui->MirrorScanCB->setChecked(true) ;
        ui->menuScanner->setEnabled (true);
        pm->scanHome();

    } else{
        mFlag = false ;
        polarFlag = false ;
        ui->scanAvgCBox->setChecked(true);
        ui->polarRB->setEnabled(false) ;
        ui->MirrorScanCB->setCheckable(false) ;
        ui->MirrorScanCB->setChecked(false) ;
        ui->menuScanner->setEnabled (false);

    }
    scanthread->setMirrorFlag (mFlag) ;
    repeatscan->setMirrorFlag (mFlag) ;

}

void MainWindow::plotCal (int n, double *dat){
    ui->plotWidget->plotSpectrum (dat, 2048) ;


}
void MainWindow::plotScan (int n, double *dat){
    ui->plotWidget->plotSpectrum (dat, 2048) ;
    if (scanthread->scanning && polarFlag) {
        mysocket->writeData(scanthread->serverString.toLatin1());
        ui->ppmmWidget->plotPolarData (scanthread->angleList.last(), scanthread->ppmmList.last()) ;
        return ;
    }
    if (repeatscan->scanning && polarFlag) {
        mysocket->writeData(repeatscan->serverString.toLatin1());
        ui->ppmmWidget->plotPolarData (repeatscan->angleList.last(), repeatscan->ppmmList.last()) ;
        return ;
    }
    if (scanthread->scanning){
        ui->ppmmWidget->plotData (scanthread->timeList, scanthread->ppmmList) ;
        mysocket->writeData(scanthread->serverString.toLatin1());
        return ;
    }
    else if (repeatscan->scanning) {
        ui->ppmmWidget->plotData (repeatscan->timeList, repeatscan->ppmmList) ;
        mysocket->writeData(repeatscan->serverString.toLatin1());
        return ;
    }

}

void MainWindow::setCalFlag (int flag) {

    calFlag |= flag ;
    if (calFlag ==15) {
        ui->scanButton->setEnabled (true) ;
        ui->repeatScanButton->setEnabled(true);
        ui->AlertButton->setStyleSheet ("background-color:") ;
        ui->plotWidget->setCals (pso2->dark, pso2->low, pso2->high,pso2->ref) ;


    } else {
        ui->scanButton->setEnabled (false) ;
        ui->repeatScanButton->setEnabled(false);
    }

}

void MainWindow::getGPSInfo () {

    //qDebug ("Hello gps") ;
    gpsdlg = new GPSInfoDialog(this) ;
    gpsdlg->setGPS (gps) ;
    gpsdlg->show () ;

}

void MainWindow::filecal() {


}


void MainWindow::updateGUI() {
    if (!ui->GpsLE) return ;
    if (scanthread->scanning|| repeatscan->scanning){
        ui->stopButton->setEnabled (true) ;

    } else ui->stopButton->setEnabled (false) ;

    if (gps){
        QString gpslabel = QString ("%1  %2").arg(*gps->timestring).arg(*gps->posstring);
        ui->GpsLE->setText (gpslabel) ;
    }

    ui->statusLE->setText (modeString) ;
    if (gps->fix != oldFix){
        setGPSFix (gps->fix);
        oldFix = gps->fix ;
    }
    //QString *str  = new QString("") ;
    char vstring [80] ;
    strcpy (vstring, "") ;

    this->myIntKit->getResultsString ( vstring) ;
    ui->ancilLE->setText (ancilLabel) ;

    if (scanthread->scanning)
        strcpy (scanthread->voltString, vstring) ;
    if (repeatscan->scanning)
        strcpy (repeatscan->voltString, vstring) ;
    //delete str ;
}

void MainWindow::on_scanButton_clicked()
{
    // start scanning
    QString filestring ;
    QTime qtim = QTime::currentTime () ;
    QDate qdat = QDate::currentDate() ;
    filestring = workDir+"/"+filestring.sprintf ("Scan_%04d_%02d_%02d_%02d%02d", qdat.year(), qdat.month(), qdat.day(), qtim.hour(), qtim.minute()) ;
    QString str = QFileDialog::getSaveFileName(this, "Scan File",filestring) ;
    if (str.length() < 1) return ;
    this->numScans = ui->nscansLE->text().toInt () ;
    this->writeParamFile (filestring+"_params.txt");
    pso2->processCals() ;
    ui->scanButton->setEnabled (false) ;
    ui->repeatScanButton->setEnabled (false) ;
    ui->stopButton->setEnabled (true) ;

    scanthread->setScanFile (str) ;
    scanthread->nscans = numScans ;
    if (ui->scanAvgCBox->isChecked()){
        mySpec->setNScansAvg (AutoInt::nscansAvg[intLevel]);
    }
    else mySpec->setNScansAvg(1) ;
    scanthread->setGPS (this->gps) ;
    //ui->plotWidget->detachCals() ;
    ui->scanButton->setStyleSheet ("background-color:green;color:yellow") ;
    pm->setRef() ;
    scanthread->start() ;
}

void MainWindow::scanComplete () {
    ui->scanButton->setEnabled (true) ;
    ui->repeatScanButton->setEnabled (true) ;
    ui->stopButton->setEnabled (false) ;
    ui->repeatScanButton->setStyleSheet ("background-color:;color:black") ;
    ui->scanButton->setStyleSheet ("background-color:;color:black") ;

}

void MainWindow::on_autoIntButton_clicked()
{
    pm->setRef() ;
    ui->plotWidget->detachCals() ;
    bool avgFlag = ui->scanAvgCBox->isChecked() ;
    aint->setScanAvgFlag (avgFlag) ;
    aint->start() ;

    ui->autoIntButton->setStyleSheet ("background-color:green;color:yellow") ;
    pm->setRef() ;
}


void MainWindow::auto_int_done (int lev){
    ui->intCB->setCurrentIndex (lev) ;
    intLevel = lev ;
    //if (lev==AutoInt::numLevels-1)
    ui->autoIntButton->setStyleSheet ("background-color:;color:") ;

}

void MainWindow::on_actionProcess_Scanfile_triggered()
{
    int i, count=0 ;
    float val ;
    float *fdat = new float [2048] ;
    double *sdat = new double [2048] ;
    QString str ;

    pso2->processCals () ;
    QString sfile = QFileDialog::getOpenFileName (this, "Scan File ", workDir) ;
    QFile qf (sfile) ;
    qf.open (QIODevice::ReadOnly) ;

    QFile qfout ("out.txt") ;
    qfout.open (QIODevice::WriteOnly) ;
    xvalsVec.clear() ;
    yvalsVec.clear() ;
    while (!qf.atEnd()){
        qf.read ((char *)fdat, 2048 * 4) ;
        for (i=0; i<2048; i++) *(sdat+i) = *(fdat+i) ;
        plotScan (i, sdat) ;
        val = pso2->processScan (sdat, 0, 0) ;
        str.sprintf ("%d %f\r\n", count, val) ;
        xvalsVec.append (count) ;
        yvalsVec.append (val) ;
        ui->ppmmWidget->plotData (xvalsVec, yvalsVec) ;
        qfout.write (str.toLatin1().data()) ;
        usleep (50) ;
        QApplication::processEvents () ;
        count++ ;
    }

    qf.close() ;
    qfout.close() ;
}

void MainWindow::setWorkDir(QString w){
    workDir = w ;
}

void MainWindow::on_actionFull_Cal_triggered()
{

    QString filestring ;
    QTime qtim = QTime::currentTime () ;
    QDate qdat = QDate::currentDate() ;
    filestring = workDir+"/"+filestring.sprintf ("Cal_%04d_%02d_%02d_%02d%02d", qdat.year(), qdat.month(), qdat.day(), qtim.hour(), qtim.minute()) ;
    QString str = QFileDialog::getSaveFileName(this, "Dark File",filestring) ;
    if (str.length() < 2) return ;
    ui->plotWidget->detachCals() ;
    if (!ui->scanAvgCBox->isChecked() )
        mySpec->setNScansAvg (AutoInt::nscansAvg[this->intLevel]);
    else mySpec->setNScansAvg(1) ;
    base_angle = pm->curAng ;
    calFlag = 0 ;
    cscan->setFName (str) ;
    cscan->setMode (0) ;
    cscan->start() ;



    //pm->setPosition (90) ;
    //setCalFlag (15) ;



}

void MainWindow::on_actionDark_Cal_triggered()
{
    //pm->scanHome() ;
    QString filestring ;
    QTime qtim = QTime::currentTime () ;
    QDate qdat = QDate::currentDate() ;
    filestring = workDir+"/"+filestring.sprintf ("Cal_%04d_%02d_%02d_%2d%2d", qdat.year(), qdat.month(), qdat.day(), qtim.hour(), qtim.minute()) ;
    QString str = QFileDialog::getSaveFileName(this, "Dark Prefix",filestring) ;
    if (str.length() < 1) return ;
    cscan->setFName (str) ;
    cscan->setMode (0) ;
    cscan->start() ;
    cscan->setMode (1) ;
    cscan->start() ;

    //pm->setPosition (90) ;

}

void MainWindow::on_actionLow_Cal_triggered()
{
    //pm->scanHome() ;
    QString filestring ;
    QTime qtim = QTime::currentTime () ;
    QDate qdat = QDate::currentDate() ;
    filestring = workDir+"/"+filestring.sprintf ("Cal_%04d_%02d_%02d_%2d%2d", qdat.year(), qdat.month(), qdat.day(), qtim.hour(), qtim.minute()) ;
    QString str = QFileDialog::getSaveFileName(this, "Low Prefix",filestring) ;
    if (str.length() < 1) return ;
    cscan->setFName (str) ;
    cscan->setMode (0) ;
    cscan->start() ;
    cscan->setMode (2) ;
    cscan->start() ;

    //pm->setPosition (90) ;

}

void MainWindow::on_actionHigh_Cal_triggered()
{
    //m->scanHome() ;
    QString filestring ;
    QTime qtim = QTime::currentTime () ;
    QDate qdat = QDate::currentDate() ;
    filestring = workDir+"/"+filestring.sprintf ("Cal_%04d_%02d_%02d_%2d%2d", qdat.year(), qdat.month(), qdat.day(), qtim.hour(), qtim.minute()) ;
    QString str = QFileDialog::getSaveFileName(this, "High Prefix",filestring) ;
    if (str.length() < 2) return ;
    cscan->setFName (str) ;
    cscan->setMode (0) ;
    cscan->start() ;
    cscan->setMode (3) ;
    cscan->start() ;

    //pm->setPosition (90) ;
}

void MainWindow::on_actionRef_Cal_triggered()
{
    //pm->scanHome() ;
    QString filestring ;
    QTime qtim = QTime::currentTime () ;
    QDate qdat = QDate::currentDate() ;
    filestring = workDir+"/"+filestring.sprintf ("Cal_%04d_%02d_%02d_%2d%2d", qdat.year(), qdat.month(), qdat.day(), qtim.hour(), qtim.minute()) ;
    QString str = QFileDialog::getSaveFileName(this, "Ref Prefix",filestring, "*.bin") ;
    if (str.length() < 2) return ;
    base_angle = pm->curAng ;
    cscan->setFName (str) ;
    cscan->setMode (0) ;
    cscan->start() ;
    cscan->setMode (4) ;
    cscan->start() ;

   //pm->setPosition (90) ;

}

void MainWindow::on_actionSet_Working_Directory_triggered()
{
    QString wdir = QFileDialog::getExistingDirectory (this, "Set Working Directory") ;
    if (wdir.length()>0) workDir = wdir ;
}

void MainWindow::on_actionFile_Cale_triggered()
{
    int i, j ;
    float total ;
    float *tmpdata = new float [2048*10] ;
    QString str = QFileDialog::getOpenFileName(this, "Select Dark File", this->workDir, "*.bin") ;
    if (str.length() < 2) return ;
    QFile *qf = new QFile(str) ;
    qf->open (QIODevice::ReadOnly) ;
    qf->read ((char *)tmpdata, 2048 * 4 *10) ;
    qf->close() ;
    cscan->darkFile = QString(str) ;
    for (j=0; j<2048; j++){
        total = 0. ;
        for (i=0; i<10; i++){
            total+= *(tmpdata+i*2048+j) / 10. ;
        }
        this->pso2->dark[j] = total ;
    }
    str.replace ("dark","low") ;
    cscan->lowFile = QString(str) ;

    qf = new QFile(str) ;
    qf->open (QIODevice::ReadOnly) ;
    qf->read ((char *)tmpdata, 2048 * 4 *10) ;
    qf->close() ;

    for (j=0; j<2048; j++){
        total = 0. ;
        for (i=0; i<10; i++){
                total+= *(tmpdata+i*2048+j) / 10. ;
        }
        this->pso2->low[j] = total ;
    }
    str.replace ("low","high") ;
    cscan->highFile = QString(str) ;
    qf = new QFile(str) ;
    qf->open (QIODevice::ReadOnly) ;
    qf->read ((char *)tmpdata, 2048 * 4 *10) ;
    qf->close() ;

    for (j=0; j<2048; j++){
        total = 0. ;
        for (i=0; i<10; i++){
                total+= *(tmpdata+i*2048+j) / 10. ;
        }
        this->pso2->high[j] = total ;
    }
    str.replace ("high","ref") ;
    cscan->refFile = QString(str) ;
    qf = new QFile(str) ;
    qf->open (QIODevice::ReadOnly) ;
    qf->read ((char *)tmpdata, 2048 * 4 *10) ;
    qf->close() ;

    for (j=0; j<2048; j++){
        total = 0. ;
        for (i=0; i<10; i++){
                total+= *(tmpdata+i*2048+j) / 10. ;
        }
        this->pso2->ref[j] = total ;
    }

    setCalFlag (15) ;

}

void MainWindow::on_actionRead_Parameter_File_triggered()
{
    QString qstr ("") ;
    qstr = QFileDialog::getOpenFileName (this, "Parameter File", workDir, "*.txt") ;
    if (qstr.length()<3) {
        return ;
    }
    readParameterFile(qstr.toLatin1().data() ) ;
}

void MainWindow::on_actionPlots_triggered()
{
    PlotLimitsDlg *pld = new PlotLimitsDlg (this);
    pld->setValues (minDN, maxDN, minPPMM, maxPPMM, ui->ppmmWidget->nscansToPlot ) ;
    int status = pld->exec () ;
    if (status != QDialog::Accepted) return ;
    minPPMM = pld->ppmmMin ;
    maxPPMM = pld->ppmmMax ;
    minDN = pld->dnMin ;
    maxDN = pld->dnMax ;
    ui->ppmmWidget->setNScansToPlot (pld->nscans);
    if (!this->polarFlag)
        ui->ppmmWidget->setYAxisScale (minPPMM, maxPPMM) ;
    else
        ui->ppmmWidget->setRadiusScale (maxPPMM) ;
    ui->plotWidget->setYAxis (minDN, maxDN) ;
    //ui->plotWidget->setAxisScale (QwtPlot::yLeft, minDN, maxDN) ;
}

void MainWindow::intChange(int lev){

    int ind = ui->intCB->currentIndex ();
    if (lev < 0){
        if (ind > 0){
            intLevel = ind - 1;
            mySpec->setIntegrationTime (AutoInt::intlevels[ind-1]) ;
            mySpec->setNScansAvg (AutoInt::nscansAvg[ind-1]) ;
            mySpec->setIntLevel (intLevel) ;


        }

    }
    if (lev >0){
        if (ind < AutoInt::numLevels-1){
            intLevel = ind + 1;
            mySpec->setIntegrationTime (AutoInt::intlevels[ind+1]) ;
            if (!ui->scanAvgCBox->isChecked() )
                mySpec->setNScansAvg (AutoInt::nscansAvg[ind+1]) ;
            mySpec->setIntLevel (intLevel) ;

        }

    }
    ui->intCB->setCurrentIndex(intLevel);
}

void MainWindow::on_intCB_currentIndexChanged(const QString &arg1)
{
    int ind = ui->intCB->currentIndex ();
    intLevel = ind ;
    mySpec->setIntegrationTime (AutoInt::intlevels[ind]) ;
    if (ui->scanAvgCBox->isChecked())
        mySpec->setNScansAvg (AutoInt::nscansAvg[ind]) ;
    else
        mySpec->setNScansAvg (1) ;
    mySpec->setIntLevel (intLevel) ;


}

// this is the scan avg checkbox, for averaging incoming spectra

/*
void MainWindow::on_checkBox_clicked()
{
    bool state = ui->scanAvgCBox->isChecked() ;
    if (state){
        int ind = ui->intCB->currentIndex ();
        intLevel = ind ;
        mySpec->setNScansAvg (AutoInt::nscansAvg[intLevel]) ;

    }
    else mySpec->setNScansAvg (1) ;
}
*/
void MainWindow::on_stopButton_clicked()
{
    if (scanthread ){
        scanthread->scanning = false ;
        repeatscan->scanning = false ;
        ui->scanButton->setEnabled(true);
        ui->repeatScanButton->setEnabled(true);
        ui->repeatScanButton->setStyleSheet ("background-color:;color:") ;
        ui->scanButton->setStyleSheet ("background-color:;color:") ;

    }
}

void MainWindow::on_insertLowButton_clicked()
{
    int nscansInsert ;
    QString str = ui->cellInsertScanLE->text() ;
    nscansInsert = str.toInt() ;

    if (scanthread->scanning){
        scanthread->insertCell (0, nscansInsert) ;
    }
    if (repeatscan->scanning){
        repeatscan->insertCell (0, nscansInsert) ;
    }
}

void MainWindow::on_insertHighButton_clicked()
{
    int nscansInsert ;
    QString str = ui->cellInsertScanLE->text( ) ;
    nscansInsert = str.toInt() ;


    if (scanthread->scanning){
        scanthread->insertCell (1, nscansInsert) ;
    }
    if (repeatscan->scanning){
        repeatscan->insertCell (1, nscansInsert) ;
    }
}


void MainWindow::setCellState(int state)
{
    QString str ;
    switch (state) {
        case 0 :
            str = "DARK" ;
            ui->cellStateButt->setStyleSheet ("background-color :rgb(50,50,50);color:white;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
            ui->cellStateButt->setText (str) ;
            break ;
        case 1 :
            str = "LOW" ;
            ui->cellStateButt->setStyleSheet ("background-color:yellow;color:black;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
            ui->cellStateButt->setText (str) ;
            break ;
        case 2 :
            str = "HIGH" ;
            ui->cellStateButt->setStyleSheet ("background-color:orange;color:black;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
            ui->cellStateButt->setText (str) ;
            break ;
        case 3 :
            str = "REF" ;
            ui->cellStateButt->setStyleSheet ("background-color:white;color:black;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
            ui->cellStateButt->setText (str) ;
            break ;

    }
}

void MainWindow::satAlert (bool state) {
    // unsaturated
    if (!state) {
        ui->satStateButton->setStyleSheet ("background-color:green;color:yellow;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
        ui->satStateButton->setText ("Unsaturated") ;
    }
    else {
        ui->satStateButton->setStyleSheet ("font:bold 12px;background-color:yellow;color:red;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
        ui->satStateButton->setText ("Saturated !") ;

    }
}

void MainWindow::on_repeatScanButton_clicked()
{
    RepeatScanDialog *rsd = new RepeatScanDialog (this) ;
    rsd->setTimes (startTime, endTime ) ;
    int status = rsd->exec () ;
    if (status != QDialog::Accepted) return ;
    startTime = rsd->startTime ;
    endTime = rsd->endTime ;

    // start scanning
    QString filestring ;
    QTime qtim = QTime::currentTime () ;
    QDate qdat = QDate::currentDate() ;
    filestring = workDir+"/"+filestring.sprintf ("%04d_%02d_%02d_%02d%02d", qdat.year(), qdat.month(), qdat.day(), qtim.hour(), qtim.minute()) ;
    //QString str = QFileDialog::getSaveFileName(this, "Scan File",filestring) ;
    bool state = ui->scanAvgCBox->isChecked() ;
    if (state){
        int ind = ui->intCB->currentIndex ();
        intLevel = ind ;
        mySpec->setNScansAvg (AutoInt::nscansAvg[intLevel]) ;

    }
    else mySpec->setNScansAvg (1) ;
    this->writeParamFile (filestring+"_params.txt");
    pso2->processCals() ;
    ui->repeatScanButton->setEnabled (false) ;
    ui->scanButton->setEnabled (false) ;

    ui->stopButton->setEnabled (true) ;
    repeatscan->setStartTime (startTime, endTime) ;
    //repeatscan->setScanFile (str) ;
    repeatscan->setWorkdir (workDir) ;
    repeatscan->setGPS (this->gps) ;
    ui->repeatScanButton->setStyleSheet ("background-color:green; color:yellow") ;
    repeatscan->start() ;
}


void MainWindow::setGPSFix (int state) {
    if (state <= 0) {
        ui->GPSFixButton->setStyleSheet ("font:bold 12px;background-color:red;color:yellow;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
        ui->GPSFixButton->setText ("GPS- NoFix") ;

    }
    else {
        ui->GPSFixButton->setStyleSheet ("font:bold 12px;background-color:green;color:yellow;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
        ui->GPSFixButton->setText ("GPS- OK") ;
    }
}

void MainWindow::on_actionScan_Mirror_triggered()
{

    int status;
    MirrorConfigDialog *mcd = new MirrorConfigDialog() ;
    mcd->setAngles (this->startAngle, this->endAngle, this->incAngle) ;
    status = mcd->exec() ;
    if (status == QDialog::Rejected) return ;
    mcd->getAngles (&startAngle, &endAngle, &incAngle) ;
    pm->setMirrorAngles (startAngle, endAngle, incAngle) ;
    ui->ppmmWidget->setAngles (startAngle, endAngle, incAngle) ;
}

void MainWindow::on_actionPosition_Mirror_triggered()
{
    int status ;
    PosMirrorDialog *pmd = new PosMirrorDialog () ;
    pmd->setMirrorPos(pm->curAng);
    status = pmd->exec() ;
    if (status != QDialog::Accepted) return ;
    pm->scanSet (pmd->mirrorPos) ;

}

void MainWindow::on_actionScan_Parameters_triggered()
{
    int status;
    float scanoff, scanscale ;
    MirrorConfigDialog *mcd = new MirrorConfigDialog() ;
    mcd->setAngles (this->startAngle, this->endAngle, this->incAngle) ;
    mcd->setScanScaleOff (pm->scanoff, pm->scanscale) ;
    status = mcd->exec() ;
    if (status == QDialog::Rejected) return ;
    mcd->getAngles (&startAngle, &endAngle, &incAngle) ;

    mcd->getScanConfig (&scanoff, &scanscale) ;
    pm->setScanScaleOff (scanoff, scanscale) ;
    pm->setMirrorAngles (startAngle, endAngle, incAngle) ;
    ui->ppmmWidget->setAngles (startAngle, endAngle, incAngle) ;

}

void MainWindow::on_actionPolar_Plot_changed()
{
    polarFlag = ui->actionPolar_Plot->isChecked();
    scanthread->polarFlag = polarFlag ;
    repeatscan->polarFlag = polarFlag ;

}

void MainWindow::on_actionConnect_to_Server_triggered()
{
    int status ;
    ServerConnectDlg *scd = new ServerConnectDlg () ;
    scd->setServerString (serverString) ;
    scd->setPortString (portString) ;
    status = scd->exec() ;
    if (status == QDialog::Rejected) return ;
    serverString = scd->serverString ;
    portString = scd->portString ;
    mysocket->setPortNumber (portString.toInt()) ;
    mysocket->setServerString (serverString) ;
    mysocket->connectToHost (serverString) ;
    ui->actionDisconnect->setEnabled (true) ;
    ui->actionConnect_to_Server->setEnabled(false) ;
    ui->ServerStatusButton->setStyleSheet ("background-color:green;color:yellow;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
    ui->ServerStatusButton->setText ("Server: Connected") ;
    //scanthread->setSocket (mysocket) ;
    //repeatscan->setSocket (mysocket) ;

}

void MainWindow::reconServer () {

    mysocket->reconnect() ;
}


void MainWindow::on_checkBox_2_clicked()
{
    bool f = ui->checkBox_2->isChecked() ;
    repeatscan->autoLevelFlag = f ;
    scanthread->autoLevelFlag = f ;
}

void MainWindow::on_actionDisconnect_triggered()
{
    mysocket->closeUp() ;
    ui->actionDisconnect->setEnabled (false) ;
    ui->actionConnect_to_Server->setEnabled(true) ;
    ui->ServerStatusButton->setStyleSheet ("background-color:orange;color:black;border-radius:5px;border-style:inset;border-width:1px;border-color:black") ;
    ui->ServerStatusButton->setText ("Server: Disconn.") ;
}

void MainWindow::on_timeSeriesRB_toggled(bool checked)
{
    ui->ppmmWidget->togglePlotType (!checked) ;
    polarFlag =!checked ;
    scanthread->polarFlag = polarFlag ;
    repeatscan->polarFlag = polarFlag ;

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox qmsb ;
    qmsb.setWindowTitle ("FLYSPEC INC.") ;
    qmsb.setText ("Lapfly Version 6.0\nCopyright : Flyspec Inc., June 2015") ;
    qmsb.exec() ;

}

void MainWindow::on_MirrorScanCB_toggled(bool checked)
{

    scanthread->mirrorFlag = checked ;
    repeatscan->mirrorFlag = checked ;
    ui->timeSeriesRB->setChecked (!checked) ;
    ui->polarRB->setChecked(checked) ;

}

void MainWindow::on_MirrorScanCB_clicked()
{

}

void MainWindow::on_scanAvgCBox_stateChanged(int arg1)
{
    bool state = ui->scanAvgCBox->isChecked() ;
    if (state){
        int ind = ui->intCB->currentIndex ();
        intLevel = ind ;
        mySpec->setNScansAvg (AutoInt::nscansAvg[intLevel]) ;

    }
    else mySpec->setNScansAvg (1) ;
}
/*

private void writeParamFile (String outfile) {
    String outstr ;
    try {
        FileOutputStream fos = new FileOutputStream (outfile) ;
        outstr = "Parameter File : "+paramfile+"\r\n" ;
        fos.write (outstr.getBytes () ) ;
        outstr = "Dark File : "+darkfile+"\r\n" ;
        fos.write (outstr.getBytes () ) ;
        outstr = "Low File : "+lowfile+"\r\n" ;
        fos.write (outstr.getBytes () ) ;
        outstr = "High File : "+highfile+"\r\n" ;
        fos.write (outstr.getBytes () ) ;
        outstr = "Ref File : "+reffile+"\r\n" ;
        fos.write (outstr.getBytes () ) ;
        outstr = "Mirror angle for ref : "+ref_angle+"\r\n" ;
        fos.write (outstr.getBytes() ) ;
        outstr = "GPS StartTime  : "+timestr+"\r\n" ;
        fos.write (outstr.getBytes () ) ;
        outstr = "Base integration time  : "+myspec.baseIntValue+"\r\n" ;
        fos.write (outstr.getBytes () ) ;
        //outstr = "Scans to average  : Variable\r\n" ;
        outstr = "Scans to average : "+myspec.scans_to_avg+"\r\n" ;
        fos.write (outstr.getBytes () ) ;
        fos.close () ;

     }
    catch (IOException ioe){}


}

*/
void MainWindow::writeParamFile (QString ofile){

    QFile qf (ofile);
    qf.open (QIODevice::WriteOnly | QIODevice::Text) ;
    QTextStream qts (&qf);
    QString str = QString("Param file : %1").arg(this->paramFile) ;
    qts << str << endl ;
    str = QString("Dark : %1\r").arg(cscan->darkFile) ;
    qts << str << endl ;
    str = QString("Low : %1").arg(cscan->lowFile) ;
    qts << str << endl ;
    str = QString("High : %1").arg(cscan->highFile) ;
    qts << str << endl ;
    str = QString("Ref : %1").arg(cscan->refFile) ;
    qts << str << endl ;
    str = QString("GPS Start Time : %1").arg(*gps->timestring) ;
    qts << str << endl ;
    str = QString("Base Int. Time : %1").arg(mySpec->intTime) ;
    qts << str << endl ;
    str = QString("Scans To Average : %1").arg(mySpec->nscansAvg) ;
    qts << str << endl ;
    str = QString("Ref Mirror Angle  : %1").arg(base_angle) ;
    qts << str << endl ;

    qf.close() ;

}


void MainWindow::on_scanAvgCBox_clicked()
{
    bool state = ui->scanAvgCBox->isChecked() ;
    if (state){
        int ind = ui->intCB->currentIndex ();
        intLevel = ind ;
        mySpec->setNScansAvg (AutoInt::nscansAvg[intLevel]) ;

    }
    else mySpec->setNScansAvg (1) ;

}
