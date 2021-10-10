#ifndef SUNSETRISE_H
#define SUNSETRISE_H

#include "Data.h"

class SunsetRise
{
public:
    SunsetRise();
    void setData(const Data& data);
    std::optional<double> calculateConfiguredTime() const;

private:
    double minutesToDegrees(double minutes) const;
    double toHumanTime(double time) const;

    double longtitudeToHour() const;
    double sunsMeanAnomaly() const;
    double sunsTrueLongtitude() const;
    double sunsRightAscension() const;
    std::optional<double> sunsDeclination() const;
    std::optional<double> localMeanTime() const;
    std::optional<double> toUTC() const;
    std::optional<double> utToLocalTimeZone() const;

    std::optional<double> getZenith(const std::optional<Data::ZenithType> &zenith) const;

private:
    Data m_data;
};

#endif // SUNSETRISE_H

