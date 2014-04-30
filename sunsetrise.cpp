#include "sunsetrise.h"
#include <qmath.h>
#include <QMessageBox>
#include "bulsv_lib.h"

SunSetRise::SunSetRise(int day,
                       int month,
                       int year,
                       qreal longtitude,
                       qreal latitude,
                       qreal zenith,
                       int localOffset,
                       bool isSet,
                       bool isWest)
    : itsDay(day)
    , itsMonth(month)
    , itsYear(year)
    , itsLongitude(longtitude)
    , itsLatitude(latitude)
    , itsZenith(zenith)
    , itsLocalOffset(localOffset)
    , itsIsSet(isSet)
    , itsIsWest(isWest)
{
}

SunSetRise::SunSetRise()
    : itsDay(0)
    , itsMonth(0)
    , itsYear(0)
    , itsLongitude(0)
    , itsLatitude(0)
    , itsZenith(0)
    , itsLocalOffset(0)
    , itsIsSet(true)
    , itsIsWest(true)
{
}

void SunSetRise::setDay(const int &day)
{
    itsDay = day;
}

void SunSetRise::setMonth(const int &month)
{
    itsMonth = month;
}

void SunSetRise::setYear(const int &year)
{
    itsYear = year;
}

void SunSetRise::setZenith(const ZENITH &zenith)
{
    switch(zenith)
    {
    case 0: itsZenith = ZENITH_OFFICIAL;
        break;
    case 1: itsZenith = ZENITH_CIVIL;
        break;
    case 2: itsZenith = ZENITH_NAUTICAL;
        break;
    case 3: itsZenith = ZENITH_ASTRONOMICAL;
        break;
    default: QMessageBox::critical(0, "ERROR", "Zenith was selected an incorrect way!");
        break;
    }
}

void SunSetRise::setLoclOffset(const qreal &timeOffset)
{
    itsLocalOffset = timeOffset;
}

void SunSetRise::setLongtitude(const qreal &longtitude)
{    
    itsLongitude = longtitude;
#ifdef DEBUG
    qDebug() << "SunSetRise::setLongtitude: itsLongitude =" << itsLongitude;
#endif
}

void SunSetRise::setLatitude(const qreal &latitude)
{
    itsLatitude = latitude;
}

void SunSetRise::setSetOrRise(const bool &isSet)
{
    itsIsSet = isSet;
}

void SunSetRise::setEastOrWest(const bool &isWest)
{
    itsIsWest = isWest;
}

qreal SunSetRise::minutesToDegrees(const qreal &minutes) const
{
    return ((100*minutes) / 60);
}

qreal SunSetRise::degreesToRadians(const qreal &degrees) const
{
    return ((degrees*4*qAtan(1)) / 180);
}

qreal SunSetRise::radiansToDegrees(const qreal &radians) const
{
    return ((radians*180) / (4*qAtan(1)));
}

qreal SunSetRise::toHumanTime(const qreal &time) const
{
    int hours;
    qreal minutes;

    hours = (int)time;
    minutes = time - hours;
    minutes = (minutes*60) / 100; // округлить до 0,01
    return (qreal)hours + BLib::round(minutes, 2);
}

//1. first calculate the day of the year

int SunSetRise::whatDay() const
{
    int N;
    int N1;
    int N2;
    int N3;

    N1 = qFloor(275*itsMonth/9);
    N2 = qFloor((itsMonth+9) / 12);
    N3 = (1+qFloor((itsYear-4*qFloor(itsYear/4)+2)/3));
    N = N1-(N2*N3)+itsDay-30;

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

    lngHour = itsLongitude/15;
    if(!itsIsSet)
        t = whatDay() + ((6-lngHour)/24);
    else
        t = whatDay() + ((18-lngHour)/24);

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
    qDebug() << "SunSetRise::sunsMeanAnomaly() =" << (0.9856*longtitudeToHour())-3.289;
#endif
    return ((0.9856*longtitudeToHour())-3.289);
}

//4. calculate the Sun's true longitude

qreal SunSetRise::sunsTrueLongtitude() const
{
    qreal L;

    L = sunsMeanAnomaly() + (1.916*qSin(degreesToRadians(sunsMeanAnomaly()))) + (0.020*qSin(degreesToRadians(2*sunsMeanAnomaly()))) + 282.634;

    if(L>=360)
        L-=360;
    if(L<0)
        L+=360;
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

    RA = qAtan(0.91764*qTan(degreesToRadians(sunsTrueLongtitude())));
    RA = radiansToDegrees(RA);
    Lquadrant = (qFloor(sunsTrueLongtitude()/90))*90;
    RAquadrant = (qFloor(RA/90))*90;
    RA = RA + (Lquadrant - RAquadrant);

    if(RA >= 360)
        RA -= 360;
    if(RA < 0)
        RA += 360;

    RA/=15;
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

    sinDec = 0.39782*qSin(degreesToRadians(sunsTrueLongtitude()));
    cosDec = qCos(qAsin(sinDec));
//7a. calculate the Sun's local hour angle
    cosH = (qCos(degreesToRadians(itsZenith)) - (sinDec*qSin(degreesToRadians(itsLatitude)))) / (cosDec*qCos(degreesToRadians(itsLatitude)));
#ifdef DEBUG
    qDebug() << "SunSetRise::sunsDeclination(): sinDec =" << sinDec;
    qDebug() << "SunSetRise::sunsDeclination(): cosDec =" << cosDec;
    qDebug() << "SunSetRise::sunsDeclination(): cosH =" << cosH;
#endif
    if (cosH >  1)
    {
        //the sun never rises on this location (on the specified date)
        QMessageBox::information(0, "Information", "The sun never rises on this location\n(on the specified date)");
    }
    if (cosH < -1)
    {
        //the sun never sets on this location (on the specified date)
        QMessageBox::information(0, "Information", "The sun never sets on this location\n(on the specified date)");
    }
//7b. finish calculating H and convert into hours
    if(!itsIsSet)
        H = 360 - radiansToDegrees(qAcos(cosH));
    else
        H = radiansToDegrees(qAcos(cosH));
    H/=15;
#ifdef DEBUG
    qDebug() << "SunSetRise::sunsDeclination(): H =" << H;
#endif
    return H;
}

//8. calculate local mean time of rising/setting
qreal SunSetRise::localMeanTime() const
{
    qreal T;
    T = sunsDeclination() + sunsRightAscension() - (0.06571*longtitudeToHour()) - 6.622;
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

    lngHour = itsLongitude/15;
    UT = localMeanTime() - lngHour;

    if(UT>=24)
    {
        UT-=24;
#ifdef DEBUG
    qDebug() << "SunSetRise::toUTC(): UT >= 24";
#endif
    }
    if(UT<0)
    {
        UT+=24;
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
    localT = BLib::round(toUTC() + BLib::sextaToDeca(itsLocalOffset), 2);
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
    if(itsIsWest)
    {
        itsLongitude = - itsLongitude;
    }
    return utToLocalTimeZone();
}

