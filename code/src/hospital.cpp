#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/appointment.h"
#include "../includes/patient.h"
#include "../includes/medical_data.h"
#include <algorithm>
#include <memory>

Hospital::Hospital(std::string name, Location location)
    : name(std::move(name)), location(std::move(location)) {}

Hospital::~Hospital() = default;

void Hospital::addDoctor(std::unique_ptr<Doctor> doctor) {
    doctors.emplace_back(std::move(doctor));
}

void Hospital::addAppointment(std::unique_ptr<Appointment> appointment) {
    appointments.emplace_back(std::move(appointment));
}

void Hospital::addPatientToDoctor(const std::string& doctorName, Patient* patient) {
    if (patient->getDiseases().empty()) return;

    const std::string& disease = patient->getDiseases().begin()->first;
    auto it = diseaseToSpecialty.find(disease);
    if (it == diseaseToSpecialty.end()) return;

    const std::string& requiredSpecialty = it->second;

    for (const auto& doctor : doctors) {
        if (doctor->getName() == doctorName && doctor->getSpecialty() == requiredSpecialty) {
            doctor->assignPatient(patient);
            return;
        }
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

void Hospital::scheduleAppointment(const std::string& doctorName, Patient* patient, const std::string& date, const std::string& time) {
    if (!isDoctorAvailable(doctorName, date, time)) {
        return;
    }

    for (const auto& doctor : doctors) {
        if (doctor->getName() == doctorName) {
            auto appointment = std::make_unique<Appointment>(date, time, doctor.get(), location.getTimezoneOffset());
            doctor->addAppointment(appointment.get());
            addAppointment(std::move(appointment));
            return;
        }
    }
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
    std::cout << "Appointments in the hospital:\n";
    for (const auto& appointment : appointments) {
        std::cout << *appointment << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Hospital& h) {
    os << "Hospital: " << h.name << ", Location: " << h.location << ", Total Profit: $" << h.totalProfit << "\n";
    return os;
}