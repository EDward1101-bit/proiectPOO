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
        os << "[Info: Patient already printed. Skipping repeated output.]\n";
        return os;
    }
    visited.insert(&patient);

    os << "Patient Name: " << patient.getName()
       << "\nCNP: " << patient.getCNP()
       << "\nAge: " << patient.getAge()
       << "\nGender: " << patient.getGender();

    if (!patient.getDiseases().empty()) {
        os << "\nDiseases: ";
        bool first = true;
        for (const auto& disease : patient.getDiseases()) {
            if (!first) os << ", ";
            os << disease;
            first = false;
        }
    } else {
        os << "\nDiseases: None";
    }

    os << "\n";
    visited.erase(&patient);
    return os;
}




