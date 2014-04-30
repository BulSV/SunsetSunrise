#include "debug.h"
#include <QWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QDir>
#include <QList>
#include "ui_GetSunSetRise.h"
#include "sunsetrise.h"

//const int numTimeZones = 75;

class GetSunSetRise : public QWidget, public Ui::GetSunSetRise
{
    Q_OBJECT
    SunSetRise *sunSetRisen;
    QMenu *menuCities;
    QList<float> timeZones;

    qreal zoneToTime(const int &index);
    QString toHumanTime(float preResult);
    QDir directoryOf(const QString &subdir);
    void addCities();
protected:
    virtual void contextMenuEvent(QContextMenuEvent *pe)
    {
        menuCities->exec(pe->globalPos());
    }

public:
    GetSunSetRise(QWidget *pwgt = 0);
public slots:
    void calc();
    void clickedCity(QAction *pAction);
};
