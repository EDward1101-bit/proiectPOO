#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/appointment.h"
#include "../includes/patient.h"
#include "../includes/medical_data.h"
#include <algorithm>
#include <memory>
#include <iostream>
#include <unordered_map>

Hospital::Hospital(std::string name, const Location& location)
    : name(std::move(name)), location(location) {}

Hospital::~Hospital() = default;

void Hospital::addDoctor(std::unique_ptr<Doctor> doctor) {
    doctors.emplace_back(std::move(doctor));
}

void Hospital::addAppointment(std::unique_ptr<Appointment> appointment) {
    appointments.emplace_back(std::move(appointment));
}

void Hospital::addPatientToDoctor(const std::string& doctorName, Patient* patient) {
    const auto& patientDiseases = patient->getDiseases();
    if (patientDiseases.empty()) {
        std::cerr << "Error: Patient has no recorded conditions to assign.\n";
        return;
    }

    Doctor* targetDoc = nullptr;
    for (const auto& docPtr : doctors) {
        if (docPtr->getName() == doctorName) {
            targetDoc = docPtr.get();
            break;
        }
    }
    if (!targetDoc) {
        std::cerr << "Error: Doctor '" << doctorName << "' not found.\n";
        return;
    }

    const std::string docSpec = targetDoc->getSpecialty();
    bool match = false;
    for (const auto& [disease, cost] : patientDiseases) {
        auto it = diseaseToSpecialty.find(disease);
        if (it != diseaseToSpecialty.end() && it->second == docSpec) {
            match = true;
            break;
        }
    }

    if (match) {
        targetDoc->assignPatient(patient);
        std::cout << "Patient '" << patient->getName()
                  << "' successfully assigned to Dr. " << doctorName << ".\n";
    } else {
        std::unordered_set<std::string> neededSpecs;
        for (const auto& [disease, cost] : patientDiseases) {
            auto it = diseaseToSpecialty.find(disease);
            if (it != diseaseToSpecialty.end()) {
                neededSpecs.insert(it->second);
            }
        }
        std::cerr << "Error: Dr. " << doctorName
                  << "'s specialty (" << docSpec << ") does not match patient's needs (";
        bool first = true;
        for (auto& s : neededSpecs) {
            if (!first) std::cerr << ", ";
            std::cerr << s;
            first = false;
        }
        std::cerr << ").\n";
    }
}

bool Hospital::isDoctorAvailable(const std::string& doctorName, const std::string& date, const std::string& time) const {
    for (const auto& doctor : doctors) {
        if (doctor->getName() == doctorName) {
            for (const auto& appointment : doctor->getAppointments()) {
                if (appointment->getDate() == date && appointment->getTime() == time) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

void Hospital::scheduleAppointment(const std::string& doctorName, Patient* /*patient*/, const std::string& date, const std::string& time) {
    if (!Appointment::isValidDateTime(date, time, location.getTimezoneOffset())) {
        std::cerr << "Error: Invalid date or time format.\n";
        return;
    }

    for (const auto& doctor : doctors) {
        if (doctor->getName() == doctorName) {
            if (!isDoctorAvailable(doctorName, date, time)) {
                std::cerr << "Error: Doctor is not available at this time.\n";
                return;
            }
            auto appointment = std::make_unique<Appointment>(date, time, doctor.get(), location.getTimezoneOffset());
            doctor->addAppointment(appointment.get());
            addAppointment(std::move(appointment));
            return;
        }
    }

    std::cerr << "Error: Doctor '" << doctorName << "' not found for appointment.\n";
}

void Hospital::dischargePatient(Patient* patient, Doctor* doctor) {
    if (!patient->isHealthy()) {
        std::cerr << "Discharge failed: Patient is not healthy.\n";
        return;
    }

    double cost = patient->getTotalTreatmentCost();
    if (patient->getFunds() < cost) {
        std::cerr << "Discharge failed: Insufficient funds.\n";
        return;
    }

    patient->deductFunds(cost);
    totalProfit += cost;
    doctor->removePatient(patient);

    auto recheck = std::make_unique<Appointment>("2025-05-01", "09:00", doctor, location.getTimezoneOffset());
    doctor->addAppointment(recheck.get());
    addAppointment(std::move(recheck));
}

double Hospital::getProfit() const {
    return totalProfit;
}

void Hospital::printInfo() const {
    std::cout << "Hospital: " << name << "\nLocation: " << location << "\n";
}

void Hospital::printDoctors() const {
    std::cout << "Doctors in the hospital:\n";
    for (const auto& doctor : doctors) {
        std::cout << doctor->getName() << " - Specialty: " << doctor->getSpecialty() << "\n";
    }
}

void Hospital::printAppointments() const {
    std::vector<Appointment*> sortedAppointments;
    for (const auto& appt : appointments) {
        sortedAppointments.push_back(appt.get());
    }

    std::sort(sortedAppointments.begin(), sortedAppointments.end(), [](const Appointment* a, const Appointment* b) {
        return a->getDate() < b->getDate() ||
              (a->getDate() == b->getDate() && a->getTime() < b->getTime());
    });

    std::cout << "Appointments in the hospital (sorted):\n";
    for (const auto* appointment : sortedAppointments) {
        std::cout << *appointment << "\n";
    }
}

std::vector<std::pair<std::string, int>> Hospital::getMostCommonDiseases(int topN) const {
    std::unordered_map<std::string, int> diseaseCounts;

    for (const auto& doctor : doctors) {
        const auto& patients = doctor->getPatientList();
        for (const auto* patient : patients) {
            const auto& patientDiseases = patient->getDiseases();
            for (const auto& [disease, _] : patientDiseases) {
                ++diseaseCounts[disease];
            }
        }
    }

    std::vector<std::pair<std::string, int>> sortedDiseases(diseaseCounts.begin(), diseaseCounts.end());

    std::sort(sortedDiseases.begin(), sortedDiseases.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    if ((int)sortedDiseases.size() > topN) {
        sortedDiseases.resize(topN);
    }

    return sortedDiseases;
}

const std::vector<std::unique_ptr<Doctor>>& Hospital::getDoctors() const {
    return doctors;
}

const Location& Hospital::getLocation() const {
    return location;
}

const std::string& Hospital::getName() const {
    return name;
}

const std::vector<std::unique_ptr<Appointment>>& Hospital::getAppointments() const {
    return appointments;
}

std::ostream& operator<<(std::ostream& os, const Hospital& h) {
    os << "Hospital: " << h.name << ", Location: " << h.location << ", Total Profit: $" << h.totalProfit << "\n";
    return os;
}
