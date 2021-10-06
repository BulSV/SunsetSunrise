#ifndef SUNSETRISE_H
#define SUNSETRISE_H

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
    void setDay(const int &day);
    void setMonth(const int &month);
    void setYear(const int &year);
    void setLongtitude(const double &longtitude);
    void setLatitude(const double &latitude);
    void setZenith(const ZENITH &zenith);
    void setLoclOffset(const double &timeOffset);
    void setSetOrRise(const bool &isSet);
    void setEastOrWest(const bool &isWest);
    double result();

private:
    double minutesToDegrees(const double &minutes) const;
    double degreesToRadians(const double &degrees) const;
    double radiansToDegrees(const double &radians) const;
    double toHumanTime(const double &time) const;

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

