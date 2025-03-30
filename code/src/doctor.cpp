#include "../includes/doctor.h"

// Constructor
Doctor::Doctor(std::string name, std::string specialty)
    : name(std::move(name)), specialty(std::move(specialty)) {}

// Getter for name
const std::string& Doctor::getName() const {  // Fixed: Return by const reference
    return name;
}


void Doctor::printInfo() const {
    std::cout << "Doctor: " << name << ", Specialty: " << specialty << "\n";
}

// Operator<< Overload
std::ostream& operator<<(std::ostream& os, const Doctor& d) {
    os << "Doctor: " << d.name << ", Specialty: " << d.specialty;
    return os;
}
