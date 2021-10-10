#include "Data.h"

bool Data::isValid() const {
    return date.isValid()
            && coordinates.longitude.has_value()
            && coordinates.latitude.has_value()
            && coordinates.meridian.has_value()
            && zenith.has_value()
            && localOffset.has_value()
            && calculationType.has_value();
}
