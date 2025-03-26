#include "../includes/patient.h"
#include "../includes/doctor.h"

// Constructor
Patient::Patient(std::string name, int age, char gender, std::string disease, Doctor* doctor)
    : name(std::move(name)), age(age), gender(gender), disease(std::move(disease)), doctor(doctor) {}

// Copy Constructor
Patient::Patient(const Patient& other)
    : name(other.name), age(other.age), gender(other.gender), disease(other.disease), doctor(other.doctor) {
    std::cout << "Copy constructor called for Patient: " << name << std::endl;
}

// Copy Assignment Operator
Patient& Patient::operator=(const Patient& other) {
    if (this == &other) return *this; // Avoid self-assignment
    name = other.name;
    age = other.age;
    gender = other.gender;
    disease = other.disease;
    doctor = other.doctor;
    std::cout << "Copy assignment operator called for Patient: " << name << std::endl;
    return *this;
}

// Destructor
Patient::~Patient() {
    std::cout << "Destructor called for Patient: " << name << std::endl;
}

// Public Methods
void Patient::updateDisease(const std::string& newDisease) {
    disease = newDisease;
}

void Patient::assignDoctor(Doctor* doc) {
    doctor = doc;
}

void Patient::printInfo() const {
    std::cout << "Patient: " << name << ", Age: " << age << ", Gender: " << gender
              << ", Disease: " << disease << "\n";
}

// Operator<< Overload
std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "Patient: " << p.name << ", Age: " << p.age << ", Gender: " << p.gender
       << ", Disease: " << p.disease;
    return os;
}
