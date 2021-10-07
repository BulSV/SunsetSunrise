#include "SunsetRise.h"

#include <qmath.h>

#include <QMessageBox>
#include <QtMath>

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
    : m_longitude(0.0)
    , m_latitude(0.0)
    , m_zenith(0.0)
    , m_localOffset(0.0)
    , m_isSet(true)
    , m_isWest(true)
{
}

void SunsetRise::setDate(const QDate &date)
{
    m_date = date;
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
    return (100.0 * minutes) / 60.0;
}

double SunsetRise::toHumanTime(double time) const
{
    auto hours = static_cast<int>(time);
    auto minutes = time - hours;
    minutes = (minutes * 60.0) / 100.0; // round to 0.01
    return static_cast<double>(hours) +
            static_cast<double>(round(static_cast<double>(minutes), 2));
}

//2. convert the longitude to hour value and calculate an approximate time
double SunsetRise::longtitudeToHour() const
{
    auto lngHour = m_longitude / 15.0;
    if(m_isSet) {
        return m_date.dayOfYear() + ((18.0 - lngHour) / 24.0);
    }
    return m_date.dayOfYear() + ((6.0 - lngHour) / 24.0);
}

//3. calculate the Sun's mean anomaly
double SunsetRise::sunsMeanAnomaly() const
{
    return ((0.9856 * longtitudeToHour()) - 3.289);
}

//4. calculate the Sun's true longitude
double SunsetRise::sunsTrueLongtitude() const
{
    auto L = sunsMeanAnomaly() + (1.916 * qSin(qDegreesToRadians(sunsMeanAnomaly()))) +
            (0.020 * qSin(qDegreesToRadians(2.0 * sunsMeanAnomaly()))) + 282.634;

    if(L > 360.0 || qFuzzyCompare(L, 360.0)) {
        L -= 360.0;
    }
    if(L < 0) {
        L += 360.0;
    }

    return L;
}

//5a. calculate the Sun's right ascension
double SunsetRise::sunsRightAscension() const
{
    auto RA = qAtan(0.91764 * qTan(qDegreesToRadians(sunsTrueLongtitude())));
    RA = qRadiansToDegrees(RA);
    auto Lquadrant = qFloor(sunsTrueLongtitude() / 90.0) * 90;
    auto RAquadrant = qFloor(RA / 90.0) * 90;
    RA = RA + (Lquadrant - RAquadrant);

    if(RA > 360.0 || qFuzzyCompare(RA, 360.0)) {
        RA -= 360.0;
    }
    if(RA < 0) {
        RA += 360.0;
    }

    RA /= 15.0;

    return RA;
}

//6. calculate the Sun's declination
double SunsetRise::sunsDeclination() const
{
    auto sinDec = 0.39782 * qSin(qDegreesToRadians(sunsTrueLongtitude()));
    auto cosDec = qCos(qAsin(sinDec));
    //7a. calculate the Sun's local hour angle
    auto cosH = (qCos(qDegreesToRadians(m_zenith)) -
                 (sinDec * qSin(qDegreesToRadians(m_latitude)))) /
            (cosDec * qCos(qDegreesToRadians(m_latitude)));
    if (cosH >  1.0) {
        //the sun never rises on this location (on the specified date)
        QMessageBox::information(
                    nullptr,
                    "Information",
                    "The sun never rises on this location\n(on the specified date)");
    }
    if (cosH < -1.0) {
        //the sun never sets on this location (on the specified date)
        QMessageBox::information(
                    nullptr,
                    "Information",
                    "The sun never sets on this location\n(on the specified date)");
    }
    //7b. finish calculating H and convert into hours
    if(m_isSet) {
        return qRadiansToDegrees(qAcos(cosH)) / 15.0;
    }
    return (360.0 - qRadiansToDegrees(qAcos(cosH))) / 15.0;
}

//8. calculate local mean time of rising/setting
double SunsetRise::localMeanTime() const
{
    auto T = sunsDeclination() + sunsRightAscension() -
            (0.06571 * longtitudeToHour()) - 6.622;

    return T;
}

//9. adjust back to UTC
double SunsetRise::toUTC() const
{
    auto lngHour = m_longitude / 15.0;
    auto UT = localMeanTime() - lngHour;

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
    auto localT = round(toUTC() + sextaToDeca(m_localOffset), 2);

    return toHumanTime(localT);
}

double SunsetRise::getConfiguredTime()
{
    if(m_isWest) {
        m_longitude *= -1.0;
    }

    return utToLocalTimeZone();
}
