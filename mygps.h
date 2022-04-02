#ifndef MYGPS_H
#define MYGPS_H
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
//#include "nmea.h"
#include <string.h>



#include <QThread>

class MyGPS : public QThread
{
    Q_OBJECT
public:

    explicit MyGPS(QObject *parent = 0);
    ~MyGPS () ;
    int fd, c, res ;
    //nmeaINFO infostruc ;
    //nmeaPARSER parser ;
    char devname [80] ;
    struct termios oldtio, newtio ;
    bool runGPS, gpsStatus  ;
    void setDeviceName (char *) ;
    void parseSentence (char *) ;
    void parseTime (float) ;
    void setLabel (QString *qstr) ;
    void init() ;
    void run () ;
    int hr, min, sec, nSats ;
    float time, lat, lon, alt ;
    int   fix ;
    //NMEA *parser ;
    bool NFlag, WFlag ;
    QString *timestring, *posstring, *gpsLabel ;
signals:
    
public slots:
    
};

#endif // MYGPS_H
