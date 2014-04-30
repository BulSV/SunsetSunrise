#ifndef SUNSETRISE_H
#define SUNSETRISE_H

#include "debug.h"
#include <QApplication>

const qreal ZENITH_OFFICIAL = 90.0+5.0/6.0;
const qreal ZENITH_CIVIL = 96.0;
const qreal ZENITH_NAUTICAL = 102.0;
const qreal ZENITH_ASTRONOMICAL = 108.0;

class SunSetRise
{    
    int itsDay;
    int itsMonth;
    int itsYear;
    qreal itsLongitude; // долгота
    qreal itsLatitude; // широта
    qreal itsZenith;
    int itsLocalOffset; // часовой пояс +2 для Киева
    bool itsIsSet;
    bool itsIsWest;

    qreal minutesToDegrees(const qreal &minutes) const;
    qreal degreesToRadians(const qreal &degrees) const;
    qreal radiansToDegrees(const qreal &radians) const;
    qreal toHumanTime(const qreal &time) const;

    int whatDay() const;
    qreal longtitudeToHour() const;
    qreal sunsMeanAnomaly() const;
    qreal sunsTrueLongtitude() const;
    qreal sunsRightAscension() const;
    qreal sunsDeclination() const;
    qreal localMeanTime() const;
    qreal toUTC() const;
    qreal utToLocalTimeZone() const;

public:
    enum ZENITH {OFFICIAL=0, CIVIL, NAUTICAL, ASTRONOMICAL};
    SunSetRise();
    SunSetRise(int day,
               int month,
               int year,
               qreal longtitude,
               qreal latitude,
               qreal zenith,
               int localOffset,
               bool isSet,
               bool isWest);
    void setDay(const int &day);
    void setMonth(const int &month);
    void setYear(const int &year);
    void setLongtitude(const qreal &longtitude);
    void setLatitude(const qreal &latitude);
    void setZenith(const ZENITH &zenith);
    void setLoclOffset(const qreal &timeOffset);
    void setSetOrRise(const bool &isSet);
    void setEastOrWest(const bool &isWest);
    qreal result();
};

#endif // SUNSETRISE_H

