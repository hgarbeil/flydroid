#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if (argc >1){
        w.setParamFile (argv[1]);
    }
    if (argc >2){
        w.setWorkDir (argv[2]);
    }
    w.show();
    
    return a.exec();
}
