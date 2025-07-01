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
    os << "Patient Name: " << patient.getName() << "\n"
       << "CNP: " << patient.getCNP() << "\n"
       << "Age: " << patient.getAge() << "\n"
       << "Gender: " << patient.getGender() << "\n"
       << "Diseases: ";

    const auto& diseases = patient.getDiseases();
    if (diseases.empty()) {
        os << "None";
    } else {
        bool first = true;
        for (const auto& disease : diseases) {
            if (!first) os << ", ";
            os << disease;
            first = false;
        }
    }
    os << "\n";
    return os;
}







