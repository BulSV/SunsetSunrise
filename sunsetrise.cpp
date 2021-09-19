#include "sunsetrise.h"

#include <qmath.h>

#include <QMessageBox>

#include "functions.h"

namespace
{
constexpr qreal ZENITH_OFFICIAL = 90.0 + 5.0 / 6.0;
constexpr qreal ZENITH_CIVIL = 96.0;
constexpr qreal ZENITH_NAUTICAL = 102.0;
constexpr qreal ZENITH_ASTRONOMICAL = 108.0;
} // namespace

using namespace functions;

SunSetRise::SunSetRise(int day,
                       int month,
                       int year,
                       qreal longtitude,
                       qreal latitude,
                       qreal zenith,
                       int localOffset,
                       bool isSet,
                       bool isWest)
    : m_day(day)
    , m_month(month)
    , m_year(year)
    , m_longitude(longtitude)
    , m_latitude(latitude)
    , m_zenith(zenith)
    , m_localOffset(localOffset)
    , m_isSet(isSet)
    , m_isWest(isWest)
{
}

SunSetRise::SunSetRise()
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

void SunSetRise::setDay(const int &day)
{
    m_day = day;
}

void SunSetRise::setMonth(const int &month)
{
    m_month = month;
}

void SunSetRise::setYear(const int &year)
{
    m_year = year;
}

void SunSetRise::setZenith(const ZENITH &zenith)
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

void SunSetRise::setLoclOffset(const qreal &timeOffset)
{
    m_localOffset = timeOffset;
}

void SunSetRise::setLongtitude(const qreal &longtitude)
{
    m_longitude = longtitude;
#ifdef DEBUG
    qDebug() << "SunSetRise::setLongtitude: itsLongitude =" << itsLongitude;
#endif
}

void SunSetRise::setLatitude(const qreal &latitude)
{
    m_latitude = latitude;
}

void SunSetRise::setSetOrRise(const bool &isSet)
{
    m_isSet = isSet;
}

void SunSetRise::setEastOrWest(const bool &isWest)
{
    m_isWest = isWest;
}

qreal SunSetRise::minutesToDegrees(const qreal &minutes) const
{
    return ((100.0 * minutes) / 60.0);
}

qreal SunSetRise::degreesToRadians(const qreal &degrees) const
{
    return ((degrees * 4.0 * qAtan(1.0)) / 180.0);
}

qreal SunSetRise::radiansToDegrees(const qreal &radians) const
{
    return ((radians * 180.0) / (4.0 * qAtan(1.0)));
}

qreal SunSetRise::toHumanTime(const qreal &time) const
{
    int hours;
    qreal minutes;

    hours = static_cast<int>(time);
    minutes = time - hours;
    minutes = (minutes * 60.0) / 100.0; // округлить до 0,01
    return static_cast<qreal>(hours) + static_cast<qreal>(round(static_cast<float>(minutes), 2));
}

//1. first calculate the day of the year

int SunSetRise::whatDay() const
{
    int N;
    int N1;
    int N2;
    int N3;

    N1 = qFloor(275.0 * m_month / 9.0);
    N2 = qFloor((m_month + 9.0) / 12.0);
    N3 = (1 + qFloor((m_year - 4.0 * qFloor(m_year / 4.0) + 2.0) / 3.0));
    N = N1 - (N2 * N3) + m_day - 30;

#ifdef DEBUG
    qDebug() << "N =" << N;
#endif

    return N;
}

//2. convert the longitude to hour value and calculate an approximate time

qreal SunSetRise::longtitudeToHour() const
{
    qreal lngHour;
    qreal t;

    lngHour = m_longitude / 15.0;
    if(!m_isSet) {
        t = whatDay() + ((6.0 - lngHour) / 24.0);
    } else {
        t = whatDay() + ((18.0 - lngHour) / 24.0);
    }
#ifdef DEBUG
    qDebug() << "itsLongitude =" << itsLongitude;
    qDebug() << "t =" << t;
#endif

    return t;
}

//3. calculate the Sun's mean anomaly
qreal SunSetRise::sunsMeanAnomaly() const
{
#ifdef DEBUG
    qDebug() << "SunSetRise::sunsMeanAnomaly() =" << (0.9856 * longtitudeToHour()) - 3.289;
#endif
    return ((0.9856 * longtitudeToHour()) - 3.289);
}

//4. calculate the Sun's true longitude

