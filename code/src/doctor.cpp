#include "../includes/doctor.h"

// Constructor
Doctor::Doctor(std::string name, std::string specialty, std::vector<std::string> availableDays)
    : name(std::move(name)), specialty(std::move(specialty)), availableDays(std::move(availableDays)) {}

// Copy Constructor
Doctor::Doctor(const Doctor& other)
    : name(other.name), specialty(other.specialty), availableDays(other.availableDays) {}

// Copy Assignment Operator
Doctor& Doctor::operator=(const Doctor& other) {
    if (this == &other) return *this;
    name = other.name;
    specialty = other.specialty;
    availableDays = other.availableDays;
    return *this;
}

// Destructor
Doctor::~Doctor() {}

// Public Methods
void Doctor::changeSpecialty(const std::string& newSpecialty) {
    specialty = newSpecialty;
}

void Doctor::addAvailableDay(const std::string& day) {
    availableDays.push_back(day);
}

bool Doctor::isAvailableOn(const std::string& day) const {
    for (const auto& availableDay : availableDays) {
        if (availableDay == day) return true;
    }
    return false;
}

void Doctor::printInfo() const {
    std::cout << "Doctor: " << name << ", Specialty: " << specialty << ", Available Days: ";
    for (const auto& day : availableDays) {
        std::cout << day << " ";
    }
    std::cout << "\n";
}

// Operator<< Overload
std::ostream& operator<<(std::ostream& os, const Doctor& d) {
    os << "Doctor: " << d.name << ", Specialty: " << d.specialty;
    os << ", Available Days: ";
    for (const auto& day : d.availableDays) {
        os << day << " ";
    }
    return os;
}
