/********************************************************************************
** Form generated from reading UI file 'gpsinfodialog.ui'
**
** Created: Wed Feb 5 13:02:34 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPSINFODIALOG_H
#define UI_GPSINFODIALOG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_GPSInfoDialog
{
public:
    QLabel *label;
    QLineEdit *gpsPortLE;
    QLabel *FixLabel;
    QLabel *label_2;
    QLineEdit *nSatsLE;
    QLineEdit *posLE;
    QLabel *label_3;

    void setupUi(QDialog *GPSInfoDialog)
    {
        if (GPSInfoDialog->objectName().isEmpty())
            GPSInfoDialog->setObjectName(QString::fromUtf8("GPSInfoDialog"));
        GPSInfoDialog->resize(372, 300);
        label = new QLabel(GPSInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 81, 17));
        gpsPortLE = new QLineEdit(GPSInfoDialog);
        gpsPortLE->setObjectName(QString::fromUtf8("gpsPortLE"));
        gpsPortLE->setGeometry(QRect(140, 10, 111, 23));
        FixLabel = new QLabel(GPSInfoDialog);
        FixLabel->setObjectName(QString::fromUtf8("FixLabel"));
        FixLabel->setGeometry(QRect(300, 10, 66, 21));
        FixLabel->setFrameShape(QFrame::Box);
        FixLabel->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(GPSInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 101, 17));
        nSatsLE = new QLineEdit(GPSInfoDialog);
        nSatsLE->setObjectName(QString::fromUtf8("nSatsLE"));
        nSatsLE->setGeometry(QRect(140, 50, 111, 23));
        posLE = new QLineEdit(GPSInfoDialog);
        posLE->setObjectName(QString::fromUtf8("posLE"));
        posLE->setGeometry(QRect(20, 100, 341, 23));
        label_3 = new QLabel(GPSInfoDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 80, 111, 20));

        retranslateUi(GPSInfoDialog);

        QMetaObject::connectSlotsByName(GPSInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *GPSInfoDialog)
    {
        //GPSInfoDialog->setWindowTitle(QApplication::translate("GPSInfoDialog", "GPS Info", 0, QApplication::UnicodeUTF8));
        GPSInfoDialog->setWindowTitle(QApplication::translate("GPSInfoDialog", "GPS Info", 0 ));
        label->setText(QApplication::translate("GPSInfoDialog", "TIME :", 0)) ;
        FixLabel->setText(QApplication::translate("GPSInfoDialog", "FIX", 0)) ;
        label_2->setText(QApplication::translate("GPSInfoDialog", "Sats in View :", 0)) ;
        label_3->setText(QApplication::translate("GPSInfoDialog", "Position Info : ", 0)) ;
    } // retranslateUi

};

namespace Ui {
    class GPSInfoDialog: public Ui_GPSInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPSINFODIALOG_H
