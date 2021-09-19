#ifndef SUNSETRISE_H
#define SUNSETRISE_H

#include "debug.h"
#include "functions.h"

class SunSetRise
{
public:
    enum class ZENITH {
        OFFICIAL,
        CIVIL,
        NAUTICAL,
        ASTRONOMICAL
    };
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

private:
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

private:
    int m_day;
    int m_month;
    int m_year;
    qreal m_longitude; // долгота
    qreal m_latitude; // широта
    qreal m_zenith;
    qreal m_localOffset; // часовой пояс +2 для Киева
    bool m_isSet;
    bool m_isWest;
};

#endif // SUNSETRISE_H

