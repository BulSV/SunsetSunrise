#include <memory>

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
    explicit GetSunsetRise(QWidget *pwgt = nullptr);

protected:
    virtual void contextMenuEvent(QContextMenuEvent *pe);

private:
    void calc();
    void clickedCity(QAction *pAction);
    qreal zoneToTime(const int &index);
    QString toHumanTime(double preResult);
    QDir directoryOf(const QString &subdir);
    void addCities();

private:
    std::unique_ptr<SunsetRise> m_sunSetRise = std::make_unique<SunsetRise>();
    std::unique_ptr<QMenu> m_menuCities;
    QList<double> m_timeZones;
};
