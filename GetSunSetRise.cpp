#include "GetSunSetRise.h"
#include <QMessageBox>
#include <QAction>
#include <QStringList>
#include <QFile>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QTextStream>
#include "bulsv_lib.h"

GetSunSetRise::GetSunSetRise(QWidget *pwgt)
    : QWidget(pwgt)    
    , sunSetRisen(new SunSetRise)
{    
    setupUi(this);
    QFile file(QString("scripts/timeZonesRC.txt"));
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(0, "ERROR", "Cannot open file " + file.fileName());
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
#ifdef DEBUG
        QString str = in.readLine();
        timeZones << str.toFloat();
        qDebug() << "str =" << str;
#endif
#ifndef DEBUG
        timeZones << in.readLine().toFloat(); // можно и append вместо <<
#endif
    }
    file.close();
#ifdef DEBUG
    qDebug() << "timeZones =" << timeZones;
#endif
    QDir dir;

    if(!QDir("scripts").exists())
    {
        if(!dir.mkdir("scripts"))
        {
            QMessageBox::critical(0, "ERROR", "Cannot create directory \"scripts\"");
        }
    }
    menuCities = new QMenu(this);
    addCities();

    connect(bCalc, SIGNAL(clicked()), this, SLOT(calc()));
    connect(menuCities, SIGNAL(triggered(QAction*)), this , SLOT(clickedCity(QAction*)));
}

void GetSunSetRise::calc()
{
    sunSetRisen->setDay(calendarWidget->selectedDate().day());
    sunSetRisen->setMonth(calendarWidget->selectedDate().month());
    sunSetRisen->setYear(calendarWidget->selectedDate().year());    
    sunSetRisen->setLongtitude(leLongtitude->text().toFloat());
    sunSetRisen->setLatitude(leLatitude->text().toFloat());
    sunSetRisen->setZenith((SunSetRise::ZENITH)cbSunZenith->currentIndex());
    sunSetRisen->setLoclOffset(zoneToTime(cbTimeZone->currentIndex()));
    sunSetRisen->setSetOrRise(rbSunSet->isChecked());
    sunSetRisen->setEastOrWest(rbWest->isChecked());

    if(rbSunSet->isChecked())
        lResults->setText(QString::fromUtf8("Закат в ") + toHumanTime((float)sunSetRisen->result()));
    else
        lResults->setText(QString::fromUtf8("Восход в ") + toHumanTime((float)sunSetRisen->result()));
}

void GetSunSetRise::clickedCity(QAction *pAction)
{
    QFile file(QString("scripts/") + QString(pAction->property("cityName").toString()) + QString(".js"));
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(0, "ERROR", "Cannot open file " + file.fileName());
    }
    QTextStream in(&file);
//    in.setCodec("UTF-8");
    QString script;

    // долгота
    QScriptEngine longitudeEngine;
    QScriptValue longitude = longitudeEngine.newQObject(leLongtitude);
    longitudeEngine.globalObject().setProperty("longitude", longitude);
    // широта
    QScriptEngine latitudeEngine;
    QScriptValue latitude = latitudeEngine.newQObject(leLatitude);
    latitudeEngine.globalObject().setProperty("latitude", latitude);
    // восток
    QScriptEngine eastEngine;
    QScriptValue east = eastEngine.newQObject(rbEast);
    eastEngine.globalObject().setProperty("east", east);
    // часовой пояс
    QScriptEngine timeZoneEngine;
    QScriptValue timeZone = timeZoneEngine.newQObject(cbTimeZone);
    timeZoneEngine.globalObject().setProperty("timeZone", timeZone);

    while(!in.atEnd())
    {
        script = in.readLine();
        longitudeEngine.evaluate(script);
        script = in.readLine();
        latitudeEngine.evaluate(script);
        script = in.readLine();
        eastEngine.evaluate(script);
        script = in.readLine();
        timeZoneEngine.evaluate(script);
    }

    file.close();
}


qreal GetSunSetRise::zoneToTime(const int &index)
{
    if(timeZones.size() < index + 1)
    {
        QMessageBox::critical(0, "ERROR", "The time zone was selected an incorrect way!");
        return 0;
    }
    return timeZones.at(index);
}

QString GetSunSetRise::toHumanTime(float preResult)
{
    QString hours = QString::number((int)preResult);
    QString minuts = QString::number(BLib::round(preResult - (int)preResult, 2));

    switch (hours.size())
    {
    case 0: hours.push_front('0');
        hours.push_front('0');
        break;
    case 1: hours.push_front('0');
        break;
    default: break;
    }
#ifdef DEBUG
    qDebug() << "minuts.size() =" << minuts.size();
#endif
    switch (minuts.size())
    {
    case 0: minuts.push_back('0');
        minuts.push_back('0');
        break;
    case 1: minuts.push_back('0');
        break;
    case 3: minuts.remove(0, 2);
        minuts.push_back('0');
        break;
    case 4: if(minuts < 0)
        {
            minuts.remove(0, 3);
            minuts.push_back('0');
        }
        else
        {
            minuts.remove(0, 2);
        }
        break;
    case 5: minuts.remove(0, 3);
        break;
    default: minuts.remove(0, 2);
        break;
    }
#ifdef DEBUG
    qDebug() << "minuts.size() =" << minuts.size();
#endif
    return QString(hours + ':' + minuts);
}

QDir GetSunSetRise::directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());

    dir.cd(subdir);
#ifdef DEBUG
    qDebug() << "QApplication::applicationDirPath() =" << QApplication::applicationDirPath();
#endif
    return dir;
}

void GetSunSetRise::addCities()
{
    QDir scriptsDir = directoryOf("scripts");
    QStringList fileNames = scriptsDir.entryList(QStringList("*.js"), QDir::Files);

    foreach(QString fileName, fileNames)
    {
        QString text = fileName;
        text.chop(3);
        QAction *city = new QAction(text, menuCities);
        city->setProperty("cityName", text);
        menuCities->addAction(city);
    }
}
