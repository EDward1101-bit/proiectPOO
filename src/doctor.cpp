#include "../includes/doctor.h"
#include "../includes/patient.h"
#include <algorithm>


Doctor::Doctor(const std::string& name, const std::string& specialty)
    : name(name), specialty(specialty) {}

bool Doctor::dischargePatient(const std::string& patientName) {
    auto it = std::remove_if(patients.begin(), patients.end(),
        [&patientName](const Patient* p) {
            return p && p->getName() == patientName;
        });

    if (it != patients.end()) {
        patients.erase(it, patients.end());
        return true;
    }
    return false;
}

const std::string& Doctor::getName() const {
    return name;
}

const std::string& Doctor::getSpecialty() const {
    return specialty;
}

const std::vector<Patient*>& Doctor::getPatients() const {
    return patients;
}

void Doctor::assignPatient(Patient* patient) {
    if (patient) {
        patients.push_back(patient);
    }
}

void Doctor::removePatient(const Patient* patient) {
    patients.erase(
        std::remove_if(patients.begin(), patients.end(),
            [patient](const Patient* p) {
                return p == patient;
            }),
        patients.end()
    );
}

bool Doctor::hasPatient(const std::string& patientName) const {
    for (const auto& p : patients) {
        if (p && p->getName() == patientName) {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Doctor& doctor) {
    os << "Doctor: " << doctor.name
       << ", Specialty: " << doctor.specialty
       << ", Patients: ";
    if (doctor.patients.empty()) {
        os << "None";
    } else {
        for (const auto& p : doctor.patients) {
            if (p) {
                os << "[" << p->getName() << "] ";
            }
        }
    }
    return os;
}
