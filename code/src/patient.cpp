#include "../includes/patient.h"
#include <algorithm>

// Constructor
Patient::Patient(std::string name, int age, char gender, std::string disease)
    : name(std::move(name)), age(age), gender(gender), disease(std::move(disease)) {}

// Copy Constructor
Patient::Patient(const Patient& other)
    : name(other.name), age(other.age), gender(other.gender), disease(other.disease), doctors(other.doctors) {}

// Copy Assignment Operator
Patient& Patient::operator=(const Patient& other) {
    if (this == &other) return *this;
    name = other.name;
    age = other.age;
    gender = other.gender;
    disease = other.disease;
    doctors = other.doctors;
    return *this;
}

// Destructor
Patient::~Patient() {}

// Public Methods
void Patient::updateDisease(const std::string& newDisease) {
    disease = newDisease;
}

void Patient::assignDoctor(Doctor* doc) {
    doctors.push_back(doc);
}

void Patient::removeDoctor(Doctor* doc) {
    // Remove the doctor by name using std::remove_if
    auto it = std::remove_if(doctors.begin(), doctors.end(), [doc](Doctor* d) {
        return d->getName() == doc->getName();  // Compare by doctor name or another unique identifier
    });
    doctors.erase(it, doctors.end());
}

void Patient::printInfo() const {
    std::cout << "Patient: " << name << ", Age: " << age << ", Gender: " << gender << ", Disease: " << disease << "\n";
}

void Patient::printDoctors() const {
    std::cout << "Doctors for " << name << ":\n";
    for (const auto& doc : doctors) {
        std::cout << *doc << "\n";
    }
}

// Operator<< Overload
std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "Patient: " << p.name << ", Age: " << p.age << ", Gender: " << p.gender << ", Disease: " << p.disease;
    return os;
}
