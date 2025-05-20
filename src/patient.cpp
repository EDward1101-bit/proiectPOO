#include "../includes/patient.h"
#include <algorithm>

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

void Patient::adaugaServiciu(const std::shared_ptr<ServiciuMedical>& serviciu) {
    istoricServicii.push_back(serviciu);
}

bool Patient::esteBolnav() const {
    return !diseases.empty();
}

bool Patient::esteProcesabil() const {
    return !esteExternat;
}

void Patient::setExternat(bool val) {
    esteExternat = val;
}

bool Patient::getExternat() const {
    return esteExternat;
}

void Patient::setHealthy(bool val) {
    esteHealthy = val;
}

bool Patient::getHealthy() const {
    return esteHealthy;
}

double Patient::calculeazaCostTotal() const {
    double total = 0;
    for (const auto& s : istoricServicii) {
        total += s->getCost();
    }
    return total;
}

const std::vector<std::shared_ptr<ServiciuMedical>>& Patient::getIstoric() const {
    return istoricServicii;
}


std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << "Patient Name: " << patient.name
       << ", CNP: " << patient.cnp
       << ", Age: " << patient.age
       << ", Gender: " << patient.gender;

    if (!patient.diseases.empty()) {
        os << ", Diseases: ";
        auto it = patient.diseases.begin();
        os << *it;
        ++it;
        for (; it != patient.diseases.end(); ++it) {
            os << ", " << *it;
        }
    } else {
        os << ", Healthy";
    }
    return os;
}

