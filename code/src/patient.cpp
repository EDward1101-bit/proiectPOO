#include "../includes/patient.h"

// Constructor
Patient::Patient(std::string name, int age, char gender, std::string disease)
    : name(std::move(name)), age(age), gender(gender), disease(std::move(disease)) {}

void Patient::updateDisease(const std::string& newDisease) {
    disease = newDisease;  // Update the patient's disease
}

void Patient::printInfo() const {
    std::cout << "Patient: " << name << ", Age: " << age << ", Gender: " << gender
              << ", Disease: " << disease << "\n";
}

// Operator<< Overload to print patient info
std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "Patient: " << p.name << ", Age: " << p.age << ", Disease: " << p.disease;
    return os;
}
