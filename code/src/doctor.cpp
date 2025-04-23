#include "../includes/doctor.h"
#include "../includes/medical_data.h"
#include <iostream>

Doctor::Doctor(std::string name, std::string specialty)
    : name(std::move(name)), specialty(std::move(specialty)) {}

std::string const& Doctor::getName() const {
    return name;
}

std::string const& Doctor::getSpecialty() const {
    return specialty;
}

void Doctor::addAppointment(Appointment* appointment) {
    appointments.push_back(appointment);
}

const std::vector<Appointment*>& Doctor::getAppointments() const {
    return appointments;
}

void Doctor::assignPatient(Patient* p) {
    patients.push_back(p);
}

void Doctor::removePatient(const Patient* p) {
    auto it = std::find_if(patients.begin(), patients.end(), [p](const Patient* patient) {
        return patient == p;
    });
    if (it != patients.end()) {
        patients.erase(it);
    }
}

void Doctor::printInfo() const {
    std::cout << "Doctor: " << name << ", Specialty: " << specialty << "\n";
}

void Doctor::printPatients() const {
    std::cout << "Patients assigned to Dr. " << name << ":\n";
    for (const auto* patient : patients) {
        std::cout << *patient << "\n";
    }
}

Doctor::~Doctor() {
    for (Appointment* appointment : appointments) {
        delete appointment;
    }
}

std::ostream& operator<<(std::ostream& os, const Doctor& d) {
    os << "Doctor: " << d.name << ", Specialty: " << d.specialty;
    return os;
}

bool Doctor::isValidSpecialty(const std::string& specialty) {
    return knownSpecialties.count(specialty) > 0;
}