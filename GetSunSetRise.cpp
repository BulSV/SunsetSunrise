#include "GetSunSetRise.h"

#include <QAction>
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

#include "functions.h"

GetSunSetRise::GetSunSetRise(QWidget *pwgt)
    : QWidget(pwgt)
{
    setupUi(this);
    QFile file(QString(":/timeZonesRC.txt"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "ERROR", "Cannot open file " + file.fileName());
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
#ifdef DEBUG
        QString str = in.readLine();
        timeZones << str.toFloat();
        qDebug() << "str =" << str;
#endif
#ifndef DEBUG
        m_timeZones << in.readLine().toDouble();
#endif
    }
    file.close();
#ifdef DEBUG
    qDebug() << "timeZones =" << timeZones;
#endif
    QDir dir;
    if(!QDir("scripts").exists()) {
        if(!dir.mkdir("scripts")) {
            QMessageBox::critical(nullptr, "ERROR", "Cannot create directory \"scripts\"");
        }
    }

    m_menuCities = std::make_unique<QMenu>(this);
    addCities();

    connect(bCalc, &QPushButton::clicked, this, &GetSunSetRise::calc);
    connect(m_menuCities.get(), &QMenu::triggered, this , &GetSunSetRise::clickedCity);
}

void GetSunSetRise::calc()
{
    m_sunSetRise->setDay(calendarWidget->selectedDate().day());
    m_sunSetRise->setMonth(calendarWidget->selectedDate().month());
    m_sunSetRise->setYear(calendarWidget->selectedDate().year());
    m_sunSetRise->setLongtitude(leLongtitude->text().toDouble());
    m_sunSetRise->setLatitude(leLatitude->text().toDouble());
    m_sunSetRise->setZenith(static_cast<SunSetRise::ZENITH>(cbSunZenith->currentIndex()));
    m_sunSetRise->setLoclOffset(zoneToTime(cbTimeZone->currentIndex()));
    m_sunSetRise->setSetOrRise(rbSunSet->isChecked());
    m_sunSetRise->setEastOrWest(rbWest->isChecked());

    if(rbSunSet->isChecked()) {
        lResults->setText(QString::fromUtf8("Закат в ") + toHumanTime(static_cast<double>(m_sunSetRise->result())));
    } else {
        lResults->setText(QString::fromUtf8("Восход в ") + toHumanTime(static_cast<double>(m_sunSetRise->result())));
    }
}

void GetSunSetRise::clickedCity(QAction *pAction)
{
    QFile file(QString("scripts/") + QString(pAction->property("cityName").toString()) + QString(".js"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "ERROR", "Cannot open file " + file.fileName());

        return;
    }

    QTextStream in(&file);
    QString script;

    QScriptEngine longitudeEngine;
    QScriptValue longitude = longitudeEngine.newQObject(leLongtitude);
    longitudeEngine.globalObject().setProperty("longitude", longitude);

    QScriptEngine latitudeEngine;
    QScriptValue latitude = latitudeEngine.newQObject(leLatitude);
    latitudeEngine.globalObject().setProperty("latitude", latitude);

    QScriptEngine eastEngine;
    QScriptValue east = eastEngine.newQObject(rbEast);
    eastEngine.globalObject().setProperty("east", east);

    QScriptEngine timeZoneEngine;
    QScriptValue timeZone = timeZoneEngine.newQObject(cbTimeZone);
    timeZoneEngine.globalObject().setProperty("timeZone", timeZone);

    while(!in.atEnd()) {
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
    if(m_timeZones.size() < index + 1) {
        QMessageBox::critical(nullptr, "ERROR", "The time zone was selected an incorrect way!");

        return 0.0;
    }

    return m_timeZones.at(index);
}

QString GetSunSetRise::toHumanTime(double preResult)
{
    QString hours = QString::number(static_cast<int>(preResult));
    QString minutes = QString::number(functions::round(preResult - static_cast<double>(static_cast<int>(preResult)), 2));

    switch (hours.size()) {
    case 0:
        hours.push_front('0');
        hours.push_front('0');
        break;
    case 1:
        hours.push_front('0');
        break;
    default:
        break;
    }
#ifdef DEBUG
    qDebug() << "minuts.size() =" << minuts.size();
#endif
    // maximum size of minutes if 5: "-0.xx". It is always less than one in absolute value
    switch (minutes.size()) {
    case 0: // ""
        minutes.push_back('0');
        minutes.push_back('0');
        break;
    case 1: // "0"
        minutes.push_back('0');
        break;
    case 3: // "0.x"
        minutes.remove(0, 2); // remove "0."
        minutes.push_back('0');
        break;
    case 4:
        if(minutes.indexOf("-") != -1) { // "-0.x"
            minutes.remove(0, 3);
            minutes.push_back('0');
        } else { // "0.xx"
            minutes.remove(0, 2);
        }
        break;
    case 5:
        minutes.remove(0, 3); // remove "-0."
        break;
    default: // "0."
        minutes.remove(0, 2);
        break;
    }
#ifdef DEBUG
    qDebug() << "minuts.size() =" << minuts.size();
#endif

    return QString(hours + ':' + minutes);
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

    for(const auto& fileName : fileNames) {
        QString text = fileName;
        text.chop(3);
        QAction *city = new QAction(text, m_menuCities.get());
        city->setProperty("cityName", text);
        m_menuCities->addAction(city);
    }
}
