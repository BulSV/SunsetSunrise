#include "GetSunsetRise.h"

#include <QAction>
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

GetSunsetRise::GetSunsetRise(QWidget* pwgt)
    : QWidget(pwgt)
{
    setupUi(this);

    QFile file(QString(":/timeZonesRC.txt"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Load time zones"),
                              tr("Cannot open file ") + file.fileName());
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        m_timeZones << in.readLine().toDouble();
    }
    file.close();

    QDir dir;
    if(!QDir("scripts").exists()) {
        if(!dir.mkdir("scripts")) {
            QMessageBox::critical(this,
                                  tr("Create directory \"scripts\""),
                                  tr("Cannot create directory \"scripts\""));
        }
    }

    m_menuCities = std::make_unique<QMenu>(this);
    loadCities();

    connect(bCalc, &QPushButton::clicked, this, &GetSunsetRise::calculate);
    connect(m_menuCities.get(), &QMenu::triggered,
            this, &GetSunsetRise::loadSelectedCityCoordinates);
    connect(rbWest, &QRadioButton::clicked, [=](bool checked) {
        rbEast->setChecked(!checked); });
    connect(rbEast, &QRadioButton::toggled, [=](bool checked) {
        rbWest->setChecked(!checked); });

    connect(leLatitude, &QLineEdit::textChanged, this, &GetSunsetRise::clearDataOutput);
    connect(leLongtitude, &QLineEdit::textChanged, this, &GetSunsetRise::clearDataOutput);
    connect(rbEast, &QRadioButton::clicked, this, &GetSunsetRise::clearDataOutput);
    connect(rbWest, &QRadioButton::clicked, this, &GetSunsetRise::clearDataOutput);
    connect(cbTimeZone, &QComboBox::currentTextChanged,
            this, &GetSunsetRise::clearDataOutput);
}

void GetSunsetRise::contextMenuEvent(QContextMenuEvent* e)
{
    m_menuCities->exec(e->globalPos());
}

void GetSunsetRise::calculate()
{
    Data data;
    data.date = calendarWidget->selectedDate();
    bool ok{};
    if(const auto& value = leLongtitude->text().toDouble(&ok); ok) {
        data.coordinates.longitude = value;
    }
    if(const auto& value = leLatitude->text().toDouble(&ok); ok) {
       data.coordinates.latitude = value;
    }
    data.zenith =  static_cast<Data::ZenithType>(cbSunZenith->currentIndex());
    data.localOffset = zoneToTime(cbTimeZone->currentIndex());
    data.calculationType = rbSunSet->isChecked()
            ? Data::CalculationType::Sunset
            : Data::CalculationType::Sunrise;
    data.coordinates.meridian = rbWest->isChecked()
            ? Data::Meridian::West
            : Data::Meridian::East;

    m_sunSetRise->setData(data);
    showResult(m_sunSetRise->calculateConfiguredTime());
}

void GetSunsetRise::showResult(const std::optional<double>& result)
{
    if(result) {
        if(*result == std::numeric_limits<double>::min()) {
            QMessageBox::information(
                        this,
                        "Results",
                        "The sun never rises on this location\n(on the specified date)");
            return;
        } else if(*result == std::numeric_limits<double>::max()) {
            QMessageBox::information(
                        this,
                        "Results",
                        "The sun never sets on this location\n(on the specified date)");
            return;
        } else {
            lResults->setText(tr("%1%2 at %3")
                              .arg(rbSunSet->isChecked() ? tr("Sunset") : tr("Sunrise"))
                              .arg(m_currentCityName.isEmpty()
                                   ? ""
                                   : tr(" in ") + m_currentCityName)
                              .arg(toHumanTime(*result)));
        }
    } else {
        QMessageBox::information(
                    this,
                    "Results",
                    "No input data specified");
        return;
    }
}

void GetSunsetRise::loadSelectedCityCoordinates(QAction* action)
{
    QFile file(QString("scripts/") +
               QString(action->property("cityName").toString()) +
               QString(".js"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr,
                              tr("Load coordinates from script"),
                              tr("Cannot open file ") + file.fileName());

        return;
    }
    clearDataInput();

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

    script = in.readLine();
    int errorsCount = longitudeEngine.evaluate(script).isError() ? 1 : 0;
    script = in.readLine();
    errorsCount += latitudeEngine.evaluate(script).isError() ? 1 : 0;
    script = in.readLine();
    errorsCount += eastEngine.evaluate(script).isError() ? 1 : 0;
    script = in.readLine();
    errorsCount += timeZoneEngine.evaluate(script).isError() ? 1 : 0;

    if(errorsCount != 0) {
        clearDataInput();
        QMessageBox::warning(this,
                             tr("Load coordinates from script"),
                             tr("Script coordinates are not valid!"));
        return;
    }

    file.close();

    m_currentCityName = action->property("cityName").toString();
}

void GetSunsetRise::clearDataInput()
{
    leLatitude->clear();
    leLongtitude->clear();
    rbEast->setChecked(true);
    rbSunSet->setChecked(true);
    cbSunZenith->setCurrentIndex(0);
    cbTimeZone->setCurrentIndex(0);
    lResults->setText(tr("None"));
    m_currentCityName.clear();
}

void GetSunsetRise::clearDataOutput()
{
    m_currentCityName.clear();
    lResults->setText(tr("None"));
}

std::optional<double> GetSunsetRise::zoneToTime(int index) const
{
    if(index < 0 || index >= m_timeZones.size()) {
        QMessageBox::warning(nullptr,
                             tr("Calculate"),
                             tr("The time zone was selected an incorrect way!"));

        return std::nullopt;
    }

    return m_timeZones.at(index);
}

QString GetSunsetRise::toHumanTime(double preResult) const
{
    return QString("%1").arg(preResult, 5, 'f', 2, QChar('0')).replace(".", ":");
}

std::optional<QDir> GetSunsetRise::directoryOf(const QString& subdir) const
{
    QDir dir(QApplication::applicationDirPath());
    dir.cd(subdir);

    return dir;
}

void GetSunsetRise::loadCities()
{
    if(const auto& scriptsDir = directoryOf("scripts")) {
        QStringList fileNames = scriptsDir->entryList(QStringList("*.js"), QDir::Files);

        for(const auto& fileName : fileNames) {
            QString text = fileName;
            text.chop(3);
            QAction *city = new QAction(text, m_menuCities.get());
            city->setProperty("cityName", text);
            m_menuCities->addAction(city);
        }
    }
}
