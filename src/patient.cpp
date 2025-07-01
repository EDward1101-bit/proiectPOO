#include "../includes/patient.h"
#include <algorithm>
#include <unordered_set>
#include <thread>

Patient::Patient(const std::string& name, const std::string& cnp, int age, char gender)
    : name(name), cnp(cnp), age(age), gender(gender) {}

Patient::Patient(const Patient& other)
    : name(other.name), cnp(other.cnp), age(other.age), gender(other.gender), diseases(other.diseases) {}

Patient& Patient::operator=(const Patient& other) {
    if (this != &other) {
        name = other.name;
        cnp = other.cnp;
        age = other.age;
        gender = other.gender;
        diseases = other.diseases;
    }
    return *this;
}

Patient::~Patient() {}

const std::string& Patient::getName() const { return name; }
const std::string& Patient::getCNP() const { return cnp; }
int Patient::getAge() const { return age; }
char Patient::getGender() const { return gender; }
const std::set<std::string>& Patient::getDiseases() const { return diseases; }

void Patient::addDisease(const std::string& disease) {
    diseases.insert(disease);
}

void Patient::removeDisease(const std::string& disease) {
    diseases.erase(disease);
}

bool Patient::isValidCNP(const std::string& cnp) {
    return cnp.length() == 13 && std::all_of(cnp.begin(), cnp.end(), ::isdigit);
}


std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    static thread_local std::unordered_set<const void*> visited;
    if (visited.count(&patient)) {
        os << "[Patient info suppressed to prevent circular printing]\n";
        return os;
    }

    visited.insert(&patient);
    os << "Patient Name: " << patient.name << "\n";
    os << "CNP: " << patient.cnp << "\n";
    os << "Age: " << patient.age << "\n";
    os << "Gender: " << patient.gender << "\n";
    os << "Diseases: ";
    for (auto it = patient.diseases.begin(); it != patient.diseases.end(); ++it) {
        if (it != patient.diseases.begin()) os << ", ";
        os << *it;
    }
    os << "\n";
    visited.erase(&patient);
    return os;
}


