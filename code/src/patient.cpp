#include "../includes/patient.h"
#include <iostream>

// Constructor for the Patient class
Patient::Patient(std::string name, int age, char gender, std::string disease)
    : name(std::move(name)), age(age), gender(gender), disease(std::move(disease)) {}

// Update the patient's disease information
void Patient::updateDisease(const std::string& newDisease) {
    disease = newDisease;
}

// Print the patient's information
void Patient::printInfo() const {
    std::cout << "Patient: " << name << ", Age: " << age << ", Gender: " << gender
              << ", Disease: " << disease << "\n";
}

// Operator<< Overload to print patient info
std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "Patient: " << p.name << ", Age: " << p.age << ", Disease: " << p.disease;
    return os;
}
