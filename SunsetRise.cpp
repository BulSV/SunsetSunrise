#include "SunsetRise.h"

#include <qmath.h>

#include <QMessageBox>

#include "functions.h"

namespace
{
constexpr double ZENITH_OFFICIAL = 90.0 + 5.0 / 6.0;
constexpr double ZENITH_CIVIL = 96.0;
constexpr double ZENITH_NAUTICAL = 102.0;
constexpr double ZENITH_ASTRONOMICAL = 108.0;
} // namespace

using namespace functions;

SunsetRise::SunsetRise()
    : m_day(0)
    , m_month(0)
    , m_year(0)
    , m_longitude(0.0)
    , m_latitude(0.0)
    , m_zenith(0.0)
    , m_localOffset(0.0)
    , m_isSet(true)
    , m_isWest(true)
{
}

void SunsetRise::setDay(int day)
{
    m_day = day;
}

void SunsetRise::setMonth(int month)
{
    m_month = month;
}

void SunsetRise::setYear(int year)
{
    m_year = year;
}

void SunsetRise::setZenith(ZENITH zenith)
{
    switch(zenith)
    {
    case ZENITH::OFFICIAL:
        m_zenith = ZENITH_OFFICIAL;
        break;
    case ZENITH::CIVIL:
        m_zenith = ZENITH_CIVIL;
        break;
    case ZENITH::NAUTICAL:
        m_zenith = ZENITH_NAUTICAL;
        break;
    case ZENITH::ASTRONOMICAL:
        m_zenith = ZENITH_ASTRONOMICAL;
        break;
    }
}

void SunsetRise::setLoclOffset(double timeOffset)
{
    m_localOffset = timeOffset;
}

void SunsetRise::setLongtitude(double longtitude)
{
    m_longitude = longtitude;
}

void SunsetRise::setLatitude(double latitude)
{
    m_latitude = latitude;
}

void SunsetRise::setSetOrRise(bool isSet)
{
    m_isSet = isSet;
}

void SunsetRise::setEastOrWest(bool isWest)
{
    m_isWest = isWest;
}

double SunsetRise::minutesToDegrees(double minutes) const
{
    return ((100.0 * minutes) / 60.0);
}

double SunsetRise::degreesToRadians(double degrees) const
{
    return ((degrees * 4.0 * qAtan(1.0)) / 180.0);
}

double SunsetRise::radiansToDegrees(double radians) const
{
    return ((radians * 180.0) / (4.0 * qAtan(1.0)));
}

double SunsetRise::toHumanTime(double time) const
{
    int hours;
    double minutes;

    hours = static_cast<int>(time);
    minutes = time - hours;
    minutes = (minutes * 60.0) / 100.0; // round to 0.01
    return static_cast<double>(hours) + static_cast<double>(round(static_cast<float>(minutes), 2));
}

//1. first calculate the day of the year
int SunsetRise::whatDay() const
{
    int N;
    int N1;
    int N2;
    int N3;

    N1 = qFloor(275.0 * m_month / 9.0);
    N2 = qFloor((m_month + 9.0) / 12.0);
    N3 = (1 + qFloor((m_year - 4.0 * qFloor(m_year / 4.0) + 2.0) / 3.0));
    N = N1 - (N2 * N3) + m_day - 30;

    return N;
}

//2. convert the longitude to hour value and calculate an approximate time
double SunsetRise::longtitudeToHour() const
{
    double lngHour;
    double t;

    lngHour = m_longitude / 15.0;
    if(!m_isSet) {
        t = whatDay() + ((6.0 - lngHour) / 24.0);
    } else {
        t = whatDay() + ((18.0 - lngHour) / 24.0);
    }

    return t;
}

//3. calculate the Sun's mean anomaly
double SunsetRise::sunsMeanAnomaly() const
{
    return ((0.9856 * longtitudeToHour()) - 3.289);
}

//4. calculate the Sun's true longitude
double SunsetRise::sunsTrueLongtitude() const
{
    double L;

    L = sunsMeanAnomaly() + (1.916 * qSin(degreesToRadians(sunsMeanAnomaly()))) + (0.020 * qSin(degreesToRadians(2.0 * sunsMeanAnomaly()))) + 282.634;

    if(L > 360.0 || qFuzzyCompare(L, 360.0)) L -= 360.0;
    if(L < 0) L += 360.0;

    return L;
}

//5a. calculate the Sun's right ascension
double SunsetRise::sunsRightAscension() const
{
    double RA;
    int Lquadrant;
    int RAquadrant;

    RA = qAtan(0.91764 * qTan(degreesToRadians(sunsTrueLongtitude())));
    RA = radiansToDegrees(RA);
    Lquadrant = qFloor(sunsTrueLongtitude() / 90.0) * 90;
    RAquadrant = qFloor(RA / 90.0) * 90;
    RA = RA + (Lquadrant - RAquadrant);

    if(RA > 360.0 || qFuzzyCompare(RA, 360.0)) RA -= 360.0;
    if(RA < 0) RA += 360.0;

    RA /= 15.0;

    return RA;
}

//6. calculate the Sun's declination
double SunsetRise::sunsDeclination() const
{
    double sinDec;
    double cosDec;
    double cosH;
    double H;

    sinDec = 0.39782 * qSin(degreesToRadians(sunsTrueLongtitude()));
    cosDec = qCos(qAsin(sinDec));
    //7a. calculate the Sun's local hour angle
    cosH = (qCos(degreesToRadians(m_zenith)) - (sinDec * qSin(degreesToRadians(m_latitude)))) / (cosDec * qCos(degreesToRadians(m_latitude)));
    if (cosH >  1.0) {
        //the sun never rises on this location (on the specified date)
        QMessageBox::information(nullptr, "Information", "The sun never rises on this location\n(on the specified date)");
    }
    if (cosH < -1.0) {
        //the sun never sets on this location (on the specified date)
        QMessageBox::information(nullptr, "Information", "The sun never sets on this location\n(on the specified date)");
    }
    //7b. finish calculating H and convert into hours
    if(!m_isSet) {
        H = 360.0 - radiansToDegrees(qAcos(cosH));
    } else {
        H = radiansToDegrees(qAcos(cosH));
    }
    H /= 15.0;

    return H;
}

//8. calculate local mean time of rising/setting
double SunsetRise::localMeanTime() const
{
    double T;
    T = sunsDeclination() + sunsRightAscension() - (0.06571 * longtitudeToHour()) - 6.622;

    return T;
}

//9. adjust back to UTC
double SunsetRise::toUTC() const
{
    double lngHour;
    double UT;

    lngHour = m_longitude / 15.0;
    UT = localMeanTime() - lngHour;

    if(UT > 24.0 || qFuzzyCompare(UT, 24.0)) {
        UT -= 24.0;
    }
    if(UT < 0) {
        UT += 24.0;
    }

    return UT;
}

//10. convert UT value to local time zone of latitude/longitude
double SunsetRise::utToLocalTimeZone() const
{
    double localT;
    localT = round(toUTC() + sextaToDeca(m_localOffset), 2);

    return toHumanTime(localT);
}

double SunsetRise::getConfiguredTime()
{
    if(m_isWest) {
        m_longitude *= -1.0;
    }

    return utToLocalTimeZone();
}
