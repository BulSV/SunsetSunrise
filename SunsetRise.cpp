#include "SunsetRise.h"

#include <QtMath>

#include "functions.h"

namespace
{
constexpr double ZENITH_OFFICIAL = 90.0 + 5.0 / 6.0;
constexpr double ZENITH_CIVILIAN = 96.0;
constexpr double ZENITH_NAUTICAL = 102.0;
constexpr double ZENITH_ASTRONOMICAL = 108.0;
} // namespace

using namespace functions;

SunsetRise::SunsetRise()
{
}

void SunsetRise::setData(const SunsetRise::Data& data)
{
    m_data = data;
}

void SunsetRise::setDate(const QDate &date)
{
    m_date = date;
}

void SunsetRise::setZenith(ZenithType zenith)
{
    switch(zenith)
    {
    case ZenithType::Official:
        m_zenith = ZENITH_OFFICIAL;
        break;
    case ZenithType::Civilian:
        m_zenith = ZENITH_CIVILIAN;
        break;
    case ZenithType::Nautical:
        m_zenith = ZENITH_NAUTICAL;
        break;
    case ZenithType::Astronomical:
        m_zenith = ZENITH_ASTRONOMICAL;
        break;
    }
}

void SunsetRise::setLoclOffset(const std::optional<double> &timeOffset)
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

void SunsetRise::setCalculationType(CalculationType type)
{
    m_calculationType = type;
}

void SunsetRise::setMeridian(Meridian meridian)
{
    m_meridian = meridian;
    if(m_meridian == Meridian::West) {
        m_longitude.value() *= -1.0;
    }
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
    auto lngHour = m_longitude.value() / 15.0;
    if(*m_calculationType == CalculationType::Sunset) {
        return m_date.dayOfYear() + (18.0 - lngHour) / 24.0;
    }
    return m_date.dayOfYear() + (6.0 - lngHour) / 24.0;
}

//3. calculate the Sun's mean anomaly
double SunsetRise::sunsMeanAnomaly() const
{
    return 0.9856 * longtitudeToHour() - 3.289;
}

//4. calculate the Sun's true longitude
double SunsetRise::sunsTrueLongtitude() const
{
    auto L = sunsMeanAnomaly() + (1.916 * qSin(qDegreesToRadians(sunsMeanAnomaly()))) +
            0.020 * qSin(qDegreesToRadians(2.0 * sunsMeanAnomaly())) + 282.634;

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
    auto cosH = (qCos(qDegreesToRadians(m_zenith.value())) -
                 sinDec * qSin(qDegreesToRadians(m_latitude.value()))) /
            (cosDec * qCos(qDegreesToRadians(m_latitude.value())));
    if (cosH >  1.0) {
        //the sun never rises on this location (on the specified date)
        return std::numeric_limits<double>::min();
    }
    if (cosH < -1.0) {
        //the sun never sets on this location (on the specified date)
        return std::numeric_limits<double>::max();
    }
    //7b. finish calculating H and convert into hours
    if(*m_calculationType == CalculationType::Sunset) {
        return qRadiansToDegrees(qAcos(cosH)) / 15.0;
    }
    return (360.0 - qRadiansToDegrees(qAcos(cosH))) / 15.0;
}

//8. calculate local mean time of rising/setting
double SunsetRise::localMeanTime() const
{
    if(const auto& declination = sunsDeclination();
            declination == std::numeric_limits<double>::min() ||
            declination == std::numeric_limits<double>::max()) {
        return declination;
    } else {
        return declination + sunsRightAscension() - 0.06571 * longtitudeToHour() - 6.622;
    }
}

//9. adjust back to UTC
double SunsetRise::toUTC() const
{
    if(const auto& meanTime = localMeanTime();
            meanTime == std::numeric_limits<double>::min() ||
            meanTime == std::numeric_limits<double>::max()) {
        return meanTime;
    } else {
        auto lngHour = m_longitude.value() / 15.0;
        auto UT = meanTime - lngHour;

        if(UT > 24.0 || qFuzzyCompare(UT, 24.0)) {
            UT -= 24.0;
        }
        if(UT < 0) {
            UT += 24.0;
        }

        return UT;
    }
}

//10. convert UT value to local time zone of latitude/longitude
double SunsetRise::utToLocalTimeZone() const
{
    if(const auto& utc = toUTC(); utc == std::numeric_limits<double>::min() ||
            utc == std::numeric_limits<double>::max()) {
        return utc;
    } else {
        auto localT = round(utc + sextaToDeca(m_localOffset.value()), 2);

        return toHumanTime(localT);
    }
}

bool SunsetRise::isInit() const
{
    return m_date.isValid() && m_longitude.has_value() && m_latitude.has_value() &&
            m_zenith.has_value() && m_localOffset.has_value() &&
            m_calculationType.has_value() && m_meridian.has_value();
}

std::optional<double> SunsetRise::calculateConfiguredTime() const
{
    if(!isInit()) {
        return std::nullopt;
    }

    return utToLocalTimeZone();
}
