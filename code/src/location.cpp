#include "../includes/location.h"

Location::Location(std::string country, int timezoneOffset)
    : country(std::move(country)), timezoneOffset(timezoneOffset) {}

Location& Location::operator=(const Location& other) {
    if (this != &other) {
        country = other.country;
        timezoneOffset = other.timezoneOffset;
    }
    return *this;
}

Location::~Location() = default;

int Location::getTimezoneOffset() const {
    return timezoneOffset;
}

std::ostream& operator<<(std::ostream& os, const Location& loc) {
    os << loc.country << " (UTC" << (loc.timezoneOffset >= 0 ? "+" : "") << loc.timezoneOffset << ")";
    return os;
}