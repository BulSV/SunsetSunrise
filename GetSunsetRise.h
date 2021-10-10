#ifndef GETSUNSETRISE_H
#define GETSUNSETRISE_H

#include <memory>
#include <optional>

#include <QContextMenuEvent>
#include <QDir>
#include <QList>
#include <QMenu>
#include <QWidget>

#include "SunsetRise.h"
#include "ui_GetSunsetRise.h"

class GetSunsetRise : public QWidget, public Ui::GetSunSetRise
{
    Q_OBJECT

public:
    explicit GetSunsetRise(QWidget* pwgt = nullptr);

protected:
    virtual void contextMenuEvent(QContextMenuEvent* e);

private:
    void calculate();
    void showResult(const std::optional<double>& result);
    void loadSelectedCityCoordinates(QAction* action);
    void clearDataInput();
    void clearDataOutput();
    std::optional<double> zoneToTime(int index) const;
    QString toHumanTime(double preResult) const;
    std::optional<QDir> directoryOf(const QString& subdir) const;
    void loadCities();

private:
    std::unique_ptr<SunsetRise> m_sunSetRise = std::make_unique<SunsetRise>();
    std::unique_ptr<QMenu> m_menuCities;
    QList<double> m_timeZones;
    QString m_currentCityName;
};

#endif // GETSUNSETRISE
