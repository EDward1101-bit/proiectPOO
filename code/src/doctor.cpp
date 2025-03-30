#include "../includes/doctor.h"

// Constructor
Doctor::Doctor(std::string name, std::string specialty)
    : name(std::move(name)), specialty(std::move(specialty)) {}

// Getter for name
std::string Doctor::getName() const {
    return name;
}

// Public Methods
void Doctor::changeSpecialty(const std::string& newSpecialty) {
    specialty = newSpecialty;
}

void Doctor::printInfo() const {
    std::cout << "Doctor: " << name << ", Specialty: " << specialty << "\n";
}

// Operator<< Overload
std::ostream& operator<<(std::ostream& os, const Doctor& d) {
    os << "Doctor: " << d.name << ", Specialty: " << d.specialty;
    return os;
}
