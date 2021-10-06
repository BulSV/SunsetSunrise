#ifndef SUNSETRISE_H
#define SUNSETRISE_H

#include "functions.h"

class SunsetRise
{
public:
    enum class ZENITH {
        OFFICIAL,
        CIVIL,
        NAUTICAL,
        ASTRONOMICAL
    };
    SunsetRise();
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    void setLongtitude(double longtitude);
    void setLatitude(double latitude);
    void setZenith(ZENITH zenith);
    void setLoclOffset(double timeOffset);
    void setSetOrRise(bool isSet);
    void setEastOrWest(bool isWest);
    double getConfiguredTime();

private:
    double minutesToDegrees(double minutes) const;
    double degreesToRadians(double degrees) const;
    double radiansToDegrees(double radians) const;
    double toHumanTime(double time) const;

    int whatDay() const;
    double longtitudeToHour() const;
    double sunsMeanAnomaly() const;
    double sunsTrueLongtitude() const;
    double sunsRightAscension() const;
    double sunsDeclination() const;
    double localMeanTime() const;
    double toUTC() const;
    double utToLocalTimeZone() const;

private:
    int m_day;
    int m_month;
    int m_year;
    double m_longitude;
    double m_latitude;
    double m_zenith;
    double m_localOffset;
    bool m_isSet;
    bool m_isWest;
};

#endif // SUNSETRISE_H

