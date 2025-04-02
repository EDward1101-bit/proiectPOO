#include "../includes/doctor.h"
#include "../includes/patient.h"

// Constructor
Doctor::Doctor(std::string name, std::string specialty, const unsigned int tarif)
    : name(std::move(name)), specialty(std::move(specialty)), tarif(tarif) {}

void Doctor::printInfo() const {
    std::cout << "Doctor: " << name << ", Specialty: " << specialty << ", Tarif: " << tarif << "\n";
}

void Doctor::assignPatient(Patient* p) {
    std::string CNP = p->getCNP();

    // Check if the length of CNP is 13
    if (CNP.length() != 13) {
        std::cout << "CNP invalid" << std::endl;
        return;
    }

    // Check if every character in CNP is a digit
    for (unsigned int i = 0; i < CNP.length(); i++) {
        if (!std::isdigit(CNP[i])) {
            std::cout << "CNP contains non-digit characters" << std::endl;
            return;
        }
    }

    patients.push_back(p);  // Assign the patient to this doctor
    std::cout << "Patient assigned successfully" << std::endl;
}

void Doctor::removePatient(const Patient* p) {
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (*it == p) {
            patients.erase(it);  // Remove the patient from the doctor's list
            break;
        }
    }
}

void Doctor::printPatients() const {
    std::cout << "Patients of Dr. " << name << ":\n";
    for (const Patient* patient : patients) {
        std::cout << *patient << "\n";  // Print patient info
    }
}

// Operator<< Overload to print doctor info
std::ostream& operator<<(std::ostream& os, const Doctor& d) {
    os << "Doctor: " << d.name << ", Specialty: " << d.specialty << ", Tarif: " << d.tarif << std::endl;
    return os;
}
