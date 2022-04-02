#include "mygps.h"
#include "unistd.h"




MyGPS::MyGPS(QObject *parent) :
    QThread(parent)
{
    //nmea_zero_INFO (&infostruc) ;
    //nmea_parser_init (&parser) ;
    runGPS = true ;
    lat = lon = alt = 0. ;
    fix = 0 ;
    nSats = 0 ;
    NFlag = true ;
    WFlag = false ;
    timestring = new QString("");
    posstring = new QString("No Fix") ;
    gpsStatus = true ;

}

MyGPS::~MyGPS (){
    if (this->isRunning()) this->terminate() ;

}


void MyGPS::setDeviceName (char *dname) {
    strcpy (devname, dname) ;

}

void MyGPS::setLabel (QString *qstr){
    gpsLabel= qstr ;
}

void MyGPS::init () {

    char tempdev [120] ;
    strcpy (tempdev, devname) ;
    fd = open (devname, O_RDONLY | O_NOCTTY) ;
    if (fd<0) {
        perror (devname);
        printf ("Coould not open gps") ;
        gpsStatus = false ;
        return ;
    }

    tcgetattr (fd, &oldtio) ;
    newtio.c_cflag = B4800 | CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
    newtio.c_cc[VMIN]     =  1;   /* blocking read until 5 chars received */





}

void MyGPS::run() {
    int  count = 0 ;
    char buf [255],  linebuf[5120] ;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
    while (runGPS) {
        //strcpy (buf, "") ;
        res = read (fd, buf, 1) ;
        //qDebug (buf[0]) ;
        if (buf[0]=='$'){
            count= 0 ;

        }
        linebuf[count++] = buf[0] ;
        if (count>=255) {
            count = 0 ;
        }
        //
        if (buf[0]=='\n'){
                //linebuf[count++] = buf[0] ;
                linebuf[count]='\0' ;
                //printf ("%s", linebuf) ;
                if (linebuf[count-5] == '*'){
                    parseSentence (linebuf) ;
		}
        }
        //gpsLabel = new QString (*timestring + "  " + *posstring) ;

    }



}


void MyGPS::parseSentence (char *nmeaStr){
    int nchars ;
    char *typestr = strtok (nmeaStr, ",") ;
    char *tmpstr ;
    char latCh[80], lonCh[80] ;
    //printf ("Sentence is \n%s\n", nmeaStr) ;
    //printf ("type is : %s\n", typestr) ;
    //problem with alt with short string .... (no fix)

    time = 0 ;
     if (strstr (typestr, "GPGGA")) {
         tmpstr = strtok (NULL, "," ) ;
         if (tmpstr == NULL) return ;
         nchars = strlen (tmpstr) ;
         if (nchars<10) return ;
         time = atof (tmpstr) ;
         parseTime (time) ;
         tmpstr = strtok (NULL, ",") ;
	 if (strlen(tmpstr)<5) return ;

         lat = atof (tmpstr) ;

         tmpstr = strtok (NULL, ",") ;
         if (strstr(tmpstr,"N")) NFlag = true ;
         else NFlag = false ;
         strcpy (latCh, tmpstr) ;
         tmpstr = strtok (NULL, ",") ;
         lon = atof (tmpstr) ;
         tmpstr = strtok (NULL, ",") ;
         if (strstr(tmpstr, "W")) WFlag = true ;
         else WFlag = false ;
         strcpy (lonCh, tmpstr) ;
         tmpstr = strtok (NULL, ",") ;
         fix = atoi (tmpstr) ;
         tmpstr = strtok (NULL, ",") ;
         nSats = atoi (tmpstr) ;
         //HDOP
         tmpstr = strtok (NULL, ",") ;
         // alt
         tmpstr = strtok (NULL, ",") ;
         alt = atof (tmpstr) ;

         //printf ("%f  %f  %f %d %d\r\n", time, lat, lon, fix, nSats) ;
         posstring->sprintf ("%f %s %f %s %f", lat, latCh, lon, lonCh, alt) ;




     }

}




void MyGPS::parseTime (float tim){
    QString teststr ;
    int loc_hr, loc_min ;
    float loc_sec ;
    loc_hr = int (tim / 1.0E4) ;
    loc_min = int ((tim - (hr * 1.0E4)) / 100) ;
    loc_sec = tim- (hr * 1.0E4)-(min*100) ;

    QChar z ('0') ;
    *timestring = QString ("%1%2%3").arg(loc_hr,2,10,z).arg(loc_min,2,10,z).arg(loc_sec,4,'f',1,z) ;
    hr = loc_hr ;
    min = loc_min ;
    sec = loc_sec ;


}
