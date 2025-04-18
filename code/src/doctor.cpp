#include "../includes/doctor.h"
#include <iostream>

// Constructor
Doctor::Doctor(std::string name, std::string specialty)
    : name(std::move(name)), specialty(std::move(specialty)) {}

// Getter for doctor's name
std::string Doctor::getName() const {
    return name;
}

std::string Doctor::getSpecialty() const {
    return specialty;
}

// Assign a patient to the doctor
void Doctor::assignPatient(Patient* p) {
    patients.push_back(p);
}

// Remove a patient from the doctor
void Doctor::removePatient(const Patient* p) {
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (*it == p) {
            patients.erase(it);
            break;
        }
    }
}

// Print doctor information
void Doctor::printInfo() const {
    std::cout << "Doctor: " << name << ", Specialty: " << specialty << "\n";
}

// Print the list of patients
void Doctor::printPatients() const {
    std::cout << "Patients of Dr. " << name << ":\n";
    for (const Patient* patient : patients) {
        std::cout << *patient << "\n";  // Print patient info
    }
}

// Operator<< Overload to print doctor info
std::ostream& operator<<(std::ostream& os, const Doctor& d) {
    os << "Doctor: " << d.name << ", Specialty: " << d.specialty;
    return os;
}
