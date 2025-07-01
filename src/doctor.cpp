#include "../includes/doctor.h"
#include "../includes/patient.h"
#include <algorithm>
#include <unordered_set>
#include <thread>

Doctor::Doctor(const std::string& name, const std::string& specialty)
    : name(name), specialty(specialty) {}

const std::string& Doctor::getName() const { return name; }
const std::string& Doctor::getSpecialty() const { return specialty; }
const std::vector<Patient*>& Doctor::getPatients() const { return patients; }

void Doctor::assignPatient(Patient* patient) {
    if (patient) {
        patients.push_back(patient);
    }
}

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

std::ostream& operator<<(std::ostream& os, const Doctor& doctor) {
    static thread_local std::unordered_set<const void*> visited;
    if (visited.count(&doctor)) {
        os << "[Info: Doctor already printed. Skipping repeated output.]\n";
        return os;
    }
    visited.insert(&doctor);

    os << "Doctor: " << doctor.name
       << "\nSpecialty: " << doctor.specialty
       << "\nPatients:";

    if (doctor.patients.empty()) {
        os << " None\n";
    } else {
        os << "\n";
        for (const auto* patient : doctor.patients) {
            if (patient) os << *patient << "\n";
        }
    }

    visited.erase(&doctor);
    return os;
}

