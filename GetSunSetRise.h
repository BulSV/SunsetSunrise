#include <memory>

#include <QContextMenuEvent>
#include <QDir>
#include <QList>
#include <QMenu>
#include <QWidget>

#include "debug.h"
#include "sunsetrise.h"
#include "ui_GetSunSetRise.h"

class GetSunSetRise : public QWidget, public Ui::GetSunSetRise
{
    Q_OBJECT

public:
    GetSunSetRise(QWidget *pwgt = nullptr);

protected:
    virtual void contextMenuEvent(QContextMenuEvent *pe)
    {
        m_menuCities->exec(pe->globalPos());
    }

private:
    void calc();
    void clickedCity(QAction *pAction);
    qreal zoneToTime(const int &index);
    QString toHumanTime(double preResult);
    QDir directoryOf(const QString &subdir);
    void addCities();

private:
    std::unique_ptr<SunSetRise> m_sunSetRise = std::make_unique<SunSetRise>();
    std::unique_ptr<QMenu> m_menuCities;
    QList<double> m_timeZones;
};
