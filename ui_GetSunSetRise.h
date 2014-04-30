/********************************************************************************
** Form generated from reading UI file 'GetSunSetRise.ui'
**
** Created: Wed 16. Jan 16:01:56 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETSUNSETRISE_H
#define UI_GETSUNSETRISE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSplitter>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GetSunSetRise
{
public:
    QGridLayout *gridLayout;
    QCalendarWidget *calendarWidget;
    QFrame *line;
    QLabel *label_4;
    QLabel *label;
    QSplitter *splitter_6;
    QLineEdit *leLongtitude;
    QLineEdit *leLatitude;
    QSplitter *splitter;
    QRadioButton *rbEast;
    QRadioButton *rbWest;
    QSplitter *splitter_2;
    QRadioButton *rbSunSet;
    QRadioButton *rbSunRise;
    QLabel *label_7;
    QLabel *label_2;
    QComboBox *cbTimeZone;
    QComboBox *cbSunZenith;
    QPushButton *bCalc;
    QLabel *lResults;

    void setupUi(QWidget *GetSunSetRise)
    {
        if (GetSunSetRise->objectName().isEmpty())
            GetSunSetRise->setObjectName(QString::fromUtf8("GetSunSetRise"));
        GetSunSetRise->resize(284, 406);
        gridLayout = new QGridLayout(GetSunSetRise);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        calendarWidget = new QCalendarWidget(GetSunSetRise);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(calendarWidget->sizePolicy().hasHeightForWidth());
        calendarWidget->setSizePolicy(sizePolicy);

        gridLayout->addWidget(calendarWidget, 0, 0, 1, 2);

        line = new QFrame(GetSunSetRise);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 2);

        label_4 = new QLabel(GetSunSetRise);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 2, 1);

        label = new QLabel(GetSunSetRise);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 1, 1, 1);

        splitter_6 = new QSplitter(GetSunSetRise);
        splitter_6->setObjectName(QString::fromUtf8("splitter_6"));
        splitter_6->setOrientation(Qt::Horizontal);
        leLongtitude = new QLineEdit(splitter_6);
        leLongtitude->setObjectName(QString::fromUtf8("leLongtitude"));
        leLongtitude->setEnabled(true);
        leLongtitude->setReadOnly(false);
        splitter_6->addWidget(leLongtitude);
        leLatitude = new QLineEdit(splitter_6);
        leLatitude->setObjectName(QString::fromUtf8("leLatitude"));
        leLatitude->setEnabled(true);
        splitter_6->addWidget(leLatitude);

        gridLayout->addWidget(splitter_6, 4, 0, 1, 2);

        splitter = new QSplitter(GetSunSetRise);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        rbEast = new QRadioButton(splitter);
        rbEast->setObjectName(QString::fromUtf8("rbEast"));
        rbEast->setChecked(true);
        splitter->addWidget(rbEast);
        rbWest = new QRadioButton(splitter);
        rbWest->setObjectName(QString::fromUtf8("rbWest"));
        splitter->addWidget(rbWest);

        gridLayout->addWidget(splitter, 5, 0, 1, 1);

        splitter_2 = new QSplitter(GetSunSetRise);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        rbSunSet = new QRadioButton(splitter_2);
        rbSunSet->setObjectName(QString::fromUtf8("rbSunSet"));
        rbSunSet->setChecked(true);
        splitter_2->addWidget(rbSunSet);
        rbSunRise = new QRadioButton(splitter_2);
        rbSunRise->setObjectName(QString::fromUtf8("rbSunRise"));
        splitter_2->addWidget(rbSunRise);

        gridLayout->addWidget(splitter_2, 5, 1, 1, 1);

        label_7 = new QLabel(GetSunSetRise);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        label_2 = new QLabel(GetSunSetRise);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 8, 0, 1, 1);

        cbTimeZone = new QComboBox(GetSunSetRise);
        cbTimeZone->setObjectName(QString::fromUtf8("cbTimeZone"));
        cbTimeZone->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cbTimeZone->sizePolicy().hasHeightForWidth());
        cbTimeZone->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(cbTimeZone, 9, 0, 1, 2);

        cbSunZenith = new QComboBox(GetSunSetRise);
        cbSunZenith->setObjectName(QString::fromUtf8("cbSunZenith"));
        sizePolicy.setHeightForWidth(cbSunZenith->sizePolicy().hasHeightForWidth());
        cbSunZenith->setSizePolicy(sizePolicy);

        gridLayout->addWidget(cbSunZenith, 7, 0, 1, 2);

        bCalc = new QPushButton(GetSunSetRise);
        bCalc->setObjectName(QString::fromUtf8("bCalc"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        bCalc->setFont(font);

        gridLayout->addWidget(bCalc, 10, 0, 1, 2);

        lResults = new QLabel(GetSunSetRise);
        lResults->setObjectName(QString::fromUtf8("lResults"));
        lResults->setFont(font);
        lResults->setFrameShape(QFrame::WinPanel);
        lResults->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(lResults, 11, 0, 1, 2);


        retranslateUi(GetSunSetRise);

        QMetaObject::connectSlotsByName(GetSunSetRise);
    } // setupUi

    void retranslateUi(QWidget *GetSunSetRise)
    {
        GetSunSetRise->setWindowTitle(QApplication::translate("GetSunSetRise", "\320\222\320\276\321\201\321\205\320\276\320\264 \320\270 \320\267\320\260\321\205\320\276\320\264 \321\201\320\276\320\273\320\275\321\206\320\260", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("GetSunSetRise", "\320\224\320\276\320\273\320\263\320\276\321\202\320\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GetSunSetRise", "\320\250\320\270\321\200\320\276\321\202\320\260", 0, QApplication::UnicodeUTF8));
        rbEast->setText(QApplication::translate("GetSunSetRise", "\320\222\320\276\321\201\321\202\320\276\320\272", 0, QApplication::UnicodeUTF8));
        rbWest->setText(QApplication::translate("GetSunSetRise", "\320\227\320\260\320\277\320\260\320\264", 0, QApplication::UnicodeUTF8));
        rbSunSet->setText(QApplication::translate("GetSunSetRise", "\320\227\320\260\320\272\320\260\321\202", 0, QApplication::UnicodeUTF8));
        rbSunRise->setText(QApplication::translate("GetSunSetRise", "\320\222\320\276\321\201\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("GetSunSetRise", "\320\227\320\265\320\275\320\270\321\202 \321\201\320\276\320\273\320\275\321\206\320\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GetSunSetRise", "\320\247\320\260\321\201\320\276\320\262\320\276\320\271 \320\277\320\276\321\217\321\201", 0, QApplication::UnicodeUTF8));
        cbTimeZone->clear();
        cbTimeZone->insertItems(0, QStringList()
         << QApplication::translate("GetSunSetRise", "(UTC -12:00) \320\233\320\270\320\275\320\270\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\321\213 \320\264\320\260\321\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -11:00) \320\222\321\200\320\265\320\274\321\217 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 UTC -11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -10:00) \320\223\320\260\320\262\320\260\320\271\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -09:00) \320\220\320\273\321\217\321\201\320\272\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "UTC -08:00) \320\235\320\270\320\266\320\275\321\217\321\217 \320\232\320\260\320\273\320\270\321\204\320\276\321\200\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -08:00) \320\242\320\270\321\205\320\276\320\276\320\272\320\265\320\260\320\275\321\201\320\272\320\276\320\265 \320\262\321\200\320\265\320\274\321\217 (\320\241\320\250\320\220 \320\270 \320\232\320\260\320\275\320\260\320\264\320\260)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -07:00) \320\220\321\200\320\270\320\267\320\276\320\275\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -07:00) \320\223\320\276\321\200\320\275\320\276\320\265 \320\262\321\200\320\265\320\274\321\217 (\320\241\320\250\320\220 \320\270 \320\232\320\260\320\275\320\260\320\264\320\260)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -07:00) \320\233\320\260-\320\237\320\260\321\201, \320\234\320\260\320\267\320\260\321\202\320\273\320\260\320\275, \320\247\320\270\321\205\321\203\320\260\321\205\321\203\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -06:00) \320\223\320\262\320\260\320\264\320\260\320\273\320\260\321\205\320\260\321\200\320\260, \320\234\320\265\321\205\320\270\320\272\320\276, \320\234\320\276\320\275\321\202\320\265\321\200\321\200\320\265\320\271", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -06:00) \320\241\320\260\321\201\320\272\320\260\321\207\320\265\320\262\320\260\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -06:00) \320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\260\321\217 \320\220\320\274\320\265\321\200\320\270\320\272\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -06:00) \320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\276\320\265 \320\262\321\200\320\265\320\274\321\217 (\320\241\320\250\320\220 \320\270 \320\232\320\260\320\275\320\260\320\264\320\260)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -05:00) \320\221\320\276\320\263\320\276\321\202\320\260, \320\233\320\270\320\274\320\260, \320\232\320\270\321\202\320\276", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -05:00) \320\222\320\276\321\201\321\202\320\276\321\207\320\275\320\276\320\265 \320\262\321\200\320\265\320\274\321\217 (\320\241\320\250\320\220 \320\270 \320\232\320\260\320\275\320\260\320\264\320\260)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -05:00) \320\230\320\275\320\264\320\270\320\260\320\275\320\260 (\320\262\320\276\321\201\321\202\320\276\320\272)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -04:30) \320\232\320\260\321\200\320\260\320\272\320\260\321\201", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -04:00) \320\220\321\201\321\203\320\275\321\201\321\214\320\276\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -04:00) \320\220\321\202\320\273\320\260\320\275\321\202\320\270\321\207\320\265\321\201\320\272\320\276\320\265 \320\262\321\200\320\265\320\274\321\217 (\320\232\320\260\320\275\320\260\320\264\320\260)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -04:00) \320\224\320\266\320\276\321\200\320\264\320\266\321\202\320\260\321\203\320\275, \320\233\320\260-\320\237\320\260\321\201, \320\234\320\260\320\275\320\260\321\203\321\201, \320\241\320\260\320\275-\320\245\321\203\320\260\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -04:00) \320\232\321\203\321\217\320\261\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -04:00) \320\241\320\260\320\275\321\202\321\214\321\217\320\263\320\276", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -03:30) \320\235\321\214\321\216\321\204\320\260\321\203\320\275\320\264\320\273\320\265\320\275\320\264", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -03:00) \320\221\321\200\320\260\320\267\320\270\320\273\320\270\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -03:00) \320\221\321\203\321\215\320\275\320\276\321\201-\320\220\320\271\321\200\320\265\321\201", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -03:00) \320\223\321\200\320\265\320\275\320\273\320\260\320\275\320\264\320\270\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -03:00) \320\232\320\260\320\271\320\265\320\275\320\275\320\260, \320\244\320\276\321\200\321\202\320\260\320\273\320\265\320\267\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -03:00) \320\234\320\276\320\275\321\202\320\265\320\262\320\270\320\264\320\265\320\276", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -03:00) \320\241\320\260\320\273\321\214\320\262\320\260\320\264\320\276\321\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -02:00) \320\222\321\200\320\265\320\274\321\217 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 UTC -02", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -02:00) \320\241\321\200\320\265\320\264\320\275\320\265\320\260\321\202\320\273\320\260\320\275\321\202\320\270\321\207\320\265\321\201\320\272\320\276\320\265 \320\262\321\200\320\265\320\274\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -01:00) \320\220\320\267\320\276\321\200\321\201\320\272\320\270\320\265 \320\276-\320\262\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC -01:00) \320\236-\320\262\320\260 \320\227\320\265\320\273\320\265\320\275\320\276\320\263\320\276 \320\274\321\213\321\201\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC) \320\222\321\200\320\265\320\274\321\217 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 UTC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC) \320\224\321\203\320\261\320\273\320\270\320\275, \320\233\320\270\321\201\321\201\320\260\320\261\320\276\320\275, \320\233\320\276\320\275\320\264\320\276\320\275, \320\255\320\264\320\270\320\275\320\261\321\203\321\200\320\263", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC) \320\232\320\260\321\201\320\260\320\261\320\273\320\260\320\275\320\272\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC) \320\234\320\276\320\275\321\200\320\276\320\262\320\270\321\217, \320\240\320\265\320\271\320\272\321\214\321\217\320\262\320\270\320\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +01:00) \320\220\320\274\321\201\321\202\320\265\321\200\320\264\320\260\320\274, \320\221\320\265\321\200\320\273\320\270\320\275, \320\221\320\265\321\200\320\275, \320\222\320\265\320\275\320\260, \320\240\320\270\320\274, \320\241\321\202\320\276\320\272\320\263\320\276\320\273\321\214\320\274", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +01:00) \320\221\320\265\320\273\320\263\321\200\320\260\320\264, \320\221\321\200\320\260\321\202\320\270\321\201\320\273\320\260\320\262\320\260, \320\221\321\203\320\264\320\260\320\277\320\265\321\210\321\202, \320\233\321\216\320\261\320\273\321\217\320\275\320\260, \320\237\321\200\320\260\320\263\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +01:00) \320\221\321\200\321\216\321\201\321\201\320\265\320\273\321\214, \320\232\320\276\320\277\320\265\320\275\320\263\320\260\320\263\320\265\320\275, \320\234\320\260\320\264\321\200\320\270\320\264, \320\237\320\260\321\200\320\270\320\266", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +01:00) \320\222\320\260\321\200\321\210\320\260\320\262\320\260, \320\227\320\260\320\263\321\200\320\265\320\261, \320\241\320\260\321\200\320\260\320\265\320\262\320\276, \320\241\320\272\320\276\320\277\321\214\320\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +01:00) \320\222\320\270\320\275\320\264\321\205\321\203\320\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +01:00) \320\227\320\260\320\277\320\260\320\264\320\275\320\260\321\217 \320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\260\321\217 \320\220\321\204\321\200\320\270\320\272\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\220\320\274\320\260\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\220\321\204\320\270\320\275\321\213, \320\221\321\203\321\205\320\260\321\200\320\265\321\201\321\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\221\320\265\320\271\321\200\321\203\321\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\222\320\270\320\273\321\214\320\275\321\216\321\201, \320\232\320\270\320\265\320\262, \320\240\320\270\320\263\320\260, \320\241\320\276\321\204\320\270\321\217, \320\242\320\260\320\273\320\273\320\270\320\275, \320\245\320\265\320\273\321\214\321\201\320\270\320\275\320\272\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\222\320\276\321\201\321\202\320\276\321\207\320\275\320\260\321\217 \320\225\320\262\321\200\320\276\320\277\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\224\320\260\320\274\320\260\321\201\320\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\230\320\265\321\200\321\203\321\201\320\260\320\273\320\270\320\274", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\232\320\260\320\270\321\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\241\321\202\320\260\320\274\320\261\321\203\320\273", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +02:00) \320\245\320\260\321\200\320\260\321\200\320\265, \320\237\321\200\320\265\321\202\320\276\321\200\320\270\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +03:00) \320\221\320\260\320\263\320\264\320\260\320\264", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +03:00) \320\232\320\260\320\273\320\270\320\275\320\270\320\263\321\200\320\260\320\264, \320\234\320\270\320\275\321\201\320\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +03:00) \320\232\321\203\320\262\320\265\320\271\321\202, \320\255\321\200-\320\240\320\270\321\217\320\264", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +03:00) \320\235\320\260\320\271\321\200\320\276\320\261\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +03:30) \320\242\320\265\320\263\320\265\321\200\320\260\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +04:00) \320\220\320\261\321\203-\320\224\320\260\320\261\320\270, \320\234\321\203\321\201\320\272\320\260\321\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +04:00) \320\221\320\260\320\272\321\203", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +04:00) \320\222\320\276\320\273\320\263\320\276\320\263\321\200\320\260\320\264, \320\234\320\276\321\201\320\272\320\262\320\260, \320\241\320\260\320\275\320\272\321\202-\320\237\320\265\321\202\320\265\321\200\320\261\321\203\321\200\320\263", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +04:00) \320\225\321\200\320\265\320\262\320\260\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +04:00) \320\237\320\276\321\200\321\202-\320\233\321\203\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +04:00) \320\242\320\261\320\270\320\273\320\270\321\201\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +04:30) \320\232\320\260\320\261\321\203\320\273", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +05:00) \320\230\321\201\320\273\320\260\320\274\320\260\320\261\320\260\320\264, \320\232\320\260\321\200\320\260\321\207\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +05:00) \320\242\320\260\321\210\320\272\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +05:30) \320\232\320\276\320\273\320\272\320\260\321\202\320\260, \320\234\321\203\320\274\320\261\320\260\320\270, \320\235\321\214\321\216-\320\224\320\265\320\273\320\270, \320\247\320\265\320\275\320\275\320\260\320\271", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +05:30) \320\250\321\200\320\270-\320\224\320\266\320\260\321\217\320\262\320\260\321\200\320\264\320\265\320\275\320\265-\320\277\321\203\321\200\320\260-\320\232\320\276\321\202\321\202\320\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +05:45) \320\232\320\260\321\202\320\274\320\260\320\275\320\264\321\203", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +06:00) \320\220\321\201\321\202\320\260\320\275\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +06:00) \320\224\321\205\320\260\320\272\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +06:00) \320\225\320\272\320\260\321\202\320\270\321\200\320\270\320\275\320\261\321\203\321\200\320\263", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +06:30) \320\257\320\275\320\263\320\276\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +06:30) \320\240\320\260\320\263\321\203\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +07:00) \320\221\320\260\320\275\320\263\320\272\320\276\320\272, \320\224\320\266\320\260\320\272\320\260\321\200\321\202\320\260, \320\245\320\260\320\275\320\276\320\271", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +07:00) \320\235\320\276\320\262\320\276\321\201\320\270\320\261\320\270\321\200\321\201\320\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +08:00) \320\223\320\276\320\275\320\272\320\276\320\275\320\263, \320\237\320\265\320\272\320\270\320\275, \320\243\321\200\321\203\320\274\321\207\320\270, \320\247\321\203\320\275\321\206\320\270\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +08:00) \320\232\321\200\320\260\321\201\320\275\320\276\321\217\321\200\321\201\320\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +08:00) \320\232\321\203\320\260\320\273\320\260-\320\233\321\203\320\274\320\277\321\203\321\200, \320\241\320\270\320\275\320\263\320\260\320\277\321\203\321\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +08:00) \320\237\320\265\321\200\321\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +08:00) \320\242\320\260\320\271\320\261\321\215\320\271", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +08:00) \320\243\320\273\320\260\320\275-\320\221\320\260\321\202\320\276\321\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +09:00) \320\230\321\200\320\272\321\203\321\202\321\201\320\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +09:00) \320\236\321\201\320\260\320\272\320\260, \320\241\320\260\320\277\320\277\320\276\321\200\320\276, \320\242\320\276\320\272\320\270\320\276", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +09:00) \320\241\320\265\321\203\320\273", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +09:30) \320\220\320\264\320\265\320\273\320\260\320\270\320\264\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +09:30) \320\224\320\260\321\200\320\262\320\270\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +10:00) \320\221\321\200\320\270\321\201\320\261\320\265\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +10:00) \320\223\321\203\320\260\320\274, \320\237\320\276\321\200\321\202-\320\234\320\276\321\200\321\201\320\261\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +10:00) \320\232\320\260\320\275\320\261\320\265\321\200\321\200\320\260, \320\234\320\265\320\273\321\214\320\261\321\203\321\200\320\275, \320\241\320\270\320\264\320\275\320\265\320\271", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +10:00) \320\245\320\276\320\261\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +10:00) \320\257\320\272\321\203\321\202\321\201\320\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +11:00) \320\222\320\273\320\260\320\264\320\270\320\262\320\276\321\201\321\202\320\276\320\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +11:00) \320\241\320\276\320\273\320\276\320\274\320\276\320\275\320\276\320\262\321\213 \320\276-\320\262\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +12:00) \320\222\320\265\320\273\320\273\320\270\320\275\320\263\321\202\320\276\320\275, \320\236\320\272\320\273\320\265\320\275\320\264", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +12:00) \320\222\321\200\320\265\320\274\321\217 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 UTC +12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +12:00) \320\234\320\260\320\263\320\260\320\264\320\260\320\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +12:00) \320\244\320\270\320\264\320\266\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +12:00) \320\235\321\203\320\272\321\203\320\260\320\273\320\276\321\204\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "(UTC +13:00) \320\241\320\260\320\274\320\276\320\260", 0, QApplication::UnicodeUTF8)
        );
        cbSunZenith->clear();
        cbSunZenith->insertItems(0, QStringList()
         << QApplication::translate("GetSunSetRise", "\320\236\320\244\320\230\320\246\320\230\320\220\320\233\320\254\320\235\320\253\320\231", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "\320\223\320\240\320\220\320\226\320\224\320\220\320\235\320\241\320\232\320\230\320\231", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "\320\235\320\220\320\222\320\230\320\223\320\220\320\246\320\230\320\236\320\235\320\235\320\253\320\231", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GetSunSetRise", "\320\220\320\241\320\242\320\240\320\236\320\235\320\236\320\234\320\230\320\247\320\225\320\241\320\232\320\230\320\231", 0, QApplication::UnicodeUTF8)
        );
        bCalc->setText(QApplication::translate("GetSunSetRise", "\320\240\320\260\321\201\321\207\321\221\321\202", 0, QApplication::UnicodeUTF8));
        lResults->setText(QApplication::translate("GetSunSetRise", "\320\236\321\202\320\262\320\265\321\202:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GetSunSetRise: public Ui_GetSunSetRise {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETSUNSETRISE_H
