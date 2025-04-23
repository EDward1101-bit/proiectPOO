#include "../includes/patient.h"
#include <regex>

// Constructor
Patient::Patient(std::string name, int age, char gender, std::string cnp, double funds)
    : name(std::move(name)), age(age), gender(gender), cnp(std::move(cnp)), funds(funds) {}

// Copy constructor
Patient::Patient(const Patient& other)
    : name(other.name), age(other.age), gender(other.gender), cnp(other.cnp), funds(other.funds), diseases(other.diseases) {}

// Copy assignment
Patient& Patient::operator=(const Patient& other) {
    if (this != &other) {
        name = other.name;
        age = other.age;
        gender = other.gender;
        cnp = other.cnp;
        funds = other.funds;
        diseases = other.diseases;
    }
    return *this;
}

// Destructor
Patient::~Patient() = default;

std::string const& Patient::getName() const {
    return name;
}

const std::map<std::string, double>& Patient::getDiseases() const {
    return diseases;
}

double Patient::getTotalTreatmentCost() const {
    double total = 0.0;
    for (const auto& [disease, cost] : diseases) {
        total += cost;
    }
    return total;
}

double Patient::getFunds() const {
    return funds;
}

std::string Patient::getCNP() const {
    return cnp;
}

void Patient::addFunds(double amount) {
    funds += amount;
}

void Patient::deductFunds(double amount) {
    if (funds >= amount) {
        funds -= amount;
    }
}

void Patient::addDisease(const std::string& disease, double cost) {
    diseases[disease] = cost;
}

void Patient::removeDisease(const std::string& disease) {
    diseases.erase(disease);
}

void Patient::clearDiseases() {
    diseases.clear();
}

bool Patient::isHealthy() const {
    return diseases.empty();
}

bool Patient::isValidCNP(const std::string& cnp) {
    if (cnp.size() != 13 || !std::regex_match(cnp, std::regex("\\d{13}"))) return false;

    int s = cnp[0] - '0';
    if (s < 1 || s > 8) return false;

    std::string yy = cnp.substr(1, 2);
    std::string mm = cnp.substr(3, 2);
    std::string dd = cnp.substr(5, 2);

    int year = std::stoi(yy);
    int month = std::stoi(mm);
    int day = std::stoi(dd);

    if (month < 1 || month > 12 || day < 1 || day > 31) return false;

    // Control digit check (optional): You can add checksum logic here

    return true;
}

void Patient::printInfo() const {
    std::cout << "Patient: " << name << ", Age: " << age << ", Gender: " << gender
              << ", CNP: " << cnp << ", Funds: $" << funds << "\nDiseases:\n";
    for (const auto& [disease, cost] : diseases) {
        std::cout << " - " << disease << ": $" << cost << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "Patient: " << p.name << ", Age: " << p.age << ", Gender: " << p.gender
       << ", CNP: " << p.cnp << ", Funds: $" << p.funds << ", Diseases: ";
    if (p.diseases.empty()) {
        os << "None";
    } else {
        for (const auto& [disease, cost] : p.diseases) {
            os << "[" << disease << ": $" << cost << "] ";
        }
    }
    return os;
}