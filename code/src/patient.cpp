#include "../includes/patient.h"

// Constructor
Patient::Patient(std::string name, int age, char gender, double funds)
    : name(std::move(name)), age(age), gender(gender), funds(funds) {}

// Copy constructor
Patient::Patient(const Patient& other)
    : name(other.name), age(other.age), gender(other.gender), funds(other.funds), diseases(other.diseases) {}

// Copy assignment
Patient& Patient::operator=(const Patient& other) {
    if (this != &other) {
        name = other.name;
        age = other.age;
        gender = other.gender;
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

void Patient::printInfo() const {
    std::cout << "Patient: " << name << ", Age: " << age << ", Gender: " << gender << ", Funds: $" << funds << "\nDiseases:\n";
    for (const auto& [disease, cost] : diseases) {
        std::cout << " - " << disease << ": $" << cost << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "Patient: " << p.name << ", Age: " << p.age << ", Gender: " << p.gender << ", Funds: $" << p.funds << ", Diseases: ";
    if (p.diseases.empty()) {
        os << "None";
    } else {
        for (const auto& [disease, cost] : p.diseases) {
            os << "[" << disease << ": $" << cost << "] ";
        }
    }
    return os;
}