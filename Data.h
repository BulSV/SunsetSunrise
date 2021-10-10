#ifndef DATA_H
#define DATA_H

#include <optional>

#include <QDate>

class Data
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
    bool isValid() const;

public:
    QDate date;
    GeoCoordinates coordinates;
    std::optional<ZenithType> zenith;
    std::optional<double> localOffset;
    std::optional<CalculationType> calculationType;
};

#endif // DATA_H
