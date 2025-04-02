#include "../includes/hospital.h"

// Constructor
Spital::Spital(std::string name) : name(std::move(name)) {}

// Assign Doctor to Hospital
void Spital::assignDoctor(Doctor* doc) {
    doctors.push_back(doc);
}

// Assign Nurse to Hospital
void Spital::assignNurse(Nurse* nurse) {
    nurses.push_back(nurse);
}

// Print all doctors
void Spital::printDoctors() const {
    std::cout << "Doctors in " << name << ":\n";
    for (const auto& doc : doctors) {
        std::cout << *doc << "\n";
    }
}

// Print all nurses
void Spital::printNurses() const {
    std::cout << "Nurses in " << name << ":\n";
    for (const auto& nurse : nurses) {
        std::cout << *nurse << "\n";
    }
}

// Copy assignment operator
Spital& Spital::operator=(const Spital& other) {
    if (this != &other) {
        name = other.name;
        doctors = other.doctors;
        nurses = other.nurses;
    }
    return *this;
}

// Operator<< for Spital info
std::ostream& operator<<(std::ostream& os, const Spital& spital) {
    os << "Hospital Name: " << spital.name << "\n";
    return os;
}

// Destructor
Spital::~Spital() = default;
