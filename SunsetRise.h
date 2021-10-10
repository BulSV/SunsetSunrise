#ifndef SUNSETRISE_H
#define SUNSETRISE_H

#include <limits>
#include <optional>

#include <QDate>

class SunsetRise
{
public:
    enum class CalculationType {
        Sunset,
        Sunrise
    };
    enum class Meridian {
        East,
        West
    };
    enum class ZenithType {
        Official,
        Civilian,
        Nautical,
        Astronomical
    };
    struct GeoCoordinates {
        std::optional<double> longitude;
        std::optional<double> latitude;
        std::optional<Meridian> meridian;
    };
    struct Data {
        QDate date;
        GeoCoordinates coordinates;
        std::optional<ZenithType> zenith;
        std::optional<double> localOffset;
        std::optional<CalculationType> calculationType;
        bool isInit() const {
            return date.isValid()
                    && coordinates.longitude.has_value()
                    && coordinates.latitude.has_value()
                    && coordinates.meridian.has_value()
                    && zenith.has_value()
                    && localOffset.has_value()
                    && calculationType.has_value();
        }
    };

    SunsetRise();
    void setData(const Data& data);
    void setDate(const QDate& date);
    void setLongtitude(double longtitude);
    void setLatitude(double latitude);
    void setZenith(ZenithType zenith);
    void setLoclOffset(const std::optional<double>& timeOffset);
    void setCalculationType(CalculationType type);
    void setMeridian(Meridian meridian);
    std::optional<double> calculateConfiguredTime() const;

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

    bool isInit() const;

private:
    Data m_data;
    QDate m_date;
    std::optional<double> m_longitude;
    std::optional<double> m_latitude;
    std::optional<double> m_zenith;
    std::optional<double> m_localOffset;
    std::optional<CalculationType> m_calculationType;
    std::optional<Meridian> m_meridian;
};

#endif // SUNSETRISE_H

