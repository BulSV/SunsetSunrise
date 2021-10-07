#ifndef SUNSETRISE_H
#define SUNSETRISE_H

#include <QDate>

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
    void setDate(const QDate& date);
    void setLongtitude(double longtitude);
    void setLatitude(double latitude);
    void setZenith(ZENITH zenith);
    void setLoclOffset(double timeOffset);
    void setSetOrRise(bool isSet);
    void setEastOrWest(bool isWest);
    double getConfiguredTime();

private:
    double minutesToDegrees(double minutes) const;
    double toHumanTime(double time) const;

    double longtitudeToHour() const;
    double sunsMeanAnomaly() const;
    double sunsTrueLongtitude() const;
    double sunsRightAscension() const;
    double sunsDeclination() const;
    double localMeanTime() const;
    double toUTC() const;
    double utToLocalTimeZone() const;

private:
    QDate m_date;
    double m_longitude;
    double m_latitude;
    double m_zenith;
    double m_localOffset;
    bool m_isSet;
    bool m_isWest;
};

#endif // SUNSETRISE_H

