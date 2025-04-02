#include "../includes/doctor.h"

// Constructor
Doctor::Doctor(std::string name, std::string specialty)
    : name(std::move(name)), specialty(std::move(specialty)) {}


void Doctor::printInfo() const {
    std::cout << "Doctor: " << name << ", Specialty: " << specialty << "\n";
}

void Doctor::assignPatient(Patient* p) {
    patients.push_back(p);  // Assign the patient to this doctor
}

void Doctor::removePatient(const Patient* p) {
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (*it == p) {
            patients.erase(it);  // Remove the patient from the doctor's list
            break;
        }
    }
}

void Doctor::printPatients() const {
    std::cout << "Patients of Dr. " << name << ":\n";
    for (const Patient* patient : patients){
        std::cout << *patient << "\n";  // Print patient info
    }
}

Doctor::~Doctor() {}

// Operator<< Overload to print doctor info
std::ostream& operator<<(std::ostream& os, const Doctor& d) {
    os << "Doctor: " << d.name << ", Specialty: " << d.specialty;
    return os;
}
