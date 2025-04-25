#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>

class Location {
private:
    std::string country;
    int timezoneOffset;

public:
    Location(std::string country, int timezoneOffset);
    Location(const Location& other) = default;
    Location& operator=(const Location& other);
    ~Location();

    [[nodiscard]] int getTimezoneOffset() const;

    friend std::ostream& operator<<(std::ostream& os, const Location& loc);
};

#endif // LOCATION_H
