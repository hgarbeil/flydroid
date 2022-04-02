#-------------------------------------------------
#
# Project created by QtCreator 2013-09-15T16:11:31
#
#-------------------------------------------------

QT       +=  core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport

TARGET = beaglebone
TEMPLATE = app
Release : DESTDIR = release





CONFIG += qt


SOURCES += main.cpp\
    mainwindow.cpp \
    myplot.cpp \
    myspectrometer.cpp \
    phidgetsMot.cpp \
    calscan.cpp \
    gpsinfodialog.cpp \
    #mygps.cpp \
    nmea.cpp \ 
    processso2.cpp \
    autoint.cpp \
    infodialog.cpp \
    scanthread.cpp \
    myppmmplot.cpp \
    plotlimitsdlg.cpp \
    repeatscandialog.cpp \
    repeatScan.cpp \
    qcustomplot.cpp \
    myinterfacekit.cpp \
    mirrorconfigdialog.cpp \
    posmirrordialog.cpp \
    mysocket.cpp \
    serverconnectdlg.cpp \
    qgpsdevice.cpp \
    polyfitd/svdvar.c \
    polyfitd/svdfit_d.c \
    polyfitd/svbksb.c \
    polyfitd/poly.cpp \
    polyfitd/nrutil.c \
    polyfitd/svdcmp_d.c \
    polyfitd/svbksb_d.c

HEADERS  += mainwindow.h \
    myplot.h \
    myspectrometer.h \
    phidgetsMot.h \
    calscan.h \
    gpsinfodialog.h \
    #mygps.h \
    nmea.h \ 
    processso2.h \
    autoint.h \
    infodialog.h \
    scanthread.h \
    myppmmplot.h \
    plotlimitsdlg.h \
    repeatscandialog.h \
    repeatScan.h \
    qcustomplot.h \
    myinterfacekit.h \
    mirrorconfigdialog.h \
    posmirrordialog.h \
    mysocket.h \
    serverconnectdlg.h \
    qgpsdevice.h \
    polyfitd/nrutil.h

FORMS    += mainwindow.ui \
    gpsinfodialog.ui \
    infodialog.ui \
    plotlimitsdlg.ui \
    repeatscandialog.ui \
    mirrorconfigdialog.ui \
    posmirrordialog.ui \
    serverconnectdlg.ui

#target.path += /home/root/programs
INSTALLS += target

#INCLUDEPATH+= /hbeta/harold/workdir/build-qwt-beaglebone-Debug/include
# for linux install
#INCLUDEPATH+= /usr/local/include/seabreeze

#for windows install

#INCLUDEPATH+= /home/fly/workdir/seabreeze/include
#INCLUDEPATH+= "C:\Program Files\Phidgets"

#INCLUDEPATH+= C:\hg\workdir\seabreeze-3.0.7\seabreeze-3.0.7\include\
#INCLUDEPATH+= C:\hg\workdir\seabreeze-3.0.7\seabreeze-3.0.7\include\native\usb
INCLUDEPATH+= /home/fly/workdir/seabreeze-3.0.11/SeaBreeze/include

#INCLUDEPATH+= /home/fly/workdir/polyfitd
#LIBS += -LC:\Users\FLYSPEC\workdir\seabreeze\lib "C:\Program Files\Phidgets\x86\phidget21.lib"
#LIBS += "C:/hg/workdir/seabreeze-3.0.7/seabreeze-3.0.7/lib/SeaBreeze.lib" "C:\Program Files\Phidgets\x86\phidget21.lib"
# linux build uses libs below
LIBS+= -L/home/fly/workdir/seabreeze-3.0.11/SeaBreeze/lib -lseabreeze -lusb  -lphidget21
#LIBS+= -lphidget21
# windows build
#LIBS += -lSeaBreeze

