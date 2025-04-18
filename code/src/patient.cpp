#include "../includes/patient.h"

// Constructor
Patient::Patient(std::string name, int age, char gender, std::string disease)
    : name(std::move(name)), age(age), gender(gender), disease(std::move(disease)) {}

// Get the name of the patient
std::string const& Patient::getName() const {
    return name; // Return by constant reference to avoid unnecessary copies
}

// Get the disease of the patient
std::string const& Patient::getDisease() const {
    return disease; // Return by constant reference to avoid unnecessary copies
}

// Update the disease of the patient
void Patient::updateDisease(const std::string& newDisease) {
    disease = newDisease;  // Update the patient's disease
}

// Print the patient's information
void Patient::printInfo() const {
    std::cout << "Patient: " << name << ", Age: " << age << ", Gender: " << gender
              << ", Disease: " << disease << "\n";
}

// Overloaded operator<< to print the patient's information
std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "Patient: " << p.name << ", Age: " << p.age << ", Disease: " << p.disease;
    return os;
}
