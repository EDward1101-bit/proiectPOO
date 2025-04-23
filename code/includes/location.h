#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>

class Location {
private:
    std::string country;
    int timezoneOffset; // +2 for Romania, -5 for EST

public:
    Location(std::string country, int timezoneOffset);
    Location(const Location& other);
    Location& operator=(const Location& other);
    ~Location();

    const std::string& getCountry() const;
    int getTimezoneOffset() const;

    friend std::ostream& operator<<(std::ostream& os, const Location& loc);
};

#endif // LOCATION_H