qreal SunSetRise::sunsTrueLongtitude() const
{
    qreal L;

    L = sunsMeanAnomaly() + (1.916 * qSin(degreesToRadians(sunsMeanAnomaly()))) + (0.020 * qSin(degreesToRadians(2.0 * sunsMeanAnomaly()))) + 282.634;

    if(L > 360.0 || qFuzzyCompare(L, 360.0)) L -= 360.0;
    if(L < 0) L += 360.0;
#ifdef DEBUG
    qDebug() << "SunSetRise::sunsTrueLongtitude() =" << L;
#endif

    return L;
}

//5a. calculate the Sun's right ascension
qreal SunSetRise::sunsRightAscension() const
{
    qreal RA;
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
#ifdef DEBUG
    qDebug() << "SunSetRise::Lquadrant =" << Lquadrant;
    qDebug() << "SunSetRise::RAquadrant =" << RAquadrant;
    qDebug() << "SunSetRise::sunsRightAscension() =" << RA;
#endif

    return RA;
}

//6. calculate the Sun's declination
qreal SunSetRise::sunsDeclination() const
{
    qreal sinDec;
    qreal cosDec;
    qreal cosH;
    qreal H;

    sinDec = 0.39782 * qSin(degreesToRadians(sunsTrueLongtitude()));
    cosDec = qCos(qAsin(sinDec));
//7a. calculate the Sun's local hour angle
    cosH = (qCos(degreesToRadians(m_zenith)) - (sinDec * qSin(degreesToRadians(m_latitude)))) / (cosDec * qCos(degreesToRadians(m_latitude)));
#ifdef DEBUG
    qDebug() << "SunSetRise::sunsDeclination(): sinDec =" << sinDec;
    qDebug() << "SunSetRise::sunsDeclination(): cosDec =" << cosDec;
    qDebug() << "SunSetRise::sunsDeclination(): cosH =" << cosH;
#endif
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
#ifdef DEBUG
    qDebug() << "SunSetRise::sunsDeclination(): H =" << H;
#endif

    return H;
}

//8. calculate local mean time of rising/setting
qreal SunSetRise::localMeanTime() const
{
    qreal T;
    T = sunsDeclination() + sunsRightAscension() - (0.06571 * longtitudeToHour()) - 6.622;
#ifdef DEBUG
    qDebug() << "SunSetRise::localMeanTime(): T =" << T;
#endif

    return T;
}

//9. adjust back to UTC
qreal SunSetRise::toUTC() const
{
    qreal lngHour;
    qreal UT;

    lngHour = m_longitude / 15.0;
    UT = localMeanTime() - lngHour;

    if(UT > 24.0 || qFuzzyCompare(UT, 24.0)) {
        UT -= 24.0;
#ifdef DEBUG
    qDebug() << "SunSetRise::toUTC(): UT >= 24";
#endif
    }
    if(UT < 0) {
        UT += 24.0;
#ifdef DEBUG
    qDebug() << "SunSetRise::toUTC(): UT < 0";
#endif
    }
#ifdef DEBUG
    qDebug() << "SunSetRise::toUTC(): UT =" << UT;
#endif

    return UT;
}

//10. convert UT value to local time zone of latitude/longitude
qreal SunSetRise::utToLocalTimeZone() const
{
    qreal localT;
    localT = round(toUTC() + sextaToDeca(m_localOffset), 2);
#ifdef DEBUG
    qDebug() << "SunSetRise::utToLocalTimeZone(): itsLocalOffset =" << itsLocalOffset;
    qDebug() << "SunSetRise::utToLocalTimeZone(): localT =" << localT;
    qDebug() << "SunSetRise::utToLocalTimeZone(): toHumanTime(localT) =" << toHumanTime(localT);
#endif
#ifdef DEBUG
    qDebug() << "SunSetRise::itsDay =" << itsDay;
    qDebug() << "SunSetRise::itsMonth =" << itsMonth;
    qDebug() << "SunSetRise::itsYear =" << itsYear;
    qDebug() << "SunSetRise::itsLongitude =" << itsLongitude;
    qDebug() << "SunSetRise::itsLatitude =" << itsLatitude;
    qDebug() << "SunSetRise::itsZenith =" << itsZenith;
    qDebug() << "SunSetRise::itsLocalOffset =" << itsLocalOffset;
    qDebug() << "SunSetRise::itsIsSet =" << itsIsSet;
    qDebug() << "SunSetRise::itsIsWest =" << itsIsWest;
#endif

    return toHumanTime(localT);
}

qreal SunSetRise::result()
{
    if(m_isWest) {
        m_longitude *= -1.0;
    }

    return utToLocalTimeZone();
}
