#include "../includes/patient.h"
#include <regex>


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

Patient::~Patient() = default;

const std::string& Patient::getName() const {
    return name;
}

const std::string& Patient::getCNP() const {
    return cnp;
}

int Patient::getAge() const {
    return age;
}

char Patient::getGender() const {
    return gender;
}

const std::set<std::string>& Patient::getDiseases() const {
    return diseases;
}

void Patient::addDisease(const std::string& disease) {
    diseases.insert(disease);
}

void Patient::removeDisease(const std::string& disease) {
    diseases.erase(disease);
}

bool Patient::isHealthy() const {
    return diseases.empty();
}

bool Patient::isValidCNP(const std::string& cnp) {
    return std::regex_match(cnp, std::regex("\\d{13}"));
}


std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << "Patient Name: " << patient.name
       << ", CNP: " << patient.cnp
       << ", Age: " << patient.age
       << ", Gender: " << patient.gender
       << ", Diseases: ";
    if (patient.diseases.empty()) {
        os << "None";
    } else {
        for (const auto& disease : patient.diseases) {
            os << "[" << disease << "] ";
        }
    }
    return os;
}
